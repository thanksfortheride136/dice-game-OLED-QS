//must use small OLED square screen
//must use adafruit ssd1306 library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int button_pin = 10;
long dice_one, dice_two, player_score, computer_score;

// Create display object (128x64 pixels, using I2C)
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

void setup() {
  // Initialize OLED screen
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Halt if screen isn't found
  }

  // Initial screen message
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println(F("Press Button To"));
  oled.println(F("Roll Dice!"));
  oled.display();
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  readButton();
}

void readButton() {
  if (digitalRead(button_pin) == LOW) {
    delay(1000);  // debounce delay
    diceRoll();
  }
}

void diceRoll() {
  oled.clearDisplay();
  dice_one = random(1, 7);  // 1 to 6
  dice_two = random(1, 7);

  // Update score first
  scoreUpdate();

  Serial.println("Dice 1: " + String(dice_one));
  Serial.println("Dice 2: " + String(dice_two));

  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.print("Player Dice: ");
  oled.println(dice_one);

  oled.setCursor(0, 20);
  oled.print("Computer Dice: ");
  oled.println(dice_two);

  oled.setCursor(0, 40);
  oled.println("Scores: ");
  oled.setCursor(0, 50);
  oled.println("Player: " + String(player_score));
  oled.setCursor(62, 50);
  oled.println("Computer: " + String(computer_score));

  oled.display();
}


void scoreUpdate(){
  if(dice_one > dice_two){
    player_score = player_score + 1;
  } else if (dice_one < dice_two){
    computer_score = computer_score + 1;
  }
}
