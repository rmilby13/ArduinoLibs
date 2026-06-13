#include "ln_lissy_rep.h"
#include <arduino.h>

namespace LocoNet {
	LN_LISSY_REP::LN_LISSY_REP() : LNPacket (8) {
		this->data[0] = DigiTraxOpcLissyRep;
		this->setCheckSum ();
	}

	LN_LISSY_REP::LN_LISSY_REP( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LISSY_REP::LN_LISSY_REP( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LISSY_REP::toString() {
		return LNPacket::toString () + "LISSY_REP";
	}
}
