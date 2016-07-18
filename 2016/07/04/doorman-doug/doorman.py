#!/usr/bin/env python 

from spyrk import SparkCloud as ParticleCloud  # Setup Particle Library
import RPi.GPIO as GPIO  # Setup Pi libraries # import RPi.GPIO module    
import sys
import time  # for time.sleep(sec)
# Define Pins or other Constants

# Get runtime variables
ACCESS_TOKEN = os.environ['HOME']



class PI_Helper(object):
    PIN_MODES = [GPIO.IN, GPIO.OUT, GPIO.SPI, GPIO.I2C, GPIO.HARD_PWM, GPIO.SERIAL, GPIO.UNKNOWN]
    def __init__(self):
        self.BTN = 19
        self.DOOR = 7
        self.LED = 0
        btn = {'name':'btn', 'pin':self.BTN, 'last_state':None}
        door = {'name':'door', 'pin':self.DOOR, 'last_state':None}
        led = {'name':'led', 'pin':self.LED, 'last_state':None}
        self.pin = {str(self.BTN):btn, str(self.DOOR):door, str(self.LED):led}

    def on_door_change(self, state):
        if state == 1:
            print('Door opened')
            matt.command('doug/door/open')
        elif state == 0:
            print('Door closed')
            matt.command('doug/door/close')

    def output(self, pin, value):
        self.pin[str(pin)] = value
        GPIO.output(pin, value)
        
    def input(self, pin):
        newval = GPIO.input(pin)
        if(newval != self.pin[str(pin)]):
            time.sleep(0.1)
            if(newval != self.pin[str(pin)]):
                self.on_change(pin, newval)
                self.pin[str(pin)] = newval
        return self.pin[str(pin)]
    
    def on_change(self, pin, value):
        if(pin==self.DOOR):
            self.on_door_change(value)
        
        

def setup_particle():
    global matt
    #Particle Setup
    particle = ParticleCloud(ACCESS_TOKEN)
    matt = particle.Matt
    # parker = particle.Parker
    # comrad = particle.Comrad
    matt.command('doug/on')

def setup_gpio():
    GPIO.cleanup()  # returning all channels you have used back to inputs with no pull up/down
    # PI/GPIO Setup
    # choose BOARD or BCM  
    GPIO.setmode(GPIO.BCM)               # BCM for GPIO numbering  
    # GPIO.setmode(GPIO.BOARD)             # BOARD for P1 pin numbering  
    
    # Set up Inputs  
    GPIO.setup(pi.BTN, GPIO.IN)     # set port/pin as an input  
    
    GPIO.setup(pi.DOOR, GPIO.IN,  pull_up_down=GPIO.PUD_UP)   # input with pull-up   
    
    # Set up Outputs  
    GPIO.setup(pi.LED, GPIO.OUT, initial=1)    # set initial value option (1 or 0) 

# Sets up pins as outputs
def setup():
    setup_gpio()
    setup_particle()

def while_loop():
    door_is_open = pi.input(pi.DOOR) 
    if(door_is_open == 1):
        pi.output(pi.LED, 1)
    elif(door_is_open == 0):
        pi.output(pi.LED, 0)

def ping():
    print('waiting...')

if __name__ == '__main__':
    pi = PI_Helper()
    setup()
    
    try:
        while True:
            while_loop()
    # Stop on Ctrl+C and clean up
    except KeyboardInterrupt:
        #GPIO.cleanup()
        sys.exit(0)
    finally:
        pass
        #GPIO.cleanup()
        #matt.command('doug_off')
