#include "ln_gpon.h"

//#define DEBUGLNGPON
//#define TRACELNGPON

#ifdef TRACELNGPON
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNGPON
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNGPON
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif
namespace LocoNet {

	LN_GPON::LN_GPON() : LNPacket (2) {
		this->data[0] = DigiTraxOpcBusy;
		this->setCheckSum ();
	}

	LN_GPON::LN_GPON( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_GPON::LN_GPON( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_GPON::toString() {
		return LNPacket::toString () + "GPON";
	}
}
