#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define dlugoschasla 7 

int pozycja ;   

char rozmiarhasla[dlugoschasla];
char prawidlowe_haslo[dlugoschasla] = "111111"; 
byte wpis =0;

char klawisz ; 

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
bool zamek = 1 ; 

byte rowPins[ROWS] = {14, 15, 16, 17}; 
byte colPins[COLS] = {18, 19, 20, 21}; 

Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  myservo.attach(A8);
  ZamekZamykanie();
  lcd.begin(16, 2);
  lcd.print(" Zamek do drzwi");
  lcd.setCursor(0, 1);
  lcd.print("Projekt");
  delay(3000);
  lcd.clear();

}

void loop()
{
  if (zamek == 0)
  {
    klawisz= klawiatura.getKey();

    if (klawisz== '#')

    {
      lcd.clear();
      ZamekZamykanie();
      lcd.print("Drzwi zamkniete");
      delay(3000);
      zamek = 1;
      lcd.clear (); 
    }
  }

  else DrzwiOtwieranie();
}

void ZerowanieWartosci()
{
  while (wpis != 0)
  { 
    rozmiarhasla[wpis--] = 0; 
  }
  return;
}

void ZamekOtwieranie()
{
  for (pozycja = 180; pozycja >= 0; pozycja -= 5) { 
    myservo.write(pozycja);              
    delay(15);                       
  }
}

void ZamekZamykanie()
{
  for (pozycja = 0; pozycja <= 180; pozycja+= 5) { 
    myservo.write(pozycja);            
    delay(15);                       
  }
}

void DrzwiOtwieranie()
{
  lcd.setCursor(0, 0);
  lcd.print("Podaj Haslo");
  
 klawisz = klawiatura.getKey();
  if (klawisz) 
  {
    rozmiarhasla[wpis] = klawisz; 
    lcd.setCursor(wpis, 1); 
    lcd.print(rozmiarhasla[wpis]); 
    wpis++; 
  }

  if (wpis == dlugoschasla - 1) 
  {
    if (strcmp(rozmiarhasla, prawidlowe_haslo)==0) 
    {
      lcd.clear();
      ZamekOtwieranie();
      lcd.print("Drzwi otwarte");
      zamek = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("Zle haslo");
      delay(1000);
     zamek= 1;
    }
    ZerowanieWartosci();
  }
}
