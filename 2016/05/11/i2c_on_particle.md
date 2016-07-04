---
title:  "I2C on Particle"
tags:
  - Particle
  - I2C
  - cpp
  - code_review
  - project_notebook
date: 2016-05-11
published: true

author: Nathan Genetzky

layout: single
---

Discussion about code development on I2C module for Particle

## Existing I2C code

### 1st Attempt on I2C module [**A1**](#f1)
My first attempt was all contained in a single **"main.ino"**. While this worked
it was very ugly and did not encapsulate the i2c functions.

#### main.ino
Uses an array for data recieved from i2c and for data meant to be sent out on
i2c. The board led will flash at a regular interval so that the user knows the
program is running.

#### example.bash
Will have Matt send a string to Parker over i2c. Then will request data from
Parker.

#### Exposed API
```
  Variables:
    bytes_on_req (int32)
    i2c_address (int32)
    i2c_target (int32)
    i2c_data (string)
    i2c_slaves (string)
  Functions:
    int i2c(String args) 
    int send(String args) 
    int target(String args)
```

#### Circuit
For now I won't go into much detail. There are three nodes . Below describes what
is attached to each. I used R1=R2=2.2 kOhms.

```
{
    "nodes":["3V3", "I2C_DATA", "I2C_CLK"],
    "connections":[
        "3V3=Parker.3V3=R1+=R2+",
        "I2C_DATA=Parker.D0=Matt.D0=R1-",
        "I2C_CLK=Parker.D1=Matt.D1=R2-"
        ]
}
```

###  2nd Attempt  on I2C module [**A2**](#f2)
Next I split the major functions into **i2c\_particle.h** & **i2c\_particle.cpp** files.

#### main.ino
The *loop* in this file would execute a function based on a variable **sys**.
The function would then a segment of code based on another variable **state**.
The idea was to provide a way to implement separate [FSM][1] as each of the
functions and then provide a method to switch the system. This method
worked to implement multiple systems in one code base; however, it was overly
complex.

#### i2c\_particle (.h/.cpp)
This implementation relied on a ringbuffer that was defined as static voltile
within the cpp file. Any data recieved was send to the buffer. There were functions
to allow the buffer to be **published** or to be send out via i2c.

#### example.bash
I wrote a simple bash script that that demonstrated the functionality. *Matt* will
send a message to *Parker*, which will then publish that message.

#### Circuit
Same circuit as was used for [A1](#A1).

#### Exposed API
```
  Variables:
    state (int32)
    sys (int32)
    ms_per_loop (int32)
    wreg (string)
    my_address (int32)
    target (int32)
  Functions:
    int set_wreg(String args) 
    int act(String args) 
    int i2c(String args) 
```

#### Errors / TODO

Currently there is an error created in the example that I can not explain. I do
not intend to fix it in this code, but rather avoid it in the new revision.

## New I2C code

I am currently working on a new set of files to work with i2c. They are part of
a larger project. The description of the project will take some time and therefore
will be left for later. 

## Learned
1. I learned an easy way check if one string (cmd) starts with another ("target").

```c++
// Will check if cmd starts with "target"
if (strncmp(cmd, "target", strlen("target"))==0) {}
```

2. How to echo commands executed in Bash.

```bash
# Shows the commands as they are executed. ">> " appears before command.
trap 'echo ">> $BASH_COMMAND"' DEBUG
```

## Projects

particle-i2c-a1 <b id="f1">A1</b>
- [main.ino][a1_main]
- [example.bash][a1_example]

particle-i2c-a2 <b id="f2">A2</b>
- [main.ino][a2_main]
- [example.bash][a2_example]
- [main.ino][a2_main]
- [i2c_particle.h][a2_i2c_particle_h]
- [i2c_particle.cpp][a2_i2c_particle_cpp]

[1]: https://en.wikipedia.org/wiki/Finite-state_machine
[a1_main]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a1/main.ino
[a1_example]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a1/example.bash
[a2_main]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a2/main.ino
[a2_i2c_particle_h]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a2/i2c_particle.h
[a2_i2c_particle_cpp]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a2/i2c_particle.cpp
[a2_example]: https://github.com/NGenetzky/project_notebook/blob/7e33bf62132e712c3f3e59e0c9224ed824f2f3c4/2016/05/11/particle-i2c-a2/example.bash
