//感谢使用艾森lorawan开发套件.
//使用前需要将libraries目录下lora文件放入arduino\libraries目录下.
#include <SoftwareSerial.h>
#include <floatToString.h>
#include <Lora.h>
#define LORA_TX_PIN 8
#define LORA_RX_PIN 7//软串口默认为8和7
Lora lora(LORA_TX_PIN, LORA_RX_PIN, false);

#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 4

void setup() {
  Serial.begin(9600);//串口波特率
  Serial.print("Start Init");
  lora.begin(9600);//和lorawan模组通讯波特率
  delay(500);
  lora.join();
  delay(1000);
  Serial.print("Down Init");
}

void loop() {
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
  String payload = "{\"h\":" + humString + ",\"t\":" + tempString + "}";

  lora.msg("10," + payload);
  lora.cir(50);
  Serial.println(payload);

  delay(2000);

}



