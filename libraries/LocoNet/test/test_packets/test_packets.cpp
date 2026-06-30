#include <unity.h>
#include <memory>
#include <vector>

#include "ln_packet.h"
#include "ln_sw_req.h"
#include "ln_sw_rep.h"
#include "ln_input_rep.h"
#include "ln_wr_sl_data.h"
#include "ln_fast_clock_slot_data.h"

using namespace LocoNet;

// Helper: build packet_data from LNPacket instance
static packet_data packetFrom(const LNPacket &p) {
    packet_data out;
    for (uint i = 0; i < p.len(); ++i) out.push_back(p.getByte(i));
    return out;
}

void test_sw_req_roundtrip_address(void) {
    LN_SW_REQ req;
    req.setAddress(123);
    TEST_ASSERT_EQUAL_UINT16(123, req.getAddress());
    req.setClosed(true);
    TEST_ASSERT_TRUE(req.getClosed());
    req.setActive(false);
    TEST_ASSERT_FALSE(req.getActive());
}

void test_input_rep_roundtrip_address(void) {
    LN_INPUT_REP r;
    r.setAddress(257);
    TEST_ASSERT_EQUAL_UINT16(257, r.getAddress());
    r.setActive(true);
    TEST_ASSERT_TRUE(r.getActive());
}

void test_fast_clock_fields_and_factory(void) {
    LN_FAST_CLOCK_SLOT_DATA fc;
    fc.setRate(10);
    fc.setFracMin(0x1234);
    fc.setMinute(7);
    fc.setHour(14);
    fc.setDay(3);
    fc.setSlot(5);
    fc.setValid(true);
    fc.setSynchronized(true);
    fc.setRunning(false);
    fc.setDeviceId1(0x12);
    fc.setDeviceId2(0x34);

    TEST_ASSERT_EQUAL_UINT8(10, fc.getRate());
    TEST_ASSERT_EQUAL_UINT16(0x1234, fc.getFracMin());
    TEST_ASSERT_EQUAL_UINT8(7, fc.getMinute());
    TEST_ASSERT_EQUAL_UINT8(14, fc.getHour());
    TEST_ASSERT_EQUAL_INT(3, fc.getDay());
    TEST_ASSERT_EQUAL_UINT8(5, fc.getSlot());
    TEST_ASSERT_TRUE(fc.isValid());
    TEST_ASSERT_TRUE(fc.isSynchronized());
    TEST_ASSERT_FALSE(fc.isRunning());
    TEST_ASSERT_EQUAL_UINT8(0x12, fc.getDeviceId1());
    TEST_ASSERT_EQUAL_UINT8(0x34, fc.getDeviceId2());

    // Factory roundtrip
    auto pdata = packetFrom(fc);
    auto pkt = LNPacket::factory(pdata);
    // Should be recognized as fast clock subtype
    TEST_ASSERT_NOT_NULL(pkt.get());
    TEST_ASSERT_EQUAL_INT(LN_OPC_WR_SL_DATA, pkt->get_opcode());
}

void test_factory_sw_req_and_checksum(void) {
    LN_SW_REQ req;
    req.setAddress(42);
    req.setActive(true);
    req.setClosed(true);

    auto pdata = packetFrom(req);
    auto pkt = LNPacket::factory(pdata);
    TEST_ASSERT_NOT_NULL(pkt.get());
    // Check validity (checksum)
    TEST_ASSERT_TRUE(pkt->valid());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_sw_req_roundtrip_address);
    RUN_TEST(test_input_rep_roundtrip_address);
    RUN_TEST(test_fast_clock_fields_and_factory);
    RUN_TEST(test_factory_sw_req_and_checksum);
    return UNITY_END();
}
