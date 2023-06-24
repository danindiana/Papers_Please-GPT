#include <HID.h>
#include <Keyboard.h>
#include <Mouse.h>

void initRNG() {
  // Enable the APBC clock for the RNG
  MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;

  // Set up and enable the RNG
  TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
}

uint32_t getRandomNumber() {
  while (TRNG->INTFLAG.bit.DATARDY == 0);  // Wait for a random number to be ready
  return TRNG->DATA.reg;  // Read the random number
}

void simulateMouseMovement(uint32_t randNum) {
  int8_t dx = (randNum & 0x0F) - 7;
  int8_t dy = ((randNum >> 4) & 0x0F) - 7;
  Mouse.move(dx, dy);
}

void simulateKeyPress(uint32_t randNum) {
  char key;
  if (randNum % 36 < 26) {
    key = 'A' + (randNum % 26);
  } else {
    key = '0' + (randNum % 10);
  }
  
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize TRNG
  initRNG();

  // Keyboard and Mouse HID setup
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  uint32_t runSeconds;
  
  Serial.println("Enter the number of seconds to run the program:");
  while (Serial.available() == 0);
  runSeconds = Serial.parseInt();
  Serial.flush();

  // Countdown before starting
  Serial.println("Program starting in 10 seconds:");
  for (int i = 10; i > 0; i--) {
    Serial.print(i);
    Serial.println("...");
    delay(1000);
  }
  
  uint32_t startTime = millis();
  while (millis() - startTime < runSeconds * 1000) {
    uint32_t randNum = getRandomNumber();

    if (randNum % 2 == 0) {
      simulateMouseMovement(randNum);
    } else {
      simulateKeyPress(randNum);
    }
    
    delay(200);
    
    uint32_t remainingTime = runSeconds - ((millis() - startTime) / 1000);
    Serial.print("Time remaining: ");
    Serial.print(remainingTime);
    Serial.println(" seconds");
  }

  Serial.println("Program finished. Ready for another run.");
}
