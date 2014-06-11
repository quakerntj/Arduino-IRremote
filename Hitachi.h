// Copyright for QuakerNTj 2014
// https://github.com/quakerntj

#ifndef HITACHI_AC_H
#define HITACHI_AC_H

enum {
    CLOSE_COUNTDOWN_TIME_LOW_MASK = 0x0F,
    CLOSE_COUNTDOWN_TIME_HIGH_MASK = 0xFE,
};
    

enum {
    // not open case.
    KEYPAD_POWER = 0xC8,
    KEYPAD_WIND_SPEED = 0x42,
    KEYPAD_FUNCTION = 0x82,
    KEYPAD_FAST = 0x91,
    KEYPAD_UP = 0x22,
    KEYPAD_DOWN = 0xC2,
    KEYPAD_LEFT = 0xF8,
    KEYPAD_RIGHT = 0x44,

    // not open case.
    KEYPAD_SLEEP = 0x8C,
    KEYPAD_KEEP_MOISTURE = 0x87,
    KEYPAD_MOULD_PROOF = 0x47,
    KEYPAD_CANCEL_SCHEDULE = 0x24,
    KEYPAD_SCHEDULE = 0x44,
    KEYPAD_WIND_LR = 0x31,
    KEYPAD_WIND_UD = 0x81,
    KEYPAD_BRIGHTNESS = 0x93,
    KEYPAD_POWER_RETURN = 0xD9,

    KEYPAD_BYTE = 12,
    KEYPAD_MASK = 0xFF,
};

enum {
    WIND_LR_AUTO = 0x00,
    WIND_LR_R2 = 0x80,  // larger angel
    WIND_LR_R1 = 0x40,
    WIND_LR_CENTER = 0xC0,
    WIND_LR_L1 = 0x20,
    WIND_LR_L2 = 0xA0,  // larger angel

    WIND_LR_BYTE = 36,
    WIND_LR_MASK = 0xE0,
};

// 38
enum {
    WIND_UD_SWING = 0x04,
    WIND_UD_NOT_SWING = 0x00,
    WIND_UD_MASK = 0x04,
    BIRGHTNESS_FULL = 0x00,  // Full bightness
    BIRGHTNESS_HALF = 0x01,  // Half bightness
    BIRGHTNESS_ONOFF = 0x03,  // Only show machine on/off.
    BIRGHTNESS_NO = 0x02,  // No display
    BIRGHTNESS_NO_MASK = 0x03,
    KEEP_MOISTURE_LOW = 0x40,
    KEEP_MOISTURE_HIGH = 0x50,
    KEEP_MOISTURE_OFF = 0x00,
    KEEP_MOISTURE_MASK = 0x50,
    MOULD_PROOF_ON = 0x20,
    MOULD_PROOF_OFF = 0x00,
    MOULD_PROOF_MASK = 0x20,
    POWER_RETURN_ON = 0x08,
    POWER_RETURN_OFF = 0x00,
    POWER_RETURN_MASK = 0x08,

    WBKMP_BYTE = 38,
};

enum {
    FUNCTION_DEHUMIDIFY = 0xA0,
    FUNCTION_WARM = 0x60,
    FUNCTION_WIND = 0x80,
    FUNCTION_AUTO_CONTROL = 0xE0,
    FUNCTION_COLD = 0xC0,
    FUNCTION_MASK = 0xE0,  // Each function has one bit of difference.
    WIND_SPEED_AUTO = 0x0A,
    WIND_SPEED_4 = 0x02,
    WIND_SPEED_3 = 0x0C,
    WIND_SPEED_2 = 0x04,
    WIND_SPEED_1 = 0x08,
    WIND_MASK = 0xE0,

    FUNCTION_BYTE = 26,
};

enum {
    SCHEDULE_EVERY_DAY = 0x01,
    SCHEDULE_OPEN = 0x04,
    SCHEDULE_CLOSE = 0x08,
    SCHEDULE_BYTE = 24,
    SCHEDULE_MASK = 0x0F,

    SCHEDULE_CLOSE_LOW_BYTE = 18,
    SCHEDULE_CLOSE_TIME_MASK_LOW = 0xFF,  // byte 18
    SCHEDULE_CLOSE_HIGH_BYTE = 20,
    SCHEDULE_CLOSE_TIME_MASK_HIGH = 0xE0,  // byte 20

    SCHEDULE_OPEN_LOW_BYTE = 22,
    SCHEDULE_OPEN_TIME_MASK_LOW = 0xFF,  // byte 22
    SCHEDULE_OPEN_HIGH_BYTE = 24,
    SCHEDULE_OPEN_TIME_MASK_HIGH = 0xE0,  // byte 24
};

enum {
    POWER_ON = 0x08,
    POWER_OFF = 0x00,

    POWER_BYTE = 28,
    POWER_MASK = 0x08,
};

struct HitachiAC {
    unsigned char unknown[8];
    unsigned char unknown1;  // 10
    unsigned char unknown1i;  // 11
    unsigned char keypad;  // 12
    unsigned char keypadi;  // 13
    unsigned char temperature;  // 14
    unsigned char temperaturei;  // 15
    unsigned char sleep;  // 16
    unsigned char sleepi;  // 17
    unsigned char scheduleCloseL;  // 18  Count down
    unsigned char scheduleCloseLi;  // 19
    unsigned char scheduleCloseH;  // 20
    unsigned char scheduleCloseHi;  // 21
    unsigned char scheduleOpenL;  // 22  Count down
    unsigned char scheduleOpenLi;  // 23
    unsigned char scheduleOpenH;  // 24 With other Flags
    unsigned char scheduleOpenHi;  // 25
    unsigned char function;  // 26
    unsigned char functioni;  // 27
    unsigned char power;  // 28
    unsigned char poweri;  // 29
    unsigned char day;  // 30
    unsigned char dayi;  // 31
    unsigned char month;  // 32
    unsigned char monthi;  // 33
    unsigned char unknown2;  // 34  0x01
    unsigned char unknown2i;  // 35  0xFE
    unsigned char windLR;  // 36
    unsigned char windLRi;  // 37
    unsigned char wbm;  // 38  Only control swinging or not.  Can't specify an angel.
    unsigned char wbmi;  // 39
    unsigned char timeH;  // 40  TOTAL 11bits.  The minutes of a day
    unsigned char timeHi;  // 41
    unsigned char timeL;  // 42
    unsigned char timeLi;  // 43
};

// bitreverse do MSB->LSB.  For example 10011111 -> 11111001
unsigned char bitReverse(register unsigned char x) {
    x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
    x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
    return((x >> 4) | (x << 4));
}

union HitachiACUnion {
    unsigned char data[43];
    struct HitachiAC code;

    HitachiACUnion() {
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

    void updateCurrentTime() {
        // get date
        //setDate(month, day, hour, min);
    }

    void send() {
        updateCurrentTime();
    }

    void copyFrom(HitachiACUnion temp) {
        memcpy(data, temp.data, sizeof(data));
    }

    int setDate(int month, int day, int hour, int min) {
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
        setData(30, 0, 0xFF, month);
        setData(32, 0, 0xFF, day);
        return 0;
    }

    int setTime(int hour, int min) {
        if (hour > 23 || hour < 0 || min > 59 || min < 0)
            return -1;
        unsigned int time = min + hour * 60;
        setData(40, 0, 0xFF, time & 0xFF);
        setData(42, 0, 0x07, time >> 8);
        return 0;
    }

    // Only can set one byte. Do data bit reverse inside.  Used for data in integer.
    void setData(int byteIdx, int bitOffset, unsigned char bitmask, unsigned char out_) {
        unsigned char out = bitReverse(out_);
        const int idx = byteIdx - 1;
        unsigned char tmp = data[idx];
        data[idx] &= ~bitmask >> bitOffset;
        data[idx] |= out >> bitOffset;
    }
};

#endif  // HITACHI_AC_H
