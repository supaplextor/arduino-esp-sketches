#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include "BluetoothSerial.h"
#include "Syslog.h"

WiFiMulti WiFiMulti;
const char* ssid = "RT-AC1200G_70_2G";
const char* password = "";

// Syslog server connection info
#define SYSLOG_SERVER "192.168.50.85"
#define SYSLOG_PORT 514

// This device info
#define DEVICE_HOSTNAME "esp32"
#define BT_APP_NAME "bt-serial-io"
#define TTY_APP_NAME "ttyUSB0-io"

BluetoothSerial SerialBT;

#define DEBUG_PORT Serial
#define ELM_PORT   SerialBT

//The udp library class
WiFiUDP udpClient;

// Create a new syslog instance with LOG_KERN facility
Syslog syslogBT    (udpClient, SYSLOG_SERVER, SYSLOG_PORT, DEVICE_HOSTNAME, BT_APP_NAME, LOG_KERN);
Syslog syslogSerial(udpClient, SYSLOG_SERVER, SYSLOG_PORT, DEVICE_HOSTNAME, TTY_APP_NAME, LOG_KERN);


void setup()
{
  DEBUG_PORT.begin(115200);
  DEBUG_PORT.println("Booting esp32/M5Stick-C");

  // We start by connecting to a WiFi network
  WiFiMulti.addAP(ssid,password);

  DEBUG_PORT.println();
  DEBUG_PORT.println();
  DEBUG_PORT.printf("Waiting for WiFi... %s",ssid);

  while (WiFiMulti.run() != WL_CONNECTED) {
    DEBUG_PORT.print(".");
    delay(250);
  }

  syslogBT.server(SYSLOG_SERVER, SYSLOG_PORT);
  syslogSerial.server(SYSLOG_SERVER, SYSLOG_PORT);
  syslogBT.deviceHostname(DEVICE_HOSTNAME);
  syslogSerial.deviceHostname(DEVICE_HOSTNAME);
  syslogBT.appName(BT_APP_NAME);
  syslogSerial.appName(TTY_APP_NAME);
  syslogBT.defaultPriority(LOG_DEBUG);
  syslogSerial.defaultPriority(LOG_DEBUG);

  DEBUG_PORT.println("");
  DEBUG_PORT.println("WiFi connected");
  DEBUG_PORT.print("IP address: ");
  DEBUG_PORT.println(WiFi.localIP());
  // dunno how println works on serial, but not this....
  syslogSerial.logf(LOG_DEBUG, "IP address: %s",WiFi.localIP());
  // Jul  3 06:06:51 esp32 ttyUSBx-io IP address: 0#033@?<C0><A8>2'

  ELM_PORT.setPin("1234");
  ELM_PORT.begin("OBDII", true);
  DEBUG_PORT.println("Attempting to connect to ELM327...");

  while (!ELM_PORT.connect("OBDII"))
  {
    DEBUG_PORT.println("Cannot connect to OBD scanner");
    delay(5000);
  }

  DEBUG_PORT.println("Connected to ELM327");
  DEBUG_PORT.println("Ensure your serial monitor line ending is set to 'Carriage Return'");
  DEBUG_PORT.println("Type and send commands/queries to your ELM327 through the serial monitor");
  DEBUG_PORT.println();

  syslogBT.log(LOG_DEBUG, "Connected to ELM327 (bluetooth layer)");

  syslogBT.log(LOG_DEBUG, "Probing for ELM327 on BT Serial...");
  ELM_PORT.print("\r");
  syslogBT.log(LOG_DEBUG, "Reset to default (atz)");
  ELM_PORT.print("atz\r");
  syslogBT.log(LOG_DEBUG, "Disable echo");
  ELM_PORT.print("ate0\r");
  syslogBT.log(LOG_DEBUG, "Alternate chip id/version");
  ELM_PORT.print("ati\r");
  // let loop() do the dirty work on the BT and ttyUSB0 i/o
}

void loop()
{
  long foo = 0;
  foo = DEBUG_PORT.available();
 
  if(foo > 0)
  {
    syslogSerial.logf(LOG_DEBUG, "foo = DEBUG_PORT.available(); = (%d)",foo);
    char c = DEBUG_PORT.read();
    syslogSerial.logf(LOG_DEBUG, "char c = DEBUG_PORT.read(); = (%c)", c);

    DEBUG_PORT.write(c); // echo on
    
    // int b = ELM_PORT.write(c);
    int b = ELM_PORT.print(c);
    if (0 == b) {
      syslogBT.logf(LOG_DEBUG, "int b = ELM_PORT.write(%c) = (%d) !!!",c ,b);
    }
    syslogBT.logf(LOG_DEBUG, "int b = ELM_PORT.write(%c) = (%d)", c, b);
  }

  foo = ELM_PORT.available();

  if(foo > 0)
  {
    syslogSerial.logf(LOG_DEBUG, "foo = ELM_PORT.available(); = (%d)",foo);
    char c = ELM_PORT.read();
    syslogBT.logf(LOG_DEBUG, "char c = ELM_PORT.read(); = (%c)", c);

    if(c == '>')
      DEBUG_PORT.println();

    int b = DEBUG_PORT.write(c);
    if (b == 0) {
      syslogBT.logf(LOG_DEBUG, "int b = DEBUG_PORT.write(%c); // (%d)", c, b);
    }
    syslogBT.logf(LOG_DEBUG, "int b = DEBUG_PORT.write(%c) = (%d)", c, b);
  }

}
