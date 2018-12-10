import serial

class Arduino:
    def __init__(self, port, baudrate, timeout):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout

    def cmdToSerial(self, query):
        sp = serial.Serial()
        sp.port = self.port
        sp.baudrate = self.baudrate
        sp.parity = serial.PARITY_NONE
        sp.bytesize = serial.EIGHTBITS
        sp.stopbits = serial.STOPBITS_ONE
        sp.timeout = self.timeout
        sp.xonxoff = False
        sp.rtscts = False
        sp.dsrdtr = False

        sp.open()

        value = sp.readline()

        sp.write(query.encode('utf8'))
        value = sp.readline()
        sp.close()
        return value


#if __name__ == "__main__":
    #Arduino = Arduino('COM3', 9600, 2)
    #print (Arduino.cmdToSerial("U1T1pOnR1OnR2OnR3On\n"))
    #print (Arduino.cmdToSerial("U1T1pOffR1OffR2OffR3Off\n"))
