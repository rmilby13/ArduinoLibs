#ifndef LIBRARIES_LOCONET_SRC_LN_UNLINK_SLOTS_H_
#define LIBRARIES_LOCONET_SRC_LN_UNLINK_SLOTS_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_UNLINK_SLOTS : public LNPacket {
	public:
		LN_UNLINK_SLOTS();
		LN_UNLINK_SLOTS( packet_data &pdata );
		LN_UNLINK_SLOTS( LNPacket &packet );
		arduino::String toString();

		byte getSlotA();
		byte getSlotB();
		void setSlotA(byte a);
		void setSlotB(byte b);
	};
}

#endif
