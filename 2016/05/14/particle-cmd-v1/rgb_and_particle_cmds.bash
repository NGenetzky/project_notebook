
trap 'echo ">> $BASH_COMMAND"' DEBUG

# Compile device Matt
particle flash Matt main.ino global.h global.cpp cmd/*.*h cmd/*.*cpp
particle flash Parker main.ino global.h global.cpp cmd/*.*h cmd/*.*cpp
# 15s is enough to flash device
sleep 20s

particle call Matt "do" "1" # Show the list of exposed commands
particle call Parker "do" "1" # Show the list of exposed commands
# Example published data:
# [(1,cmd_publish),(2,led_on),(3,led_off),(4,release),(5,white),(6,silver),
# (7,grey),(8,black),(9,red),(10,maroon),(11,yellow),(12,olive),(13,lime),(14,green)]

# Both respond to published events (with event name "do")
particle publish "do" "red" --private
sleep 2s

particle publish "do" "yellow" --private
sleep 2s

particle publish "do" "green" --private
sleep 2s

# The do function can be called with the uid of the command or the name of the command.
particle call Matt "do" "2" # Main LED on
particle call Parker "do" "led_on" # Main LED on
sleep 2s

particle call Matt "do" "5" # white
particle call Parker "do" "white" # white
sleep 2s

particle call Matt "do" "9" # red
particle call Parker "do" "red" # red
sleep 2s

particle call Matt "do" "11" # yellow
particle call Parker "do" "yellow" # yellow
sleep 2s

particle call Matt "do" "13" # lime
particle call Parker "do" "lime" # lime
sleep 2s

particle call Matt "do" "15" # aqua
particle call Parker "do" "aqua" # aqua
sleep 2s

particle call Matt "do" "17" # blue
particle call Parker "do" "blue" # blue
sleep 2s

particle call Matt "do" "19" # fuchsia
particle call Parker "do" "fuchsia" # fuchsia
sleep 2s

particle call Matt "do" "4" # release
particle call Parker "do" "release" # release
sleep 2s

particle call Matt "do" "3" # Main LED off
particle call Parker "do" "led_off" # Main LED off