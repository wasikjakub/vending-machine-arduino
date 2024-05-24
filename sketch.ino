#include <LiquidCrystal.h>

// Inicjalizacja wyświetlacza LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Zmienne do przechowywania salda konta i cen produktów
int balance = 0;
const int beveragePrice = 3; 
const int snackPrice = 5; 
int selectedProductPrice = snackPrice; 
String selectedProduct = "Snack"; 

// Piny przycisków i buzzera
const int purchaseButtonPin = 2;
const int coinButtonPin = 3;
const int beverageButtonPin = 5;
const int snackButtonPin = 6;
const int buzzerPin = 4;

// Zmienne do odczytu stanu przycisków
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
  lcd.begin(16, 2);
  updateDisplay();
}

void loop() {
  // Odczytanie stanu przycisków
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

  if (purchaseButtonState == LOW && balance >= selectedProductPrice) {
    balance -= selectedProductPrice;
    dispensingAnimation();
    updateDisplay();
    delay(500);
  }
 
  if (coinButtonState == LOW) {
    balance++;
    updateDisplay();
    delay(500);
  }
}

// Funkcja aktualizująca wyświetlacz
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
}

// Funkcja wyświetlająca animację wydawania produktu
void dispensingAnimation() {

  for (int i = 0; i < 3; i++) {
    lcd.clear();
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
