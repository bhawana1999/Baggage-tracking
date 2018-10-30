#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN    D3
#define SS_PIN     D8
MFRC522 mfrc522(SS_PIN, RST_PIN);                                           // Create MFRC522 instance.

void setup()                                                                 //This function setups the Arduino
{
  Serial.begin(9600);                                                        // Initiate a serial communication
  SPI.begin();                                                               // Initiate  SPI bus
  mfrc522.PCD_Init();                                                        // Initiate MFRC522
}

char a[12];

void loop()                                                                  //This function runs in loop
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  a = content;
  Serial.write(a);
}
