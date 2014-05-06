/*
  Button Test Sketch (LED optional)
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 7. 
 The circuit:
 * LED attached from pin 13 to ground 
 * momentary switch attached to pin 2 from +5V
 * 10K resistor attached as pull-down resistor
 */
//constants
const int buttonPin = 2;     // <=======  the number of the pushbutton pin
const int ledPin =  13;      // <=======  the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int count= 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);      // initialize the LED pin as an output:
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input:
  Serial.begin(9600);  
}

void loop()
{
  buttonState = digitalRead(buttonPin);     // read the state of the pushbutton value:
  //Serial.println(buttonState);

  if (buttonState == HIGH)       // check if the pushbutton is pressed.
  {     
    digitalWrite(ledPin, HIGH);  // turn LED on: (send +5V to pin)
 //   Serial.println("            Button is ON ");    //  print to serial monitor
    count++;
    Serial.println(count);
  } 
  else 
  {
    digitalWrite(ledPin, LOW);     // turn LED off: (send 0V to pin)
  //      Serial.println(" Button is OFF ");      // print text to serial monitor
  }
  delay(200);        // delay so that print to serial monitor is not too fast
}
