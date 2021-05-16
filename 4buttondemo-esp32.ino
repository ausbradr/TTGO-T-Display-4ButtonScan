//Button Scanning routine by Brad Rogers, 10th March 2021.
//Free for all reuse
//Init the TTGO T-Display's screen:
#include <TFT_eSPI.h>
#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif
#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif
#define TFT_BL          4  // Display backlight control pin
#define LED_CTRL        0 // Pinnumber of external led to control. Set to 0 if there isn't a external led attached.
int ledBacklight = 100; // Initial TFT backlight intensity on a scale of 0 to 255. Initial value is 80.
TFT_eSPI gfx = TFT_eSPI(); // Define TFT_eSPI object with the size of the screen: 135 pixels width and 240 pixels height. We will rotate it later a quarter clockwise.
// Setting PWM properties, do not change this!
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;




// This snippet is going to be bare bones and all below code can be copied into the right spots to provide you with plug/play button checking. See the demos for more info on how they work. 


//4buttonscan prerequisites
//Set the pins we'll be using for all 4 buttons
int buttonA = 32;
int buttonB = 33;
int buttonC = 37;
int buttonD = 38;
//Define the variables used to store whether each button is pressed
int buttonAstate=0;
int buttonBstate=0;
int buttonCstate=0;
int buttonDstate=0;
//define the variable and zero it, for keypad total. This will help us indicate simultaneous keypresses, if your program is looking for that.
int keypadtotal=0;

void setup() {
//serial
Serial.begin(115200); // Set Serial baudrate at 115200
Serial.println();
Serial.print("COMPort activated");


//screen setup
  gfx.init();
  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  Serial.println("DONE");
  Serial.print("Setting PWM for TFT backlight to default intensity... ");
  ledcWrite(pwmLedChannelTFT, ledBacklight);
  Serial.println("DONE");
  gfx.setRotation(1); // Rotate display a quarter clockwise
  gfx.setTextSize(2);
  gfx.setTextWrap(false);
  gfx.fillScreen(TFT_BLACK);




//4buttonscan void setup lines:
//For the pins we're connecting the buttons to, we need to define them as inputs:
pinMode(buttonA, INPUT);
pinMode(buttonB, INPUT);
pinMode(buttonC, INPUT);
pinMode(buttonD, INPUT);




}

void loop() {
// Literally just call keypadcheckloop to halt the program until keypress, or call keypadcheckonce in your own loop to multitask. Don't copy anything here, just call as you need in your own code flow.
keypadcheckloop();

Serial.println(keypadtotal);

if(keypadtotal==10){
  gfx.fillScreen(TFT_RED);
}
if(keypadtotal==50){
  gfx.fillScreen(TFT_GREEN);
}
if(keypadtotal==100){
  gfx.fillScreen(TFT_BLUE);
}
if(keypadtotal==200){
  gfx.fillScreen(TFT_YELLOW);
}

  
  
  //You can also call the function keypadcheckonce, then test the keypadtotal with those if statements you see above
  //if you intend to run your own loop that involves running your own background tasks. Just be sure to include the
  //if's to check the keypadtotal to allow the loop to be exited from as needed. 
  
  
  
}




//4buttonscan subroutines that get added below just outside of void loop to get things running. 
void keypadcheckloop(){
do
{
//reset keypad total
keypadtotal =0;
//check the buttons, and don't return to void loop until we have a keypress.
buttonAstate = digitalRead(buttonA);
if (buttonAstate!=0){
  keypadtotal = keypadtotal + 10;
}
buttonBstate = digitalRead(buttonB);
if (buttonBstate!=0){
  keypadtotal = keypadtotal + 50;
}
buttonCstate = digitalRead(buttonC);
if (buttonCstate!=0){
  keypadtotal = keypadtotal + 100;
}
buttonDstate = digitalRead(buttonD);
if (buttonDstate!=0){
  keypadtotal = keypadtotal + 200;
}
} while (keypadtotal < 10);
}

void keypadcheckonce(){
//reset keypad total
keypadtotal =0;
//check the keypad once and return control to void loop
buttonAstate = digitalRead(buttonA);
if (buttonAstate!=0){
  keypadtotal = keypadtotal + 10;
}
buttonBstate = digitalRead(buttonB);
if (buttonBstate!=0){
  keypadtotal = keypadtotal + 50;
}
buttonCstate = digitalRead(buttonC);
if (buttonCstate!=0){
  keypadtotal = keypadtotal + 100;
}
buttonDstate = digitalRead(buttonD);
if (buttonDstate!=0){
  keypadtotal = keypadtotal + 200;
}
}
