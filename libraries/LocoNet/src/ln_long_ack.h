/*
 * LNLongAck.h
 *
 *  Created on: Nov 6, 2024
 *      Author: rmilb
 */

#ifndef LIBRARIES_LOCONET_SRC_LNLONGACK_H_
#define LIBRARIES_LOCONET_SRC_LNLONGACK_H_

#include <ln_packet.h>
#include <Arduino.h>
namespace LocoNet {

	class LN_Long_Ack : public LNPacket {
	public:
		LN_Long_Ack();
		LN_Long_Ack( LN_OP_CODE opc, bool ack );
		LN_Long_Ack( packet_data &pdata );
		LN_Long_Ack( LNPacket &packet );
		virtual ~LN_Long_Ack();
		arduino::String toString();
	};

} /* namespace LocoNet */

#endif /* LIBRARIES_LOCONET_SRC_LNLONGACK_H_ */
