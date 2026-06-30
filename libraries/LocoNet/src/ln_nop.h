#ifndef LIBRARIES_LOCONET_SRC_LN_NOP_H_
#define LIBRARIES_LOCONET_SRC_LN_NOP_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_NOP : public LNPacket {
	public:
		LN_NOP();
		LN_NOP( packet_data &pdata );
		LN_NOP( LNPacket &packet );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
