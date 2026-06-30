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
	// Ensure this is the fast clock slot message opcode 0x7B in byte 2 per format
	this->data[2] = 0x7B;
	// default length/other bytes are left as-is by LN_WR_SL_DATA constructor	this->setCheckSum();
}

LN_FAST_CLOCK_SLOT_DATA::LN_FAST_CLOCK_SLOT_DATA( LNPacket &packet ) :LN_WR_SL_DATA(packet) {
	// packet-based ctor; assume packet already follows format
}
LN_FAST_CLOCK_SLOT_DATA::LN_FAST_CLOCK_SLOT_DATA( packet_data &pdata ) :LN_WR_SL_DATA(pdata) {
	// raw data ctor
}

arduino::String LN_FAST_CLOCK_SLOT_DATA::toString(){
	arduino::String s = LN_WR_SL_DATA::toString();
	s += " FastClock rate=" + arduino::String(this->getRate());
	s += ", day=" + arduino::String(this->getDay());
	s += ", time=" + arduino::String(this->getHour()) + ":" + (this->getMinute() < 10 ? "0" : "") + arduino::String(this->getMinute());
	s += ", slot=" + arduino::String(this->getSlot());
	s += ", ctrl=0x" + arduino::String(this->getClockControl(), HEX);
	return s;
}

// Rate at data[3]
byte LN_FAST_CLOCK_SLOT_DATA::getRate() {
	return this->data[3];
}

void LN_FAST_CLOCK_SLOT_DATA::setRate( byte rate ) {
	this->data[3] = rate;
	this->setCheckSum();
}

// Fractional minute low/high at 4/5
byte LN_FAST_CLOCK_SLOT_DATA::getFracMinLow(){
	return this->data[4];
}

byte LN_FAST_CLOCK_SLOT_DATA::getFracMinHigh(){
	return this->data[5];
}

void LN_FAST_CLOCK_SLOT_DATA::setFracMinLow(byte v){
	this->data[4] = v;
	this->setCheckSum();
}

void LN_FAST_CLOCK_SLOT_DATA::setFracMinHigh(byte v){
	this->data[5] = v;
	this->setCheckSum();
}

uint16_t LN_FAST_CLOCK_SLOT_DATA::getFracMin(){
	return ((uint16_t)this->getFracMinHigh() << 8) | (uint16_t)this->getFracMinLow();
}

void LN_FAST_CLOCK_SLOT_DATA::setFracMin(uint16_t v){
	this->setFracMinLow((byte)(v & 0xFF));
	this->setFracMinHigh((byte)((v >> 8) & 0xFF));
}

// Minute stored as (256 - minute) modulo 0-59 at data[6]
byte LN_FAST_CLOCK_SLOT_DATA::getMinute() {
	byte raw = this->data[6];
	int minute = (256 - (int)raw) & 0xFF;
	return (byte)(minute % 60);
}

void LN_FAST_CLOCK_SLOT_DATA::setMinute( byte minute ) {
	minute = minute % 60;
	this->data[6] = (byte)((256 - minute) & 0xFF);
	this->setCheckSum();
}

// Hour stored as (256 - hour) modulo 0-23 at data[8]
byte LN_FAST_CLOCK_SLOT_DATA::getHour() {
	byte raw = this->data[8];
	int hour = (256 - (int)raw) & 0xFF;
	return (byte)(hour % 24);
}

void LN_FAST_CLOCK_SLOT_DATA::setHour( byte hour ) {
	hour = hour % 24;
	this->data[8] = (byte)((256 - hour) & 0xFF);
	this->setCheckSum();
}

int LN_FAST_CLOCK_SLOT_DATA::getDay() {
	return (int)this->data[9];
}

void LN_FAST_CLOCK_SLOT_DATA::setDay( int day ) {
	this->data[9] = (byte)day;
	this->setCheckSum();
}

void LN_FAST_CLOCK_SLOT_DATA::setSlot( byte slot ){
	this->data[7] = slot; // TRK/slot byte
	this->setCheckSum();
}

byte LN_FAST_CLOCK_SLOT_DATA::getSlot(){
	return this->data[7];
}

byte LN_FAST_CLOCK_SLOT_DATA::getClockControl(){
	return this->data[10];
}

void LN_FAST_CLOCK_SLOT_DATA::setClockControl(byte ctrl){
	this->data[10] = ctrl;
	this->setCheckSum();
}

// D6: 1 = valid clock info (mask 0x40)
bool LN_FAST_CLOCK_SLOT_DATA::isValid(){
	return (this->getClockControl() & 0x40) != 0;
}

void LN_FAST_CLOCK_SLOT_DATA::setValid(bool valid){
	if (valid) this->data[10] |= 0x40; else this->data[10] &= (byte)~0x40;
	this->setCheckSum();
}

// Use bit0 for synchronized and bit1 for running (keeps old behavior but moved to control byte)
bool LN_FAST_CLOCK_SLOT_DATA::isSynchronized(){
	return (this->getClockControl() & 0x01) != 0;
}

void LN_FAST_CLOCK_SLOT_DATA::setSynchronized(bool sync){
	if (sync) this->data[10] |= 0x01; else this->data[10] &= (byte)~0x01;
	this->setCheckSum();
}

bool LN_FAST_CLOCK_SLOT_DATA::isRunning(){
	return (this->getClockControl() & 0x02) != 0;
}

void LN_FAST_CLOCK_SLOT_DATA::setRunning(bool run){
	if (run) this->data[10] |= 0x02; else this->data[10] &= (byte)~0x02;
	this->setCheckSum();
}

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning(bool sync, bool run){
	this->setSynchronized(sync);
	this->setRunning(run);
}

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning(bool sync, bool run, byte rate){
	this->setSynchronized(sync);
	this->setRunning(run);
	this->setRate(rate);
}

void LN_FAST_CLOCK_SLOT_DATA::setSynchronizedRunning(bool sync, bool run, byte rate, int day, byte hour, byte minute, byte slot){
	this->setSynchronized(sync);
	this->setRunning(run);
	this->setRate(rate);
	this->setDay(day);
	this->setHour(hour);
	this->setMinute(minute);
	this->setSlot(slot);
}

byte LN_FAST_CLOCK_SLOT_DATA::getDeviceId1(){
	return this->data[11];
}

byte LN_FAST_CLOCK_SLOT_DATA::getDeviceId2(){
	return this->data[12];
}

void LN_FAST_CLOCK_SLOT_DATA::setDeviceId1(byte id1){
	this->data[11] = id1;
	this->setCheckSum();
}

void LN_FAST_CLOCK_SLOT_DATA::setDeviceId2(byte id2){
	this->data[12] = id2;
	this->setCheckSum();
}

LN_FAST_CLOCK_SLOT_DATA::~LN_FAST_CLOCK_SLOT_DATA() {
	// no-op
}

} /* namespace LocoNet */
