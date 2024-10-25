#include "ln_gpoff.h"

//#define DEBUGLNGPON
//#define TRACELNGPON

#ifdef TRACELNGPOFF
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNGPOFF
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNGPOFF
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_GPOFF::LN_GPOFF() : LNPacket(2) {
	this->data[0] = DigiTraxOpcBusy;
	this->setCheckSum();
}

LocoNet::LN_GPOFF::LN_GPOFF(packet_data &pdata) : LNPacket(pdata){

}

arduino::String LocoNet::LN_GPOFF::toString() {
	return LNPacket::toString() + "GPOFF";
}
