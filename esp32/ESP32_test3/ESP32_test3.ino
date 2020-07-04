#include "BluetoothSerial.h"


BluetoothSerial SerialBT;


#define DEBUG_PORT Serial
#define ELM_PORT   SerialBT


void setup()
{
  /*
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  */

  DEBUG_PORT.begin(115200);

  ELM_PORT.setPin("1234");
  ELM_PORT.begin("ESP32test", true);

  DEBUG_PORT.println("Attempting to connect to ELM327...");

  if (!ELM_PORT.connect("OBDII"))
  {
    DEBUG_PORT.println("Couldn't connect to OBD scanner");
    while(1);
  }

  DEBUG_PORT.println("Connected to ELM327");
  DEBUG_PORT.println("Ensure your serial monitor line ending is set to 'Carriage Return'");
  DEBUG_PORT.println("Type and send commands/queries to your ELM327 through the serial monitor");
  DEBUG_PORT.println();
}


void loop1() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
}

void loop()
{
  if(DEBUG_PORT.available())
  {
    char c = DEBUG_PORT.read();

    DEBUG_PORT.write(c);
    size_t w = ELM_PORT.write(c);
    DEBUG_PORT.println();
    DEBUG_PORT.printf("wrote %d byte(s) (%c) to ELM_PORT (SerialBT)", w, c);
    DEBUG_PORT.println();
    ELM_PORT.flush();
  }

  if(ELM_PORT.available())
  {
    char c = ELM_PORT.read();

    if(c == '>')
      DEBUG_PORT.println();

    DEBUG_PORT.write(c);
  }

  delay(20);
}
