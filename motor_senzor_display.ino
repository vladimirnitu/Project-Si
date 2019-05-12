#include <LiquidCrystal.h> 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // creaza o variabila de tip LiquidCrystal, aceasta are rolul de a conecta pinii aceia la pinii de pe ecranul LCD  folosim 8 data reg

// Partea dreapta - Motor A
int IN1=10;
int IN2=11;

// partea stanga  Motor B 
int IN3 = 12;
int IN4= 13;

//controlSenzor
const int trigPin1 = 3;
const int echoPin1 = 2;

const int distantaPericol =50;
long duration1;
int distance1;


void setup() 
{
//SET PIN MODES
  lcd.begin(16, 2); // initializare lcd cu  16 coloane si 2 randuri
  Serial.begin(9600); //bits the data rate in bits per second // numarul de biti pe care ii trimite de odata placii (cantitatea de biti pe secunda care este trimisa placii)
  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(IN1 , OUTPUT);
  pinMode(IN2 , OUTPUT);
  pinMode(IN3 , OUTPUT);
  pinMode(IN4 , OUTPUT);
}
  
void startCar() 
{
  digitalWrite( IN1 , HIGH);
  digitalWrite( IN2 , LOW);
  digitalWrite( IN3 , HIGH);
  digitalWrite( IN4 , LOW);
}

void reverseCar() 
{
  digitalWrite( IN1 , LOW);
  digitalWrite( IN2 , HIGH);
  digitalWrite( IN3 , LOW);
  digitalWrite( IN4 , HIGH);
}

void stopCar() 
{
  digitalWrite( IN1 , LOW);
  digitalWrite( IN2 , LOW);
  digitalWrite( IN3 , LOW);
  digitalWrite( IN4 , LOW);
}

void stanga()
{                                                                                                
  digitalWrite( IN1 , HIGH);
  digitalWrite( IN2 , LOW);
  digitalWrite( IN3 , LOW);
  digitalWrite( IN4 , LOW);
}

void dreapta()
{
  digitalWrite( IN1 , LOW);
  digitalWrite( IN2 , LOW);
  digitalWrite( IN3 , HIGH);
  digitalWrite( IN4 , LOW);
}

int senzor1()
{
// Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH); // transmite un "impuls"
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH); //the length of the pulse (in microseconds) or 0 if no pulse started before the timeout (unsigned long)

// Calculating the distance
  distance1= duration1*0.034/2;

// Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance1);

  return distance1;
}

void loop()
{
  lcd.setCursor(0, 3);
  lcd.print(senzor1());
  if((senzor1() > 5)&&(senzor1() < 15))
    {  lcd.setCursor(5,10);
       lcd.print("|||");
       delay(500);
       Serial.print("Zona 1");
    } else if((senzor1() > 15) && (senzor1() < 50))
              { lcd.setCursor(6,10);
                lcd.print("||");
                delay(500);
                Serial.print("Zona 2");
              } else if((senzor1() > 50)&&(senzor1() < 80))
                        { lcd.setCursor(7,10);
                          lcd.print("|");
                          delay(500);
                          Serial.print("Zona 3");
                        } else
                          { lcd.setCursor(5,10);
                            lcd.print("          ");
                            lcd.setCursor(6,10);
                            lcd.print("           ");
                            lcd.setCursor(7,10);
                            lcd.print("           ");
                            Serial.print("Zona 4");
                          }
  if(analogRead(0)>1000 && senzor1() > distantaPericol)                                                                                                                                                     
  {
    startCar();
    delay(500);
  } else if(analogRead(1)>1000 && senzor1() > distantaPericol)
          {
            reverseCar();
            delay(500);
          } else if(senzor1() <distantaPericol)
                  { // daca senzorul masoara mai putin decat distanta periculoasa atunci sa se opreasca masina
                    Serial.println("STOP");
                    stopCar();
                    delay(500);
                    dreapta();
                    delay(500);
                    stopCar();
                  }
}
