/*
  Row-Column Scanning an 8x8 LED matrix with X-Y input

  This example controls an 8x8 LED matrix using two analog inputs.

  This example works for the Lumex LDM-24488NI Matrix. See
  http://sigma.octopart.com/140413/datasheet/Lumex-LDM-24488NI.pdf
  for the pin connections.

  For other LED cathode column matrixes, you should only need to change the pin
  numbers in the row[] and column[] arrays.

  rows are the anodes
  cols are the cathodes
  ---------

  Pin numbers:
  Matrix:
  - digital pins 2 through 13,
  - analog pins 2 through 5 used as digital 16 through 19
  Potentiometers:
  - center pins are attached to analog pins 0 and 1, respectively
  - side pins attached to +5V and ground, respectively

  created 27 May 2009
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/RowColumnScanning

  see also http://www.tigoe.net/pcomp/code/category/arduinowiring for more
*/

// 2-dimensional array of row pin numbers:
const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels:
int pixels[8][8];

// cursor position:
int x = 5;
int y = 5;
int sw = 0;

unsigned long lidinn_timi = 0;
int bidtimi = 100;


void setup() {
  
  // initialize the I/O pins as outputs iterate over the pins:
  pinMode(sw,INPUT);
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[thisPin], LOW);
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = LOW;
    }
  }
}

void loop() {
  // read input:
  int timi_nuna = millis ();
  if (timi_nuna - lidinn_timi > bidtimi) {
  
    readSensors();
    lidinn_timi = timi_nuna; 
  }

  // draw the screen:
  refreshScreen();
}

void readSensors() {
  int xPosition = analogRead(A0);
  int yPosition = analogRead(A1);
   if(xPosition < 200){
      if(x<7){
         if(pixels[x][y] != 2)
          pixels[x][y] = 0;
         x++;
         pixels[x][y] = 1;
      }
  }
  if(xPosition>700){
     if(x>0){
        if (pixels[x][y] != 2)
          pixels[x][y] = 0;
         x--;
         if(pixels[x][y] != 2)
          pixels[x][y] = 1;
     }
  }
  //if(yPosition<497){
    //pixels[x][y]=2;
  //}
  //if(yPosition>1023){
    //pixels[x][y]=1;
  if(yPosition < 200) {
   if(y<7){
         if(pixels[x][y] != 2)
          pixels[x][y] = 0;
         y++;
         pixels[x][y] = 1;
      }
  }
  if(yPosition>700){
     if(y>0){
        if (pixels[x][y] != 2)
        pixels[x][y] = 0;
         y--;
         if(pixels[x][y] != 2)
         pixels[x][y] = 1;
     }
 

  }
}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], LOW);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == HIGH) {
        digitalWrite(col[thisCol], LOW);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], HIGH);
  }
}
