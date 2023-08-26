// use an IR remote to control a RGB LED
// ejr: 2023-08-26
// combination of lesson 4 and lesson 14
// IR remote is from elegoo kit

/*-----( Includes )-----*/
#include "IRremote.h"

/*-----( Definitions )-----*/
// Define Pins for RGB LED
#define BLUE_PIN 3
#define GREEN_PIN 5
#define RED_PIN 6
// Define Pin for IR
#define IR_PIN 11
// Define buttons for IR reciever
#define BUTTON_0 0xE916FF00
#define BUTTON_1 0xF30CFF00
#define BUTTON_2 0xE718FF00
#define BUTTON_3 0xA15EFF00
#define BUTTON_4 0xF708FF00
#define BUTTON_5 0xE31CFF00
#define BUTTON_6 0xA55AFF00
#define BUTTON_7 0xBD42FF00
#define BUTTON_8 0xAD52FF00
#define BUTTON_9 0xB54AFF00
#define BUTTON_POWER 0xBA45FF00
#define BUTTON_STOP 0xB847FF00
#define BUTTON_VOL_UP 0xB946FF00
#define BUTTON_REV 0xBB44FF00
#define BUTTON_PAUSE 0xBF40FF00
#define BUTTON_FF 0xBC43FF00
#define BUTTON_DOWN 0xF807FF00
#define BUTTON_VOL_DOWN 0xEA15FF00
#define BUTTON_UP 0xF609FF00
#define BUTTON_EQ 0xE619FF00
#define BUTTON_ST_REPT 0xF20DFF00


/*-----( Initialize Variables )-----*/
//variable to store the last decodedRawData
uint32_t last_decodedRawData = 0;
int R = 0;
int G = 0;
int B = 0;

/*-----( Declare objects )-----*/
// this is for the remote
IRrecv irrecv(IR_PIN);     // create instance of 'irrecv'

/*-----( Functions )-----*/
void translateIR() // takes action based on IR code received
{
  // Check if it is a repeat IR code 
  if (irrecv.decodedIRData.flags)
  {
    //set the current decodedRawData to the last decodedRawData 
    irrecv.decodedIRData.decodedRawData = last_decodedRawData;
    Serial.println("REPEAT!");
  } else
  {
    //output the IR code on the serial monitor
    Serial.print("IR code:0x");
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
  }
  
  switch (irrecv.decodedIRData.decodedRawData)
  {
    case BUTTON_0: R =   0; G =   0; B =   0; break; //off
    case BUTTON_1: R = 255; G =   0; B =   0; break; //red
    case BUTTON_2: R = 255; G =  25; B =   0; break; //orange
    case BUTTON_3: R = 255; G =  50; B =   0; break; //yellow
    case BUTTON_4: R =   0; G = 255; B =   0; break; //green
    case BUTTON_5: R =   0; G =   0; B = 255; break; //blue
    case BUTTON_6: R =  50; G =   0; B = 255; break; //indigo
    case BUTTON_7: R = 255; G =   0; B = 255; break; //violet
    case BUTTON_8: R = 255; G =  10; B =  10; break; //pink
    case BUTTON_9: R = 255; G = 255; B = 255; break; //white
  }
  analogWrite(RED_PIN,   R);
  analogWrite(GREEN_PIN, G);
  analogWrite(BLUE_PIN,  B);
  delay(500); // Do not get immediate repeat
}


void setup() {
  // setup for LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  // setup for remote
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn(); // Start the receiver

}

void loop()
{
  if (irrecv.decode()) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}
