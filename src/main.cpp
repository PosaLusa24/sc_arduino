#include <Arduino.h>
#include <LiquidCrystal.h>

#define LED_RED         13
#define LED_YELLOW      10 
#define LED_GREEN       9 
#define BUZZER          8
#define LCD_CONTRAST    6

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup () {
    Serial.begin(9600);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    analogWrite(LCD_CONTRAST, 10);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("READY");
}

void loop () {
    if (Serial.available() > 0) {
        String chunk;
        char x;

        chunk = "";
        x = Serial.read();
        while (x != '\n') {
            if (isascii(x)) chunk +=x ;
            x = Serial.read();
        }
        Serial.print(chunk);

        if (chunk == "scom_lcd>") {
            chunk = "";
            x = Serial.read();
            while (x != '\n') {
                if (isascii(x)) chunk +=x ;
                x = Serial.read();
            }
            lcd.clear();
            lcd.print(chunk);
            Serial.print(chunk);
        } else if (chunk == "scom_feedback>") {
            chunk = "";
            x = Serial.read();
            while (x != '\n') {
                if (isascii(x)) chunk +=x ;
                x = Serial.read();
            }
            Serial.print(chunk);
            if (chunk == "N") {
                digitalWrite(LED_RED, HIGH);
                tone(BUZZER, 10000);
                delay(250);
                noTone(BUZZER);
                delay(250);
                tone(BUZZER, 10000);
                delay(250);
                noTone(BUZZER);
                delay(1250);
                digitalWrite(LED_RED, LOW);
            } else if (chunk == "Y") {
                delay(150);
                tone(BUZZER, 5000);
                delay(350);
                noTone(BUZZER);

                digitalWrite(LED_RED, HIGH); 
                delay(900);
                digitalWrite(LED_RED, LOW);

                digitalWrite(LED_YELLOW, HIGH);
                delay(900);
                digitalWrite(LED_YELLOW, LOW);

                digitalWrite(LED_GREEN, HIGH);
                delay(900);
                digitalWrite(LED_GREEN, LOW);
                
            }
        }
    }
}
