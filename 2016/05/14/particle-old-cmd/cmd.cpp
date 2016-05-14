#include "cmd.h"
#include "pub.h"
#include "var.h"
    // Requires error()

#define DO_FUNCTION 
#define DO_SUBSCRIBE 
    // Subscribe allows the command to be process by multiple photons.

int cmd_setup(){
    #ifdef DO_FUNCTION
        Particle.function("do", do_function);
    #endif
    #ifdef DO_SUBSCRIBE
        bool success = Particle.subscribe("do", do_handler, MY_DEVICES); // Requires --private flag.
        if( !success ){ error(1000); }
        return success;
    #endif
    
    return 0;
}

int cmd_lookup(String cmd){
    for(int i=0; i<CMD::MAX; i++){
        if (strcmp(cmd, cmds[i])==0) {
            return i;
        }
    }
    return -1;
}

int do_function(String args){
    int cmdid = args.toInt();
    if(cmdid != 0){
        return do_int(cmdid);
    }
    
    cmdid = cmd_lookup(args);
    if(cmdid != -1){
        return do_int(cmdid);
    }
    error(-1);
    return -1;
}

void do_handler(const char *topic, const char *data){
    if (strcmp(topic, "do")==0) {
        do_function(data);
    } else {
        error(9);
    }
}

int do_int(int cmd){
    if(CMD::MAX < cmd){
        error(7);
        return -2;
    }
    notify(String(cmds[cmd]));
    
    return cmdf[cmd]();
}

// Sample Commands -------------------------------------------------------------
int ndef(){
    error(-1);
    return -1;
}
int led_on(){
    digitalWrite(BOARD_LED, HIGH);
    return 0;
}

int led_off(){
    digitalWrite(BOARD_LED, LOW);
    return 0;
}

int pub_thingspeak(){
    read_pins();
    thingspeak();
    return 0;
}

int pub_dweet(){
    read_pins();
    dweet();
    return 0;
}

int read_pins(){
    //do not set the pinMode() with analogRead(). The pinMode() is automatically set to AN_INPUT the first time analogRead()
    double b = analogRead(A0) * ANALOG_RES; 
    double c = analogRead(A1) * ANALOG_RES;
    
    put_user_string(1, String(millis()));
    put_user_string(2, String(b));
    put_user_string(3, String(c));
    return 0;
}

int color_led(){
    union Tricolor {
        byte r,g,b;
        int v;
    };
    union Tricolor rgb;
    rgb.v=0;
    rgb.r=215;
    rgb.g=165;
    rgb.b=255;
    RGB.control(true);
    RGB.color(rgb.r, rgb.g, rgb.b);
    return rgb.v;
}