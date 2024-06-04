#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int beverageCount = 1;
int snackCount = 5;
int balance = 0;
const int beveragePrice = 3;
const int snackPrice = 5;
int selectedProductPrice = snackPrice;
String selectedProduct = "Snack";

const int purchaseButtonPin = 2;
const int coinButtonPin = 3;
const int beverageButtonPin = 5;
const int snackButtonPin = 6;
const int buzzerPin = 4;

int purchaseButtonState = 0;
int coinButtonState = 0;
int beverageButtonState = 0;
int snackButtonState = 0;

void setup() {
  pinMode(purchaseButtonPin, INPUT_PULLUP);
  pinMode(coinButtonPin, INPUT_PULLUP);
  pinMode(beverageButtonPin, INPUT_PULLUP);
  pinMode(snackButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(20, 4);
  updateDisplay();
}

void loop() {
  purchaseButtonState = digitalRead(purchaseButtonPin);
  coinButtonState = digitalRead(coinButtonPin);
  beverageButtonState = digitalRead(beverageButtonPin);
  snackButtonState = digitalRead(snackButtonPin);

  if (beverageButtonState == LOW) {
    selectedProductPrice = beveragePrice;
    selectedProduct = "Beverage";
    updateDisplay();
    delay(500);
  }

  if (snackButtonState == LOW) {
    selectedProductPrice = snackPrice;
    selectedProduct = "Snack";
    updateDisplay();
    delay(500);
  }

  if (purchaseButtonState == LOW) {
    if (selectedProduct == "Beverage" && beverageCount > 0 && balance >= selectedProductPrice) {
      beverageCount--;
      balance -= selectedProductPrice;
      dispensingAnimation();
      updateDisplay();
      delay(500);
    } else if (selectedProduct == "Snack" && snackCount > 0 && balance >= selectedProductPrice) {
      snackCount--;
      balance -= selectedProductPrice;
      dispensingAnimation();
      updateDisplay();
      delay(500);
    } else if (selectedProduct == "Beverage" && beverageCount == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Out Of Stock!");
      delay(1000);
      updateDisplay();
    } else if (selectedProduct == "Snack" && snackCount == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Out Of Stock!");
      delay(1000);
      updateDisplay();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please insert");
      lcd.setCursor(0, 1);
      lcd.print("correct amount");
      delay(1000);
      updateDisplay();
    }
  }

  if (coinButtonState == LOW) {
    balance++;
    updateDisplay();
    delay(500);
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Balance: ");
  lcd.print(balance);
  lcd.print(" PLN");
  lcd.setCursor(0, 1);
  lcd.print(selectedProduct);
  lcd.print(": ");
  lcd.print(selectedProductPrice);
  lcd.print(" PLN");
  lcd.setCursor(0, 2);
  lcd.print("Beverages: ");
  lcd.print(beverageCount);
  lcd.setCursor(0, 3);
  lcd.print("Snacks: ");
  lcd.print(snackCount);
}

void dispensingAnimation() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dispensing...");

  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Dispensing   ");
    tone(buzzerPin, 500);
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Dispensing.  ");
    noTone(buzzerPin);
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Dispensing.. ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
    delay(500);
  }
}
