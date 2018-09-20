void screen0() {    // Jedes Menü hat einen Screen
  lcd.clear();
  lcd.print(F("Am Amfang"));
}

/*
  x=menue0
  string nrmenue[x]

  y=submenue
*/

const String PROGMEM menue0char[4]  = {"Innen", "Aussen", "Uhr", "SD Karte"};

//zeilen dann spalten
/*const  PROGMEM  char subMenue[][3]  = {
  {'Temperatur', 'Relative Feuchte', 'anspolute Feuchte'},
  {'Temperatur', 'Relative Feuchte', 'anspolute Feuchte'},
  {'Uhrzeit', 'Datum', ' ' },
  {'initialisiert', 'speicher', ' '}
  };
*/

const String PROGMEM subMenue[][3]  = {
  {"Temperatur", "Relative Feuchte", "anspolute Feuchte"},
  {"Temperatur", "Relative Feuchte", "anspolute Feuchte"},
  {"Uhrzeit", "Datum", " " },
  {"initialisiert", "speicher", " "}
};

//const String PROGMEM
const String PROGMEM  test[][4] = {
  {"Das 1", "Dann 2", "oder 3", "doch 4"},
  {"nr 1", "nr 2", "nnr 3", "rrnn 4"}
};

void screen2() {
  lcd.clear();
  lcd.home();
  lcd.print(menue0);
  lcd.print(". ");
  lcd.print(test[1][menue0 - 1]);
}

void screenMenue0() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menue0);
  lcd.print(".");
  lcd.print(menue0char[menue0 - 1]);
  lcd.setCursor(0, 1);
  lcd.print(submenue);
  lcd.print(".");
  lcd.print(subMenue[menue0 - 1][submenue - 1]);
}

void screenSubMenue() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(submenue);
  lcd.print(".");
  lcd.print(subMenue[menue0 - 1][submenue - 1]);
  lcd.setCursor(0, 1);
  lcd.print("Wert");
}

void screenWert() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wert");
  lcd.setCursor(0, 1);
  lcd.print("hier steht der Wert");

}

