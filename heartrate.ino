int sensorPin = 2;
int buzzer = 4;


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
   
}
void loop ()
{ 
  if(index_ == length_){
    
    median = median/length_;
    Serial.print(median);
    Serial.print('\n');


    if(median>remember_median){
    
      tone(buzzer,1000);
    }else{
      noTone(buzzer);
    }
    remember_median = median;
    old_value = value;
    delay(period);
    index_ = 0;
  }
  index_++;
  
  static double old_value = 0;
  static double old_change = 0;
  int raw_value = analogRead(sensorPin);
  double value = alpha * old_value + (1-alpha) * raw_value*0.1;
  median = (median + value);
  
  
  


} 
