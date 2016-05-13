
#define BOARD_LED D7
#define I2C_BUFFER_SIZE 32
#define I2C_NO_ADDRESS -1

volatile byte I2C_in_buffer[I2C_BUFFER_SIZE+1];
byte I2C_out_buffer[I2C_BUFFER_SIZE];

int bytes_on_request = 1; // default will be single byte
int I2C_address = 0x02;
int I2C_target = 2;

int board_led_state = 0;
bool I2C_new_data = false;
char I2C_data[64];//arbitrary length
char I2C_slaves[40]; // 10 address array * 4 char max.
long timestamp;

/* This function is called once at start up ----------------------------------*/
void setup(){
    pinMode(BOARD_LED, OUTPUT); //INPUT, INPUT_PULLUP, INPUT_PULLDOWN or OUTPUT
     
    setup_particle();
    
    I2C_setup_slave(I2C_address);
}
void setup_particle(){
    Particle.variable("bytes_on_req", bytes_on_request);
    Particle.variable("i2c_address", I2C_address);
    Particle.variable("i2c_target", I2C_target);
    Particle.variable("i2c_data", I2C_data);
    Particle.variable("i2c_slaves", I2C_slaves);

    // The command should be one of the specific strings or an integer.
    Particle.function("i2c", I2C_function);

    // The command should be string less than 32 characters.
    Particle.function("send", I2C_send);
    
    // The command should be the integer of the slave to request from. 7 bit address.
    Particle.function("target", I2C_set_target);
}

/* This function loops forever -----------------------------------------------*/
void loop(){
    if(I2C_new_data){
        //I2C_in_buffer[I2C_BUFFER_SIZE] = '\0'; // Terminate c string.
        sprintf(I2C_data, "%s", I2C_in_buffer);
        Particle.publish("I2C_DATA", I2C_data);
        I2C_new_data = false;
    }
    
    timestamp = millis();
    board_led_state = timestamp % 2;
    digitalWrite(BOARD_LED, board_led_state);
    delay(500);
}

void event_handler(const char *topic, const char *data){
    
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
        
    } else if (strcmp(cmd, "request")==0) {
        return I2C_request(I2C_target);
    } else if(number_cmd != 0){
        I2C_setup_slave(number_cmd);
        return 0;
    } else{
        return -1;
    }
}

int I2C_send(String cmd){
    int error_code;
    int len = cmd.length();
    if(len < I2C_BUFFER_SIZE){
        cmd.getBytes(I2C_out_buffer, len);

        Wire.beginTransmission(I2C_target); // transmit to slave device
        Wire.write(I2C_out_buffer, len);

        error_code = Wire.endTransmission();    // stop transmitting
        I2C_end_transmission_debug(error_code);
        return error_code;
    } else {
        Particle.publish("I2C_send","String too long.");
        return -1;
    }
}

int I2C_request(int slave_address){
    int n_bytes = Wire.requestFrom(slave_address, bytes_on_request);  // if request succeeded
    if (n_bytes)
    {
        for (byte i = 0; i < n_bytes; i++){
            I2C_in_buffer[i] = Wire.read();
        }
        I2C_new_data = true;
    } else {
        Particle.publish("I2C", "Request Failed");
        // failure ... maybe slave wasn't ready or not connected
    }
    return n_bytes;
}

int I2C_scan(){
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

int I2C_set_target(String cmd){
    I2C_target = cmd.toInt();
    return 0;
}
void I2C_setup_master(){
    if ( Wire.isEnabled() ) {
        Wire.end();
    }
    
    Particle.publish("I2C","begin(Master)");
    Wire.begin();
}
void I2C_setup_slave(int address){
    if ( Wire.isEnabled() ) {
        //Particle.publish("I2C_function","I2C already enabled.");
        Wire.end();
    }
    I2C_address = address;
    Particle.publish("I2C",String("begin("+String(I2C_address)+")"));

    Wire.begin(address);                  // join i2c bus
    Wire.onReceive(I2C_on_receive);   // register event
    Wire.onRequest(I2C_on_request);   // register event
}

// function registered with Wire.onReceive()
// Note that receive event is called from an Interrupt Service Routine (ISR)!
void I2C_on_receive(int bytesReceived){
    for (byte i = 0; i < bytesReceived; i++)
    {
        I2C_in_buffer [i] = Wire.read();
    }
    if(Wire.available()){ // ERROR
        I2C_in_buffer [0] = '!';
    }
    I2C_new_data = true;
}

// function registered with Wire.onRequest()
// Note that request event is called from an Interrupt Service Routine (ISR).
// You can only do one Wire.write in a request event.
void I2C_on_request(){
    byte buf [] = {'S'};
    Wire.write (buf, 1);   // send response
}

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