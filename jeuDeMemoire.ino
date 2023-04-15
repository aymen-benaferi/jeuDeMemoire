#include<LiquidCrystal.h>
LiquidCrystal lcd(A5,A4,A3,A2,A1,A0);
void setup()
{
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(10, OUTPUT); 
   pinMode(9, OUTPUT); 
   pinMode(8, OUTPUT); 
  
   pinMode(7, INPUT_PULLUP);
   pinMode(6, INPUT_PULLUP);
   pinMode(5, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(2, INPUT_PULLUP);
 
  
  Serial.begin(9600);
  randomSeed(42); 
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("The Memory Game");
  lcd.setCursor(6,1);
  lcd.print("Ready...");
  delay(2000);
  lcd.clear();
  successed();
}

byte randomNumber,size=1,Highscore=0,life=10;
byte arr[250];
bool isSuccess = true,btn1,btn2,btn3,btn4,btn5,btn6;

bool secondLevel = true;
bool thirdLevel = true;
int maxNumber = 11;
void loop()
{
  Serial.println(size);
  for(byte i=0 ; i<size ;i++)
  {
	if(size > 1&&secondLevel==true)
    {
	  maxNumber = 12;
	  lcd.clear();
	  lcd.print("Level Up. Orange");
      lcd.setCursor(0,1);
	  lcd.print("Led Including");
      delay(2000);
	  lcd.clear();
	  secondLevel = false;
	  successed();
	}
	if(size > 2&&thirdLevel==true)
    {
	  maxNumber = 13;
	  lcd.clear();
	  lcd.print("Level Up. White");
      lcd.setCursor(0,1);
	  lcd.print("Led Including");
      delay(2000);
	  lcd.clear();
	  thirdLevel = false;
	  successed();
	}
	 
    randomNumber = random(8,maxNumber);
    arr[i]=randomNumber;
    digitalWrite(randomNumber,HIGH);
    delay(400);
    digitalWrite(randomNumber,LOW);
    delay(200);
   
    if(randomNumber==13)
     Serial.println("White");
    
	else if(randomNumber==12)
     Serial.println("Orange");
      
	else if(randomNumber==11)
     Serial.println("Red");
      
	else if(randomNumber==10)
     Serial.println("Blue");
	 
	else if(randomNumber==9)
     Serial.println("Yellow");
	 
	else if(randomNumber==8)
     Serial.println("Green");
   
  }
  
  for(byte i=0 ; i<size ;)
  {
    btn1=digitalRead(7);
    btn2=digitalRead(6);
    btn3=digitalRead(5);
    btn4=digitalRead(4);
	btn5=digitalRead(3);
	btn6=digitalRead(2);
    
    if(btn1&&btn2&&btn3&&btn4&&btn5&&btn6)
    {
      continue;
    }
    
    if(arr[i]==8&&!btn1&&btn2&&btn3&&btn4&&btn5&&btn6)
      i++;
    else if(arr[i]==9&&btn1&&!btn2&&btn3&&btn4&&btn5&&btn6)
      i++;
    else if(arr[i]==10&&btn1&&btn2&&!btn3&&btn4&&btn5&&btn6)
      i++;
    else if(arr[i]==11&&btn1&&btn2&&btn3&&!btn4&&btn5&&btn6)
      i++;
	else if(arr[i]==12&&btn1&&btn2&&btn3&&btn4&&!btn5&&btn6)
      i++;
	else if(arr[i]==13&&btn1&&btn2&&btn3&&btn4&&btn5&&!btn6)
      i++;
    else
    {
        life--;
		if(life)
        {
          lives();
        }
        else
        {
          isSuccess=false;
        }
      
      break;
    }
    delay(500);
  }

  if(isSuccess)
  {
    Serial.println("Sucessed");
    size++;
    successed();
  }
  else
  {
    
    Serial.println("Game over !");
    size=1;
    life=10;
    isSuccess=true;
    over();
  }
}

void buttonWait(int buttonPin){
  int buttonState = 0;
  while(1){
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      return;
    }
  }
}

void successed()
{
  	lcd.clear();
    lcd.print("Score: ");
    lcd.print(size-1);
    lcd.setCursor(0,1);
}
void over()
{
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Game");
    lcd.setCursor(8,1);
    lcd.print("over !");
    delay(1000);
    successed();
}
void lives()
{
  lcd.clear();
  	for(byte i=0 ; i<life ;i++)
      lcd.print("#");
 	
  lcd.setCursor(0,1);
  lcd.print(" U've a ");
  lcd.print(life);
  lcd.print(" life");
  delay(1000);
  size--;
  successed();

}