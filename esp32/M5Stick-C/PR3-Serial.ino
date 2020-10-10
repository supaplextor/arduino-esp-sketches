#include <M5StickC.h>
#include <WiFi.h>

const char* ssid = "CATUO";
const char* password = "";

//IP Address; Server side (not us)
IPAddress server(192, 168, 0, 10);
WiFiClient client;

int tick = 0 ;

void setup()
{
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(0, 30, 4);
  M5.Lcd.printf("Hi %s",ssid);
  delay(2000);

  // Connecting to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED)
  {
    tick++;
    M5.Lcd.setCursor(0, 30, 4);
    M5.Lcd.printf("(%d) %s    ",tick,ssid);
    delay(500);
  }

  Serial.println("");
  Serial.println("Connected to Wifi");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  tick = 0;
  while(1) {
    tick++;
    M5.Lcd.setCursor(0, 30, 4);
    M5.Lcd.printf("(%d) ->> TCP:35000   ",tick);
  
    if (client.connect(server, 35000)) {
      Serial.println("TCP connected");     
      break;
    } else {
      Serial.print("connection failed from ");
      Serial.println(WiFi.localIP());
      delay(500);
    }
  }
}

void loop()
{
  delay(2500);
  Serial.print(".");
}
