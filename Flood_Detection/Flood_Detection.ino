const int LED = 4;
const int buzzer = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Initializes serial communication at 9600 bps for debugging.
  pinMode(4, OUTPUT); // Sets pin 4 (LED) as an output.
  pinMode(7, OUTPUT); // Sets pin 7 (buzzer) as an output.
}


}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A3); // Reads analog input from pin A3 (sensor output).
  Serial.print("value:");     // Prints "value:" to the Serial Monitor.
  Serial.println(value);      // Prints the sensor value to the Serial Monitor.

 if(value < 400) {
    digitalWrite(4, HIGH);  // Turns the LED on (indicates heavy rain).
    digitalWrite(7, HIGH);  // Activates the buzzer (sound alert).
    Serial.print("Heavy rain LED is on"); // Prints the status to the Serial Monitor.
  } else {
    digitalWrite(4, LOW);   // Turns the LED off.
    digitalWrite(7, LOW);   // Turns the buzzer off.
  }

}
