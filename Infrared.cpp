#!/usr/bin/env python
import RPi.GPIO as GPIO

ObstaclePin = 11

def setup():
	GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
	GPIO.setup(ObstaclePin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def loop():
	while True:
		if (0 == GPIO.input(ObstaclePin)):	#当检测到障碍物时，输出低电平信号
			print "Detected Barrier!"	
		else :
			print "****Nothing!******"
			

def destroy():
	GPIO.cleanup()                     # Release resource

if __name__ == '__main__':     # Program start from here
	setup()
	try:
		loop()
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()
