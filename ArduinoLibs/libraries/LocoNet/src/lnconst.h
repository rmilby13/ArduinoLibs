/*
 * lnconst.h
 *
 *  Created on: Apr 17, 2022
 *      Author: Rob
 */

#ifndef LIBRARIES_LOCONET_SRC_LNCONST_H_
#define LIBRARIES_LOCONET_SRC_LNCONST_H_

#define lnaddr unsigned short

#define DigiTraxInitPriority 25
#define DigiTraxBituS 60
#define DigiTractCDBackOffuS DigiTraxBituS*20
#define DigiTraxOpcNoOp 0x80
#define DigiTraxOpcBusy 0x81
#define DigiTraxOpcGpoff 0x82
#define DigiTraxOpcGpon 0x83
#define DigiTraxOpcIdle 0x85
#define DigiTraxOpcLocoSpd 0xA0
#define DigiTraxOpcLocoDirF 0xA1
#define DigiTraxOpcLocoSnd 0xA2
#define DigiTraxOpcSwReq 0xB0
#define DigiTraxOpcSwRep 0xB1
#define DigiTraxOpcInputRep 0xB2
#define DigiTraxOpcSlotStat1 0xB5
#define DigiTraxOpcLongAck 0xB4
#define DigiTraxOpcConsistFunc 0xB6
#define DigiTraxOpcMoveSlots 0xBA
#define DigiTraxOpcRqSlData 0xBB
#define DigiTraxOpcLinkSlots 0xB9
#define DigiTraxOpcUnlinkSlots 0xB8
#define DigiTraxOpcSwState 0xBC
#define DigiTraxOpcSwAck 0xBD
#define DigiTraxOpcMultiSense 0xD0
#define DigiTraxOpcPeerXfer 0xE5
#define DigiTraxOpcLissyRep 0xE4
#define DigiTraxOpcProg 0xE6
#define DigiTraxOpcImmPacket 0xED
#define DigiTraxOpcSlRdData 0xE7
#define DigiTraxOpcWrSlData 0xEF
#define LOCONET_MAX_PACKET_SIZE 127

namespace LocoNet {
	enum LN_OP_CODE {
		LN_OPC_UNKNOWN, LN_OPC_NOOP, // 0x80
		LN_OPC_BUSY, // 0x81
		LN_OPC_GPOFF, // 0x82
		LN_OPC_GPON, // 0x83
		LN_OPC_IDLE, // 0x85
		LN_OPC_LOCO_SPD, // 0xA0
		LN_OPC_LOCO_DIRF, // 0xA1
		LN_OPC_LOCO_SND, // 0xA2
		LN_OPC_SW_REQ, // 0xB0
		LN_OPC_SW_REP, // 0xB1
		LN_OPC_INPUT_REP, // 0xB2
		LN_OPC_LONG_ACK, // 0xB4
		LN_OPC_SLOT_STAT1, // 0xB5
		LN_OPC_CONSIST_FUNC, // 0xB6
		LN_OPC_LINK_SLOTS, // 0xB9
		LN_OPC_UNLINK_SLOTS, // 0xB8
		LN_OPC_MOVE_SLOTS, // 0xBA
		LN_OPC_RQ_SL_DATA, // 0xBB
		LN_OPC_SW_STATE, // 0xBC
		LN_OPC_SW_ACK, // 0xBD
		LN_OPC_MULTI_SENSE, // 0xD0
		LN_OPC_LISSY_REP, // 0xE4
		LN_OPC_PEER_XFER, // 0xE5
		LN_OPC_PROG, // 0xE6
		LN_OPC_SL_RD_DATA, // 0xE7
		LN_OPC_IMM_PACKET, // 0xED
		LN_OPC_WR_SL_DATA // 0XEF
	};

	enum SignalHeadAspect {
		SignalHeadRed,
		SignalHeadYellow,
		SignalHeadGreen,
		SignalHeadLunar,
		SignalHeadFlashingRed,
		SignalHeadFlashingYellow,
		SignalHeadFlashingGreen,
		SignalHeadFlashingLunar,
		SignalHeadDark
	};

	enum LN_SENSOR_STATUS {
		LN_SEN_UNDEF, LN_SEN_ACTIVE, LN_SEN_INACTIVE
	};

	enum LN_SWITCH_STATUS {
		LN_SW_UNDEF, LN_SW_CLOSED_ACTIVE, LN_SW_CLOSED_INACTIVE, LN_SW_THROWN_ACTIVE, LN_SW_THROWN_INACTIVE
	};
}
;

#endif /* LIBRARIES_LOCONET_SRC_LNCONST_H_ */
