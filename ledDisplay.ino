/*  Software to drive the 3461BS 4x7+1
 *  common anode LED.
 *  
 *  CC-BY Roy Dybing, October 2016
 *  
 *  Relies heavily on tutorial by
 *  Rudy Schiaf with similar but 
 *  common cathode 4x7+1 LED
 */

// GLOBALS

// set ontime for LEDs per cycle
#define onTime 3000

// pins to adress LED
// ard. pin     LED pin
#define A 2     //11
#define B 3     //7
#define C 4     //4
#define D 5     //2
#define E 6     //1
#define f 7     //10
#define G 8     //5
#define DP 9    //3
// common anode pins
#define CA1 10  //12
#define CA2 11  //9
#define CA3 12  //8
#define CA4 13  //6

/* definition of segments
 *  
 *     -------
 *    |   A   |
 *   F|       |B
 *    |---G---|
 *   E|       |C
 *    |   D   |
 *     -------  * DP
 */

 #define numberSegments { \
  {1, 1, 1, 1, 1, 1, 0, 0},\
  {0, 1, 1, 0, 0, 0, 0, 0},\
  {1, 1, 0, 1, 1, 0, 1, 0},\
  {1, 1, 1, 1, 0, 0, 1, 0},\
  {0, 1, 1, 0, 0, 1, 1, 0},\
  {1, 0, 1, 1, 0, 1, 1, 0},\
  {0, 0, 1, 1, 1, 1, 1, 0},\
  {1, 1, 1, 0, 0, 0, 0, 0},\
  {1, 1, 1, 1, 1, 1, 1, 0},\
  {1, 1, 1, 0, 0, 1, 1, 0}\
 }

//set numbers 0-9 to bitmask in numberSegments
byte numbers[10][8] = numberSegments;
//array containing the pins for activating each segment
const int segments[8] = {A, B, C, D, E, f, G, DP};

void setup() {
  Serial.begin(9600);
  
  // set pins IO
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  pinMode(CA3, OUTPUT);
  pinMode(CA4, OUTPUT);
  // set pins initial state
  digitalWrite(A, HIGH); // Cathode end +5V
  digitalWrite(B, HIGH); // to bias to off
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(DP, HIGH);
  digitalWrite(CA1, LOW); // Anode end +0V
  digitalWrite(CA2, LOW); // to bias to off
  digitalWrite(CA3, LOW);
  digitalWrite(CA4, LOW);
    
}

void setSegments(int number, int digit, int duration){

  // close anode before opening cathodes
  digitalWrite(digit, LOW);

  // write the segments on the given digit
  for (int seg = 0; seg < 8; seg++){
    if (numbers[number][seg]==1){
      // open cathode to segments that are to be turned on
      digitalWrite(segments[seg], LOW);
    }
    else{
      // block cathode to segments to remain off
      digitalWrite(segments[seg], HIGH);
    }
  }
  // open anode to given digit to light it up
  digitalWrite(digit, HIGH);
  // wait a bit...
  delayMicroseconds(duration);
  // ...and close the anode again
  digitalWrite(digit, LOW);
  
}

void loop() {

  int digit1 = 0;
  int digit2 = 0;
  int digit3 = 0;
  int digit4 = 0;
  
  for (int counter = 0; counter < 10000; counter++){    
    digit1 = trunc(counter / 1000);
    digit2 = trunc((counter - (digit1 * 1000)) / 100);
    digit3 = trunc((counter - (digit1 * 1000) - (digit2 * 100)) / 10);
    digit4 = counter - (digit1 * 1000) - (digit2 * 100) - (digit3 * 10);    
    setSegments(digit1, CA1, onTime);
    setSegments(digit2, CA2, onTime);
    setSegments(digit3, CA3, onTime);
    setSegments(digit4, CA4, onTime);

    /*test area
    Serial.print(digit1);
    Serial.print(" - ");
    Serial.print(digit2);
    Serial.print(" - ");
    Serial.print(digit3);
    Serial.print(" - ");
    Serial.print(digit4);
    Serial.print(" - ");
    Serial.print(counter);
    Serial.println();
    */

    delay(100);
  }
}
