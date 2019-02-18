#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define FIREBASE_HOST "rfid-data-upload.firebaseio.com"                     //Address of the Database
#define FIREBASE_AUTH "8Cu6MYRCDBynLHZoXN1sHIIGKfPgJMjZHQAEecto"            //Secret Key to access the Database
#define WIFI_SSID "harshil1"                                           //Network SSID which connects to the esp8266 wifi module
#define WIFI_PASSWORD "123456781"                                          //Password to access the wifi
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);                                           // Create MFRC522 instance.
String RFID_Tag = "";
const byte ROWS = 4;                                                        //four rows & four columns of the keypad matrix
const byte COLS = 4;
char hexaKeys[ROWS][COLS] =                                                 //define the symbols on the buttons of the keypads
{
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0};                                          //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4};                                          //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);//initialize an instance of class NewKeypad
char customKey;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

FirebaseObject requiredOtp;

void setup()                                                                 //This function setups the Arduino
{
  Serial.begin(9600);                                                        // Initiate a serial communication
  SPI.begin();                                                               // Initiate  SPI bus
  mfrc522.PCD_Init();                                                        // Initiate MFRC522
  lcd.begin(16, 2);                                                          //Initiate  Liquid Crystal Display
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //Initializes the wifi
  Serial.print("Connecting to wifi.");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              //Connects to Firebase Realtime Database
  pinMode(D0, OUTPUT);                                                       //Alarm Pin
}

void loop()                                                                  //This function runs in loop
{
  readRFID();
  readFire();
  getOtp();
  if (customKey == char(requiredOtp.getInt()))
  {
    //openServo();
  }
  else
  {
    digitalWrite(D0, HIGH);                                                   //Sound Alarm
  }
}

void readRFID()
{
  if ( ! mfrc522.PICC_IsNewCardPresent()  || ! mfrc522.PICC_ReadCardSerial())// Look for new cards or Select one of the existing cards
  {
    return;
  }
  Serial.println("Reader is ready to scan the card....");                   //Show UID on serial monitor
  delay(100);
  Serial.print("UID tag :");
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    RFID_Tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    RFID_Tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
}

void updateFire()
{
  do
  {
    Firebase.setString("rfidReader-1", RFID_Tag);                            // Upload value of RFID tag detected at each stage in firebase
    delay(50);
  }
  while (!Firebase.failed());
}

void readFire()
{
  do
  {
    requiredOtp = Firebase.get(RFID_Tag);
    delay(50);
  }
  while (!Firebase.failed());
}

void getOtp()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter OTP");
  customKey = customKeypad.getKey();
  if (customKey)
  {
    delay(10);
    lcd.setCursor(0, 1);
    lcd.print(customKey);
    delay(10);
    Serial.println(customKey);
  }
}
