import sys
########################Modules Path Information################################
sys.path.append(“/home/pi/Desktop/ICBP_NRF24/modules”)
########################Modules Path Information################################
from lib_nrf24 import NRF24
import radio
import time


while True:
    
   #### Radio.py module configures transceiver information for primary Arduino
   #### located:  /usr/lib/pymodules/ICBP_modules/Radio.py
   # radio.radio_func("radio1")
    
   #### Radio2.py module configures transceiver information for secondary Arduino
   #### located:  /usr/lib/pymodules/ICBP_modules/Radio.py
   # radio.radio_func("radio2")
 
    radio2.radio_func("radio1")
    time.sleep(1/10)

    radio2.radio_func("radio2")
    time.sleep(1/10)
