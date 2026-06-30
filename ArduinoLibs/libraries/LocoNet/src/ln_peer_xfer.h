#ifndef LIBRARIES_LOCONET_SRC_LN_PEER_XFER_H_
#define LIBRARIES_LOCONET_SRC_LN_PEER_XFER_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_PEER_XFER : public LNPacket {
	public:
		LN_PEER_XFER();
		LN_PEER_XFER( packet_data &pdata );
		LN_PEER_XFER( LNPacket &packet );
		arduino::String toString();

		byte getSrc();
		uint16_t getDst();
		byte getCount1();
		byte getCount2();
		byte getDataByte(int idx); // idx 0-7
	};
}

#endif
