#include "ln_idle.h"

//#define DEBUGLNIDLE
//#define TRACELNIDLE

#ifdef TRACELNIDLE
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNIDLE 1
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNIDLE
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_IDLE::LN_IDLE() : LNPacket(2) {
	this->data[0] = DigiTraxOpcIdle;
	this->setCheckSum();
}

LocoNet::LN_IDLE::LN_IDLE(packet_data &pdata) : LNPacket(pdata) {

}

arduino::String LocoNet::LN_IDLE::toString() {
	return LNPacket::toString() + "IDLE";
}
