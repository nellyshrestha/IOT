#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;
int servoPos = 0;

#define sensorPin1 A0
#define sensorPin2 A1
#define buzzerPin A2

int senVal1 = 0;
int senVal2 = 0;

#define RST_PIN A6
#define SS_PIN 10

int card1Balance = 5000;
int card2Balance = 300;

#define num 7
char Data[num];
byte data_count = 0;

String num1, num2, card;
int a, b;
char Key;

bool recharge = true;

MFRC522 mfrc522(SS_PIN, RST_PIN);

int state = 0;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- Function Prototypes ----------
void lcdPrint();
void LcdPrint();
void clearData();
void reCharge();
void sensorRead();
void rfid();
void KeyPad();
void servoDown();
void servoUp();

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  servo.attach(A3);
  servo.write(0); // Start closed

  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.setCursor(0, 0);
  lcd.print(" Automatic toll");
  lcd.setCursor(0, 1);
  lcd.print("collection system");
  delay(3000);
  lcd.clear();
}

void loop() {
  if (!recharge) {
    reCharge();
  } else {
    lcd.setCursor(0, 0);
    lcd.print("   Welcome!!!");
    sensorRead();
    rfid();
    KeyPad();

    if (senVal1 == 0) {
      servoDown();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vehicle detected");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Put your card to");
      lcd.setCursor(0, 1);
      lcd.print("the reader......");
      delay(2000);
      lcd.clear();
    } else if (senVal2 == 0 && state == 1) {
      servoUp();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Have a safe");
      lcd.setCursor(0, 1);
      lcd.print("journey");
      delay(1000);
      lcd.clear();
      state = 0;
    }
  }
}

void servoDown() {
  for (servoPos = 0; servoPos <= 90; servoPos++) {
    servo.write(servoPos);
    delay(10);
  }
}

void servoUp() {
  for (servoPos = 90; servoPos >= 0; servoPos--) {
    servo.write(servoPos);
    delay(10);
  }
}

void sensorRead() {
  senVal1 = digitalRead(sensorPin1);
  senVal2 = digitalRead(sensorPin2);
}

void rfid() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  if (content.substring(1) == "24 EA 29 03") {
    if (card1Balance >= 500) {
      lcdPrint();
      card1Balance -= 500;
      lcd.setCursor(9, 1);
      lcd.print(card1Balance);
      delay(2000);
      lcd.clear();
      state = 1;
    } else {
      card = content.substring(1);
      LcdPrint();
      lcd.setCursor(9, 1);
      lcd.print(card1Balance);
      lcd.print(" Tk");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Recharge");
      delay(1000);
      lcd.clear();
      state = 0;
    }
  } else if (content.substring(1) == "D3 DC C1 01") {
    if (card2Balance >= 500) {
      lcdPrint();
      card2Balance -= 500;
      lcd.setCursor(9, 1);
      lcd.print(card2Balance);
      delay(2000);
      lcd.clear();
      state = 1;
    } else {
      card = content.substring(1);
      LcdPrint();
      lcd.setCursor(9, 1);
      lcd.print(card2Balance);
      lcd.print(" Tk");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Recharge");
      delay(1000);
      lcd.clear();
      state = 0;
    }
  } else {
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Unknown Vehicle");
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    delay(1500);
    lcd.clear();
    digitalWrite(buzzerPin, LOW);
  }
}

void KeyPad() {
  char key = keypad.getKey();
  if (key && key == 'A') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Recharging Mode.");
    lcd.setCursor(0, 1);
    lcd.print("................");
    delay(1500);
    lcd.clear();
    recharge = false;
  }
}

void clearData() {
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
}

void reCharge() {
  lcd.setCursor(0, 0);
  lcd.print("Enter the amount");

  char key = keypad.getKey();
  if (key) {
    if (key == 'D') {
      if (card == "24 EA 29 03") {
        num1 = Data;
        card1Balance += num1.toInt();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your current");
        lcd.setCursor(0, 1);
        lcd.print("balance: ");
        lcd.print(card1Balance);
        lcd.print(" Tk");
        delay(3000);
        clearData();
        lcd.clear();
        recharge = true;
      } else if (card == "D3 DC C1 01") {
        num2 = Data;
        card2Balance += num2.toInt();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your current");
        lcd.setCursor(0, 1);
        lcd.print("balance: ");
        lcd.print(card2Balance);
        lcd.print(" Tk");
        delay(3000);
        clearData();
        lcd.clear();
        recharge = true;
      }
    } else if (data_count < num - 1) {
      Data[data_count] = key;
      lcd.setCursor(data_count, 1);
      lcd.print(Data[data_count]);
      data_count++;
    }
  }
}

void lcdPrint() {
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Successfully");
  lcd.setCursor(0, 1);
  lcd.print(" paid your bill");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Remaining");
  lcd.setCursor(0, 1);
  lcd.print("balance: ");
}

void LcdPrint() {
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Your balance");
  lcd.setCursor(0, 1);
  lcd.print(" is insufficient");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Remaining");
  lcd.setCursor(0, 1);
  lcd.print("balance: ");
}
