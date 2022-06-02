

#include <LiquidCrystal.h>





LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


String phrase = ""; 
char guesses [20];
int guessNum = 0;
int lives = 6;
int player = 1;
int correct = 0;
int p1W = 0;
int p1L = 0;
int p2W = 0;
int p2L = 0;

byte welcomeScreenPole[8] = { 0b00111,
                              0b00101,
                              0b00100,
                              0b00100,
                              0b00100,
                              0b00100,
                              0b00100,
                              0b11111 };
                          
byte wrong1[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00000,
                   0b00000,
                   0b00000,
                   0b00000,
                   0b00000 };

byte wrong2[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00100,
                   0b00100,
                   0b00100,
                   0b00000,
                   0b00000 };

byte wrong3[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00100,
                   0b00111,
                   0b00100,
                   0b00000,
                   0b00000 };

byte wrong4[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00100,
                   0b11111,
                   0b00100,
                   0b00000,
                   0b00000 };

byte wrong5[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00100,
                   0b11111,
                   0b00100,
                   0b01000,
                   0b01000 };

byte wrong6[8] = { 0b11100,
                   0b01110,
                   0b01110,
                   0b00100,
                   0b11111,
                   0b00100,
                   0b01010,
                   0b01010 };
                   
byte pole[8] = { 0b00111,
                 0b00100,
                 0b00100,
                 0b00100,
                 0b00100,
                 0b00100,
                 0b00100,
                 0b00100 };




void setup() 
{
  

  lcd.createChar(0, welcomeScreenPole);
  
  lcd.createChar(1, wrong1);
  lcd.createChar(2, wrong2);
  lcd.createChar(3, wrong3);
  lcd.createChar(4, wrong4);
  lcd.createChar(5, wrong5);
  lcd.createChar(6, wrong6);

  lcd.createChar(7, pole);
  

  Serial.begin (9600);

 
  lcd.begin(16, 2);
  

  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
    
  lcd.print (" HANGMAN ");
  
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)0);
  
  lcd.setCursor(3,2);
  lcd.print("2 Jucatori");
  delay (3000);
  lcd.clear();
}




void loop() 
{

  getPhrase ();


 
  lcd.print("Ghiceste");
  

  lcd.setCursor (14,1);
  lcd.print("|");
  
  lcd.setCursor (14,0);
  lcd.write((uint8_t)7);

  
  lcd.setCursor(0,2);
  for (int i = 0; i < phrase.length(); i ++)
  {
    lcd.print("_");
  }


  while (lives > 1 && correct != phrase.length())
  {

    updateScreen(correctness(getGuess()));
  }
  
  delay (400);
  lcd.clear();
  

  if (player == 1)
  {
    if (lives <= 1)
    {
      lcd.print("    LOSS !!!    ");
      p1L ++;
    }
      
    else
    {
      lcd.print("     WIN!!!     ");
      p1W ++;
    }
      
    player = 2;
  }
  
  else
  {
    if (lives <= 1)
    {
      lcd.print("    LOSS !!!    ");
      p2L ++;
    }
    else
    {
      lcd.print("     WIN!!!     ");
      p2W ++;
    }
      
    player = 1;
  }

  delay (1000);
  

  phrase = "";
  guessNum = 0;
  lives = 6;
  correct = 0;

  for (int i = 0; i < 20; i ++)
  {
    guesses[i] = '\0';
  }


  lcd.clear();
}





void getPhrase ()
{
  
  lcd.print ("PL");
  lcd.print (player);
  lcd.print("|");
  
  if (player == 1)
  {
    lcd.print("  W:");
    lcd.print(p1W);
    lcd.print("  L:");
    lcd.print(p1L);
  }
  else
  {
    lcd.print("  W:");
    lcd.print(p2W);
    lcd.print("  L:");
    lcd.print(p2L);
  }
  
  lcd.setCursor(0,2);
  lcd.print("  Introdu cuvant");
  
  while (phrase.length() == 0)
  {
    if (Serial.available() > 0)
    {
      phrase = Serial.readString();

      if (phrase.length() > 14)
      {
  
        lcd.clear();
        lcd.print ("PL");
        lcd.print (player);
        lcd.print("|  Prea lung");

        delay(1000);
        lcd.clear ();

        lcd.print ("PL");
        lcd.print (player);
        lcd.print("|  Introdu cuvant");
        
        phrase = "";
      } 
    }
  }

  phrase.toUpperCase();
  lcd.clear();
}





char getGuess ()
{
  char guess = '-';
  
  while (guess == '-')
  {
    if (Serial.available() > 0)
    {
      String temp = Serial.readString();
      temp.toUpperCase();
      guess = temp.charAt(0);
    }
  }
  
  return guess;
}




int correctness (char guess)
{
  
  for (int i = 0; i < phrase.length(); i ++)
  {
    if (guess == guesses[i])
    {
      return 0;
    }
      
      
    if (phrase.charAt(i) == guess)
    {
      guessNum ++;
      guesses [guessNum-1] = guess;
      return 1;
    }
  }

  
  lives --;
  guessNum ++;
  guesses [guessNum-1] = guess;
  
  return -1;
  
}




void updateScreen (int code)
{  
  if (code == 0)
  {
    for (int i = 0; i < 3; i ++)
    {
      lcd.setCursor(0,0);
      lcd.print("    REPETAT    ");
      delay(200);
      lcd.setCursor(0,0);
      lcd.print("              ");
      delay(200);
    }
    
    lcd.setCursor(0,0);
    lcd.print("Ghiceste");
  }
  
  if (code == 1)
  {
    for (int i = 0; i < phrase.length(); i ++)
    {
      if (phrase.charAt(i) == guesses [guessNum-1])
      {
        correct ++;
        lcd.setCursor(i,1);
        lcd.print(guesses [guessNum-1]);
      }
    }
    
  }

  if (code == -1)
  {
    lcd.setCursor(15,0);
    lcd.write((uint8_t)(7-lives));
  }
}