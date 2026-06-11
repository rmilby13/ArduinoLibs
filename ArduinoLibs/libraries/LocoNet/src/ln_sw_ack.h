/*
 * LNSWACK.h
 *
 *  Created on: Nov 5, 2024
 *      Author: rmilb
 */

#ifndef LIBRARIES_LOCONET_SRC_LNSWACK_H_
#define LIBRARIES_LOCONET_SRC_LNSWACK_H_

#include <ln_packet.h>

namespace LocoNet {

	class LN_SW_ACK : public LNPacket {
	public:
		LN_SW_ACK();
		LN_SW_ACK( packet_data &pdata );
		LN_SW_ACK( LNPacket &packet );
		virtual ~LN_SW_ACK();
		lnaddr getAddress();
		arduino::String toString();
		void setAddress( lnaddr address );
		void setClosed( bool closed );
		bool getClosed();
		void setActive(bool active);
		bool getActive();
	};

} /* namespace LocoNet */

#endif /* LIBRARIES_LOCONET_SRC_LNSWACK_H_ */
