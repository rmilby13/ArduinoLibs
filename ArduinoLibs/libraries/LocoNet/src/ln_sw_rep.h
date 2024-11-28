#pragma once
#ifndef LIBRARIES_LOCONET_SRC_LNSWREP_H_
#define LIBRARIES_LOCONET_SRC_LNSWREP_H_

#include "lnpacket.h"
#include <Arduino.h>
namespace LocoNet {
	class LN_SW_REP : public LNPacket {
	public:
		LN_SW_REP();
		LN_SW_REP( lnaddr address, bool closed, bool active );
		LN_SW_REP( packet_data &pdata );
		LN_SW_REP( LNPacket &packet );
		arduino::String toString();

		lnaddr getAddr();
		void setAddr( lnaddr address );
		void setClosed( bool closed );
		bool getClosed();
		void setActive( bool active );
		bool getActive();
	protected:
	private:
	};
}
#endif /* LIBRARIES_LOCONET_SRC_LNSWREP_H_ */
