//File includes
#include "i2c_particle.h"


char I2C_slaves[40]; // 10 address array * 4 char max.
int my_address=2, target=2;

int I2C_init(){
    Particle.variable("my_address", my_address);
    Particle.variable("target", target);
    
    Particle.function("i2c", I2C_function);
    
    // bool success = Particle.subscribe("i2c_", I2C_event_handler);
    // if( !success ){
    //     Particle.publish("I2C","Subscribe failed");
    // }
    // return success;
    return 0;
}

int I2C_function(String cmd){
    // If no valid conversion could be performed because the string doesn't
    // start with a integral number, a zero is returned.
    int number_cmd = cmd.toInt(); 

    if (strcmp(cmd, "master")==0) {
        I2C_setup_master();
        return 0;
        
    } else if (strcmp(cmd, "scan")==0) {
        return I2C_scan();
        
    } else if (strncmp(cmd, "target", strlen("target"))==0) { // Simplies way to say "starts with".
        target = wreg.toInt();
        return target;
        
    } else if (strcmp(cmd, "request")==0) {
        return I2C_request();
        
    } else if (strcmp(cmd, "send")==0) {
        // The command should be string less than 32 characters.
        return I2C_send();
        
    } else if (strcmp(cmd, "my_address")==0) {
        my_address = wreg.toInt();
        return my_address;
        
    } else if (strcmp(cmd, "slave")==0) {
        return I2C_setup_slave();
        
    } else if (strcmp(cmd, "ringbuffer")==0) {
        ringbuffer_publish();
        return 0;
        
    } else if(number_cmd != 0){
        return -3;
    } else {
        return -1;
    }
}

// Event entry points
// void I2C_event_handler(const char *topic, const char *data){
//     // Every event should start with "i2c_"
//     char debug[100];
//     sprintf(debug, "%s-%s", topic, data);
//     Particle.publish("i2c", debug);
    
//     if (strcmp(topic,"i2c_master")==0) {
//         I2C_setup_master();
//     } else if (strcmp(topic,"i2c_scan")==0) {
//         I2C_scan();   
//     } else{
//         Particle.publish("i2c_scan","");
//     }
// }

// Setup functions
int I2C_setup_master(){
    if ( Wire.isEnabled() ) {
        Wire.end();
        Particle.publish("I2C","reset;begin(Master)");
    } else{
        Particle.publish("I2C","begin(Master)");
    }
    Wire.begin();
    return 0;
}

// Helper functions
// Public: I2C_slaves: String that contains list of all connected slaved.
int I2C_scan(){
    if ( !Wire.isEnabled() ) {
        I2C_setup_master();
    }
    
    int error;
    int slaves[10]= {0}; int i_slaves=0;
    
    for(int address = 1; address < 127; address++ ){
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        if(error==0){ // Ack from slave
            slaves[i_slaves] = address;
            i_slaves++;
        }
    }

    if(i_slaves==0){
        Particle.publish("I2C_scan", "No Slaves found");
    } else{
        sprintf(I2C_slaves, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                slaves[0], slaves[1], slaves[2], slaves[3], slaves[4],
                slaves[5], slaves[6], slaves[7], slaves[8], slaves[9]);
        Particle.publish("I2C_scan", I2C_slaves); 
    }
    return i_slaves;
}

int I2C_send(){
    byte out_buffer[32];
    
    int error_code;
    int len = wreg.length()+1;
    
    if(len < 32){
        wreg.getBytes(out_buffer, len);

        Wire.beginTransmission(target); // transmit to slave device
        Wire.write(out_buffer, len);

        error_code = Wire.endTransmission();    // stop transmitting
        I2C_end_transmission_debug(error_code);
        return error_code;
    } else {
        Particle.publish("I2C_send","String too long.");
        return -1;
    }
}

#define I2C_REQUEST_LENGTH 1
int I2C_request(){
    char requested_data[I2C_REQUEST_LENGTH]; 
    int n_bytes = Wire.requestFrom(target, 1);  // if request succeeded
    if (n_bytes)
    {
        for (byte i = 0; i < n_bytes; i++){
            requested_data[i] = Wire.read();
        }
        Particle.publish("I2C-Request", requested_data);
    } else {
        Particle.publish("I2C", "Request Failed");
        // failure ... maybe slave wasn't ready or not connected
    }
    return n_bytes;
}

// Slave functions
int I2C_setup_slave(){
    if ( Wire.isEnabled() ) {
        Wire.end();
        Particle.publish("I2C",String("reset;begin("+String(my_address)+")"));
    } else{
        Particle.publish("I2C",String("begin("+String(my_address)+")"));
    }

    Wire.begin(my_address);                  // join i2c bus
    
    return my_address;
}

void I2C_on_receive_to_ringbuffer(int bytesReceived){
    while(Wire.available()){
        ringbuffer_put(Wire.read());
    }
}

// Debug related
void I2C_end_transmission_debug(int ret_code){
  char error_string[65];
  switch(ret_code){
    case 0: sprintf(error_string,"0: success"); break;
    case 1: sprintf(error_string,"1: busy timeout upon entering endTransmission()"); break;
    case 2: sprintf(error_string,"2: START bit generation timeout"); break;
    case 3: sprintf(error_string,"3: end of address transmission timeout"); break;
    case 4: sprintf(error_string,"4: data byte transfer timeout"); break;
    case 5: sprintf(error_string,"5: data byte transfer succeeded, busy timeout immediately after"); break;
  }
  if(ret_code != 0){
    Particle.publish("I2C_END_TRANSMISSION", error_string);
  }
}

#ifdef RINGBUFFER
    const int ringbuffer_SIZE = 32;
    static volatile unsigned int ringbuffer_iread = 0;
    static volatile unsigned int ringbuffer_iwrite = 0;
    static volatile char ringbuffer_array[ringbuffer_SIZE];
#endif // RINGBUFFER

#ifdef RINGBUFFER
    int ringbuffer_is_empty(){
        return (ringbuffer_iread == ringbuffer_iwrite);
    }
    
    void ringbuffer_clear(){
        ringbuffer_iread = ringbuffer_iwrite;
    }
    
    void ringbuffer_put(unsigned data){
        //in your ISR
        ringbuffer_array[ringbuffer_iwrite] = data;
        ringbuffer_iwrite = (ringbuffer_iwrite+1) % ringbuffer_SIZE;
    }
    
    int ringbuffer_get(){
        char value;
        if (ringbuffer_iread != ringbuffer_iwrite) {
            value = ringbuffer_array[ringbuffer_iread];
            ringbuffer_iread = (ringbuffer_iread+1) % ringbuffer_SIZE;
            return value;
        } else
            return -1;
    }
    
    void ringbuffer_publish(){
        char carray[ringbuffer_SIZE];
        for(int i=0; !ringbuffer_is_empty(); i++){
            carray[i] = ringbuffer_get();
        }
        
        Particle.publish("ringbuffer", carray);
    }
    
    void ringbuffer_to_i2c(){
        Wire.beginTransmission(target); // transmit to slave device
        char data = ringbuffer_get();   
        Wire.write(data);
        Wire.endTransmission(target); // transmit to slave device
    }
#endif // RINGBUFFER