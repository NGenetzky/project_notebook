
trap 'echo ">> $BASH_COMMAND"' DEBUG

particle flash Matt main.ino
particle flash Parker main.ino

sleep 20s

particle call Matt i2c master # Set Matt as master. Return 0 on success

particle call Matt i2c scan # Finds available i2c devices
# Parker will not recieve any data.

# Ensure that Parker is set up to the address of Matt's target.
particle get Matt i2c_target
particle get Parker i2c_address

particle call Matt send "Hello Parker, are you ready? " # Bug in code is cutting off the last character.
particle get Parker i2c_data

# Parker will respond with "S" when data is requested

particle call Matt i2c request # Request data from Parker. Return 1 on success.
particle get Matt i2c_data # Display the data recieved from Parker.
