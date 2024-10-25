#ifndef LIBRARIES_LOCONET_SRC_LN_IDLE_H_
#define LIBRARIES_LOCONET_SRC_LN_IDLE_H_
#pragma once

#include "lnpacket.h"
#include "Arduino.h"
namespace LocoNet {
	class LN_IDLE : public LocoNet::LNPacket {
	public:
		LN_IDLE();
		LN_IDLE( packet_data &pdata );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
