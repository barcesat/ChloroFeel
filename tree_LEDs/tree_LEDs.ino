#include <LEDFader.h>
#include <Wire.h>

int leds[12] = {
  //A RGB
  2,3,4,
  //M RGB
  5,6,7,
  //T RGB
  8,9,10,
  //H RGB
  11,12,13
};

LEDFader ledR_A; LEDFader ledG_A; LEDFader ledB_A;
LEDFader ledR_M; LEDFader ledG_M; LEDFader ledB_M;
LEDFader ledR_T; LEDFader ledG_T; LEDFader ledB_T;
LEDFader ledR_H; LEDFader ledG_H; LEDFader ledB_H;

byte comm =0x00;
byte commold =0x00;
byte a =0;
byte m =0;
byte t =0;
byte h =0;

//byte color = 0;
byte R_A,G_A,B_A = 0;
byte R_M,G_M,B_M = 0;
byte R_T,G_T,B_T = 0;
byte R_H,G_H,B_H = 0;
int duration_A = 2000;
int duration_M = 2000;
int duration_T = 2000;
int duration_H = 2000;

void setup() {
    // initialize the serial communication:
  Serial.begin(9600);
Wire.begin();        // join i2c bus (address optional for master)

ledR_A = LEDFader(leds[0]);
ledG_A = LEDFader(leds[1]);
ledB_A = LEDFader(leds[2]);

ledR_M = LEDFader(leds[3]);
ledG_M = LEDFader(leds[4]);
ledB_M = LEDFader(leds[5]);

ledR_T = LEDFader(leds[6]);
ledG_T = LEDFader(leds[7]);
ledB_T = LEDFader(leds[8]);

ledR_H = LEDFader(leds[9]);
ledG_H = LEDFader(leds[10]);
ledB_H = LEDFader(leds[11]);
}

void loop() {
Wire.requestFrom(2, 1);    // request 1 bytes from slave device #2
  if (Wire.available())    // slave may send less than requested
  { 
   comm = Wire.read(); // receive a byte as character
   // Serial.print(c);         // print the character
  }
  if (commold != comm)  {
    commold = comm;
    Serial.println(commold,BIN);
    cypher(commold);
  }
  else{
    //track LED fades
  Serial.print("A:");  Serial.print(a); Serial.print(" ");
  Serial.print("M: "); Serial.print(m);  Serial.print(" ");
  Serial.print("T: "); Serial.print(t);  Serial.print(" ");
  Serial.print("H: "); Serial.print(h);  Serial.println();

 //CONDITIONS TO UPDATE FADE   
    if (a==0){duration_A = 500; R_A = 255; G_A = 0; B_A= 0;} //f R
    else if (a==1){ duration_A = 500; R_A = 0; G_A = 192; B_A= 0;} //f Pink
    else if (a==2){ duration_A = 2000; R_A = 255; G_A = 255; B_A= 0;} //s Y
    else if (a==3){ duration_A = 2000; R_A = 0; G_A = 255; B_A= 0;}// s G
    
    if (m==0){duration_M = 500; R_M = 255; G_M = 255; B_M= 0;} //f Y
    else if (m==1){ duration_M = 2000; R_M = 0; G_M = 255; B_M= 255;} //s Cy
    else if (m==2){ duration_M = 500; R_M = 0; G_M = 0; B_M= 255;} //f B
    
    if (t==0){duration_T = 2000; R_T = 0; G_T = 0; B_T= 255;} // s B
    else if (t==1){ duration_T = 500; R_T = 255; G_T = 192; B_T= 0;} // f Or
    else if (t==2){ duration_T = 2000; R_T = 255; G_T = 0; B_T= 0;} // s R
    
    if (h==0){duration_H = 500; R_H = 255; G_H = 255; B_H= 0;} //f Y
    else if (h==1){ duration_H = 2000; R_H = 0; G_H = 255; B_H= 0;} // s G
    else if (h==2){ duration_H = 500; R_H = 0; G_H = 255; B_H= 255;}// f Cy
    
    //CHECK AND SET UPDATE OF FADES
    if (ledR_A.is_fading() == false) {
      if (ledR_A.get_value() == 0) ledR_A.fade(R_A, duration_A);
      else ledR_A.fade(0, duration_A);}
    
    if (ledG_A.is_fading() == false) {
      if (ledG_A.get_value() == 0) ledG_A.fade(G_A, duration_A);
      else ledG_A.fade(0, duration_A);}
    
    if (ledB_A.is_fading() == false) {
      if (ledB_A.get_value() == 0) ledB_A.fade(B_A, duration_A);
      else ledB_A.fade(0, duration_A);}
    
    
    if (ledR_M.is_fading() == false) {
      if (ledR_M.get_value() == 0) ledR_M.fade(R_M, duration_M);
      else ledR_M.fade(0, duration_M);}
    
    if (ledG_M.is_fading() == false) {
      if (ledG_M.get_value() == 0) ledG_M.fade(G_M, duration_M);
      else ledG_M.fade(0, duration_M);}
    
    if (ledB_M.is_fading() == false) {
      if (ledB_M.get_value() == 0) ledB_M.fade(B_M, duration_M);
      else ledB_M.fade(0, duration_M);}
      
      
     if (ledR_T.is_fading() == false) {
      if (ledR_T.get_value() == 0) ledR_T.fade(R_T, duration_T);
      else ledR_T.fade(0, duration_T);}
    
    if (ledG_T.is_fading() == false) {
      if (ledG_T.get_value() == 0) ledG_T.fade(G_T, duration_T);
      else ledG_T.fade(0, duration_T);}
    
    if (ledB_T.is_fading() == false) {
      if (ledB_T.get_value() == 0) ledB_T.fade(B_T, duration_T);
      else ledB_T.fade(0, duration_T);}
      
      
    if (ledR_H.is_fading() == false) {
      if (ledR_H.get_value() == 0) ledR_H.fade(R_H, duration_H);
      else ledR_H.fade(0, duration_H);}
    
    if (ledG_H.is_fading() == false) {
      if (ledG_H.get_value() == 0) ledG_H.fade(G_H, duration_H);
      else ledG_H.fade(0, duration_H);}
    
    if (ledB_H.is_fading() == false) {
      if (ledB_H.get_value() == 0) ledB_H.fade(B_H, duration_H);
      else ledB_H.fade(0, duration_H);}

// call to update
    ledR_A.update(); ledG_A.update();  ledB_A.update();
    ledR_M.update(); ledG_M.update(); ledB_M.update();
    ledR_T.update(); ledG_T.update(); ledB_T.update();
    ledR_H.update(); ledG_H.update(); ledB_H.update(); 
 }
}

void cypher(byte c){
if (bitRead(c,0) ==0 && bitRead(c,1) ==0) a = 0;
else if (bitRead(c,0) ==0 && bitRead(c,1) ==1) a = 1;
else if (bitRead(c,0) ==1 && bitRead(c,1) ==0) a = 2;
else if (bitRead(c,0) ==1 && bitRead(c,1) ==1) a = 3;

if (bitRead(c,2) ==0 && bitRead(c,3) ==0) m = 0;
else if (bitRead(c,2) ==0 && bitRead(c,3) ==1) m = 1;
else if (bitRead(c,2) ==1 && bitRead(c,3) ==0) m = 2;
else if (bitRead(c,2) ==1 && bitRead(c,3) ==1) m = 3;

if (bitRead(c,4) ==0 && bitRead(c,5) ==0) t = 0;
else if (bitRead(c,4) ==0 && bitRead(c,5) ==1) t = 1;
else if (bitRead(c,4) ==1 && bitRead(c,5) ==0) t = 2;
else if (bitRead(c,4) ==1 && bitRead(c,5) ==1) t = 3;

if (bitRead(c,6) ==0 && bitRead(c,7) ==0) h = 0;
else if (bitRead(c,6) ==0 && bitRead(c,7) ==1) h = 1;
else if (bitRead(c,6) ==1 && bitRead(c,7) ==0) h = 2;
else if (bitRead(c,6) ==1 && bitRead(c,7) ==1) h = 3;
}
