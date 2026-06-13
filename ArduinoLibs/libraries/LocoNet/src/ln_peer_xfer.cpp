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

	byte LN_PEER_XFER::getSrc(){
		return this->data.size() > 1 ? this->data[1] : 0;
	}

	uint16_t LN_PEER_XFER::getDst(){
		if(this->data.size() > 3) return ((uint16_t)this->data[3] << 7) | (uint16_t)(this->data[2] & 0x7F);
		return 0;
	}

	byte LN_PEER_XFER::getCount1(){
		return this->data.size() > 4 ? this->data[4] : 0;
	}

	byte LN_PEER_XFER::getCount2(){
		return this->data.size() > 10 ? this->data[10] : 0;
	}

	byte LN_PEER_XFER::getDataByte(int idx){
		int base = 5; // D1..D4 start at 5, D5..D8 at 11
		if(idx < 0 || idx > 7) return 0;
		int pos = (idx < 4) ? (base + idx) : (base + 6 + (idx-4));
		return this->data.size() > pos ? this->data[pos] : 0;
	}
}
