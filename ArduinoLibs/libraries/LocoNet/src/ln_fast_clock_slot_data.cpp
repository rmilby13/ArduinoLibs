/*
 * ln_fast_clock_slot_data.cpp
 *
 *  Created on: Jun 18, 2025
 *      Author: rmilb
 */

#include "ln_fast_clock_slot_data.h"
#include <Arduino.h>
//#define DEBUGFastClock 1
#ifdef TRACEFastClock
#define TRACE(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#define DEBUGFastClock
#else
#define TRACE(...)
#endif

#ifdef DEBUGFastClock
#define DEBUG(...) Serial.printf("\n%s:%d:\t",__FILE__,__LINE__); Serial.printf(__VA_ARGS__); Serial.println()
#else
#define DEBUG(...)
#endif

namespace LocoNet {

LN_FAST_CLOCK_SLOT_DATA::LN_FAST_CLOCK_SLOT_DATA() :LN_WR_SL_DATA() {
	this->data[2] = 0x7B;
	this->setCheckSum();
}

LN_FAST_CLOCK_SLOT_DATA::LN_FAST_CLOCK_SLOT_DATA( LNPacket &packet ) :LN_WR_SL_DATA(packet) {
	// TODO Auto-generated constructor stub
};

LN_FAST_CLOCK_SLOT_DATA::LN_FAST_CLOCK_SLOT_DATA( packet_data &pdata ) :LN_WR_SL_DATA(pdata) {
	// TODO Auto-generated constructor stub
};

arduino::String LN_FAST_CLOCK_SLOT_DATA::toString(){
	TRACE("Starting LN_FAST_CLOCK_SLOT_DATA::toString");
	arduino::String s = LN_WR_SL_DATA::toString();
	TRACE("s = %s", s.c_str());
	s += " Request Fast Clock is Synchronized, Running, rate is " + arduino::String(this->getRate()) + ":1";
	TRACE("s = %s", s.c_str());
	s += " Day " + arduino::String(this->getDay()) + ", " + arduino::String(this->gethour()) + ":" + arduino::String(this->getMinute()) +  ".";
	TRACE("s = %s", s.c_str());
	s += " Last set by ID " + arduino::String(this->getSlot());
	DEBUG("LN_FAST_CLOCK_SLOT_DATA::toString - %s", s.c_str());
	return s;
}

byte LN_FAST_CLOCK_SLOT_DATA::getRate() {
	return this->data[3];
}

void LN_FAST_CLOCK_SLOT_DATA::setRate( byte rate ) {
	this->data[3] = rate;
	this->setCheckSum();
}

int LN_FAST_CLOCK_SLOT_DATA::getDay() {
	return this->data[9];
}

void LN_FAST_CLOCK_SLOT_DATA::setDay( int day ) {
	this->data[9] = day;
	this->setCheckSum();
}

byte LN_FAST_CLOCK_SLOT_DATA::gethour() {
	return this->data[8]-104;
};

void LN_FAST_CLOCK_SLOT_DATA::setHour( byte hour ) {
	this->data[8] = hour+104;
	this->setCheckSum();
};

void LN_FAST_CLOCK_SLOT_DATA::setMinute( byte minute ) {
	this->data[6] = minute+67;
	this->setCheckSum();
};

byte LN_FAST_CLOCK_SLOT_DATA::getMinute() {
	return this->data[6]-67;
};

void LN_FAST_CLOCK_SLOT_DATA::setSecond( byte second ) {
	this->data[8] = second;
	this->setCheckSum();
};

byte LN_FAST_CLOCK_SLOT_DATA::getSecond() {
	return this->data[8];
};

void LN_FAST_CLOCK_SLOT_DATA::setSynchronized( bool sync ) {
	if (sync) {
		this->data[2] |= 0x01;
	} else {
		this->data[2] &= 0xFE;
	}
	this->setCheckSum();
};

bool LN_FAST_CLOCK_SLOT_DATA::isSynchronized() {
	return (this->data[2] & 0x01) != 0;
};

void LN_FAST_CLOCK_SLOT_DATA::setRunning( bool run ) {
	if (run) {
		this->data[2] |= 0x02;
	} else {
		this->data[2] &= 0xFD;
	}
	this->setCheckSum();
};

bool LN_FAST_CLOCK_SLOT_DATA::isRunning() {
	return (this->data[2] & 0x02) != 0;
};

void LN_FAST_CLOCK_SLOT_DATA::setSlot( byte slot ) {
	this->data[2] = (this->data[2] & 0xFC) | (slot & 0x03);
	this->setCheckSum();
};

byte LN_FAST_CLOCK_SLOT_DATA::getSlot() {
	return this->data[2] & 0x03;
};

void LN_FAST_CLOCK_SLOT_DATA::setTime( byte hour, byte minute, byte second ) {
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
};

void LN_FAST_CLOCK_SLOT_DATA::setDate( int day ) {
	this->setDay(day);
};

int LN_FAST_CLOCK_SLOT_DATA::getDate() {
	return this->getDay();
};

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning( bool sync, bool run ) {
	this->setSynchronized(sync);
	this->setRunning(run);
};

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning( bool sync, bool run, byte rate ) {
	this->setSynchronized(sync);
	this->setRunning(run);
	this->setRate(rate);
};

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning( bool sync, bool run, byte rate, int day, byte hour, byte minute, byte second ) {
	this->setSynchronized(sync);
	this->setRunning(run);
	this->setRate(rate);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
};

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning( bool sync, bool run, byte rate, int day, byte hour, byte minute, byte second, byte slot ) {
	this->setSynchronized(sync);
	this->setRunning(run);
	this->setRate(rate);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
	this->setSlot(slot);
};

void LN_FAST_CLOCK_SLOT_DATA::setFastClock( bool isFastClock ) {
	if (isFastClock) {
		this->data[2] |= 0x08; // Set the fast clock bit
	} else {
		this->data[2] &= 0xF7; // Clear the fast clock bit
	}
	this->setCheckSum();
};

bool LN_FAST_CLOCK_SLOT_DATA::isFastClock() {
	return (this->data[2] & 0x08) != 0; // Check the fast clock bit
};

void LN_FAST_CLOCK_SLOT_DATA::setFastClock( bool isFastClock, byte rate ) {
	this->setFastClock(isFastClock);
	this->setRate(rate);
};
void LN_FAST_CLOCK_SLOT_DATA::setFastClock( bool isFastClock, byte rate, int day, byte hour, byte minute, byte second ) {
	this->setFastClock(isFastClock);
	this->setRate(rate);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
};

void LN_FAST_CLOCK_SLOT_DATA::setFastClock( bool isFastClock, byte rate, int day, byte hour, byte minute, byte second, byte slot ) {
	this->setFastClock(isFastClock);
	this->setRate(rate);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSecond(second);
	this->setSlot(slot);
};

void LN_FAST_CLOCK_SLOT_DATA::setFastClockPacket(bool isFastClockPacket) {
	if (isFastClockPacket) {
		this->data[2] |= 0x08; // Set the fast clock bit
	} else {
		this->data[2] &= 0xF7; // Clear the fast clock bit
	}
	this->setCheckSum();
};

bool LN_FAST_CLOCK_SLOT_DATA::isFastClockPacket() {
	return (this->data[2] & 0x08) != 0; // Check the fast clock bit
};

void LN_FAST_CLOCK_SLOT_DATA::setSyconizedRunning( bool isSynchronizedRunning ) {
	if (isSynchronizedRunning) {
		this->data[2] |= 0x01; // Set the synchronized bit
		this->data[2] |= 0x02; // Set the running bit
	} else {
		this->data[2] &= 0xFE; // Clear the synchronized bit
		this->data[2] &= 0xFD; // Clear the running bit
	}
	this->setCheckSum();
};

bool LN_FAST_CLOCK_SLOT_DATA::isSynchronizedRunning() {
	return (this->data[2] & 0x01) != 0 && (this->data[2] & 0x02) != 0; // Check the synchronized and running bits
};

LN_FAST_CLOCK_SLOT_DATA::~LN_FAST_CLOCK_SLOT_DATA() {
	// TODO Auto-generated destructor stub
}

} /* namespace LocoNet */
