
# Shows the commands as they are executed.
trap 'echo ">> $BASH_COMMAND"' DEBUG

# Compile devices Matt and Parker
particle flash Parker main.ino i2c_particle.h i2c_particle.cpp
particle flash Matt main.ino i2c_particle.h i2c_particle.cpp
# 15s is enough to flash device
sleep 20s

particle call Parker act "2" #"SYS_SLAVE_PUBLISH" # Default slave address is 0x02
particle call Matt i2c "master" # Default target is 0x02
sleep 5s

# Check default values.
particle get Parker "my_address"
particle get Matt "target"

particle call Matt set_wreg "012312 default" # Default target address is 0x02
particle call Matt i2c "send" 
sleep 5s

# This section creates error: "3: end of address transmission timeout"
# This is because no slave is listening at 0x05

particle call Matt set_wreg "5" # Now target slave 0x05
particle call Matt i2c "target"
particle call Matt set_wreg "0123456789"
particle call Matt i2c "send"

# This section creates error: "2: START bit generation timeout"
# Unknown reason.

particle call Parker set_wreg "7" # Set slave address to 0x07
particle call Parker i2c "my_address"
particle call Parker i2c "slave"
sleep 5s

particle call Matt set_wreg "7" # Now target slave 0x07
particle call Matt i2c "target"
particle call Matt set_wreg "0123456789"
particle call Matt i2c "send" #error here
