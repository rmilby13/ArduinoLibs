#include "ln_nop.h"

//#define DEBUGLNNOP
//#define TRACELNNOP

#ifdef TRACELNNOP
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNNOP 1
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNNOP
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

LocoNet::LN_NOP::LN_NOP() : LNPacket(2) {
	this->setByte(0, LN_OPC_UNKNOWN);
	this->setCheckSum();
}

LocoNet::LN_NOP::LN_NOP(packet_data &pdata) : LNPacket(pdata){

}
