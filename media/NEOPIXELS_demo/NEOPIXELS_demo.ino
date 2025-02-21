#include <Adafruit_NeoPixel.h>

// Define pin numbers
int Power = 11; // Pin 11 is used to provide power to the NeoPixel (if needed)
int PIN = 12;   // Pin 12 is connected to the data input of the NeoPixel

// Define the number of NeoPixels
#define NUMPIXELS 1

// Create a NeoPixel object with the specified number of pixels, pin, and color format
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Declare round and color variables
int rounds = 0;
int red = 205;
int blue = 15;

// Define the number of rounds for one full cycle
#define LIMIT 5

void setup() {
  pixels.begin();  // Initialize the NeoPixel library
  
  pinMode(Power, OUTPUT); // Set Power pin as an OUTPUT
  digitalWrite(Power, HIGH); // Turn on the power to the NeoPixel (if applicable)
}

void loop() { 
  // Clear the NeoPixel (turns off all pixels)
  pixels.clear();
  
  // Update color and round logic
  if (rounds < LIMIT) {
    // Gradually transition from red to blue
    if (red > 15 || blue < 205) {
      red -= (red > 15) ? 5 : 0;     // Decrease red if it's greater than 15
      blue += (blue < 205) ? 5 : 0;  // Increase blue if it's less than 205
      
      pixels.setPixelColor(0, pixels.Color(red, 15, blue)); // Apply the color
      delay(50); // Wait 100 milliseconds
      pixels.show(); // Display the color on the NeoPixel
    } else {
      // Once color reaches final state, show it a bit longer
      pixels.setPixelColor(0, pixels.Color(red, 15, blue));
      pixels.show();
      delay(200); // Wait 500 milliseconds before next cycle
      rounds++;  // Increment rounds after the final color is shown
    }
  } else {
    // Blink three times green and then proceed to next rounds
    for (int blinkCount = 0; blinkCount < 3; blinkCount++) {
      pixels.setPixelColor(0, pixels.Color(15, 205, 15)); // Set to green
      pixels.show();
      delay(250); // Wait 250 milliseconds

      // Turn LED off
      pixels.clear();
      pixels.show();
      delay(250); // Wait 250 milliseconds
      
    // Reset the round counter and colors for next cycle
    rounds = 0;
    red = 205;   // Reset to initial red value
    blue = 15;   // Reset to initial blue value
    delay(500);  // Extra delay before restarting
    }
  }
}
