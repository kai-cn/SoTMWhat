//感谢使用艾森lorawan开发套件.
//使用前需要将libraries目录下lora文件放入arduino\libraries目录下.
#include <SoftwareSerial.h>
#include <floatToString.h>
#include<Adafruit_GPS.h>
#include <Lora.h>
#define LORA_TX_PIN 8
#define LORA_RX_PIN 7//软串口默认为8和7
Lora lora(LORA_TX_PIN, LORA_RX_PIN, false);
//#define LightDectPin  A2 //A2口模拟量输入

#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 4


SoftwareSerial mySerial(3,2);

Adafruit_GPS GPS(&mySerial);

String NMEA1;
String NMEA2;

char c;


void setup() {
  Serial.begin(115200);//串口波特率
  Serial.print("Start Init");
  lora.begin(9600);//和lorawan模组通讯波特率
  delay(500);
  lora.join();
  delay(500);
  GPS.begin(9600);
  GPS.sendCommand("$PGCMD,33,0*6D");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
//  delay(1000);
  Serial.print("Down Init");
}

void loop() {
  // put your main code here, to run repeatedly:
    String ht = readTmp();
    String gps = readGPS();  
    String payLoad = ht + gps;
    Serial.println("payLoad:"+payLoad);
    lora.msg("10," + payLoad);
    lora.cir(50);
}

String readTmp() {
  Serial.println("\n");
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK:
      Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }
  char buffer[10];
  String humString =  floatToString(buffer, (float)DHT11.humidity, 2);
  String tempString =  floatToString(buffer, (float)DHT11.temperature, 2);
  String payload = "{\"h\":" + humString + ",\"t\":" + tempString + ",";

//  lora.msg("10," + payload);
//  lora.cir(50);
//  Serial.println(payload);

  delay(1000);

  return payload;
}

String readGPS() {
  clearGPS();
  while(!GPS.newNMEAreceived()) {

    if(c != '\n')
      NMEA1 = NMEA1 + c;
    c = GPS.read();
  }

  NMEA1 = GPS.lastNMEA();


  int beginIndex = NMEA1.indexOf("GNGLL");
  String str = NMEA1.substring(beginIndex);
  String gps = "";
  String lat = "0";
  String lng = "0";

   if(str != "" && str.indexOf(",N,") > 0) {
    Serial.println("upload to lora server"+str);
//    lora.msg("10,"+str);
    int beginIndex = str.indexOf("GNGLL");
    int endIndex = str.indexOf(",N,");
    beginIndex = beginIndex + 6;
    lat = str.substring(beginIndex,endIndex);
    beginIndex = endIndex + 3;
    endIndex = str.indexOf(",E,");
    lng = str.substring(beginIndex,endIndex);

//
//    Serial.println("lat:"+lat);
//    Serial.println("lng:"+lng); 
    delay(500);

    
  }

  String payLoad = "\"address\":{\"lat\":"+ lat+",\"lng\":"+lng+"}}";

  return payLoad;

  
}

void clearGPS() {
  while(!GPS.newNMEAreceived()) {
    c = GPS.read();
  }

  GPS.parse(GPS.lastNMEA());

  while(!GPS.newNMEAreceived()) {
    c = GPS.read();
  }

  GPS.parse(GPS.lastNMEA());
}



