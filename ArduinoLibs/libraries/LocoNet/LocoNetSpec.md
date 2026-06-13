LocoNetSpec — Concise implementation & verification spec

Purpose
- Single-file, machine-friendly summary of Loconet packet types, wire layouts, and encoding rules extracted from the local spec PDFs (loconet_ln-pe-en.pdf, loconet_lnpe-parms-en.pdf, loconetpersonaledition.pdf) and the repository code. Optimized for AI consumption to implement new packet types and verify existing implementations.

Global rules
- Bytes are 8-bit with MSB (D7) acting as opcode flag when set (1). Opcode is the FIRST byte of a message.
- Checksum: final byte is 1's complement of XOR of all preceding bytes. Valid message: XOR(all bytes except checksum)==0xFF.
- Length determination:
  - D6-D5 bits of opcode encode message length: 00 -> 2 bytes, 01 -> 4 bytes, 10 -> 6 bytes, 11 -> variable with next byte a 7-bit byte count.
  - Special-case lengths: IMM_PACKET (0xED) length=11, WR_SL_DATA (0xEF) length=14 as implemented in LNPacket::getLen().

Common opcode mapping (source: lnconst.h and spec tables)
- 0x80 NOOP (2 bytes)
- 0x81 BUSY (2 bytes)
- 0x82 GPOFF (2 bytes)
- 0x83 GPON (2 bytes)
- 0x85 IDLE (2 bytes)
- 0xB0 SW_REQ (4 bytes)
- 0xB1 SW_REP (4 bytes)
- 0xB2 INPUT_REP (4 bytes)
- 0xB4 LONG_ACK (4 bytes)
- 0xBC SW_STATE (4 bytes)
- 0xBD SW_ACK (4 bytes)
- 0xD0 MULTI_SENSE (6 bytes)
- 0xED IMM_PACKET (11 bytes)
- 0xEF WR_SL_DATA (14 bytes)

Packet structures (per-byte layouts and encoding) — implemented types

1) NOOP (0x80)
- Length: 2
- Layout: [0x80][CKSUM]
- Purpose: NOP/idle placeholder. Implemented by: src/ln_nop.* (LN_NOP)

2) BUSY (0x81)
- Length: 2
- Layout: [0x81][CKSUM]
- Purpose: Master busy indicator. Implemented by: src/ln_busy.* (LN_BUSY)

3) GPON (0x83) / GPOFF (0x82)
- Length: 2
- Layout: [opcode][CKSUM]
- Purpose: Global power on/off. Implemented by: src/ln_gpon.*, src/ln_gpoff.* (LN_GPON, LN_GPOFF)
- Note: Verify ln_gpon ctor (code currently sets opcode to 0x81 in one constructor — confirm and correct if spec mismatch).

4) IDLE (0x85)
- Length: 2
- Layout: [0x85][CKSUM]
- Purpose: Force idle.

5) SW_REQ (0xB0) — Switch Request
- Length: 4
- Layout: [0xB0][A0..A6][A10..A7 + flags][CKSUM]
  - byte1: low 7 bits of switch address (A0..A6)
  - byte2: low nibble bits 0..3 = high address bits (A7..A10), bit4 = active flag, bit5 = closed flag, upper nibble preserved/reserved
- Address encoding (from code): address = ((data[2] & 0x0F) << 7) + (data[1] & 0x7F) + 1
- Implemented by: src/ln_sw_req.* (LN_SW_REQ)

6) SW_REP (0xB1) — Switch Reply
- Length: 4
- Layout identical encoding scheme to SW_REQ for address and flags
- Implemented by: src/ln_sw_rep.* (LN_SW_REP)

7) INPUT_REP (0xB2) — Input / Sensor Report
- Length: 4
- Layout: [0xB2][byte1][byte2][CKSUM]
  - Address decode (from code): ((data[2] & 0x0F) << 8) + ((data[1] & 0x7F) << 1) + ((data[2] & 0x20) >> 5) + 1
  - Active flag: bit4 of data[2] (0x10)
- Implemented by: src/ln_input_rep.* (LN_INPUT_REP)

8) SW_STATE (0xBC)
- Length: 4
- Layout: same address encoding pattern as SW_REQ/SW_REP
- Implemented by: src/ln_sw_state.* (LN_SW_State)

9) SW_ACK (0xBD)
- Length: 4
- Layout: like SW_REQ but semantics: request-with-ack
- Implemented by: src/ln_sw_ack.* (LN_SW_ACK)

10) LONG_ACK (0xB4)
- Length: 4
- Layout: [0xB4][LOPC][ACK1][CKSUM]
  - LOPC: acknowledged opcode (top bit cleared in stored byte), toString maps with |0x80 to display original opcode
  - ACK1: result byte (0 => fail, 0x7F => success in code)
- Implemented by: src/ln_long_ack.* (LN_Long_Ack)

11) IMM_PACKET (0xED)
- Length: 11 (special-case)
- Layout (typical): [0xED][COUNT][SUBTYPE][payload...][CKSUM]
- Note: LNPacket constructor initializes data[1]=0x0B and data[2]=0x7F by default for IMM_PACKET
- Implemented by: src/ln_imm_packet.* (LN_IMM_Packet)

12) WR_SL_DATA (0xEF) — Write Slot / variable data
- Length: 14 (special-case)
- Layout: [0xEF][COUNT=0x0E][subtype][payload 10 bytes][CKSUM]
- Subtypes (byte2):
  - 0x7B => Fast Clock Slot Data (Slot 123)
  - 0x7C => Programming Track format
- Implemented by: src/ln_wr_sl_data.* (LN_WR_SL_DATA)
- Packet factory: LNPacket::factory() checks opcode 0xEF and then inspects data[2] to instantiate LN_FAST_CLOCK_SLOT_DATA when 0x7B.

13) FAST_CLOCK_SLOT_DATA (WR_SL_DATA subtype 0x7B)
- Under WR_SL_DATA, data[2]==0x7B indicates Fast Clock format.
- Layout per code (data indices as in LN_FAST_CLOCK_SLOT_DATA implementation):
  - byte0: 0xEF
  - byte1: COUNT (0x0E typical)
  - byte2: 0x7B (fast clock identifier)
  - byte3: CLK_RATE — 0 = freeze, 1 = normal, 10 = 10:1, etc. (max 0x7F)
  - byte4: FRAC_MIN low
  - byte5: FRAC_MIN high
  - byte6: Minute encoded as (256 - minute) modulo 0-59
  - byte7: Slot/Track byte
  - byte8: Hour encoded as (256 - hour) modulo 0-23
  - byte9: DAYS — number of 24-hour rolls
  - byte10: CLK_CNTRL — control flags (D6=valid(0x40); bit0=synchronized; bit1=running)
  - byte11: ID1 (device id low)
  - byte12: ID2 (device id high)
  - byte13: checksum
- Behavior notes from spec: slot 123 holds fast clock; devices should use it to re-sync and not poll continuously. Typical sync interval ~70–100s.
- Implemented by: src/ln_fast_clock_slot_data.* (LN_FAST_CLOCK_SLOT_DATA)

Parameters & field tables (summary)
- Address encoding: many switch/input packets use a 11- or 12-bit composite address encoded across byte1/byte2 with formulas given above. Implementation adds +1 for 1-based addresses.
- Status & flag bits: closed=bit5, active=bit4 for switch packets; input active uses bit4 in input report; clock control uses D6 (0x40) as valid flag.
- Slot status fields and meanings: see loconet lnpe-parms for STAT1/SS2/ACK1 definitions; refer to OPC_WR_SL_DATA and OPC_FAST_CLOCK_SLOT_DATA for slot-specific mappings.

Implementation guidance for adding a new packet type
1. Determine opcode & length from spec (use above opcode table or PDFs). If variable-length, determine COUNT behavior.
2. Add constant to lnconst.h if missing (e.g., DigiTraxOpcXxx and LN_OP_CODE enum entry).
3. Create header/cpp: follow existing ln_*.h/ln_*.cpp patterns
   - Provide constructors: empty/default, from packet_data&, and from LNPacket&
   - Provide toString() for diagnostics
   - Provide accessors/mutators for encoded fields (address, flags) that match spec bit positions
   - If packet has fixed length <-> set LNPacket(base) with appropriate length
4. Include new header in ln_packets.h so the factory can construct it.
5. Update LNPacket::getLen/constructor if the packet uses a special-case length (IMM_PACKET/WR_SL_DATA model) or relies on D6/D5 rules.
6. Update LNPacket::factory(packet_data&) and factory(LNPacket&) to construct the new class when opcode (and subtype) match.
7. Add OPC_<NAME>.md under libraries/LocoNet/OPC/ documenting opcode hex, per-byte layout, and spec reference.
8. Add unit tests: construct raw packet_data examples (valid/invalid), verify factory produces correct subclass, verify getByte/len/valid (checksum), and verify accessors round-trip.

Verification checklist (use for AI testing)
- Opcode: first byte matches lnconst.h constant and spec hex.
- Length: LNPacket::getLen(byte0) produces expected length; special-case lengths match constants.
- Checksum: recomputed XOR complement equals final byte.
- Field decode/encode: round-trip encode->decode returns original values for addresses, flags, numeric fields.
- Factory: LNPacket::factory(packet_data) returns correct derived class for opcode/subtype.
- toString(): contains human-readable summary; useful for debug tests.
- Edge cases: off-by-one addressing (+1 behavior), maximum/minimum values, invalid checksum detection.

Where to find authoritative sources in this repo
- PDFs (raw): libraries/LocoNet/loconet_ln-pe-en.pdf, loconet_lnpe-parms-en.pdf, loconetpersonaledition.pdf
- Extracted text copies (convenience): libraries/LocoNet/loconet_ln-pe-en.txt, loconet_lnpe-parms-en.txt
- Code reference mapping: libraries/LocoNet/src/lnconst.h, src/ln_packet.cpp, and implemented ln_*.h/cpp files (listed in ln_packets.h)
- OPC docs folder: libraries/LocoNet/OPC/ (per-opcode markdown files and OPCODE_REFERENCE.md)

Appendix: Quick field encodings (copyable snippets)
- SW address decode: addr = ((data[2] & 0x0F) << 7) + (data[1] & 0x7F) + 1
- InputReport address decode: addr = ((data[2] & 0x0F) << 8) + ((data[1] & 0x7F) << 1) + ((data[2] & 0x20) >> 5) + 1
- Checksum calc (pseudocode):
    chksum = 0xFF
    for i in 0..(len-2): chksum ^= data[i]
    assert chksum == data[len-1]


Additional opcode coverage — spec-only packet types (not currently implemented in this library)

14) LOCO_ADR (0xBF)
- Length: 4 (format: <0xBF>,<0>,<ADR>,<CKSUM>)
- Layout: [0xBF][0x00][ADR][CKSUM]
  - ADR: 7-bit locomotive address (short) or low byte when requesting address allocation
- Purpose: Request a locomotive address be assigned/returned by the Master. If not found, master will place the address in a free slot and respond with OPC_SL_RD_DATA (0xE7).
- Spec references: loconetpersonaledition and ln-pe-en opcode tables.
- Implementation notes: Not implemented. Factory: should accept 0xBF and create LN_LOCO_ADR (new type). On receiving, expect OPC_SL_RD_DATA reply or OPC_LONG_ACK on failure.

15) RQ_SL_DATA (0xBB)
- Length: 4
- Layout: [0xBB][SLOT][0x00][CKSUM]
- Purpose: Request slot data/status block for SLOT; master responds with OPC_SL_RD_DATA (0xE7).
- Parameters: SLOT (0..127)
- Implementation notes: Not implemented. Useful for querying slot contents; verify response parsing through LNPacket::factory producing LN_SL_RD_DATA when opcode 0xE7.

16) MOVE_SLOTS (0xBA)
- Length: 4
- Layout: [0xBA][SRC][DST][CKSUM]
- Purpose: Move slot SRC to DST. On success a slot read OPC_SL_RD_DATA for destination is returned.
- Implementation notes: Not implemented. Ensure DST and SRC validate range 0..127 and handle Long Ack failure responses.

17) LINK_SLOTS (0xB9)
- Length: 4
- Layout: [0xB9][SL1][SL2][CKSUM]
- Purpose: Link slave slot SL1 to master slot SL2 (consist linking). Reply: OPC_SL_RD_DATA of affected slot(s).
- Implementation notes: Not implemented. Encoding uses 7-bit slot numbers.

18) UNLINK_SLOTS (0xB8)
- Length: 4
- Layout: [0xB8][SL1][SL2][CKSUM]
- Purpose: Unlink slots.
- Implementation notes: Not implemented.

19) CONSIST_FUNC (0xB6)
- Length: 4
- Layout: [0xB6][SLOT][DIRF][CKSUM]
- Purpose: Set function bits in a consist uplink element. DIRF encodes direction and F0..F4 function bits.
- Implementation notes: Not implemented.

20) SLOT_STAT1 (0xB5)
- Length: 4
- Layout: [0xB5][SLOT][STAT1][CKSUM]
- Purpose: Write slot status 1 (STAT1 contains busy/consist/speed-mode bits). See lnpe-parms for bit fields: D7-SL_SPURGE, D6-SL_CONUP, D3-SL_CONDN, D5/D4 SL_BUSY/SL_ACTIVE, D2..D0 decoder type.
- Implementation notes: Not implemented.

21) LOCO_SPD (0xA0), LOCO_DIRF (0xA1), LOCO_SND (0xA2)
- Length: 4 each
- Layouts:
  - LOCO_SPD: [0xA0][SLOT][SPD][CKSUM]
  - LOCO_DIRF: [0xA1][SLOT][DIRF][CKSUM]
  - LOCO_SND: [0xA2][SLOT][SND][CKSUM]
- Purpose: Set slot speed, direction/function bits, and slot sound respectively. SPD encoding: 0x00=stop, 0x01=emergency stop, 0x02-0x7F increasing speed.
- Implementation notes: Not implemented. Map to slot update behavior similar to WR_SL_DATA but for single-field updates.

22) SL_RD_DATA (0xE7) — Slot Data Read (response)
- Length: 14 (special-case/count 0x0E)
- Layout: [0xE7][0x0E][SLOT#][STAT1][ADR][SPD][DIRF][TRK][SS2][ADR2][SND][ID1][ID2][CKSUM]
- Purpose: Returned by master or as reply to slot-related requests (READ/MOVE/LINK/WRITE completion). Contains full slot content including ADR/ADR2 for long addresses, STAT1/SS2 status bytes, track flags and device IDs.
- Implement notes: Not implemented as a dedicated class; recommended LN_SL_RD_DATA or reuse LN_WR_SL_DATA for parsing responses. Factory should instantiate LN_SL_RD_DATA when opcode 0xE7.
- Parameter table: STAT1, SS2, ACK1 semantics are in lnpe-parms file (Slot Status and ACK1 definitions).

23) PEER_XFER (0xE5)
- Length: 16 (COUNT=0x10)
- Layout: [0xE5][0x10][SRC][DSTL][DSTH][PXCT1][D1..D8][PXCT2][D5..D8?]... (per spec)
- Purpose: Move 8 bytes peer-to-peer (SRC→DST). SRC values 0x70-0x7E reserved. Used for peer memory transfers between devices.
- Implementation notes: Not implemented. Exact argument positions should be taken from ln-pe-en/E5 section when implementing.

24) LISSY / WHEELCNT / RFID report (0xE4)
- Length: variable (0x08 / 0x0C / 0x0E depending on subtype)
- Layout variants indicate LISSY IR report, wheel counter reports, RFID reports, etc. Common format: [0xE4][COUNT][type/subtype][addr_hi][addr_lo][data...][CKSUM]
- Purpose: Various peripheral reports (Lissy IR, wheel counters, RFID tags). Implementation must parse subtype byte (e.g., 0x00, 0x40, 0x41) to determine exact fields.
- Implementation notes: Not implemented. Implement as a generic LN_E4_REPORT with subtype dispatching.

25) MULTI_SENSE (0xD0)
- Length: 6 (example)
- Layout: [0xD0][type][zone+section][addr_hi][addr_lo][CKSUM]
- Purpose: Power management and transponding information (transponding ARG fields per lnpe-parms).
- Implementation notes: Not implemented.

26) UHLI_FUN / UHLENBROCK function extensions (0xD4)
- Length: 6
- Layout: [0xD4][0x20][slot][function_group][function][CKSUM] (per spec table)
- Purpose: Extended function control for Uhlenbrock devices and function ranges 9-28 etc.
- Implementation notes: Not implemented; treat as IMM_PACKET-like or dedicated class if required.

27) Programming / Service Mode opcodes (0xE6 and related)
- E6: Programming service mode responses using COUNT 0x10 / 0x15. Format: <0xE6>,<COUNT>,<PCMD>,<PSTAT>,<HOPSA>,<LOPSA>,<TRK>,<CVH>,<CVL>,<DATA7>,<CHK>
- Purpose: Operations and responses for Programming Track (Slot 0x7C special slot usage). See lnpe-parms for PCMD, PSTAT, CVH/CVL and DATA7 bit encodings.
- Implementation notes: Not implemented.

Implementation guidance for unimplemented opcodes
- Add constants to lnconst.h and enum entries in LN_OP_CODE.
- Create new ln_<name>.h/.cpp classes mirroring existing patterns (constructors, packet-based ctors, toString, accessors).
- For variable-length or COUNT-based formats, use LNPacket(packet_data) constructor and parse COUNT-based payload contents; set getLen to return special-case lengths where appropriate (IMM/WR/SL_RD/PEER_XFER)
- Update ln_packets.h and LNPacket::factory to return the new classes for both direct opcode and subtype (e.g., WR_SL_DATA subtypes, E4 subtypes).

End of LocoNetSpec
