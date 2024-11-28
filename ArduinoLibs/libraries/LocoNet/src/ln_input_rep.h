#ifndef LIBRARIES_LOCONET_SRC_LN_INPUT_REP_H_
#define LIBRARIES_LOCONET_SRC_LN_INPUT_REP_H_
#pragma once

#include "lnpacket.h"
#include <Arduino.h>
namespace LocoNet {
	class LN_INPUT_REP : public LNPacket {
	public:
		LN_INPUT_REP();
		/*
		 LN_SW_REQ( byte dataArray[], uint len );
		 */
		LN_INPUT_REP( packet_data &pdata );
		LN_INPUT_REP( LNPacket &packet );
		arduino::String toString();

		lnaddr getAddr();
		void setAddr( lnaddr address );
		void setActive( bool active );
		bool getActive();
		bool isDS54();
	protected:
	private:
	};
}

#endif
