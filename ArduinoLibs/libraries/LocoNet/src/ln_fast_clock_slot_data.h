/*
 * ln_fast_clock_slot_data.h
 *
 *  Created on: Jun 18, 2025
 *      Author: rmilb
 */

#ifndef LIBRARIES_LOCONET_SRC_LN_FAST_CLOCK_SLOT_DATA_H_
#define LIBRARIES_LOCONET_SRC_LN_FAST_CLOCK_SLOT_DATA_H_

#include "ln_wr_sl_data.h"
#include <Arduino.h>
namespace LocoNet {
	class LN_FAST_CLOCK_SLOT_DATA: public LN_WR_SL_DATA {
	public:
		LN_FAST_CLOCK_SLOT_DATA();
		LN_FAST_CLOCK_SLOT_DATA( LNPacket &packet );
		LN_FAST_CLOCK_SLOT_DATA( packet_data &pdata );
		virtual arduino::String toString();

		// Rate: 0=freeze, 1=normal 1:1, 10=10:1, etc.
		byte getRate();
		void setRate( byte rate );
		// Fractional minute counter (two bytes as present on the wire)
		byte getFracMinLow();
		byte getFracMinHigh();
		void setFracMinLow(byte v);
		void setFracMinHigh(byte v);
		// Combined 16-bit fractional minute value helper (msb: high, lsb: low)
		uint16_t getFracMin();
		void setFracMin(uint16_t v);
		// Minute and Hour are stored in packet as (256 - value) modulo range
		byte getMinute();
		void setMinute( byte minute );
		byte getHour();
		void setHour( byte hour );
		// Days (number of 24 hour rolls)
		int getDay();
		void setDay( int day );
		// Slot / Track field
		void setSlot( byte slot );
		byte getSlot();
		// Clock control byte access and helpers. The raw control byte is provided
		byte getClockControl();
		void setClockControl(byte ctrl);
		// Convenience flags (operate on bits within the clock control byte)		
		// D6: 1 = This is valid clock information
		bool isValid();
		void setValid(bool valid);
		// Synchronized / Running helpers (interpretation depends on implementation)		bool isSynchronized();
		void setSynchronized(bool sync);
		bool isRunning();
		void setRunning(bool run);
		// Set both sync and run in one call and optionally rate/slot/day/time
		void setSynchronizedRunning(bool sync, bool run);
		void setSynchronizedRunning(bool sync, bool run, byte rate);
		void setSynchronizedRunning(bool sync, bool run, byte rate, int day, byte hour, byte minute, byte slot);
		// Device ID bytes (who last set the clock)		
		byte getDeviceId1();
		byte getDeviceId2();
		void setDeviceId1(byte id1);
		void setDeviceId2(byte id2);
		virtual ~LN_FAST_CLOCK_SLOT_DATA();
	};

} /* namespace LocoNet */

#endif /* LIBRARIES_LOCONET_SRC_LN_FAST_CLOCK_SLOT_DATA_H_ */