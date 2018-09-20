#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x20 for a 16 chars and 2 line display


#define links 3
#define hoch 4    //hoch
#define runter 5
#define rechts 6  //rechts

const int numberButtons = 4;
int button[numberButtons] = {links, hoch, runter, rechts};
int lastButtonState[numberButtons];
bool buttonActive[numberButtons];
unsigned long lastDebounceTime[numberButtons];

int debounceDelay = 25;
int longPressDelay = 500;

void buttonSetup() {
  for (int x = 0; x < numberButtons; x++)
  {
    lastButtonState[x] = HIGH;
    buttonActive[x] = false;
    lastDebounceTime[x] = 0;
    // buttonState[x]=HIGH;
    pinMode(button[x], INPUT_PULLUP);

  }
}

//unsigned int anzahlMenue0 = 4;
#define anzahlMenue0 4
unsigned int anzahlSubMenue [anzahlMenue0+1] = {0, 3, 3, 2, 1}; //Anzahl der Submenues pro Menue. 0 ist nur ein Platzhalter 
unsigned int anzahlPos = 3;
unsigned int wert [10]={}; //Wert der im Submenue angezeigt wird oder änderbar ist... Anzahl der Spalten ergibt sich aus der Summe der Submenues.
unsigned int menue0 = 1;   //Hauptmenü
unsigned int submenue = 1; //Untermenü
unsigned int pos = 1;      //aktuelle Positon im Menü. Je nach Wert wird das Menü,Submenü oder der Wert durch die Cursor bearbeitet.

//Funktions-Prototyp damit der compiler die Funktion schon mal kennt. Vor dem Benutzen
void screen0() ;
int buttonHandler(int number) ;
void screen();
void screen2();
void screenMenue0();
void screenSubMenue();
void screenWert();


void setup() {
  Serial.begin(19200);
  lcd.init();                      // initialize the lcd
  lcd.begin(16, 2);
  buttonSetup();
  //screen0();
}



unsigned long pause = 1000;
unsigned long lastMillis;

void loop() {
  unsigned long aktuelleMillis = millis();

  if (aktuelleMillis - lastMillis >= pause ) {
    lastMillis = aktuelleMillis;

  }
  menues();

}


// menues dient dazu die Anzahl von Menuepunkte zu verwalten bzw. die Navigation mit Buttons in den Menüs zu organisieren. Die Screens habe eine eigen Funktion.
void menues() {
  for (int x = 0; x < numberButtons; x++) {
    int state = buttonHandler(x);
    if (state != 0) {
      /*
          Serial.print("Nr:");
        Serial.print(button[x]);
        Serial.print(" ist=");
        Serial.print(buttonActive[x]);
        Serial.print(" state=");
        Serial.println(state);
      */
      //Steuert durch die Ebende 1 Menue0 2 subMenue 3 Werte
      if (button[x] == hoch) {
        pos++;
        if (pos < 1) {
          pos = anzahlPos;
        }
        if (pos > anzahlPos) {
          pos = 1;
        }
        Serial.print("Pos=");
        Serial.println(pos);
      }

      if (pos == 1) {
        if (button[x] == links) {
          Serial.print("coursor L ");
          menue0--;
          if (menue0 < 1) {
            menue0 = anzahlMenue0;
          }
          Serial.println(menue0);
        }

        if (button[x] == rechts) {
          Serial.print("coursor R ");
          menue0++;
          if (menue0 > anzahlMenue0) {
            menue0 = 1;
          }
          Serial.println(menue0);
        }
        screenMenue0();
      }
      
      if (pos == 2) {
        if (button[x] == links) {
          Serial.print("submenue L ");

          submenue--;
          anzahlSubMenue[menue0];
          if (anzahlSubMenue[menue0] < 1) {
            submenue = anzahlSubMenue[menue0];
          }
          Serial.println(submenue);
        }

        if (button[x] == rechts) {
          Serial.print("submenue R ");
          submenue++;
          if (submenue > anzahlSubMenue[menue0]) {
            submenue = 1;
          }
          Serial.println(submenue);
        }
        screenSubMenue();
      }
     if (pos == 3) {
      Serial.println("Wert");
      screenWert();      
     }
    }
  }
}

int buttonHandler(int number)
{
  //Handle presses for each button
  int reading = digitalRead(button[number]);

  //Check if button state has changed since last check
  if (reading != lastButtonState[number])
  {
    if (reading == HIGH && !buttonActive[number])
    {
      lastButtonState[number] = reading;

      //Return 0 (not pressed)
      return 0;
    }

    //if reading is high (open)
    if (reading == HIGH && buttonActive[number])
    {
      if (millis() - lastDebounceTime[number] > debounceDelay)
      {
        lastButtonState[number] = reading;

        buttonActive[number] = true;

        //Return 1 (short press)
        return 1;
      }

      lastButtonState[number] = reading;

      buttonActive[number] = false;

      //Return 0 (not pressed)
      return 0;
    }

    //if reading is low (closed)
    else if (reading == LOW)
    {
      if (!buttonActive[number])
      {
        //Start debounce timer
        lastDebounceTime[number] = millis();

        lastButtonState[number] = reading;

        buttonActive[number] = true;

        //Return 0 (not pressed)
        return 0;
      }
      //Return 0 (not pressed)
      return 0;
    }
  }

  //Check if reading still high (open)
  if (reading == HIGH)
  {
    lastButtonState[number] = reading;
    buttonActive[number] = false;

    //Return 0 (not pressed)
    return 0;
  }


  if (reading == LOW)
  {
    //Check if button pressed for long enough to register as long press
    if (millis() - lastDebounceTime[number] > longPressDelay && buttonActive[number])
    {
      lastButtonState[number] = reading;

      buttonActive[number] = false;

      //Return 2 (long press)
      return 2;
    }
    else
      //Return 0 (not pressed)
      return 0;
  }
}


