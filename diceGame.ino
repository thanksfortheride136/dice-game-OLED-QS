//must use small OLED square screen
//must use adafruit ssd1306 library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int button_pin = 10;
long dice_one, dice_two, player_score, computer_score;

// Create display object (128x64 pixels, using I2C)
Adafruit_SSD1306 lcd(128, 64, &Wire, -1);

void setup() {
  // Initialize OLED screen
  if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // Halt if screen isn't found
  }

  // Initial screen message
  lcd.clearDisplay();
  lcd.setTextSize(1);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.println(F("Press Button To"));
  lcd.println(F("Roll Dice!"));
  lcd.display();
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
  lcd.clearDisplay();
  dice_one = random(1, 7);  // 1 to 6
  dice_two = random(1, 7);

  // Update score first
  scoreUpdate();

  Serial.println("Dice 1: " + String(dice_one));
  Serial.println("Dice 2: " + String(dice_two));

  lcd.setTextSize(1);
  lcd.setTextColor(SSD1306_WHITE);
  lcd.setCursor(0, 0);
  lcd.print("Player Dice: ");
  lcd.println(dice_one);

  lcd.setCursor(0, 20);
  lcd.print("Computer Dice: ");
  lcd.println(dice_two);

  lcd.setCursor(0, 40);
  lcd.println("Scores: ");
  lcd.setCursor(0, 50);
  lcd.println("Player: " + String(player_score));
  lcd.setCursor(62, 50);
  lcd.println("Computer: " + String(computer_score));

  lcd.display();
}


void scoreUpdate(){
  if(dice_one > dice_two){
    player_score = player_score + 1;
  } else if (dice_one < dice_two){
    computer_score = computer_score + 1;
  }
}
