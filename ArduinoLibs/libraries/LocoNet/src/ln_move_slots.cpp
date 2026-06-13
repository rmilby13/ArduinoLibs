#include "ln_move_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_MOVE_SLOTS::LN_MOVE_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcMoveSlots;
		this->setCheckSum ();
	}

	LN_MOVE_SLOTS::LN_MOVE_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_MOVE_SLOTS::LN_MOVE_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_MOVE_SLOTS::toString() {
		return LNPacket::toString () + "MOVE_SLOTS";
	}
}
