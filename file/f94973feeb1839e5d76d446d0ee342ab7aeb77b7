
// Defines for hardware
#define BOARD_LED D7

// Public Particle variables
int state=-1;
int sys =-1;
long time0=0;
long ms_per_loop=0;
String wreg;

//File includes
#include "i2c_particle.h"

#define STATE_RESET 100
#define STATE_START 1

#define SYS_IDLE 0
#define SYS_MASTER 1
#define SYS_SLAVE_PUBLISH 2
#define SYS_SLAVE_LISTEN 3

void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
    
    setup_particle();
    I2C_init();
    
    sys = SYS_IDLE;
    state = STATE_START;
}

void loop(){
    loop_system(sys);
    
    timeit();
}

void setup_particle(){
    Particle.variable("state", state);
    Particle.variable("sys", sys);
    Particle.variable("ms_per_loop", ms_per_loop);
    Particle.variable("wreg", wreg);
    
    // Store a string in WREG. Can be interpreted as a int or as string.
    Particle.function("set_wreg", set_wreg);
    Particle.function("act", act_function);
    
    // Subscribe to general events
    //Particle.subscribe("unique_event_name", myHandler, MY_DEVICES);
}


int act_function(String cmd){
    int intcmd = cmd.toInt();
    if(intcmd != 0){ // an int was at the begining of the string
        if(intcmd < 6){ // Start that system.
            sys = intcmd;
            state = STATE_RESET;
            return sys;
        }
    }
    
    if (strcmp(cmd, "SYS_IDLE")==0) {
        sys = SYS_IDLE;
        state = STATE_RESET;
        return sys;
    } else{
        return -1;
    }
}

void event_handler(const char *topic, const char *data){
    
}

int set_wreg(String value){
    wreg = value;
    return 0;
}

void timeit(){
    long temp_time = time0;
    time0 = micros();
    ms_per_loop = time0-temp_time;
}

int loop_system(int sys_id){
    if(state == STATE_RESET){
        
        state = STATE_START;
    } else{
        if(sys_id == SYS_IDLE){
            digitalWrite(BOARD_LED, millis() % 2);
            
        } else if(sys_id == SYS_MASTER){
            system1_SYS_MASTER();
            
        } else if(sys_id == SYS_SLAVE_PUBLISH){
            system2_SYS_SLAVE_PUBLISH();
            
        } else if(sys_id == SYS_SLAVE_LISTEN){
            system3_SYS_SLAVE_LISTEN();
            
        }
    }
    return -1;
}

void system1_SYS_MASTER(){
    if(state == STATE_START){
        I2C_setup_master();
        state = 2;
        
    } else if(state == 2){
        I2C_scan();
        state = 3;
        
    } else if(state == 3){
        for(int i=5; 0<i; i--){
            digitalWrite(BOARD_LED, HIGH);
            delay(1000);
            digitalWrite(BOARD_LED, LOW);
            delay(1000);
        }
        state = 2;
    }
}

void system2_SYS_SLAVE_PUBLISH(){
    if(state == STATE_START){
        I2C_setup_slave();
        Wire.onReceive(I2C_on_receive_to_ringbuffer);   // register event
        state = 2;
        
    } else if(state == 2){
        if( ringbuffer_is_empty() ){
            state = 3;    
        } else {
            ringbuffer_publish();
            ringbuffer_clear();
        }
    } else if(state == 3){
        digitalWrite(BOARD_LED, HIGH);
        delay(500);
        digitalWrite(BOARD_LED, LOW);
        delay(500);
        state = 2;
    }
}


void system3_SYS_SLAVE_LISTEN(){
    char data;
    
    if(state == STATE_START){
        I2C_setup_slave();
        Wire.onReceive(I2C_on_receive_to_ringbuffer);   // register event
        state = 2;
    
    } else if(state == 2){ // Receive data from ringbuffer
        if( ringbuffer_is_empty() ){
            state = 3;    
        } else {
            data = ringbuffer_get();
            if(data == '{'){ // Message start
                state = 4;
            } else if(data == '\0'){
                
            } else {
                Particle.publish("INVALID_CHAR", String(data));
                state = 2;
            }
        }
    } else if(state == 3){ // Delay
        delay(500);
        state = 2;
        
    } else if(state == 4){ // Interpret message and act
        
        data = ringbuffer_get();
        
        if(data == '0'){
            digitalWrite(BOARD_LED, LOW);
        } else if(data == '1'){
            digitalWrite(BOARD_LED, HIGH);
        } else if(data == '.'){
            delay(1000);
        } else if(data == '}'){
            state = STATE_START;
        } else {
            Particle.publish("INVALID_CHAR", String(data));
            state = -2;
        }
    } else if(state == -2){ // Invalid data
        state = 2;
    }
    
}