#include "ln_sw_req.h"
#include "lnconst.h"

//#define DEBUGLNSWREQ
//#define TRACELNSWREQ

#ifdef TRACELNSWREQ
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNSWREQ
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNSWREQ
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_SW_REQ::LN_SW_REQ() : LNPacket(4) {
	this->data[0] = DigiTraxOpcSwReq;
	this->setAddr(1);
	this->setCheckSum();
}

LocoNet::LN_SW_REQ::LN_SW_REQ(packet_data &pdata) : LNPacket(pdata){

}

lnaddr LocoNet::LN_SW_REQ::getAddr(){
	return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F);
}

void LocoNet::LN_SW_REQ::setAddr(lnaddr address){
	lnaddr addr = address;
	this->data[1] = addr & 0x7F;
	addr = addr >> 7;
	addr = addr & 0x0F;
	this->data[2] = addr | (this->data[2] & 0xF0);
}
