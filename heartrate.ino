#include <LiquidCrystal.h>


int sensorPin = 1;
int buzzer = 0;



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



byte customChar[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};


byte customChar2[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

double alpha = 0.025;
// the delay
int period = 200;
double change = 0.0;
double minval = 0.0;
//the previous median of len amount of values
int remember_median = 0;
// the amount of values we are taking into consideration for the median
int index_ = 0;
// the initial median value
double median = 0;
// by how much to fraction 
int length_ = 15;
double old_value = 0;
double value = 0;


void setup() {
   Serial.begin(9600);
   lcd.begin(16, 2);
   
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write((byte)0);
   
}
void loop ()
{ 
  lcd.setCursor(2, 0);
  
  if(index_ == length_){
    
    median = median/length_;
    Serial.print(median);
    Serial.print('\n');
    lcd.print("Heart rate ");
    lcd.print(int(round(median)));


    if(median>remember_median){

      noTone(buzzer);
      lcd.createChar(0, customChar);
      lcd.home();
      lcd.write((byte)0);
  
    }else{
      tone(buzzer,1000);
      lcd.createChar(0, customChar2);
      lcd.home();
      lcd.write((byte)0);
    }
    remember_median = median;
    old_value = value;
    delay(period);
    index_ = 0;
    delay(10);
  }
  index_++;
  
  static double old_value = 0;
  static double old_change = 0;
  int raw_value = analogRead(sensorPin);
  double value = alpha * old_value + (1-alpha) * raw_value*0.1;
  median = (median + value);
  
  
  


} 
