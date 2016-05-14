#ifndef CMD_H
#define CMD_H

#include "application.h"
#include "global.h"

extern void error(int error_id);

int ndef(); // Used in the struct initilizer.
struct Cmd {
    int uid;
    char const *name; // Characters are immutable. The pointer is mutable. 
    int (*f) (void);
    
    // Do these constructors automatiically get moved to cpp?
    Cmd():uid(-1),name("ndef"), f(ndef) { }
    Cmd(int i, char const *c, int (*f) (void)):uid(i),name(c), f(f) { }
};

//Functions
int cmd_setup();
int do_function(String args);
void do_handler(const char *topic, const char *data);

// interacting with the Cmd struct
int cmd_set(int i, char const * s, int (*f) (void) );
Cmd* cmd_get(int uid);
Cmd* cmd_get(String name);
int execute(Cmd * cmd_ptr);
int execute(int uid);

int cmd_publish();

// Default Commands
// int pub_thingspeak();
// int read_pins();
// int pub_dweet();

#endif // CMD_H