#ifndef LORA_H
#define LORA_H

#include "SoftwareSerial.h"
#include "Arduino.h"


class Lora:public SoftwareSerial
{
  public:
    Lora(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
	void cir(uint16_t circle=1);
	void band(String band );
	void addr(String addr);
	void deveui(String deveui);
	void appeui(String appeui);
	void nwkskey(String nwkskey);
	void appskey(String appskey);
	void appkey(String appkey);
	void mode(String mode);
	void classes(String classes);
	void dr(String dr);
	void power(String power);
	void rx2(String rx2);
	void ch(String ch);
	void msg(String msg);
	void cmsg(String cmsg);
	void msghex(String msghex);
	void cmsghex(String cmsghex);
	void msg(unsigned char msg);
	void cmsg(unsigned char cmsg);
	void msghex(unsigned char msghex);
	void cmsghex(unsigned char cmsghex);
	void flush ();
	void join ();

  private:
   
};
#endif