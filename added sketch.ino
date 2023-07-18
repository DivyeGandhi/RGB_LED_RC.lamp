\begin{verbatim}
#include <IRremote.h>
#include<EEPROM.h>
#include <Adafruit_NeoPixel.h>
#ifdef AVR
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 4);
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
Adafruit_NeoPixel pixels(170, 6, NEO_GRB + NEO_KHZ800);
float R=0,B=0,G=0;
float b=100;
void setup()
{
  pixels.begin();
  pinMode(6,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A3,INPUT);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}
void writeEEPROM(int number , int address){
  byte bytee=number;
  EEPROM.write(address,bytee);
}
int readEEPROM(int address){
  byte bytee=EEPROM.read(address);
  return bytee;
}
void loop() {
//  pulseWhite(5);
  if (irrecv.decode(&results)) {

    if(results.value==0xA70){
      lcd.clear();
      delay(500);
      lcd.print("SET TO LAST SAVED COLOUR");
      delay(500);
      lcd.clear();
      R=readEEPROM(18404);
      G=readEEPROM(18405);
      B=readEEPROM(18406);
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      
    }
    if(results.value==0xDD0){
      lcd.clear();
      delay(500);
      lcd.print("SAVING COLOUR...");
      delay(500);
      lcd.clear();
      writeEEPROM(R,18404);
      writeEEPROM(G,18405);
      writeEEPROM(B,18406);
    }
    else if(results.value==0x6CE9){
      
    }
    else if (results.value==0x2CE9){
      colorWipe(pixels.Color(255,   0,   0), 50); 
    }
    else if (results.value==0x1CE9){
      whiteOverRainbow(75, 5);
    }
    else if(results.value==0xCD05 ){
       if(b+10<=100)
       {b=b+10;}
       else{
        b=100;
       }
       pixels.setBrightness(b);
    }
    else if(results.value==0xCD0){
       if(b+10<=100)
       {b=b+10;}
       else{
        b=100;
       }
       pixels.setBrightness(b);
    }
    else if(results.value==0x2D0){
       if(b-10>0)
       {b=b-10;}
       pixels.setBrightness(b);
    }
    else if(results.value==0x10)
    {
      for(int i=0; i<170; i++) {
        R=90;
        G=0;
        B=0;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
        
      }
      lcd.clear();
      lcd.print("RED");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0x810){
      for(int i=0; i<170; i++) {
        R=0;
        G=90;
        B=0;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("GREEN");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0x410){
      for(int i=0; i<170; i++) {
        R=0;
        G=0;
        B=90;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("BLUE");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0xC10){
      for(int i=0; i<170; i++) {
        R=0;
        G=90;
        B=90;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("AQUA");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0x210){
      for(int i=0; i<170; i++) {
        R=90;
        G=90;
        B=0;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("YELLOW");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0xA10){
      for(int i=0; i<170; i++) {
        R=90;
        G=0;
        B=90;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("PINK");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0x610){
      for(int i=0; i<170; i++) {
        R=60;
        G=60;
        B=60;
        R=R-7;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("WHITE");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0xE10){
      for(int i=0; i<170; i++) {
        R=0;
        G=90;
        B=70;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("TERQUOISE");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0x110){
      for(int i=0; i<170; i++) {
        R=90;
        G=10;
        B=0;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("ORANGE");
      delay(500);
      lcd.clear();
    }
    else if(results.value==0xA90){
      for(int i=0; i<170 ; i++) {
      lcd.clear();
        R=0;
        G=0;
        B=0;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("LED OFF");
      delay(500);
      lcd.clear();
    }
    else if (results.value==0x490){
      if(R+15<=90)
      {R=R+15;}
      else{
        R=90;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
    }
    else if (results.value==0x90){
      if(G+15<=90)
      {G=G+15;}
      else
      {
        G=90;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      
    }
    else if (results.value==0x2F0){
      if(B+15<=90){
       B=B+15;
      }
      else{
        B=90;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
    }
    else if(results.value==0x910){
      for(int i=0; i<170; i++) {
        R=80;
        G=80;
        B=60;
        R=R-7;
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      lcd.clear();
      lcd.print("WARM WHITE");
      delay(500);
      lcd.clear();
    }
    else if (results.value==0xC90){
      if(R-15>=0)
      {R=R-15;}
      else{
        R=0;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
    }
    else if (results.value==0x890){
      if(G-15>=0)
      {G=G-15;}
      else{
        G=0;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
    }
    else if (results.value==0xAF0){
      if(B-15>=0)
      {B=B-15;}
      else{
        B=0;
      }
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
      }
      
    }
    else if (results.value==0x290){
      digitalWrite(13,HIGH);
      float light=analogRead(A3);
      lcd.clear();
      lcd.print("ADJUST TO ROOM BRIGHTNESS =");
      delay(900);
      float vall=(1-(light/977))*100;
      lcd.print(vall);
      delay(900);
      lcd.clear();
      
      lcd.print(vall);
      b=vall;
      pixels.setBrightness(vall);
      for(int i=0; i<170; i++) {
        pixels.setPixelColor(i, pixels.Color(R, G, B));
//        pixels.show();
      }
    }
    pixels.show();
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    lcd.setCursor(0, 1);
//    lcd.print(results.value, HEX);
    
//    delay(900);
//    lcd.clear();
   lcd.clear();
      lcd.print("RED=");
//      lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
      float val = (R/90.0)*100;
    lcd.print(val);
    lcd.print("%");
//      delay(250);
      lcd.setCursor(0, 1);
//    lcd.clear();
      lcd.print("GREEN=");
      val = (G/90.0)*100;
    lcd.print(val);
    lcd.print("%");
//      delay(250);
      lcd.setCursor(0, 2);
      lcd.print("BLUE=");
      val = (B/90.0)*100;
    lcd.print(val);
    lcd.print("%");
    lcd.setCursor(0, 3);
      lcd.print("BRIGHT.=");
    lcd.print(b);
    lcd.print("%");
    
//      delay(250);
  }
  delay(90);
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel in strip...
    pixels.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    pixels.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void whiteOverRainbow(int whiteSpeed, int whiteLength) {

  if(whiteLength >= pixels.numPixels()) whiteLength = pixels.numPixels() - 1;

  int      head          = whiteLength - 1;
  int      tail          = 0;
  int      loops         = 3;
  int      loopNum       = 0;
  uint32_t lastTime      = millis();
  uint32_t firstPixelHue = 0;

  for(;;) { // Repeat forever (or until a 'break' or 'return')
    for(int i=0; i<pixels.numPixels(); i++) {  // For each pixel in strip...
      if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
         ((tail > head) && ((i >= tail) || (i <= head)))) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 255)); // Set white
      } else {                                             // else set rainbow
        int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
        pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
      }
    }

    pixels.show(); // Update strip with new contents
    // There's no delay here, it just runs full-tilt until the timer and
    // counter combination below runs out.

    firstPixelHue += 40; // Advance just a little along the color wheel

    if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
      if(++head >= pixels.numPixels()) {      // Advance head, wrap around
        head = 0;
        if(++loopNum >= loops) return;
      }
      if(++tail >= pixels.numPixels()) {      // Advance tail, wrap around
        tail = 0;
      }
      lastTime = millis();                   // Save time of last movement
    }
  }
}    \end{verbatim}
