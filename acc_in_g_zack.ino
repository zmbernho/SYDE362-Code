// http://chionophilous.wordpress.com/2011/06/20/getting-started-with-accelerometers-and-micro-controllers-arduino-adxl335/  
// these constants describe the pins. They won't change:
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis
const int ledPin = 13;
//
int sampleDelay = 1;   //number of milliseconds between readings
void setup()
{
 // initialize the serial communications:
 Serial.begin(9600);
 //
 //Make sure the analog-to-digital converter takes its reference voltage from
 // the AREF pin
 pinMode(xpin, INPUT);
 pinMode(ypin, INPUT);
 pinMode(zpin, INPUT);
 pinMode (ledPin, OUTPUT);
}
int x3 = analogRead(xpin);
int x2 = x3;
int x1 = x2;
int x_ave1 = x1;
int x_ave2 = x1;
int xdif = x1;
//
int y3 = analogRead(ypin);
int y2 = y3;
int y1 = y2;
int y_ave1 = y1;
int y_ave2 = y1;
int ydif = y1;
//
int z3 = analogRead(zpin);
int z2 = z3;
int z1 = z2;
int z_ave1 = z1;
int z_ave2 = z1;
int zdif = z1;
//
void loop()
{
 int x3 = x2;
 int x2 = x1;
 int x1 = analogRead(xpin);
 //
 //add a small delay between pin readings.  I read that you should
 //do this but haven't tested the importance
   delay(1); 
 //
 int y3 = y2;
 int y2 = y1;
 int y1 = analogRead(ypin);
 //
   delay(1); 
 //
 int z3 = z2;
 int z2 = z1;
 int z1 = analogRead(zpin) - 70;
 //
 //zero_G is the reading we expect from the sensor when it detects
 //no acceleration.  Subtract this value from the sensor reading to
 //get a shifted sensor reading.
 float zero_G = 512.0; 
 //
 //scale is the number of units we expect the sensor reading to
 //change when the acceleration along an axis changes by 1G.
 //Divide the shifted sensor reading by scale to get acceleration in Gs.
 float scale = 170.7;
 
 xdif = abs(x2 - x1);
 
 ydif = abs(y2 - y1);
 
 zdif = abs(z2 - z1);
 
 float x_G = ((float)xdif - zero_G)/scale;
 float y_G = ((float)ydif - zero_G)/scale;
 float z_G = ((float)zdif - zero_G)/scale;
 float accel = sqrt(pow(x_G,2)+pow(y_G,2)+pow(z_G,2));
 //
 Serial.print(x1);
 Serial.print("\t");
 //
 Serial.print(y1);
 Serial.print("\t");
 //
 Serial.print(z1);
 Serial.print("\t");
 //
 //
 Serial.print(x_G);
 Serial.print("\t");
 //
 Serial.print(y_G);
 Serial.print("\t");
 //
 Serial.print(z_G);
 Serial.print("\t");
 //
 //
 Serial.print(xdif);
 Serial.print("\t");
 //
 Serial.print(ydif);
 Serial.print("\t");
 //
 Serial.print(zdif);
 Serial.print("\t");
 //
 Serial.print(accel);
 Serial.print("\n");
 //
 if (accel >= 1)
 {
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(10000);                 // waits for ten seconds
  digitalWrite(ledPin, LOW);    // sets the LED off
 }
 //
 // delay before next reading:
 delay(sampleDelay);
}
