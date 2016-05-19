#include "global.h"
#include "can.h"
#include "pubbuff.h"

enum Device {COMRAD=0, MATT=1, PARKER=2, NONE, UNKNOWN};
enum Device device;

Timer pubbuff_timer(2000, pubbuff_poll); //(period, callback, one_shot)

void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    
    setup_particle();
    CAN_setup();
    pubbuff_timer.start();
    
    // Device specific setup
    device = static_cast<enum Device>(id_device());
    if(device == MATT){
        
    } else if(device == PARKER){
        
    } else{
        error(5);
    }
}

// This routine gets called repeatedly, like once every 5-15 milliseconds.
// Spark firmware interleaves background CPU activity associated with WiFi + Cloud activity with your code. 
// Make sure none of your code delays or blocks for too long (like more than 5 seconds), or weird things can happen.
void loop(){
    
    // Device specific loop
    if(device == MATT){
        CAN_receive_asci();
        
    } else if(device == PARKER){
        CAN_receive_asci();
        
    } else{
        error(5);
    }
}


void setup_particle(){
}


int id_device(){
    char first_unique = System.deviceID().charAt(0);
    switch(first_unique){
        case '3':
            return MATT;
        case '4':
            return PARKER;
        case '5':
            return COMRAD;
        default:
            return UNKNOWN;
    }
}

void error(int error_id){
    Particle.publish("error", String(error_id));
}