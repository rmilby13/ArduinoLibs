#include "ln_loco_dirf.h"
#include <arduino.h>

namespace LocoNet {
	LN_LOCO_DIRF::LN_LOCO_DIRF() : LNPacket (4) {
		this->data[0] = DigiTraxOpcLocoDirF;
		this->setCheckSum ();
	}

	LN_LOCO_DIRF::LN_LOCO_DIRF( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_LOCO_DIRF::LN_LOCO_DIRF( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_LOCO_DIRF::toString() {
		return LNPacket::toString () + "LOCO_DIRF";
	}
}
