#include <Keypad.h>
#include <Servo.h>

int redLed= 12;
int greenLed= 13;

const byte ROWS = 4;
const byte COLS = 3;

Servo myServo; 

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPin[ROWS] = {8, 7, 6, 5};
byte colPin[COLS] = {4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, ROWS, COLS);

String enteredPassword = "";  // Variable to store entered password
String correctPassword = "1234";  // Correct password

void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);

  myServo.attach(11);
}

void loop() {
  char key = keypad.getKey();  // Get key pressed

  if (key != NO_KEY) {  // If a key is pressed
    if (key == '#') {  // Check if the user presses "#" (submit key)
      if (enteredPassword == correctPassword) {  // Compare entered password with the correct one
        Serial.println("Access Granted!");
        digitalWrite(greenLed,HIGH);
      for (int greenLed = 50; greenLed <= 165; greenLed ++){  
        myServo.write(greenLed);
        
        }
        digitalWrite(redLed,LOW);
        
      } else {
        Serial.println("Access Denied!");
        digitalWrite(redLed,HIGH);
        for (int redLed = 50; redLed <= 165; redLed --){  
        myServo.write(redLed);
        }
        digitalWrite(greenLed,LOW);
      }
      enteredPassword = "";  // Clear entered password after check
    } else if (key == '*') {  // Check if "*" is pressed (clear entered password)
      enteredPassword = "";  // Reset entered password
      Serial.println("Password Cleared");
    } else {
      enteredPassword += key;  // Append the key pressed to enteredPassword
      Serial.print("Entered Password: ");
      Serial.println(enteredPassword);
    }
  }
  
  void motor(){
    Serial.println("");
    if(motor == low){
      digitalWrite(motor,LOW);
    }
    motor= high;
    Serial.println("");
}
