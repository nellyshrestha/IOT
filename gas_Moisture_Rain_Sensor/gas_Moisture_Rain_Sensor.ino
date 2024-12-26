// Pin Definitions
int redLED = 12;
int greenLED = 11;
int buzzer1 = 10;
int smoke = A0;

int LED = 4;
int buzzer = 7;
int rainPin = A1;

int moisterPin = A2;
int redLed = 6;
int greenLed = 5;
int Buzzer = 3;

// Threshold Values
int sensorThres = 100;      // Gas sensor threshold
int rainThreshold = 500;    // Rain sensor threshold
int moistureThreshold = 800; // Moisture sensor threshold

void setup() {
  // Setup pins for Gas Sensor
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(smoke, INPUT);

  // Setup pins for Rain Sensor
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(rainPin, INPUT);

  // Setup pins for Moisture Sensor
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(moisterPin, INPUT); // Corrected from OUTPUT to INPUT

  // Start Serial Communication
  Serial.begin(9600);
}

void loop() {
  // Call Sensor Functions
  checkMoisture();
  rainSensor();
  checkGas();

  delay(1000); // Delay to avoid sensor flooding
}

// Function to Check Moisture Levels
void checkMoisture() {
  int analogMoisture = analogRead(moisterPin);
  Serial.print("Moisture Sensor Value: ");
  Serial.println(analogMoisture);

  if (analogMoisture > moistureThreshold) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(Buzzer, 1000, 200); // Buzzer on
    Serial.println("Moisture Level Low: ALERT!");
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(Buzzer); // Buzzer off
    Serial.println("Moisture Level Sufficient.");
  }
}

// Function to Check Gas Levels
void checkGas() {
  int analogSensor = analogRead(smoke);
  Serial.print("Gas Sensor Value: ");
  Serial.println(analogSensor);

  if (analogSensor > sensorThres) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    tone(buzzer1, 1000, 200); // Buzzer on
    Serial.println("Gas Detected: ALERT!");
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    noTone(buzzer1); // Buzzer off
    Serial.println("Air Quality Normal.");
  }
}

// Function to Check Rain Levels
void rainSensor() {
  int value = analogRead(rainPin);
  Serial.print("Rain Sensor Value: ");
  Serial.println(value);

  if (value < rainThreshold) { 
    digitalWrite(LED, HIGH);
    digitalWrite(buzzer, HIGH); // LED and buzzer on
    Serial.println("Heavy Rain Detected!");
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(buzzer, LOW); // LED and buzzer off
    Serial.println("No Heavy Rain.");
  }
}
