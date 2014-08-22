#include "Hitachi.h"
#include <string.h>

#define RETURN_ON_ERROR(function) do { int ret = function; if (ret) return ret; } while(0)

HitachiACUnion::HitachiACUnion() {
    // do initial
    data[0] = 0x80;
    data[1] = 0x08;
    data[2] = 0x00;
    data[3] = 0x02;
    data[4] = 0xFD;
    data[5] = 0xFF;
    data[6] = 0x00;
    data[7] = 0x33;
    data[8] = 0xCC;

    for (int i = 9; i < sizeof(data); i++) {
        if (i % 0 == 0)
            i = 0x0;
        else
            i = 0xFF;
    }
}

int HitachiACUnion::setFunction(uint8 function) {
    if (function == 0x0 || function == 0x40 || function == 0x20)
        return -1;
    set(FUNCTION_BYTE, FUNCTION_MASK, function);
    return 0;
}

/**
 * For FUNCTION_WIND, the temperature can be any degree.
 * For FUNCTION_AUTO_CONTROL, the temerature are adjusted around the 
 * TEMPERATURE_AUTO_0 with -3 ~ +3.
 * For examle, setTemerature(TEMPERATURE_AUTO_0 - 3);
**/
void HitachiACUnion::setTemperature(uint8 degree) {
    if (degree < 8) {
        setReverse(TEMPERATURE_BYTE, TEMPERATURE_MASK, degree);
    } else {
        setReverse(TEMPERATURE_BYTE, TEMPERATURE_MASK, degree, TEMPERATURE_OFFSET);
    }
}

void HitachiACUnion::setWindLR(uint8 lr) {
    set(WIND_LR_BYTE, WIND_LR_MASK, lr);
}

void HitachiACUnion::setWindUD(uint8 ud) {
    set(WIND_UD_BYTE, WIND_UD_MASK, ud);
}

void HitachiACUnion::setWindSpeed(uint8 ws) {
    set(WIND_SPEED_BYTE, WIND_SPEED_MASK, ws);
    if (ws == WIND_SPEED_1)
        setFastCool(FAST_SILENT);
}

void HitachiACUnion::setFastCool(uint8 fast) {
    set(FAST_BYTE, FAST_MASK, fast);
}

void HitachiACUnion::setBrightness(uint8 brightness) {
    set(BIRGHTNESS_BYTE, BIRGHTNESS_MASK, brightness);
}

void HitachiACUnion::setKeepMoisture(uint8 km) {
    set(KEEP_MOISTURE_BYTE, KEEP_MOISTURE_MASK, km);
}

void HitachiACUnion::setMouldProof(uint8 mp) {
    set(MOULD_PROOF_BYTE, MOULD_PROOF_MASK, mp);
}

void HitachiACUnion::setPowerReturn(uint8 pr) {
    set(POWER_RETURN_BYTE, POWER_RETURN_MASK, pr);
}

void HitachiACUnion::cleanAllSchedule() {
    data[16] = data[18] = data[20] = data[22] = data[24] = 0x00;
    data[17] = data[19] = data[21] = data[23] = data[25] = 0xFF;
}

int HitachiACUnion::setSleep(int hour, int min) {
    unsigned int time = min + hour * 60;
    if (time < 0 || time >= 1440)
        return -1;
    set(SCHEDULE_BYTE, SCHEDULE_SLEEP, SCHEDULE_SLEEP);
    setReverse(SCHEDULE_SLEEP_HIGH_BYTE, SCHEDULE_SLEEP_HIGH_MASK, time >> 8);
    setReverse(SCHEDULE_SLEEP_LOW_BYTE, SCHEDULE_SLEEP_LOW_MASK, time & 0xFF);
    return 0;
}

int HitachiACUnion::setClose(int hour, int min) {
    unsigned int time = min + hour * 60;
    if (time < 0 || time >= 1440)
        return -1;
    set(SCHEDULE_BYTE, SCHEDULE_CLOSE, SCHEDULE_CLOSE);
    setReverse(SCHEDULE_CLOSE_HIGH_BYTE, SCHEDULE_CLOSE_HIGH_MASK, time >> SCHEDULE_CLOSE_HIGH_SHIFT);
    setReverse(SCHEDULE_CLOSE_LOW_BYTE, SCHEDULE_CLOSE_LOW_MASK,
        time & (1 << SCHEDULE_CLOSE_HIGH_SHIFT - 1), SCHEDULE_CLOSE_LOW_OFFSET);
    return 0;
}

int HitachiACUnion::setOpen(int hour, int min) {
    unsigned int time = min + hour * 60;
    if (time < 0 || time >= 1440)
        return -1;
    set(SCHEDULE_BYTE, SCHEDULE_OPEN, SCHEDULE_OPEN);
    setReverse(SCHEDULE_OPEN_HIGH_BYTE, SCHEDULE_OPEN_HIGH_MASK, time >> 8);
    setReverse(SCHEDULE_OPEN_LOW_BYTE, SCHEDULE_OPEN_LOW_MASK, time & 0xFF);
    return 0;
}

void HitachiACUnion::setPower(bool on) {
    set(POWER_BYTE, POWER_MASK, on ? POWER_ON : POWER_OFF);
}

void HitachiACUnion::updateCurrentTime() {
#if HAS_RTC
#else
    // arduino didn't have RTC.
    setDate(1, 1);
    setTime(0, 0);
#endif
}

int HitachiACUnion::send() {
    updateCurrentTime();
    //RETURN_ON_ERROR(someFunction());
    return 0;
}

void HitachiACUnion::copyFrom(HitachiACUnion temp) {
    memcpy(data, temp.data, sizeof(data));
}

int HitachiACUnion::setDate(int month, int day) {
    // Validate date.
    if (month > 12 || month < 1 || day < 1)
        return -1;
    // Month has four bytes, ABCD.  By Karnaugh map, (A xor D) ? 30 : 31;
    const int days = (((month & 0x8) >> 3) ^ (month & 0x1)) ? 30 : 31;
    if (month == 2) {
        if (days > 29)
            return -1;
    } else {
        if (day > days)
            return -1;
    }
    setReverse(DATA_MONTH_BYTE, DATA_MONTH_MASK, month);
    setReverse(DATA_DAY_BYTE, DATA_DAY_MASK, day);
    return 0;
}

int HitachiACUnion::setTime(int hour, int min) {
    unsigned int time = min + hour * 60;
    if (time < 0 || time > 1440)
        return -1;
    setReverse(TIME_HIGH_BYTE, TIME_HIGH_MASK, time >> 8);
    setReverse(TIME_LOW_BYTE, TIME_LOW_MASK, time & 0xFF);
    return 0;
}

// Only can set one byte. Do data bit reverse inside.  Used for data in integer.
void HitachiACUnion::setReverse(int byteIdx, uint8 bitmask, uint8 out, int offset) {
    uint8 rev = bitReverse(out);
    const int idx = byteIdx - 1;
    data[idx] &= ~bitmask;  // clean old data
    uint8 ret = data[idx] |= rev >> offset;
    data[byteIdx] = ~ret;
}

void HitachiACUnion::set(int byteIdx, uint8 bitmask, uint8 out) {
    const int idx = byteIdx - 1;
    data[idx] &= ~bitmask;  // clean old data
    uint8 ret = data[idx] |= out & bitmask;
    data[byteIdx] = ~ret;
}
