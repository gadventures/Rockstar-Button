/*
 * Rockstar Button
 * Description: The code that runs the Rockstar Button at G Adventures.
 *              This sends keyboard shortcuts to Spotify to play music
 * Author(s): Adam McKerlie
 * Version: 0.2
 * 
 */

#include <Bounce.h>

// Output Constants
const int buttonPin = 2;
const int ledPin = 5;

// Button Declaration
Bounce rockstarButton = Bounce(buttonPin, 10); // 10 ms debounce

int buttonState = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

// Function that plays the next song.
int playNext() {
  //We want to send ALT+Right to skip to the next song in Spotify
  Keyboard.set_modifier(MODIFIERKEY_ALT);
  Keyboard.send_now();

  // Skip to the next song
  Keyboard.set_key1(KEY_RIGHT);
  Keyboard.send_now(); 

  // Turn on LED
  digitalWrite(ledPin, HIGH);

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

