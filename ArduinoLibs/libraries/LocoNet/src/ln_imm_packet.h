#ifndef LIBRARIES_LOCONET_SRC_LN_IMM_Packet_H_
#define LIBRARIES_LOCONET_SRC_LN_IMM_Packet_H_
#pragma once

#include "lnpacket.h"
#include <Arduino.h>
namespace LocoNet {
	class LN_IMM_Packet : public LNPacket {
	public:
		LN_IMM_Packet();
		/*
		 LN_SW_REQ( byte dataArray[], uint len );
		 */
		LN_IMM_Packet( LNPacket &packet );
		LN_IMM_Packet( packet_data &pdata );
		arduino::String toString();
		lnaddr getAddr();
		void setAddr( lnaddr address );
		SignalHeadAspect getAspect();

		/*
		 lnaddr getAddr();
		 void setAddr( lnaddr address );
		 void setClosed( bool closed );
		 bool getClosed();
		 void setActive(bool active);
		 bool getActive();
		 */
	protected:
	private:
	};
}

#endif
