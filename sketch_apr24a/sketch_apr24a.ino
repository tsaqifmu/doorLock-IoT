

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

    // Dapetin token
char auth[] = "t8HHT8tly0K3CSaFgIcqQdO9UCkXvG6I";
    // id dan password internet 
char ssid[] = "LAPTOP";
char pass[] = "bismillah";

void setup(){
  Serial.begin(115200);
  
  //kalo pake serangkota jangan lupa ganti jadi
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
  //Blynk.begin(auth, ssid, pass);
  //Blynk.begin(auth, ssid, pass);
}

void loop(){
  
  
}
