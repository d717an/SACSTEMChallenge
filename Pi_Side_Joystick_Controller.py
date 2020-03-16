#!/usr/bin/env python3
import serial
import time
import pygame
from time import sleep

if __name__ == '__main__':
    pygame.init()
    clock = pygame.time.Clock()
    pygame.joystick.init()
    ser = serial.Serial('/dev/ttyACM0', 115200,  timeout = 1)
    pygame.joystick.init()
    pygame.joystick.get_count()
#     ser.flush()
    while True:
         pygame.event.get()
         joystick = pygame.joystick.Joystick(0)
         joystick.init()
         axis = (str(joystick.get_axis(0)) + "X" + str(joystick.get_axis(1))).encode()
         ser.write(axis+"\n".encode())
         line = ser.readline().decode('ascii').rstrip()
         #print(line)
         #pygame.time.delay(10)
         #print(axis)
         
#         joystick_count = pygame.joystick.get_count()
#         for i in range(joystick_count):
#             joystick = pygame.joystick.Joystick(i)
#             joystick.init()
#             axes = joystick.get_numaxes()
#             for i in range(axes):
#                 axis = str(joystick.get_axis(i)).encode()
#                 #print(axis)
#                 ser.write(axis+"\n".encode())
#                 #ser.readline()
#                 #ser.reset_output_buffer()
#                 #ser.readline()
#                 line = ser.readline().decode('utf-8').rstrip()
#                 #clock.tick(5)
#                 print(line)
         clock.tick(10)
  


