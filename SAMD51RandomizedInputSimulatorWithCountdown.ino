#include <HID.h>
#include <Keyboard.h>
#include <Mouse.h>

#define MIN_DELAY 100  // minimum delay in milliseconds between actions
#define MAX_DELAY 3000 // maximum delay in milliseconds between actions

char inputBuffer[10];
unsigned long endTime;
bool isRunning = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  Keyboard.begin();
  Mouse.begin();

  promptForDuration();
}

void loop() {
  if (!isRunning && Serial.available() > 0) {
    int index = 0;
    while (Serial.available() && index < 9) {
      inputBuffer[index++] = Serial.read();
      delay(2);
    }
    inputBuffer[index] = '\0';
    int duration = atoi(inputBuffer);
    endTime = millis() + (duration * 1000);
    
    isRunning = true;

    Serial.print("Randomized Input Simulator running for ");
    Serial.print(duration);
    Serial.println(" seconds...");
  }
  
  if (isRunning) {
    if (millis() < endTime) {
      performRandomAction();
      delay(random(MIN_DELAY, MAX_DELAY));
    } else {
      isRunning = false;
      promptForDuration();
    }
  }
}

void promptForDuration() {
  Serial.println("Enter duration in seconds for the randomized input simulator:");
}

void performRandomAction() {
  int action = random(3);

  switch (action) {
    case 0:
      randomMouseMovement();
      break;
    case 1:
      randomMouseClick();
      break;
    case 2:
      randomKeyboardInput();
      break;
  }
}

void randomMouseMovement() {
  int x = random(800) - 400; // Assuming a screen resolution width of 800
  int y = random(600) - 300; // Assuming a screen resolution height of 600
  Mouse.move(x, y);
}

void randomMouseClick() {
  int button = random(2);
  if (button == 0) {
    Mouse.press(MOUSE_LEFT);
    Mouse.release(MOUSE_LEFT);
  } else {
    Mouse.press(MOUSE_RIGHT);
    Mouse.release(MOUSE_RIGHT);
  }
}

void randomKeyboardInput() {
  char character = random('A', 'Z' + 1);
  Keyboard.write(character);
}
