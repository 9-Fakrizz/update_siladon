#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

///////////////setup keypad variable ///////////////
#define button1 10
#define solenoid 13

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27, 20, 4);
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
char inputText[3] = "";

////// index variable ///////
int but1;
bool task = false;


//////// function for receive input from keypad ///////////
void type_input(){
  
  char key = keypad.getKey(); // recieve key from keypad 
  but1 = digitalRead(button1); // read button

  lcd.setCursor(3,0);   //set position of lcd
  lcd.print("Input : ");
  Serial.print("key : ");
  Serial.print(key);
  Serial.print("  strlen : ");
  Serial.println(strlen(inputText));

if(key){

  // if key = D then clear lcd and start process //
  if(key == 'D'){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Processing...");
    task = true;
  }
  // reset lcd every time that input more than 2 //
  if(strlen(inputText)==2 && task == false){
    lcd.clear();
    memset(inputText, 0, sizeof(inputText));
  }

  // move cursor position when input another //
  if(strlen(inputText)<2 && task == false){
    inputText[strlen(inputText)] = key;
    lcd.setCursor(10+strlen(inputText), 0);
    lcd.print(key);
  }

  // clear lcd if key = c //
  if(key == 'C'){
    lcd.clear();
    memset(inputText, 0, sizeof(inputText));
  }
 }
}


void setup() {
  Serial.begin(9600);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();

  pinMode(button1, INPUT);
  pinMode(solenoid, OUTPUT);
  digitalWrite(solenoid, HIGH);


}

void loop() {

  if(task == false){
    type_input();
    digitalWrite(solenoid, HIGH); // solenoid still off
  }

  if(task == true){
    char key = keypad.getKey();
    if(key == 'D'){
      lcd.clear();
      task = false;
    }
    Serial.println(inputText);
    if(strcmp((inputText), "#0")==0){
      Serial.println("solenoid on");
      digitalWrite(solenoid, LOW);   // solenoid turn on
    }
  }

}
