#include "ln_nop.h"
#include <arduino.h>
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

namespace LocoNet {
	LN_NOP::LN_NOP() : LNPacket (2) {
		this->data[0] = DigiTraxOpcNoOp;
		this->setCheckSum ();
	}

	LN_NOP::LN_NOP( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_NOP::LN_NOP( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_NOP::toString() {
		return LNPacket::toString () + "NOP";
	}
}
