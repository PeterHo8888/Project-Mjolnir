#define __ASERT_USE_STDERR
#include <assert.h>
#include "sma.h"

#define RELAY_1 10
#define RELAY_2 5

enum ARM_DIR {
    CONTRACT = 0,
    RELEASE = 1,
    BANANA = 2
};

void write_arm(ARM_DIR dir)
{
    if (dir == BANANA) {
        digitalWrite(RELAY_1, LOW);
        digitalWrite(RELAY_2, LOW);
    } else {
        digitalWrite(RELAY_1, !dir);
        digitalWrite(RELAY_2, dir);
    }
}

void setup()
{
    pinMode(A0, INPUT);
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    write_arm(BANANA);

    Serial.begin(115200);

    sma_init(500, bell);
}

void bell(int x) {
    /*
       Serial.print("reached target at: ");
       Serial.println(x);
     */
}

void loop() {
    sma_push(analogRead(A0));

    int emg_avg = sma_avg();

    if (emg_avg == -1)
        write_arm(BANANA);
    else if (emg_avg < 250)
        write_arm(CONTRACT);
    else
        write_arm(RELEASE);

    Serial.println(emg_avg);
}

void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    abort();
}
