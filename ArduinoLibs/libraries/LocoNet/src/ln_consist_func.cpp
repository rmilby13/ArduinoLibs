#include "ln_consist_func.h"
#include <arduino.h>

namespace LocoNet {
	LN_CONSIST_FUNC::LN_CONSIST_FUNC() : LNPacket (4) {
		this->data[0] = DigiTraxOpcConsistFunc;
		this->setCheckSum ();
	}

	LN_CONSIST_FUNC::LN_CONSIST_FUNC( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_CONSIST_FUNC::LN_CONSIST_FUNC( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_CONSIST_FUNC::toString() {
		return LNPacket::toString () + "CONSIST_FUNC";
	}
}
