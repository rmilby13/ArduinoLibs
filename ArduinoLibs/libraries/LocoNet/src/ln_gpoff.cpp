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

namespace LocoNet {

	LN_GPOFF::LN_GPOFF() : LNPacket (2) {
		this->data[0] = DigiTraxOpcBusy;
		this->setCheckSum ();
	}

	LN_GPOFF::LN_GPOFF( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_GPOFF::LN_GPOFF( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_GPOFF::toString() {
		return LNPacket::toString () + "GPOFF";
	}
}
