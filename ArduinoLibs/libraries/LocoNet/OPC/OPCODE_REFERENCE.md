LocoNet Opcode Reference (extracted from loconet ln-pe-en spec)

2-byte opcodes (format: <OPC>,<CKSUM>):
- OPC_IDLE  0x85 — FORCE IDLE state, broadcast emergency STOP
- OPC_GPON  0x83 — GLOBAL power ON request
- OPC_GPOFF 0x82 — GLOBAL power OFF request
- OPC_BUSY  0x81 — MASTER busy code (NUL)
- OPC_NOOP  0x80 — No operation

4-byte opcodes (format: <OPC>,<ARG1>,<ARG2>,<CKSUM>):
- OPC_SW_REQ   0xB0 — Request switch function (SW1, SW2)
- OPC_SW_REP   0xB1 — Turnout sensor/state report (SN1, SN2)
- OPC_INPUT_REP 0xB2 — General sensor input report (IN1, IN2)
- OPC_LONG_ACK 0xB4 — Long acknowledge (LOPC, ACK1)
- OPC_SW_STATE 0xBC — Request state of switch (SW1, SW2)
- OPC_SW_ACK   0xBD — Request switch with acknowledge function
- OPC_LOCO_ADR 0xBF — Request loco address (example from spec)

6-byte opcodes (examples):
- OPC_MULTI_SENSE 0xD0 — Power management and transponding (type, zone, addr...)

Variable-length opcodes (format: <OPC>,<COUNT>,...):
- OPC_IMM_PACKET 0xED — Immediate packets / special-purpose small payloads (COUNT=0x0B common)
- OPC_WR_SL_DATA  0xEF — Write slot data (COUNT=0x0E typical)
  - Subtypes (byte 2) include:
    - 0x7B — Fast Clock slot data
    - 0x7C — Programming track slot format

Notes and mapping to code
- These opcode hex values match lnconst.h constants (DigiTraxOpc* definitions).
- Packet length rules (D6/D5 bits) and special-case lengths (IMM_PACKET=11, WR_SL_DATA=14) are implemented in LNPacket::getLen.
- The packet factory recognizes WR_SL_DATA with data[2]==0x7B and returns LN_FAST_CLOCK_SLOT_DATA.

References
- loconet_ln-pe-en.pdf (extracted text in loconet_ln-pe-en.txt)
- libraries/LocoNet/src/lnconst.h and src/ln_packet.cpp for code-level mappings
