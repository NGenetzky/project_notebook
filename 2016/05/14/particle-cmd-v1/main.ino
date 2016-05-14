#include "global.h"
#include "cmd.h"
#include "cmd_particle.h"
#include "cmd_rgb.h"

enum Device {COMRAD=0, MATT=1, PARKER=2, NONE, UNKNOWN};
enum Device device;

void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    
    pinMode(D5, INPUT); // Declare as input for button.
    pinMode(D6, INPUT); // Declare as input for button.
    
    setup_particle();
    // I2C_setup();
    
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
        
    } else if(device == PARKER){
        
    } else{
        error(5);
    }
}

void setup_particle(){
    // Subscribe to general events
    cmd_setup(); // Adds the "do" function
    
    cmd_set(0, "ndef", ndef); // Default function defined for ndef commands.
    cmd_set(1, "cmd_publish", cmd_publish);
    
    cmd_particle_init();
    cmd_rgb_init();
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