#include "ln_link_slots.h"
#include <arduino.h>

namespace LocoNet {
	LN_LINK_SLOTS::LN_LINK_SLOTS() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLinkSlots;
		this->setCheckSum ();
	}

	LN_LINK_SLOTS::LN_LINK_SLOTS( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LINK_SLOTS::LN_LINK_SLOTS( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LINK_SLOTS::toString() {
		return LNPacket::toString () + "LINK_SLOTS";
	}
}
