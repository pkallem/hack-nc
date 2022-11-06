#!/usr/bin/env python3

import serial
import pyrebase
from datetime import datetime



def main():
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    data = {}
    
            
    def upload():
        print("Inside upload()")
        
        
        line = ser.readline().decode('utf-8').rstrip()
        if line != "":
            print(line.split(","))
            data["Humidity"] = line.split(",")[0]
            data["Temperature"] = line.split(",")[1]
            data["Heat Index"] = line.split(",")[2]
            data["Water Level"] = line.split(",")[3]
            data["Object Detection"] = line.split(",")[4]
            data["Time"] = f"{datetime.now().time().hour}:{datetime.now().time().minute}:{datetime.now().time().second}"
            print(data)
      
    
    config = {
      "apiKey": "gDSgvAbkAkCkpj4kEfQtUZ6Ht15o4OlwDtoxbfZU",
      "authDomain": "portfolio-8fd78.firebaseapp.com",
      "databaseURL": "https://portfolio-8fd78-default-rtdb.firebaseio.com",
      "storageBucket": "portfolio-8fd78.appspot.com"
    }
    
    firebase = pyrebase.initialize_app(config)
    db = firebase.database()
    
    print("Send Data to Firebase Using Raspberry Pi")
    print("—————————————-")
    print()
    
    index = 0
    while True:
        upload()
        db.child(index).set(data)
        index += 1


 
if __name__ == '__main__':
    main()
            