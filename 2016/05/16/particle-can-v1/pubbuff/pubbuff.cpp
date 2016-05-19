#include "pubbuff.h"


const int PUBBUFF_SIZE = 1024;
char pub_name[12]={'\0'}; // Max size of event name is 12.
char pubbuffer[PUBBUFF_SIZE]={'\0'};

void pubbuff(const char * name, const char * data){
    if(strcmp(name, pub_name)==0){
        int new_len = strlen(pubbuffer) + strlen(data) + sizeof(char);
        if (new_len < PUBBUFF_SIZE){
            strcat(pubbuffer, data);
        } else {
            error(19);
        }
    } else{
        strcpy(pub_name, name);
        strcpy(pubbuffer, data);
    }
}

void pubbuff_poll(){
    if(0 < strlen(pubbuffer)){
        Particle.publish(pub_name, pubbuffer);
        strcpy(pubbuffer, ""); // Clear the C string without zeroing the buffer.
    }
}

