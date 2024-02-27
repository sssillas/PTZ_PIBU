// (c) Copyright 2022 Aaron Kimball
// This file is open source under the terms of the BSD 3-Clause license.
//
// Example basic usage for the debounce library.

#include<Arduino.h>
#include<debounce.h>
#include "JoystickController.h"
#include <ThreadController.h>
#include <PTZProtocol.h>

#include <MIDI.h>



bool blinkLED1 = false;
bool blinkLED2 = false;
bool recOn = false;

static constexpr int BUTTONS[] = {
  22,24,26,28,30,32,40,38,36,34,48,46,44,42,
  //RED
  53,52,50,
  //GREEN
  33,31,29,27,25,
  //YELLOW
  43,41,39,37,35,
  //FOCUS
  45,47

};

static constexpr int LEDS_GREEN[] = {
  14,15,16,17,18
};

static constexpr int LEDS_YELLOW[] = {
  19,20,21,49,51
};

static constexpr int LEDS_RED[] = {
  A15,A14,A13
};

const int SIZE_BUTTONS = 29;
const int SIZE_LEDS_GREEN = 5;
const int LED_WHITE = A12;
const int LED_WARNING = 4;

static constexpr int PIN_SWITCH = 23;

const int pinoPOT1 = A10;
int sensorPin1 = 0; 
float sensorValue1 = 0;  
float valuestored1 = 0;

const int pinoPOT2 = A11;
int sensorPin2 = 0; 
float sensorValue2 = 0;  
float valuestored2 = 0;

/* JOYSTICK CONTROLLER PINS */
#define PIN_PAN     A7  // analog input pin 5 (PAN)  <X-AXIS>
#define PIN_TILT    A8  // analog input pin 6 (TILT) <Y-AXIS>
#define PIN_ZOOM    A9  // analog input pin 4 (ZOOM) <Z-AXIS>


PTZProtocol protocol = PTZProtocol();

JoystickController joystick = JoystickController();

MIDI_CREATE_DEFAULT_INSTANCE();

Thread blinkLedThread = Thread();

void blinkLed(){

  if(blinkLED1 || blinkLED2){
    digitalWrite(LED_WARNING, !digitalRead(LED_WARNING));
  }

}

static void buttonHandler1(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET1,sizeof(PTZ_SET1));
    }else{
      protocol.sendViscaFrame(PTZ_CALL1,sizeof(PTZ_CALL1));
    }
    //Serial.println(address);
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler2(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET2,sizeof(PTZ_SET2));
    }else{
      protocol.sendViscaFrame(PTZ_CALL2,sizeof(PTZ_CALL2));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler3(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET3,sizeof(PTZ_SET3));
    }else{
      protocol.sendViscaFrame(PTZ_CALL3,sizeof(PTZ_CALL3));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler4(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET4,sizeof(PTZ_SET4));
    }else{
      protocol.sendViscaFrame(PTZ_CALL4,sizeof(PTZ_CALL4));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler5(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET5,sizeof(PTZ_SET5));
    }else{
      protocol.sendViscaFrame(PTZ_CALL5,sizeof(PTZ_CALL5));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler6(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET6,sizeof(PTZ_SET6));
    }else{
      protocol.sendViscaFrame(PTZ_CALL6,sizeof(PTZ_CALL6));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler7(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET7,sizeof(PTZ_SET7));
    }else{
      protocol.sendViscaFrame(PTZ_CALL7,sizeof(PTZ_CALL7));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler8(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET8,sizeof(PTZ_SET8));
    }else{
      protocol.sendViscaFrame(PTZ_CALL8,sizeof(PTZ_CALL8));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler9(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET9,sizeof(PTZ_SET9));
    }else{
      protocol.sendViscaFrame(PTZ_CALL9,sizeof(PTZ_CALL9));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler10(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET10,sizeof(PTZ_SET10));
    }else{
      protocol.sendViscaFrame(PTZ_CALL10,sizeof(PTZ_CALL10));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler11(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET11,sizeof(PTZ_SET11));
    }else{
      protocol.sendViscaFrame(PTZ_CALL11,sizeof(PTZ_CALL11));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler12(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET12,sizeof(PTZ_SET12));
    }else{
      protocol.sendViscaFrame(PTZ_CALL12,sizeof(PTZ_CALL12));
    }
  } else {
    // btnState == BTN_OPEN
  }
}

static void buttonHandler13(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET13,sizeof(PTZ_SET13));
    }else{
      protocol.sendViscaFrame(PTZ_CALL13,sizeof(PTZ_CALL13));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler14(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (recOn){
      protocol.sendViscaFrame(PTZ_SET14,sizeof(PTZ_SET14));
    }else{
      protocol.sendViscaFrame(PTZ_CALL14,sizeof(PTZ_CALL14));
    }
  } else {
    // btnState == BTN_OPEN.
  }
}


//RED

static void buttonHandler15(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.changeAdress(0x01);
    digitalWrite(LEDS_RED[0],HIGH);
    digitalWrite(LEDS_RED[1],LOW);
    digitalWrite(LEDS_RED[2],LOW);
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler16(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.changeAdress(0x02);
    digitalWrite(LEDS_RED[0],LOW);
    digitalWrite(LEDS_RED[1],HIGH);
    digitalWrite(LEDS_RED[2],LOW);
  } else {
    // btnState == BTN_OPEN.
  }
}

static void buttonHandler17(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.changeAdress(0x03);
    digitalWrite(LEDS_RED[0],LOW);
    digitalWrite(LEDS_RED[1],LOW);
    digitalWrite(LEDS_RED[2],HIGH);
  } else {
    // btnState == BTN_OPEN.
  }
}

//GREENS
static void buttonHandler18(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (digitalRead(LEDS_GREEN[0]) == HIGH){
      MIDI.sendNoteOn(1, 127, 1);
    }else{
      MIDI.sendNoteOn(1, 0, 1);
    }
    digitalWrite(LEDS_GREEN[0],!digitalRead(LEDS_GREEN[0]));
  }
}

static void buttonHandler19(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (digitalRead(LEDS_GREEN[1]) == HIGH){
      MIDI.sendNoteOn(2, 127, 1);
    }else{
      MIDI.sendNoteOn(2, 0, 1);
    }
    digitalWrite(LEDS_GREEN[1],!digitalRead(LEDS_GREEN[1]));
  } 
}

static void buttonHandler20(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (digitalRead(LEDS_GREEN[2]) == HIGH){
      MIDI.sendNoteOn(3, 127, 1);
    }else{
      MIDI.sendNoteOn(3, 0, 1);
    }
    digitalWrite(LEDS_GREEN[2],!digitalRead(LEDS_GREEN[2]));
  } 
}

static void buttonHandler21(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (digitalRead(LEDS_GREEN[3]) == HIGH){
      MIDI.sendNoteOn(4, 127, 1);
    }else{
      MIDI.sendNoteOn(4, 0, 1);
    }
    digitalWrite(LEDS_GREEN[3],!digitalRead(LEDS_GREEN[3]));
  }
}

static void buttonHandler22(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    if (digitalRead(LEDS_GREEN[4]) == HIGH){
      MIDI.sendNoteOn(5, 127, 1);
    }else{
      MIDI.sendNoteOn(5, 0, 1);
    }
    digitalWrite(LEDS_GREEN[4],!digitalRead(LEDS_GREEN[4]));
  }
}

//YELLOW

static void buttonHandler23(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.changeAdress(0x02);
    MIDI.sendNoteOn(6, 127, 1);
    digitalWrite(LEDS_YELLOW[0],HIGH);
    digitalWrite(LEDS_YELLOW[1],LOW);
    digitalWrite(LEDS_YELLOW[2],LOW);
    digitalWrite(LEDS_YELLOW[3],LOW);
    digitalWrite(LEDS_YELLOW[4],LOW);
    digitalWrite(LEDS_RED[0],LOW);
    digitalWrite(LEDS_RED[1],HIGH);
    digitalWrite(LEDS_RED[2],LOW);

  } else {
    // btnState == BTN_OPEN.

  }
}

static void buttonHandler24(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.changeAdress(0x01);
    MIDI.sendNoteOn(7, 127, 1);
    digitalWrite(LEDS_YELLOW[0],LOW);
    digitalWrite(LEDS_YELLOW[1],HIGH);
    digitalWrite(LEDS_YELLOW[2],LOW);
    digitalWrite(LEDS_YELLOW[3],LOW);
    digitalWrite(LEDS_YELLOW[4],LOW);

     digitalWrite(LEDS_RED[0],HIGH);
    digitalWrite(LEDS_RED[1],LOW);
    digitalWrite(LEDS_RED[2],LOW);
  } else {
    // btnState == BTN_OPEN.

  }
}

static void buttonHandler25(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    MIDI.sendNoteOn(8, 127, 1);
    digitalWrite(LEDS_YELLOW[0],LOW);
    digitalWrite(LEDS_YELLOW[1],LOW);
    digitalWrite(LEDS_YELLOW[2],HIGH);
    digitalWrite(LEDS_YELLOW[3],LOW);
    digitalWrite(LEDS_YELLOW[4],LOW);
  } 
}

static void buttonHandler26(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    MIDI.sendNoteOn(9, 127, 1);
    digitalWrite(LEDS_YELLOW[0],LOW);
    digitalWrite(LEDS_YELLOW[1],LOW);
    digitalWrite(LEDS_YELLOW[2],LOW);
    digitalWrite(LEDS_YELLOW[3],HIGH);
    digitalWrite(LEDS_YELLOW[4],LOW);
  }
}

static void buttonHandler27(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    MIDI.sendNoteOn(10, 127, 1);
    digitalWrite(LEDS_YELLOW[0],LOW);
    digitalWrite(LEDS_YELLOW[1],LOW);
    digitalWrite(LEDS_YELLOW[2],LOW);
    digitalWrite(LEDS_YELLOW[3],LOW);
    digitalWrite(LEDS_YELLOW[4],HIGH);
  }
}

static void buttonHandler28(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    protocol.sendViscaFrame(PTZ_FOCUS_MANUAL_ON,sizeof(PTZ_FOCUS_MANUAL_ON));
    delay(10);
    protocol.sendViscaFrame(PTZ_FOCUS_NEAR,sizeof(PTZ_FOCUS_NEAR));
  } else {
    protocol.sendViscaFrame(PTZ_FOCUS_STOP,sizeof(PTZ_FOCUS_STOP));

  }
}

static void buttonHandler29(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
     protocol.sendViscaFrame(PTZ_FOCUS_MANUAL_ON,sizeof(PTZ_FOCUS_MANUAL_ON));
     delay(10);
     protocol.sendViscaFrame(PTZ_FOCUS_FAR,sizeof(PTZ_FOCUS_FAR));
  } else {
     protocol.sendViscaFrame(PTZ_FOCUS_STOP,sizeof(PTZ_FOCUS_STOP));

  }
}



static void switchRecHandler(uint8_t btnId, uint8_t btnState) {
  if (btnState == BTN_PRESSED) {
    recOn = true;
    digitalWrite(LED_WHITE, LOW);
  } else {
    // btnState == BTN_OPEN.
    recOn = false;
    digitalWrite(LED_WHITE, HIGH);
  }
}





// Define your button with a unique id (0) and handler function.
// (The ids are so one handler function can tell different buttons apart if necessary.)
static Button myButton1(1, buttonHandler1);
static Button myButton2(2, buttonHandler2);
static Button myButton3(3, buttonHandler3);
static Button myButton4(4, buttonHandler4);
static Button myButton5(5, buttonHandler5);
static Button myButton6(6, buttonHandler6);
static Button myButton7(7, buttonHandler7);
static Button myButton8(8, buttonHandler8);
static Button myButton9(9, buttonHandler9);
static Button myButton10(10, buttonHandler10);
static Button myButton11(11, buttonHandler11);
static Button myButton12(12, buttonHandler12);
static Button myButton13(13, buttonHandler13);
static Button myButton14(14, buttonHandler14);
static Button myButton15(15, buttonHandler15);
static Button myButton16(16, buttonHandler16);
static Button myButton17(17, buttonHandler17);

static Button myButton18(18, buttonHandler18);
static Button myButton19(19, buttonHandler19);
static Button myButton20(20, buttonHandler20);
static Button myButton21(21, buttonHandler21);
static Button myButton22(22, buttonHandler22);

static Button myButton23(23, buttonHandler23);
static Button myButton24(24, buttonHandler24);
static Button myButton25(25, buttonHandler25);
static Button myButton26(26, buttonHandler26);
static Button myButton27(27, buttonHandler27);

static Button myButton28(28, buttonHandler28);
static Button myButton29(29, buttonHandler29);

static Button switchRec(30, switchRecHandler);

bool send_PTZ_Zomm = false;
bool send_PTZ_Pan= false;
bool send_PTZ_Tilt= false;

void joystickPTZChangeHandler(int pan, int tilt, int zoom){
  //Serial.println("PAN: " + (String)pan + " TILT: " + (String)tilt + " ZOOM: " + (String)zoom);
if (tilt > 20 && !send_PTZ_Tilt){
    send_PTZ_Tilt = true;
    protocol.sendViscaFrame(PTZ_UP,sizeof(PTZ_UP));
  }

  if (tilt < -20 && !send_PTZ_Tilt){
    send_PTZ_Tilt = true;
    protocol.sendViscaFrame(PTZ_DOWN,sizeof(PTZ_DOWN));
  }

  if (tilt == 0 && send_PTZ_Tilt){
    send_PTZ_Tilt = false;
     protocol.sendViscaFrame(PTZ_STOP,sizeof(PTZ_STOP));
  }








  if (pan > 20 && !send_PTZ_Pan){
    send_PTZ_Pan = true;
    protocol.sendViscaFrame(PTZ_RIGHT,sizeof(PTZ_RIGHT));
  }

  if (pan < -20 && !send_PTZ_Pan){
    send_PTZ_Pan = true;
    protocol.sendViscaFrame(PTZ_LEFT,sizeof(PTZ_LEFT));
  }

  if (pan == 0 && send_PTZ_Pan){
    send_PTZ_Pan = false;
     protocol.sendViscaFrame(PTZ_STOP,sizeof(PTZ_STOP));
  }

  if (zoom > 20 && !send_PTZ_Zomm){
    send_PTZ_Zomm = true;
    protocol.sendViscaFrame(PTZ_ZOMM_IN,sizeof(PTZ_ZOMM_IN));
  }



  if (zoom < -20 && !send_PTZ_Zomm){
    send_PTZ_Zomm = true;
    protocol.sendViscaFrame(PTZ_ZOMM_OUT,sizeof(PTZ_ZOMM_OUT));
  }
  if (zoom == 0 && send_PTZ_Zomm){
    send_PTZ_Zomm = false;
     protocol.sendViscaFrame(PTZ_ZOMM_STOP,sizeof(PTZ_ZOMM_STOP));
  }


}

void setup() {

  protocol.begin(4,3);

  MIDI.begin();
  Serial.begin(115200);
	blinkLedThread.onRun(blinkLed);
	blinkLedThread.setInterval(200);

  pinMode(pinoPOT1, INPUT); //DEFINE O PINO COMO SAÍDA

  for (int i = 0; i < SIZE_BUTTONS; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }

  pinMode(PIN_SWITCH, INPUT_PULLUP);


  for (int i = 0; i < 3; i++) {
    pinMode(LEDS_RED[i], OUTPUT);
  }

  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);

  digitalWrite(LED_WARNING, LOW);
  digitalWrite(LED_WHITE, HIGH);

  for (int i = 0; i < 5; i++) {
    pinMode(LEDS_GREEN[i], OUTPUT);
  }

  for (int i = 0; i < 5; i++) {
    pinMode(LEDS_YELLOW[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    digitalWrite(LEDS_RED[i], HIGH);
    delay(200);
    digitalWrite(LEDS_RED[i], LOW);
  }

  digitalWrite(LED_WHITE, LOW);
  delay(200);
  digitalWrite(LED_WHITE, HIGH);

  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDS_GREEN[i], HIGH);
    delay(200);
    digitalWrite(LEDS_GREEN[i], LOW);
  }



  for (int i = 0; i < 5; i++) {
    digitalWrite(LEDS_YELLOW[i], HIGH);
    delay(200);
    digitalWrite(LEDS_YELLOW[i], LOW);
  }

  digitalWrite(LEDS_RED[0],HIGH);

  pinMode(PIN_PAN, INPUT);
  pinMode(PIN_TILT, INPUT);
  pinMode(PIN_ZOOM, INPUT);
  joystick.begin(PIN_PAN,PIN_TILT,PIN_ZOOM);
  joystick.onPTZ(&joystickPTZChangeHandler);

  
}

static void pollButtons() {
  // update() will call buttonHandler() if PIN transitions to a new state and stays there
  // for multiple reads over 25+ ms.
  myButton1.update(digitalRead(BUTTONS[0]));
  myButton2.update(digitalRead(BUTTONS[1]));
  myButton3.update(digitalRead(BUTTONS[2]));
  myButton4.update(digitalRead(BUTTONS[3]));
  myButton5.update(digitalRead(BUTTONS[4]));
  myButton6.update(digitalRead(BUTTONS[5]));
  myButton7.update(digitalRead(BUTTONS[6]));
  myButton8.update(digitalRead(BUTTONS[7]));
  myButton9.update(digitalRead(BUTTONS[8]));
  myButton10.update(digitalRead(BUTTONS[9]));
  myButton11.update(digitalRead(BUTTONS[10]));
  myButton12.update(digitalRead(BUTTONS[11]));
  myButton13.update(digitalRead(BUTTONS[12]));
  myButton14.update(digitalRead(BUTTONS[13]));
  myButton15.update(digitalRead(BUTTONS[14]));
  myButton16.update(digitalRead(BUTTONS[15]));
  myButton17.update(digitalRead(BUTTONS[16]));

  myButton18.update(digitalRead(BUTTONS[17]));
  myButton19.update(digitalRead(BUTTONS[18]));
  myButton20.update(digitalRead(BUTTONS[19]));
  myButton21.update(digitalRead(BUTTONS[20]));
  myButton22.update(digitalRead(BUTTONS[21]));

  myButton23.update(digitalRead(BUTTONS[22]));
  myButton24.update(digitalRead(BUTTONS[23]));
  myButton25.update(digitalRead(BUTTONS[24]));
  myButton26.update(digitalRead(BUTTONS[25]));
  myButton27.update(digitalRead(BUTTONS[26]));

  myButton28.update(digitalRead(BUTTONS[27]));
  myButton29.update(digitalRead(BUTTONS[28]));

  
 switchRec.update(digitalRead(PIN_SWITCH));

}

static void readPOT1() {
  sensorValue1 = analogRead(pinoPOT1); 
  if(sensorValue1 != valuestored1){
    float res = sensorValue1 - valuestored1;
    res=abs(res);
    if(res>5){
       float luminosidadeLED = map(sensorValue1, 0, 1023, 0, 127);
       //Serial.println(luminosidadeLED);
       MIDI.sendControlChange(20, luminosidadeLED, 1);
       valuestored1=sensorValue1;
    }
  }
}

static void readPOT2() {
  sensorValue2 = analogRead(pinoPOT2); 
  if(sensorValue2 != valuestored2){
    float res = sensorValue2 - valuestored2;
    res=abs(res);
    if(res>5){
       float luminosidadeLED = map(sensorValue2, 0, 1023, 0, 127);
       //Serial.println(luminosidadeLED);
       //MIDI.sendControlChange(43, luminosidadeLED, 1);
        MIDI.sendControlChange(21, luminosidadeLED, 1);
       valuestored2=sensorValue2;
    }
  }
}



void loop() {
  pollButtons(); // Poll your buttons every loop.
  readPOT1();
  readPOT2();
  joystick.loop();

    if (digitalRead(LEDS_RED[0]) == HIGH && digitalRead(LEDS_YELLOW[0]) == HIGH ){
      blinkLED1 = true;
    }else{
      blinkLED1 = false;
      digitalWrite(LED_WARNING, LOW);
    }
  


    if (digitalRead(LEDS_RED[1]) == HIGH && digitalRead(LEDS_YELLOW[1]) == HIGH ){
      blinkLED2 = true;
    }else{
      blinkLED2 = false;
       digitalWrite(LED_WARNING, LOW);
    }
  

  if(blinkLedThread.shouldRun())
		blinkLedThread.run();
  delay(10); // Loop iterations should run fairly quickly, 10's of ms, not 100's.
}
