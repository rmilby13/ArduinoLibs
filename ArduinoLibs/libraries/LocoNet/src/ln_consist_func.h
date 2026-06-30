#ifndef LIBRARIES_LOCONET_SRC_LN_CONSIST_FUNC_H_
#define LIBRARIES_LOCONET_SRC_LN_CONSIST_FUNC_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_CONSIST_FUNC : public LNPacket {
	public:
		LN_CONSIST_FUNC();
		LN_CONSIST_FUNC( packet_data &pdata );
		LN_CONSIST_FUNC( LNPacket &packet );
		arduino::String toString();

		byte getSlot();
		byte getDirF();
		void setSlot(byte s);
		void setDirF(byte df);
	};
}

#endif
