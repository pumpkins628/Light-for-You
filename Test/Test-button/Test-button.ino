#include <Arduino.h>

// Define pins for buttons and LEDs
const int buttonPin_Left = 3;   // Pin number for the left button
const int buttonPin_Right = 4;  // Pin number for the right button
const int ledPin_Left = 8;      // Pin number for the left LED
const int ledPin_Right = 7;     // Pin number for the right LED

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging output
  
  pinMode(ledPin_Left, OUTPUT);  // Set the left LED pin as output
  pinMode(ledPin_Right, OUTPUT); // Set the right LED pin as output

  pinMode(buttonPin_Left, INPUT);  // Set the left button pin as input
  pinMode(buttonPin_Right, INPUT); // Set the right button pin as input

  digitalWrite(ledPin_Left, LOW);  // Initially turn off the left LED
  digitalWrite(ledPin_Right, LOW); // Initially turn off the right LED
}

void loop() {
  static int lastState_Left = HIGH;  // Store the previous state of the left button
  static int lastState_Right = HIGH; // Store the previous state of the right button

  int currentState_Left = digitalRead(buttonPin_Left);   // Read the current state of the left button
  int currentState_Right = digitalRead(buttonPin_Right); // Read the current state of the right button

  // Check if the state of the left button has changed
  if (currentState_Left != lastState_Left) {
    delay(50);  // Debounce delay
    // Re-read the button state to confirm the change
    currentState_Left = digitalRead(buttonPin_Left);
    if (currentState_Left == LOW) {
      digitalWrite(ledPin_Left, HIGH); // If the button is pressed, turn on the LED
      Serial.println("Left button pressed - LED ON");
    } else {
      digitalWrite(ledPin_Left, LOW);  // If the button is released, turn off the LED
      Serial.println("Left button released - LED OFF");
    }
    lastState_Left = currentState_Left; // Update the button state
  }

  // Check if the state of the right button has changed
  if (currentState_Right != lastState_Right) {
    delay(50);  // Debounce delay
    // Re-read the button state to confirm the change
    currentState_Right = digitalRead(buttonPin_Right);
    if (currentState_Right == LOW) {
      digitalWrite(ledPin_Right, HIGH); // If the button is pressed, turn on the LED
      Serial.println("Right button pressed - LED ON");
    } else {
      digitalWrite(ledPin_Right, LOW);  // If the button is released, turn off the LED
      Serial.println("Right button released - LED OFF");
    }
    lastState_Right = currentState_Right; // Update the button state
  }
}
