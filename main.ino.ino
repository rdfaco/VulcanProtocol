#include <DHT.h> // Biblioteca do sensor de temperatura e umidade - DHT 11
#include <SoftwareSerial.h>   //Include the SoftwareSerial library -- Bluetooth

// DADOS DE CONEXÃƒO FÃ�SICA DO SENSOR DE TEMERATURA
// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor

#define DHTPIN A1       // pino que estamos conectado
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bluetooth(9, 8); //Create a new software  serial -- TX, RX (Bluetooth)
//-------------------------------------------------

//RELAYS
#define RELAY1 2
#define RELAY2 3
#define RELAY3 4


String  lineInput       = "";
bool    stringComplete  = false;
String  modo            = "";
 
void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  lineInput.reserve(200);
  //Serial.println("DHT test OK!");
  dht.begin();
 
  pinMode(LED_BUILTIN, OUTPUT); // inicializar LED pin(13) -> output:
  pinMode(RELAY1, OUTPUT);      // inicializar RELAY1 pin(2) -> output:
  pinMode(RELAY2, OUTPUT);      // inicializar RELAY2 pin(3) -> output:
  pinMode(RELAY3, OUTPUT);      // inicializar RELAY3 pin(4) -> output:

  // Desligar RelÃ©s aoninicializa-los
  digitalWrite(RELAY1, HIGH);   
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
}

void loop() {

      //Serial
      if (Serial.available()) {
        while(Serial.available()){
          char inChar = (char)Serial.read();
          lineInput += inChar;
          if (inChar == '\n'){
            stringComplete = true;
            modo = "Serial";
          }
        }
        //Bluetooth
      }else if (bluetooth.available()) {
        while(bluetooth.available()){
          char inChar = (char)bluetooth.read();
          lineInput += inChar;
          if (inChar == '\n'){
            stringComplete = true;
            modo = "BT";
          }
        }
      }
      
      if (stringComplete){
          //Serial.flush();
          //---------TEMPERATURA: T1
          lineInput.replace("T1", getTemperatura());

          //---------UMIDADE: U1
          lineInput.replace("U1", getUmidade());

          //---------PIN LED: pOn / pOff
          if (lineInput.indexOf("pOn") != -1 ) {    
             setLed(true);
             lineInput.replace("pOn", "Led_On;"); 
          }
          if (lineInput.indexOf("pOff") != -1 ) {              
             setLed(false);
             lineInput.replace("pOff", "Led_Off;"); 
          }  

          //---------RELAY1: R1On / R1Off
          if (lineInput.indexOf("R1On") != -1 ) {    
             setRelay(true,RELAY1);
             lineInput.replace("R1On", "Relay1_On;"); 
          }
          if (lineInput.indexOf("R1Off") != -1 ) {              
             setRelay(false,RELAY1);
             lineInput.replace("R1Off", "Relay1_Off;"); 
          }  

          //----------RELAY2: R2On / R2Off 
          if (lineInput.indexOf("R2On") != -1 ) {    
             setRelay(true,RELAY2);
             lineInput.replace("R2On", "Relay2_On;");            
          }
          if (lineInput.indexOf("R2Off") != -1 ) {              
             setRelay(false,RELAY2);
             lineInput.replace("R2Off", "Relay2_Off;"); 
          }  

          //----------RELAY3: R2On / R2Off         
          if (lineInput.indexOf("R3On") != -1 ) {    
             setRelay(true,RELAY3);
             lineInput.replace("R3On", "Relay3_On;"); 
          }
          if (lineInput.indexOf("R3Off") != -1 ) {              
             setRelay(false,RELAY3);
             lineInput.replace("R3Off", "Relay3_Off;"); 
          }  
                  

          bluetooth.print(lineInput);
          Serial.print(lineInput);

          
          //Serial.flush();
          stringComplete = false;
          lineInput = "";
          modo = "";
      }
}


String getTemperatura(){
  float t = dht.readTemperature();
  if (isnan(t)){  // testa se retorno Ã© valido
      return "Failed to read from DHT";
    } else {
      return (String)t + ";";
    } 
}

String getUmidade(){
  float h = dht.readHumidity();
  if (isnan(h)){  // testa se retorno Ã© valido
      return "Failed to read from DHT";
    } else {
      return (String)h + ";";
    } 
}

void setLed(bool i){
  if(i){
    digitalWrite(LED_BUILTIN, HIGH);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setRelay(bool i, int RELAY){
  if(i){
    digitalWrite(RELAY, LOW);
  }else{
    digitalWrite(RELAY, HIGH);
  }
}
