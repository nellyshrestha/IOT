void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  Serial.println("Control System" );
}
void loop() {
  // put your main code here, to run repeatedly:
     digitalWrite(2, LOW);   
  Serial.println("Motor 1 ON"); 
   delay(3000);

  digitalWrite(2, HIGH);  
  Serial.println("Motor 1 OFF");
  delay(3000);    

   digitalWrite(4, LOW);   
  Serial.println("Light 1 ON"); 
   delay(3000);

  digitalWrite(4, HIGH);  
  Serial.println("Light 1 OFF");
  delay(3000); 
}
