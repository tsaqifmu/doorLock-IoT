//COKLAT --> GND
//MERAH --> vCC
//ORANGE --> DATA
//PIN DI nodeMCU pakai GPIO
//---------------------------------------------------------------------

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define BUZZER D2
#define LED_ABANG D8
#define LED_IJO D0


constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

Servo servo;
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  servo.attach(5); //D1
  servo.write(150);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ABANG, OUTPUT);
  pinMode(LED_IJO, OUTPUT);
  digitalWrite(LED_ABANG, LOW);
}
void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "14520110727" || tag == "43573114" || tag == "227165926" || tag == "15017423951" ) {
      Serial.println("AKSES DITERIMA");
      digitalWrite(LED_IJO, HIGH);
      tone(BUZZER, 1047);  
      delay(400);
      tone(BUZZER, 1319);
      delay(400);
      tone(BUZZER, 1568);
      delay(400);
      tone(BUZZER, 2093);
      delay(400);
      tone(BUZZER, 0);  
      servo.write(50);
      delay(3000);
      servo.write(150);
      digitalWrite(BUZZER, LOW);
      digitalWrite(LED_IJO, LOW);
      
    } else {
      Serial.println("AKSES DITOLAK");
      digitalWrite(LED_ABANG, HIGH);
      tone(BUZZER, 2093);
      delay(400);
      tone(BUZZER, 1567);
      delay(400);
      tone(BUZZER, 0);
      digitalWrite(LED_ABANG, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
