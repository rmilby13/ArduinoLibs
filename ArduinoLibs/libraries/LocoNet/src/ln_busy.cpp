#include "ln_busy.h"

#define DEBUGLNBUSY
#define TRACELNBUSY

#ifdef TRACELNBUSY
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNBUSY
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNBUSY
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif
namespace LocoNet {

	LN_BUSY::LN_BUSY() : LNPacket (2) {
		this->data[0] = DigiTraxOpcBusy;
		this->setCheckSum ();
	}

	LN_BUSY::LN_BUSY( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_BUSY::LN_BUSY(LNPacket& packet) : LNPacket(packet) {

	}

	arduino::String LN_BUSY::toString() {
		return LNPacket::toString () + "Busy";
	}
}
