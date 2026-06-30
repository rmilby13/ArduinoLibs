#ifndef LIBRARIES_LOCONET_SRC_LN_LOCO_SND_H_
#define LIBRARIES_LOCONET_SRC_LN_LOCO_SND_H_

#include <ln_packet.h>
#include "Arduino.h"
namespace LocoNet {
	class LN_LOCO_SND : public LNPacket {
	public:
		LN_LOCO_SND();
		LN_LOCO_SND( packet_data &pdata );
		LN_LOCO_SND( LNPacket &packet );
		arduino::String toString();

		byte getSlot();
		byte getSound();
		void setSlot(byte s);
		void setSound(byte snd);
	};
}

#endif
