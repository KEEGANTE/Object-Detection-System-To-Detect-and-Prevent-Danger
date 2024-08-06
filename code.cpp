#include<LiquidCrystal.h> //Include the LiquidCrystal library
LiquidCrystal lcd (7,8,9,10,11,12); // Create a LiquidCrystal object for the LCD

#include <Servo.h> // Include the Servo library
Servo servo; // Create a Servo object for the servo motor

// Define the pin numbers for various components
int trigger_pin = 2;
int echo_pin = 3;
int buzzer_pin = 6;
int red_light = 4;
int green_light = 5;
int time;
int distance; 
int serv = 13;

void setup () {
  lcd.begin (16, 2); // Initialize the LCD with 16 columns and 2 rows
  pinMode (trigger_pin, OUTPUT); // Set trigger_pin as an output
  pinMode (echo_pin, INPUT); // Set echo_pin as an input
  pinMode (buzzer_pin, OUTPUT); // Set buzzer_pin as an output
  pinMode (red_light, OUTPUT); // Set red_light as an output
  pinMode (green_light, OUTPUT); // Set green_light as an output
  servo.attach(13); // Attach the servo motor to pin 13
  
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}
void loop () {
  
  // Send a short pulse to the trigger_pin
  digitalWrite(trigger_pin, LOW); 
  digitalWrite (trigger_pin, HIGH);
  digitalWrite (trigger_pin, LOW);
  
  time = pulseIn (echo_pin, HIGH); // Measure the time it takes for the pulse to return
  
  distance = (time * 0.034) / 2; // Calculate the distance based on the time
  
  if (distance >= 200) 
  {
    // Display "OBJECT SAFE" on the LCD if the distance is greater than or equal to 200 cm
    lcd.setCursor (0,0);
    lcd.print("OBJECT SAFE");
    lcd.setCursor (0,1);
    lcd.print(distance);
    lcd.print("cm");
    
    // Turn off the servo motor, red light, buzzer, and green light
    digitalWrite (serv, LOW);
    digitalWrite (red_light, LOW);
    digitalWrite (buzzer_pin, LOW);
    digitalWrite (green_light, LOW);
  } 
  else if (distance <= 100)
  {
    // Display "OBJECT DETECTED" on the LCD if the distance is less than or equal to 100 cm
    lcd.setCursor (0,0);
    lcd.print ("OBJECT DETECTED");
    lcd.setCursor (0,1);
    lcd.print (distance); 
    lcd.print("cm");
    
    // Turn on the servo motor, red light, and buzzer. turn off the green light
    digitalWrite (serv, HIGH);
    digitalWrite (red_light, HIGH);
    digitalWrite (buzzer_pin, HIGH);
    digitalWrite (green_light, LOW);
  }
  else 
  {
    // Display "OBJECT REMOVED" on the LCD for other distances
    lcd.setCursor (0,0);
    lcd.print("OBJECT REMOVED");
    lcd.setCursor (0,1);
    lcd.println (distance); 
    lcd.print("cm");
    
    // Turn off the servo motor, red light, and buzzer; turn on the green light
    digitalWrite (serv, LOW);
    digitalWrite (green_light, HIGH);
    digitalWrite (buzzer_pin, LOW);
    digitalWrite (red_light, LOW);
  }
}
