#include "ln_input_rep.h"
#include "lnconst.h"
#include <Arduino.h>

//#define DEBUGLNINPUTREP
//#define TRACELNINPUTREP

#ifdef TRACELNINPUTREP
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNINPUTREP
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNINPUTREP
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_INPUT_REP::LN_INPUT_REP() : LNPacket (4) {
	this->data[0] = DigiTraxOpcSwReq;
	this->setAddr (1);
	this->setCheckSum ();
}

LocoNet::LN_INPUT_REP::LN_INPUT_REP( packet_data& pdata) : LNPacket(pdata){

}

LocoNet::LN_INPUT_REP::LN_INPUT_REP( LNPacket& packet) : LNPacket (packet) {

}

arduino::String LocoNet::LN_INPUT_REP::toString() {
	return LNPacket::toString() + "Input Report from Address " + arduino::String(this->getAddr()) + " currently " + this->getActive() ;
}

lnaddr LocoNet::LN_INPUT_REP::getAddr() {
	return ((this->data[2] & 0x0F) << 7) + (this->data[1] & 0x7F) + 1;
}

void LocoNet::LN_INPUT_REP::setAddr( lnaddr address ) {
	lnaddr addr = address;
	this->data[1] = addr & 0x7F;
	addr = addr >> 7;
	addr = addr & 0x0F;
	this->data[2] = addr | (this->data[2] & 0xF0);
}
