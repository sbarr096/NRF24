import sys
import time
########################Modules Path Information################################
sys.path.append(“/home/pi/Desktop/ICBP_NRF24/modules”)
########################Modules Path Information################################
from lib_nrf24 import NRF24
import RPi.GPIO as GPIO
import Unpack
import spidev
import array


def radio_func(str = ""):
    rID = str
    #print "Starting"
    #print "Radio ID = " + rID
      
    GPIO.setmode (GPIO.BCM)
    GPIO.setwarnings(False)
    str = NRF24 (GPIO, spidev.SpiDev())

    start = time.time()
    #Send and receive addresses
    pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0XE1]]

    #begin radio and pass CSN to gpio (8/ce0) and CE to gpio 17
    str.begin(0,17)

    #Max bytes 32
    str.setPayloadSize(32)
    str.setChannel(0x76)
    str.setDataRate(NRF24.BR_1MBPS)
    str.setPALevel(NRF24.PA_MIN)
    str.setAutoAck(False)
    str.enableDynamicPayloads()
    str.enableAckPayload()
    str.openWritingPipe(pipes[0])
    
    time.sleep(1/5)    
    if (rID =="radio1"):
        str.openReadingPipe(1, [0xF0, 0xF0, 0xF0, 0xF0, 0xE1])
    time.sleep(1/5)
    if (rID == "radio2"):        
        str.openReadingPipe(1, [0xF0, 0xF0, 0xF0, 0xF0, 0xB5])
    time.sleep(1/5)
    if (rID == "radio3"):        
        str.openReadingPipe(1, [0xF0, 0xF0, 0xF0, 0xF0, 0xC3])
    #str.printDetails()
    time.sleep(1/5)
        
    msg = list (rID)
    while len(msg) < 32:
        msg.append(0)

    
    str.write(msg)
    #print("sent msg: {}".format(msg))
    #The Pi's NRF24 is not listening and waiting on the arduino to reply
    str.startListening()


    #start = time.time()
    Timeout = 0
    while not str.available():
        time.sleep (1/2)
        
        if time.time() - start > 2:
            Timeout = 2            
            break


    if Timeout == 2:
        print(rID + " Timed out! ")
        str.stopListening()
        receivedMessage = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
        Unpack.unpack_func(receivedMessage, rID)
        time.sleep(1/5)
        str.stopListening()
    else:
        #print(rID + " did not time out!")
        receivedMessage = []
        str.read(receivedMessage, str.getDynamicPayloadSize())
        str.stopListening()
        Unpack.unpack_func(receivedMessage, rID)
        time.sleep(1/5)
        str.stopListening()
