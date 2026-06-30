#ifndef LIBRARIES_LOCONET_SRC_LN_MOVE_SLOTS_H_
#define LIBRARIES_LOCONET_SRC_LN_MOVE_SLOTS_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_MOVE_SLOTS : public LNPacket {
	public:
		LN_MOVE_SLOTS();
		LN_MOVE_SLOTS( packet_data &pdata );
		LN_MOVE_SLOTS( LNPacket &packet );
		arduino::String toString();

		byte getSrc();
		byte getDst();
		void setSrc(byte s);
		void setDst(byte d);
	};
}

#endif
