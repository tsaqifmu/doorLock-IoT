// YOUBEAGGER FOR INDONESIA SCIENCE
// YUK DIDIK ANAK KITA MENDAPATKAN TONTONAN YANG BAIK
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN D3
#define RST_PIN D4
#define LED_BIRU  //akses diterima LED BIRU pin
#define LED_MERAH  //akses ditolak LED BIRU pin
#define BUZZER  //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(2); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_BIRU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "XX XX XX XX" || content.substring(1) == "XX XX XX XX") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("akses kartu diterima");
    Serial.println();
    delay(500);
    digitalWrite(LED_BIRU, HIGH);
    vol.tone(BUZZER, 659, 50);
    delay(300);
    noTone(BUZZER);
    myServo.write(60);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_BIRU, LOW);
  }
 
 else   {
    Serial.println("akses kartu ditolak");
    digitalWrite(LED_MERAH, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_MERAH, LOW);
  }
}
