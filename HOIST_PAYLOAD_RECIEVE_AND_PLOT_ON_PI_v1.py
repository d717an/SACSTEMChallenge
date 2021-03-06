#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Example program to receive packets from the radio link
#
## CONFIGURATION:
#RASPBERRY PI  <>  NRF24L01+
#3.3V              3v3
#GND (pin6)        GND
#GPIO4             CE
#GPIO8 (SPI CE0)   CSN
#GPIO11(SPI SCLK)  SCK
#GPIO10(SPI MOSI)  MOSI
#GPIO9 (SPI MISO)  MISO
#                  IRQ (n/a)

import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
from lib_nrf24 import NRF24
import time
import spidev
import numpy as np
import matplotlib.pyplot as plt
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from struct import *
from drawnow import drawnow
def make_fig():
    plt.plot(x,y)
   
    
app = QtGui.QApplication([])
p = pg.plot()
p.setWindowTitle('live')
curve = p.plot()

plt.ion()
fig= plt.figure()    

x_vec = np.linspace(0,99,100)
ax_y_vec = np.zeros(len(x_vec))
ay_y_vec = np.zeros(len(x_vec))
az_y_vec = np.zeros(len(x_vec))
line1=[]
line2=[]
line3=[]
a_x = 0
a_y = 0
a_z = 0
temp = 0
g_z = 0
g_y = 0
g_z = 0
pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xF0, 0xF0, 0xF0, 0xF0, 0xe1]]
radio2 = NRF24(GPIO, spidev.SpiDev())
radio2.begin(0, 4)

radio2.setRetries(15,15)

radio2.setPayloadSize(32)
radio2.setChannel(76)
radio2.setDataRate(NRF24.BR_2MBPS)
radio2.setPALevel(NRF24.PA_MIN)

radio2.setAutoAck(True)
radio2.enableDynamicPayloads()
radio2.enableAckPayload()

radio2.openWritingPipe(pipes[0])
radio2.openReadingPipe(1, pipes[1])

radio2.startListening()
radio2.stopListening()
radio2.powerUp()

radio2.printDetails()

radio2.startListening()

time.sleep(1)
x=list()
y=list()
i=0

while True:
    recv_buffer = []
    pre_buffer = []
    accel_x_buff = []
    accel_y_buff = []
    accel_z_buff = []
    accel_buff = []
    message = ""
    accel_x = ""
    accel_y = ""
    accel_z = ""
    pipe = [0]
    while not radio2.available(pipe):
        time.sleep(10000/1000000.0)
#    radio2.read(pre_buffer, radio2.getDynamicPayloadSize())   
    radio2.read(recv_buffer, radio2.getDynamicPayloadSize())
#    print(recv_buffer)
#    if chr(recv_buffer[0]) == 'x':
#        for n in message:
#            accel_x += n
#        accel_buff.append(accel_x)
#    elif chr(recv_buffer[0]) == 'y':
#        for n in message:
#            accel_y +=n
#        accel_buff.append(accel_y)
#    elif chr(recv_buffer[0]) == 'z':
#        for n in message:
#            accel_z +=n
#        accel_buff.append(accel_z)   
#    for n in pre_buffer:
#        preamble += chr(n)
    if chr(recv_buffer[0]) == 'x':
        #accel_x_buff.append(accel_buff[1:].rstrip('\x00'))
        a_x = unpack('<f',bytes(recv_buffer[1:5]))[0]
    if chr(recv_buffer[5]) == 'y':
        #accel_y_buff.append(accel_buff[1:].rstrip('\x00'))
        a_y = unpack('<f',bytes(recv_buffer[6:10]))[0]
    if chr(recv_buffer[10]) == 'z':
        #accel_z_buff.append(accel_buff[1:].rstrip('\x00')
        a_z = unpack('<f',bytes(recv_buffer[11:15]))[0]
    if chr(recv_buffer[15]) == 'p':
        #accel_z_buff.append(accel_buff[1:].rstrip('\x00')
        g_x = unpack('<f',bytes(recv_buffer[16:20]))[0]
    if chr(recv_buffer[20]) == 'q':
        #accel_z_buff.append(accel_buff[1:].rstrip('\x00')
        g_y = unpack('<f',bytes(recv_buffer[21:25]))[0]
    if chr(recv_buffer[25]) == 'r':
        #accel_z_buff.append(accel_buff[1:].rstrip('\x00')
        g_z = unpack('<f',bytes(recv_buffer[26:30]))[0]
#    print(str(accel_buff[0][1:]).rstrip('\x00'))
    #print(float(str(message[0:3])));
#        x.append(i)
#    ax_y_vec[-1]= a_x

#    ay_y_vec[-1]= a_y
    
    #print(a_x)
    #print(g_z)
    x.append(i)
    y.append(g_x)
    curve.setData(y)
    app.processEvents()
    i = i+1
    
    #drawnow(make_fig)# setting pen=(i,3) automaticaly creates three different-colored pens
#    ax_y_vec = np.append(ax_y_vec[1:],0.0)
#    ay_y_vec = np.append(ay_y_vec[1:],0.0)
#    az_y_vec = np.append(az_y_vec[1:],0.0)

#    c = c + 1
#    if (c&1) == 0:
#        radio2.writeAckPayload(1, akpl_buf, len(akpl_buf))
##        print ("Loaded payload reply:"),
##        print (akpl_buf)
#    else:
#        pass
#        print ("(No return payload)")
