/*
 * Rockstar Button
 * Description: The code that runs the Rockstar Button at G Adventures
 * Author(s): Adam McKerlie
 * Version: 0.1
 * 
 */
#include <EEPROM.h>
#include <Bounce.h>

const int buttonPin = 2;
const int ledPin = 5;
const int counterAddress = 1;

// Button Declaration
Bounce rockstarButton = Bounce(buttonPin, 10); // 10 ms debounce

int buttonState = 1;  
int buttonPressCount = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}  
  
// Function that plays the next song.
int playNext() {
  // Make sure we're not sending any modifier keys (ctrl/cmd/shift/etc...)
  Keyboard.set_modifier(0);

  // Skip to the next song
  Keyboard.set_key1(KEY_RIGHT);
  Keyboard.send_now(); 

  // Play music
  Keyboard.set_key1(KEY_SPACE);
  Keyboard.send_now();

  // Turn on LED
  digitalWrite(ledPin, HIGH);
  buttonPressCount = EEPROM.read(counterAddress);
  EEPROM.write(counterAddress, buttonPressCount + 1);
  return 1;
}

// Function that stops the music
int stopMusic() {
  // Make sure we're not sending any modifier keys (ctrl/cmd/shift/etc...)
  Keyboard.set_modifier(0);

  // Pause the song
  Keyboard.set_key1(KEY_SPACE);
  Keyboard.send_now(); 

  // Turn off LED
  digitalWrite(ledPin, LOW);

  buttonPressCount = EEPROM.read(counterAddress);
  Serial.println(buttonPressCount);
  return 0;
}

void loop() {
  // Update the status of the button
  rockstarButton.update();

  // If the button has been pressed do some code
  if (rockstarButton.risingEdge()) {
    if (buttonState == 0) {
      buttonState = playNext();
    } else {
      buttonState = stopMusic();
    }
  } else {
    // Make sure we're not sending any modifier keys (ctrl/cmd/shift/etc...)
    Keyboard.set_modifier(0); 
    // Sending key1 as 0 releases it
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
}

