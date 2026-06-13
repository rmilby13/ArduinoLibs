#ifndef LIBRARIES_LOCONET_SRC_LN_PROG_H_
#define LIBRARIES_LOCONET_SRC_LN_PROG_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_PROG : public LNPacket {
	public:
		LN_PROG();
		LN_PROG( packet_data &pdata );
		LN_PROG( LNPacket &packet );
		arduino::String toString();
	};
}

#endif
