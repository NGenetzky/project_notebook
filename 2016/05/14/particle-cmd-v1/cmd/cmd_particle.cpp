
#include "application.h"
#include "cmd_particle.h"

#include "global.h"
#include "cmd.h"

int cmd_particle_init(){
    cmd_set(2, "led_on", led_on);
    cmd_set(3, "led_off", led_off);
    return 2;
}

int led_on(){
    digitalWrite(BOARD_LED, HIGH);
    return 0;
}

int led_off(){
    digitalWrite(BOARD_LED, LOW);
    return 0;
}
