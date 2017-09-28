

#include "Arduino.h"
#include "Lora.h"

Lora::Lora(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */)
:SoftwareSerial(receivePin, transmitPin,inverse_logic /* = false */)
{
}

void Lora::cir(uint16_t circle)
{
	do{
		delay(100);
		while (available()) {
			::Serial.write(read());
		  }
		  while (::Serial.available()) {
			write(::Serial.read());
		 }
	}while(circle-->0);
}

void Lora:: band(String band )
{
	println("at+band="+band);
	cir();
}
void Lora ::addr(String addr)
{
	
	println ("at+id=devaddr,"+addr);
	cir();
}

void Lora ::deveui(String deveui)
{
	
	println ("at+id=deveui,"+deveui);
	cir();
}

void Lora ::appeui(String appeui)
{
	
	println ("at+id=appeui,"+appeui);
	
	cir();
}

void Lora ::nwkskey(String nwkskey)
{
	
	println ("at+key=nwkskey,"+nwkskey);
	
	cir();
}
void Lora ::appskey(String appskey)
{
	
	println ("at+key=appskey,"+appskey);
	
	cir();
}
void Lora ::appkey(String appkey)
{
	
	println ("at+key=appkey,"+appkey);
	
	cir();
}
void Lora ::mode(String mode)
{
	
	println ("at+mode="+mode);
	
	cir();
}
void Lora :: classes (String classes)
{
	
	println ("at+class="+classes);
	
	cir();
}
void Lora :: dr (String dr)
{
	
	println ("at+dr="+dr);
	
	cir();
}
void Lora :: power (String power)
{
	
	println ("at+power="+power);
	
	cir();
}
void Lora :: rx2 (String rx2)
{
	
	println ("at+rx2="+rx2);
	
	cir();
}
void Lora :: ch (String ch)
{
	
	println ("at+ch="+ch);
	
	cir();
}

void Lora :: msg (String msg)
{
	
	println ("at+msg="+msg);
	
	cir();
}
void Lora :: cmsg (String cmsg)
{
	
	println ("at+cmsg="+cmsg);
	
	cir();
}
void Lora :: msghex (String msghex)
{
	
	println ("at+msghex="+msghex);
	
	cir();
}
void Lora :: cmsghex (String cmsghex)
{
	
	println ("at+cmsghex="+cmsghex);
	
	cir();
}
void Lora :: join ()
{
	
	println ("at+join=");
	
	cir();
}
void Lora :: flush ()
{
	
	println ("at+flush");
	
	cir();
}
/* void Lora :: msg (unsigned char msg)
{
	
	print ("at+msg=");
	println(msg);
	cir();
}
void Lora :: cmsg (unsigned char cmsg)
{
	
	print ("at+cmsg=");
	println(cmsg);
	cir();
}
void Lora :: msghex (unsigned char msghex)
{
	
	print ("at+msghex=");
	println(msghex);
	cir();
}
void Lora :: cmsghex (unsigned char cmsghex)
{
	
	print ("at+cmsghex=");
	println(cmsghex);
	cir();
} */