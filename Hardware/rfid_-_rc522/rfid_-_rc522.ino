#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define RST_PIN    D3
#define SS_PIN     D8
#define FIREBASE_HOST "luggagetrack-7cb6b.firebaseio.com"
#define FIREBASE_AUTH "4gtHlVz3H7rkrGDVlf3R2pCsQsSlEvCjlnIngHuQ"
#define WIFI_SSID "harshil1"
#define WIFI_PASSWORD "123456781"

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  //  Serial.println();
  //  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Put your card to the reader...");
  Serial.println();
}

String rfidTag_5;
String a;
void loop()
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
  Serial.println(" ");
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  rfidTag_5 = content;
  a = content;
  rfidTag_5 = content;
  Firebase.setString("Tag/" + rfidTag_5, "AirIndia");
  Serial.println(a);
  //  char b[12];
  //  for (int i = 0; a[i] != '\0'; i++)
  //    b[i] = a[i];
  //  //  Serial.println(b);
  //  Serial.write("7");
}
