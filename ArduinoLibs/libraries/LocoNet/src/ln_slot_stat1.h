#ifndef LIBRARIES_LOCONET_SRC_LN_SLOT_STAT1_H_
#define LIBRARIES_LOCONET_SRC_LN_SLOT_STAT1_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_SLOT_STAT1 : public LNPacket {
	public:
		LN_SLOT_STAT1();
		LN_SLOT_STAT1( packet_data &pdata );
		LN_SLOT_STAT1( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
