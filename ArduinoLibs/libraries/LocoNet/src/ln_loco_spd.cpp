#include "ln_loco_spd.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_SPD::LN_LOCO_SPD() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoSpd;
		this->setCheckSum ();
	}

	LN_LOCO_SPD::LN_LOCO_SPD( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_SPD::LN_LOCO_SPD( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_SPD::toString() {
		return LNPacket::toString () + "LOCO_SPD";
	}
}
