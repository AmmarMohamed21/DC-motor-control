#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
bool num=false;
int speed=0;
const int MaxRPM = 192;
char dirlcd1=' ';
char dirlcd2=' ';
char dirlcd3=' ';
char splcd1=' ';
char splcd2=' ';
char splcd3=' ';
char rpm1=' ';
char rpm2=' ';
char rpm3=' ';
int rpmsp1;
int rpmsp2;
int rpmsp3;
int motorPin=5;
int dir1=7;
int dir2=6;
const byte Rows= 4; 
const byte Cols= 4; 
char keymap[Rows][Cols]= { 
{'7', '8', '9', 'a'}, 
{'4', '5', '6', 'b'}, 
{'1', '2', '3', '-'}, 
{'o', '0', '=', '+'} }; 
byte rowPins[Rows]= {3,2,1,0};  
byte colPins[Cols]= {A5,A4,A3,A2}; 
Keypad keypad = Keypad( makeKeymap(keymap), rowPins, colPins, 4, 4); 
void setup() { 
lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Direction:");
  lcd.setCursor(0,1);
  lcd.print("Speed:");
  lcd.setCursor(13,1);
  lcd.print("RPM");
pinMode (dir1, OUTPUT);
pinMode (dir2, OUTPUT);
pinMode (motorPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

if (key=='o')
{
rpm1=' ';
rpm2=' ';
rpm3=' ';
while (key != '=' )
{
key=keypad.getKey();
if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9')
  num=true;
else
 num=false;
if (rpm1 == ' ' && num)
{
rpm1=key;
}
else if (rpm2 == ' ' && num)
{
rpm2=key;
}
else if (rpm3 == ' ' && num)
{
rpm3=key;
}
}
}

rpmsp1=rpm1-'0';
rpmsp2=rpm2-'0';
rpmsp3=rpm3-'0';
speed=rpmsp1*100+rpmsp2*10+rpmsp3;
if (rpm3 == ' ')
{
 speed=rpmsp1*10+rpmsp2;
}
if (rpm2 == ' ')
{
  speed=rpmsp1;
}

if (rpm1 == ' ')
{rpm1='0';
speed=0;
}
if (speed > MaxRPM)
{
speed=0;
splcd1='0';
splcd2='0';
splcd3='0';
}
else
{splcd3=rpm3;
splcd2=rpm2;
splcd1=rpm1;
}
char direction=key;
if (direction == 'a')
{ 
digitalWrite (dir1, HIGH);
digitalWrite (dir2, LOW);
dirlcd1='C';
dirlcd2='W';
dirlcd3=' ';
}
else if (direction=='b') 
{ 
digitalWrite (dir1, LOW);
digitalWrite (dir2, HIGH);
dirlcd1='C';
dirlcd2='C';
dirlcd3='W';
}
speed=map(speed, 0, MaxRPM, 0, 255);
analogWrite(motorPin, speed);
  lcd.setCursor(8, 1);
{  lcd.print(splcd1);
lcd.print(splcd2);
lcd.print(splcd3);
}
  lcd.setCursor(11,0);
{
  lcd.print(dirlcd1);
lcd.print(dirlcd2);
lcd.print(dirlcd3);

}
}
