/*
 * lnconst.h
 *
 *  Created on: Apr 17, 2022
 *      Author: Rob
 */

#ifndef LIBRARIES_LOCONET_SRC_LNCONST_H_
#define LIBRARIES_LOCONET_SRC_LNCONST_H_

#define DigiTraxInitPriority 25
#define DigiTraxBituS 60
#define DigiTractCDBackOffuS DigiTraxBituS*20
#define DigiTraxOpcNoOp 0x80
#define DigiTraxOpcBusy 0x81
#define DigiTraxOpcGpoff 0x82
#define DigiTraxOpcGpon 0x83
#define DigiTraxOpcSwReq 0xB0
#define DigiTraxOpcInputRep 0xB2
#define DigiTraxOpcMultiSense 0xD0
#define DigiTraxOpcImmPacket 0xED
#define LOCONET_MAX_PACKET_SIZE 127

namespace LocoNet {
  enum LN_OP_CODE {
    LN_OPC_NOOP, // 0x80
    LN_OPC_BUSY, // 0x81
    LN_OPC_GPOFF, // 0x82
    LN_OPC_GPON, // 0x83
    LN_OPC_SW_REQ, // 0xB0
    LN_OPC_INPUT_REP, // 0xB2
    LN_OPC_MULTI_SENSE, // 0xD0
    LN_OPC_IMM_PACKET, // 0xED
    LN_OPC_UNKNOWN
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
