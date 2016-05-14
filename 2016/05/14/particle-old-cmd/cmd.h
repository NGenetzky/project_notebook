#ifndef CMD_H
#define CMD_H

#include "application.h"
#include "global.h"
#define BOARD_LED D7

namespace CMD{
    // Prevents the cmd constants from poluting the global namespace
    enum Enum {LED_ON=1, LED_OFF=2, PUB_THINGSPEAK=3, READ_PINS=4, PUB_DWEET=5,
        COLOR_LED=6, MAX=7};
}

static char const * const cmds[] = {[0]="",
    [CMD::LED_ON]="led_on",
    [CMD::LED_OFF]="led_off",
    [CMD::PUB_THINGSPEAK]="ts",
    [CMD::READ_PINS]="read",
    [CMD::PUB_DWEET]="dweet",
    [CMD::COLOR_LED]="color_led",
    [CMD::MAX]="invalid"
    };
    
int cmd_setup();
int cmd_lookup(String cmd);
int do_function(String args);
void do_handler(const char *topic, const char *data);
int do_int(int cmd);

// Sample Commands
int ndef();
int led_on();
int led_off();
int pub_thingspeak();
int read_pins();
int pub_dweet();
int color_led();

// Default function pointers assigned for commands.
// ndef means that the function is not implemented.
typedef int (*command_fptr) ( void );
static command_fptr cmdf[] = {[0]=ndef,
    [CMD::LED_ON]=led_on,
    [CMD::LED_OFF]=led_off,
    [CMD::PUB_THINGSPEAK]=pub_thingspeak,
    [CMD::READ_PINS]=read_pins,
    [CMD::PUB_DWEET]=pub_dweet,
    [CMD::COLOR_LED]=color_led,
    [CMD::MAX]=ndef
};

#endif // CMD_H