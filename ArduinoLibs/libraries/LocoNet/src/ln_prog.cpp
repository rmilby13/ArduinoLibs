#include "ln_prog.h"
#include <arduino.h>

namespace LocoNet {
	LN_PROG::LN_PROG() : LNPacket (16) {
		this->data[0] = DigiTraxOpcProg;
		this->setCheckSum ();
	}

	LN_PROG::LN_PROG( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_PROG::LN_PROG( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_PROG::toString() {
		return LNPacket::toString () + "PROG";
	}
}
