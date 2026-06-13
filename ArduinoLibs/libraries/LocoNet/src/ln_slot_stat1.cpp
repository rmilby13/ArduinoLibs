#include "ln_slot_stat1.h"
#include <arduino.h>

namespace LocoNet {
	LN_SLOT_STAT1::LN_SLOT_STAT1() : LNPacket (4) {
		this->data[0] = DigiTraxOpcSlotStat1;
		this->setCheckSum ();
	}

	LN_SLOT_STAT1::LN_SLOT_STAT1( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_SLOT_STAT1::LN_SLOT_STAT1( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_SLOT_STAT1::toString() {
		return LNPacket::toString () + "SLOT_STAT1";
	}
}
