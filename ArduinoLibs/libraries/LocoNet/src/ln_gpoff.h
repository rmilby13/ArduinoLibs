#ifndef LIBRARIES_LOCONET_SRC_LN_GPOFF_H_
#define LIBRARIES_LOCONET_SRC_LN_GPOFF_H_
#pragma once

#include "lnpacket.h"
#include "Arduino.h"
namespace LocoNet {
	class LN_GPOFF : public LocoNet::LNPacket {
	public:
		LN_GPOFF();
		LN_GPOFF( packet_data &pdata );
		arduino::String toString();
	protected:
	private:
	};
}

#endif
