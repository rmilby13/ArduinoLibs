#ifndef LIBRARIES_LOCONET_SRC_LN_BUSY_H_
#define LIBRARIES_LOCONET_SRC_LN_BUSY_H_
#pragma once

#include "lnpacket.h"
#include "Arduino.h"
namespace LocoNet {
	class LN_BUSY : public LocoNet::LNPacket {
	public:
		LN_BUSY();
		LN_BUSY( packet_data &pdata );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
