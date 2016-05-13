#ifndef I2C_PARTICLE_H
#define I2C_PARTICLE_H

#include "application.h"

#define I2C_SYS1
#define I2C_SYS2
#define RINGBUFFER

extern String wreg; // main.ino

int I2C_init();
int I2C_function(String cmd);
void I2C_event_handler(const char *topic, const char *data);
int I2C_setup_master();
int I2C_scan();
int I2C_send();
int I2C_request();

int I2C_setup_slave();
void I2C_on_receive_to_ringbuffer(int bytesReceived);

void I2C_end_transmission_debug(int ret_code);
    
#ifdef RINGBUFFER
    int ringbuffer_is_empty();
    void ringbuffer_clear();
    void ringbuffer_put(unsigned data);
    int ringbuffer_get();
    void ringbuffer_publish();
    void ringbuffer_to_i2c();
#endif // RINGBUFFER
    
#endif /* I2C_PARTICLE_H */
