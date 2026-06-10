const int LED_PINS[]    = {D0, D1, D2, D3};
const int BUTTON_PINS[] = {D10, D9, D8, D7};
const int NUM_COLORS    = 4;

void setup() {
  // put your setup code here, to run once:
for (int i = 0; i < NUM_COLORS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
    pinMode(BUTTON_PINS[i], INPUT_PULLUP); 
}
}

void loop() {
  // put your main code here, to run repeatedly:
  flashAll(2, 150);
  playGame();
  Serial.println("Press any button to play.");
  waitForAnyButton();
}

void playGame() {
  level = 0;
  speed = 500;

  while (true) {
    sequence[level] = random(0, NUM_COLORS);
    level++;

    delay(600);
    for (int i = 0; i < level; i++) {
      flashLED(sequence[i], (int)speed);
    }

    for (int i = 0; i < level; i++) {
      int pressed = waitForButton();
      if (pressed != sequence[i]) {
        gameOver();
        return;
      }
    }

    Serial.print("Level: ");
    Serial.println(level);
    delay(400);

    // Speed up every 5 levels (minimum 150ms)
    if (level % 5 == 0) {
      speed = max(150.0f, speed - 80.0f);
      Serial.print("Speed up! Now: ");
      Serial.print((int)speed);
      Serial.println("ms");
    }

    }
  }
}

void flashLED(int index, int duration) {
  digitalWrite(LED_PINS[index], HIGH);
  delay(duration);
  digitalWrite(LED_PINS[index], LOW);
  delay(100);
}

void flashAll(int times, int duration) {
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], HIGH);
    delay(duration);
    for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], LOW);
    delay(duration);
  }
}

// Wait until a button is pressed, light its LED, return index
int waitForButton() {
  while (true) {
    for (int i = 0; i < NUM_COLORS; i++) {
      if (digitalRead(BUTTON_PINS[i]) == LOW) {
        digitalWrite(LED_PINS[i], HIGH);
        while (digitalRead(BUTTON_PINS[i]) == LOW) delay(10);
        digitalWrite(LED_PINS[i], LOW);
        delay(50);   
        return i;
      }
    }
  }
}

void waitForAnyButton() {
  delay(200);
  while (true) {
    for (int i = 0; i < NUM_COLORS; i++) {
      if (digitalRead(BUTTON_PINS[i]) == LOW) {
        while (digitalRead(BUTTON_PINS[i]) == LOW) delay(10);
        delay(50);
        return;
      }
    }
  }
}


void gameOver() {
  Serial.print("Game over! Score: ");
  Serial.println(level - 1);
  for (int t = 0; t < 6; t++) {
    for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], HIGH);
    delay(70);
    for (int i = 0; i < NUM_COLORS; i++) digitalWrite(LED_PINS[i], LOW);
    delay(70);
  }
  delay(1000);
}
