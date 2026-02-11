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
		byte getRate();
		void setRate( byte rate );
		int getDay();
		void setDay( int day );
		byte gethour();
		void setHour( byte hour );
		void setMinute( byte minute );
		byte getMinute();
		void setSecond( byte second );
		byte getSecond();
		void setSynchronized( bool sync );
		bool isSynchronized();
		void setRunning( bool run );
		bool isRunning();
		void setSlot( byte slot );
		byte getSlot();
		void setTime( byte hour, byte minute, byte second );
		void setDate( int day );
		int getDate();
		void setFastClock( bool isFastClock );
		bool isFastClock();
		void setFastClockPacket(bool isFastClockPacket);
		bool isFastClockPacket();
		void setSyconizedRunning( bool isSynchronizedRunning );
		bool isSynchronizedRunning();
		void setDayLightSavings( bool isDaylightSavings );
		void setSynchronizedRunning( bool sync, bool run );
		void setSynchronizedRunning( bool sync, bool run, byte rate );
		void setSynchronizedRunning( bool sync, bool run, byte rate, int day, byte hour, byte minute, byte second );
		void setSynchronizedRunning( bool sync, bool run, byte rate, int day, byte hour, byte minute, byte second, byte slot );
		void setFastClock( bool isFastClock, byte rate );
		void setFastClock( bool isFastClock, byte rate, int day, byte hour, byte minute, byte second );
		void setFastClock( bool isFastClock, byte rate, int day, byte hour, byte minute, byte second, byte slot );
		/**
		 * Destructor
		 */
		virtual ~LN_FAST_CLOCK_SLOT_DATA();
	};

} /* namespace LocoNet */

#endif /* LIBRARIES_LOCONET_SRC_LN_FAST_CLOCK_SLOT_DATA_H_ */
