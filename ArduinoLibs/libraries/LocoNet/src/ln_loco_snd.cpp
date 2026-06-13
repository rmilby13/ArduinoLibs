#include "ln_loco_snd.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_SND::LN_LOCO_SND() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoSnd;
		this->setCheckSum ();
	}

	LN_LOCO_SND::LN_LOCO_SND( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_SND::LN_LOCO_SND( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_SND::toString() {
		return LNPacket::toString () + "LOCO_SND";
	}
}
