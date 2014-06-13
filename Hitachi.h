// Copyright for QuakerNTj 2014
// https://github.com/quakerntj

#ifndef HITACHI_AC_H
#define HITACHI_AC_H

#ifndef uint8
#define uint8 unsigned char
#endif


/**
 * MASK has already shifted and offseted.
 * For data which is more than 8 byte, SHIFT indicate how to cut the date into half.
 * OFFSET is the position starting to put data from the MSB of bit-reversed byte.
**/

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
    BIRGHTNESS_MASK = 0x03,
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
    WIND_SPEED_MASK = 0xE0,

    FUNCTION_BYTE = 26,
};

enum {
    SCHEDULE_EVERY_DAY = 0x01,
    SCHEDULE_SLEEP = 0x02,
    SCHEDULE_OPEN = 0x04,
    SCHEDULE_CLOSE = 0x08,
    SCHEDULE_BYTE = 24,
    SCHEDULE_MASK = 0x0F,  // No need to use

    SCHEDULE_SLEEP_LOW_BYTE = 16,
    SCHEDULE_SLEEP_LOW_MASK = 0xFF,
    SCHEDULE_SLEEP_HIGH_BYTE = 18,
    SCHEDULE_SLEEP_HIGH_MASK = 0xE0,

    SCHEDULE_CLOSE_LOW_BYTE = 18,
    SCHEDULE_CLOSE_LOW_MASK = 0x0E,
    SCHEDULE_CLOSE_LOW_OFFSET = 4,
    SCHEDULE_CLOSE_HIGH_BYTE = 20,
    SCHEDULE_CLOSE_HIGH_MASK = 0xFF,
    SCHEDULE_CLOSE_HIGH_SHIFT = 3,

    SCHEDULE_OPEN_LOW_BYTE = 22,
    SCHEDULE_OPEN_LOW_MASK = 0xFF,
    SCHEDULE_OPEN_HIGH_BYTE = 24,
    SCHEDULE_OPEN_HIGH_MASK = 0xE0,
};

enum {
    POWER_ON = 0x8F,
    POWER_OFF = 0x87,

    POWER_BYTE = 28,
    POWER_MASK = 0xFF,
};

enum {
    TEMPERATURE_MASK = 0xFF,  // 3F
    TEMPERATURE_OFFSET = 2,
    TEMPERATURE_BYTE = 14,

    TEMPERATURE_AUTO_0 = 4,
};


enum {
    DATA_MONTH_BYTE = 30,
    DATA_MONTH_MASK = 0xFF,
    DATA_DAY_BYTE = 32,
    DATA_DAY_MASK = 0xFF,
    TIME_HIGH_BYTE = 40,
    TIME_HIGH_MASK = 0xFF,
    TIME_LOW_BYTE = 42,
    TIME_LOW_MASK = 0xFF,
};
    

struct HitachiAC {
    uint8 unknown[8];
    uint8 unknown1;  // 10
    uint8 unknown1i;  // 11
    uint8 keypad;  // 12
    uint8 keypadi;  // 13
    uint8 temperature;  // 14
    uint8 temperaturei;  // 15
    uint8 scheduleSleepL;  // 16
    uint8 scheduleSleepLi;  // 17
    uint8 scheduleSleepHCloseL;  // 18  Count down
    uint8 scheduleSleepHCloseLi;  // 19
    uint8 scheduleCloseH;  // 20
    uint8 scheduleCloseHi;  // 21
    uint8 scheduleOpenL;  // 22  Count down
    uint8 scheduleOpenLi;  // 23
    uint8 scheduleOpenH;  // 24 With other Flags
    uint8 scheduleOpenHi;  // 25
    uint8 function;  // 26
    uint8 functioni;  // 27
    uint8 power;  // 28
    uint8 poweri;  // 29
    uint8 day;  // 30
    uint8 dayi;  // 31
    uint8 month;  // 32
    uint8 monthi;  // 33
    uint8 unknown2;  // 34  0x01
    uint8 unknown2i;  // 35  0xFE
    uint8 windLR;  // 36
    uint8 windLRi;  // 37
    uint8 wbm;  // 38  Only control swinging or not.  Can't specify an angel.
    uint8 wbmi;  // 39
    uint8 timeH;  // 40  TOTAL 11bits.  The minutes of a day
    uint8 timeHi;  // 41
    uint8 timeL;  // 42
    uint8 timeLi;  // 43
};

union HitachiACUnion {
    uint8 data[43];
    struct HitachiAC code;

    HitachiACUnion();

    int setFunction(uint8 function);
    void setTemperature(uint8 degree);
    void setWindLR(uint8 lr);
    void setWindUD(uint8 ud);
    void setWindSpeed(uint8 ws);
    void setBrightness(uint8 brightness);
    void setKeepMoisture(uint8 km);
    void setMouldProof(uint8 mp);
    void setPowerReturn(uint8 pr);
    void cleanAllSchedule();
    int setSleep(int hour, int min);
    int setClose(int hour, int min);
    int setOpen(int hour, int min);
    void setPower(bool on);

    /**
     * After modify all the bytes (except the date & time).  Call this to send.
     * send() will not verify all byte's consistence. Please be careful.
    **/
    int send();

    /**
     * Create a HitachiACUnion by a template.
    **/
    void copyFrom(HitachiACUnion temp);

    /**
     * Set the date & time by system time.
    **/
    void updateCurrentTime();

    /**
     * Set the date.  Used by send().
    **/
    int setDate(int month, int day);

    /**
     * Set the current time.  Used by send().
    **/
    int setTime(int hour, int min);

    // Only can set one byte. Do data bit reverse inside.  Used for data in integer.
    void setReverse(int byteIdx, uint8 bitmask, uint8 out, int offset = 0);
    void set(int byteIdx, uint8 bitmask, uint8 out);


    // bitreverse do MSB->LSB.  For example 10011111 -> 11111001
    uint8 bitReverse(register uint8 x) {
        x = (((x & 0xaa) >> 1) | ((x & 0x55) << 1));
        x = (((x & 0xcc) >> 2) | ((x & 0x33) << 2));
        return((x >> 4) | (x << 4));
    }
};

#endif  // HITACHI_AC_H
