#include "ln_peer_xfer.h"
#include <arduino.h>

namespace LocoNet {
	LN_PEER_XFER::LN_PEER_XFER() : LNPacket (16) {
		this->data[0] = DigiTraxOpcPeerXfer;
		this->setCheckSum ();
	}

	LN_PEER_XFER::LN_PEER_XFER( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_PEER_XFER::LN_PEER_XFER( LNPacket &packet ) : LNPacket (packet) {

	}

	arduino::String LN_PEER_XFER::toString() {
		return LNPacket::toString () + "PEER_XFER";
	}
}
