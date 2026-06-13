- OPC code: 0xEF (WR_SL_DATA)
- Packet length: 14 bytes (special-case length)
  - byte 0: 0xEF (opcode)
  - byte 1: slot/type length byte (implementation-dependent)
  - byte 2: subtype/format selector (e.g., 0x7B for Fast Clock Slot Data)
  - bytes 3..12: payload (format depends on subtype)
  - byte 13: checksum
- Purpose: Write slot/variable-length data blocks; used as container for sub-formats such as Fast Clock Slot Data.
- Implemented by: src/ln_wr_sl_data.h, src/ln_wr_sl_data.cpp
- Notes: LN_FAST_CLOCK_SLOT_DATA (data[2]==0x7B) is handled specially in the packet factory.
- Spec reference: "OPC_WR_SL_DATA 0xEF — Write slot data" and variable formats including Fast Clock (subtype 0x7B) (loconet ln-pe-en variable byte opcodes table).

Parameters (from lnpe-parms):
- Packet format (COUNT typically 0x0E for slot data): <0xEF>,<COUNT=0x0E>,<ARG1>,...,<ARG12>,<CKSUM>
- Common ARG meanings for slot data (ARG positions shown for clarity):
  - SLOT#    — slot number (0..127)
  - STAT1    — slot status 1 (contains speed/consist/busy bits; see lnpe-parms Slot Status 1)
  - ADR, ADR2 — locomotive address low/high (7-bit each; ADR2 non-zero => long address)
  - SPD      — speed byte (0x00 = STOP, 0x01 = emergency stop, 0x02-0x7F = speed)
  - DIRF     — direction and functions packed byte
  - TRK      — track/slot flags
  - SND, ID1, ID2 — sound and device ID bytes

- For WR_SL_DATA used as Fast Clock (subtype 0x7B), see OPC_FAST_CLOCK_SLOT_DATA.md for per-byte meanings.
