#include "ln_unlink_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcUnlinkSlots;
		this->setCheckSum ();
	}

	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_UNLINK_SLOTS::LN_UNLINK_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_UNLINK_SLOTS::toString() {
		return LNPacket::toString () + "UNLINK_SLOTS";
	}
}
