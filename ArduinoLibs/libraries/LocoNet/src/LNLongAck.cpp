/*
 * LNLongAck.cpp
 *
 *  Created on: Nov 6, 2024
 *      Author: rmilb
 */

#include "LNLongAck.h"

//#define DEBUGLNLongAck
//#define TRACELNLongAck

#ifdef TRACELNLongAck
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGLNLongAck
#else
#define TRACE(...)
#endif

#ifdef DEBUGLNLongAck
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {

	LN_Long_Ack::LN_Long_Ack() : LNPacket (LN_OPC_LONG_ACK) {
		// TODO Auto-generated constructor stub

	}

	LN_Long_Ack::LN_Long_Ack( packet_data &pdata ) : LNPacket (pdata) {

	}

	LN_Long_Ack::LN_Long_Ack( LNPacket &packet ) : LNPacket (packet) {

	}

	LN_Long_Ack::LN_Long_Ack( LN_OP_CODE opc, bool ack ) : LNPacket (4) {
		this->data[0] = DigiTraxOpcLongAck;
		switch (opc) {
			case LN_OPC_SW_ACK:
				this->data[1] = DigiTraxOpcSwAck & 0x7F;
				this->data[2] = ack ? 0x7F : 0;
				break;
			case LN_OPC_SW_STATE:
				this->data[1] = DigiTraxOpcSwState & 0x7F;
				this->data[2] = ack ? 0x7F : 0;
				break;
			default:
				this->data[1] = 0;
				this->data[2] = 0;
		}
		this->setCheckSum ();
	}

	LN_Long_Ack::~LN_Long_Ack() {
		// TODO Auto-generated destructor stub
	}

	arduino::String LN_Long_Ack::toString() {
		arduino::String retstr = "Long Acknowledgment: ";
		switch (this->data[1] | 0x80){
			case DigiTraxOpcSwAck:
				retstr += "Switch Request Acknowledgment result ";
				retstr += this->data[2] == 0 ? "failed" : "success";
				break;
			case DigiTraxOpcSwState:
				retstr += "Switch State Acknowledgment result ";
				retstr += this->data[2] == 0 ? "failed" : "success";
				break;
			default:
				retstr += "unknown";
		}
		return LNPacket::toString () + retstr;
	}

} /* namespace LocoNet */
