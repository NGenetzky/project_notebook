#include "cmd.h"

#define DO_FUNCTION 
#define DO_SUBSCRIBE 
    // Subscribe allows the command to be process by multiple photons.
    
const int CMDS_MAX_SIZE=25;
Cmd cmds[CMDS_MAX_SIZE];
    
int ndef(){
    Particle.publish("CMD","ndef");
    return -1;
}

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

// Exposed to end user
int do_function(String args){
    // If args is a number then will execute cmd that relates to that number.
    int cmdid = args.toInt();
    if(cmdid != 0){
        return execute(cmdid);
    }
    
    // Searches for command with name=args.
    return execute(cmd_get(args));
}

void do_handler(const char *topic, const char *data){
    if (strcmp(topic, "do")==0) {
        do_function(data);
    } else {
        error(9);
    }
}

// Exposed to other files.
int cmd_set(int i, const char *s, int (*f) (void) ){
    int uid = i;
    if(CMDS_MAX_SIZE < i){ // Check if its too large.
        return CMDS_MAX_SIZE;
    } else if(i < 0){ // Check if its negative.
        return -1;
    } else { // No Errors. Return the commmand.
        cmds[i].uid = uid;
        cmds[i].name = s;
        cmds[i].f = f;
        return 0;
    }
}
int execute(Cmd * cmd_ptr){
    return cmd_ptr->f();
}
int execute(int uid){
    Cmd * cmd_ptr = cmd_get(uid);
    return execute(cmd_ptr);
}

/// Private (ish)
Cmd* cmd_get(int uid){
    if(CMDS_MAX_SIZE < uid){ // Check if its too large.
        return &cmds[0];
    } else if(uid < 0){ // Check if its negative.
        return &cmds[0];
    } else { // No Errors. Return the commmand.
        return &cmds[uid];
    }
}
Cmd* cmd_get(String name){
    for(int i=0; i<CMDS_MAX_SIZE; i++){
        if (strcmp(name, cmds[i].name)==0) {
            return cmd_get(i);
        }
    }
    return cmd_get(0);
}

// Commands exported by this module.

int cmd_publish(){
    Cmd *c;
    // This is currently a problem. If it is too small stuff breaks.
    const int BUFF_LENGTH = 1000;
    char c_cmds[BUFF_LENGTH] = {};
    char prefix = '[';
    int len;
    
    for(int i=1; i<CMDS_MAX_SIZE; i++){
        len =strlen(c_cmds);
        if(BUFF_LENGTH < len){
            error(19);
            break;
        }
        c = cmd_get(i);
        sprintf(c_cmds + len,"%c(%d,%s)",prefix, c->uid, c->name);
        prefix=',';
    }
    sprintf(c_cmds + strlen(c_cmds),"]");
    
    Particle.publish("cmds=", c_cmds);
    return strlen(c_cmds);
}