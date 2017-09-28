//感谢使用艾森lorawan开发套件.
//使用前需要将libraries目录下lora文件放入arduino\libraries目录下.
#include <SoftwareSerial.h>
#include <floatToString.h>
#include<Adafruit_GPS.h>
#include <Lora.h>
#define LORA_TX_PIN 8
#define LORA_RX_PIN 7//软串口默认为8和7
Lora lora(LORA_TX_PIN, LORA_RX_PIN, false);

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
  delay(1000);
  GPS.begin(9600);
  GPS.sendCommand("$PGCMD,33,0*6D");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
  Serial.print("Down Init");
}

void loop() {
  // put your main code here, to run repeatedly:
    readGPS();  
}

void readGPS() {
  clearGPS();
  while(!GPS.newNMEAreceived()) {

    if(c != '\n')
      NMEA1 = NMEA1 + c;
    c = GPS.read();
  }

  NMEA1 = GPS.lastNMEA();


  int beginIndex = NMEA1.indexOf("GNGLL");
  String str = NMEA1.substring(beginIndex);

  Serial.println("str:"+str);

   Serial.println(NMEA1);
   if(str != "") {
    Serial.println("upload to lora server"+str);
    lora.msg("10,"+str);
    delay(500);
  }
  
  
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



