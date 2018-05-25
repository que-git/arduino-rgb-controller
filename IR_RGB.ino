/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <EEPROM.h>

int ADR_LED_R = 1;
int ADR_LED_G = 5;
int ADR_LED_B = 10;

int RECV_PIN = 3;
int LED_PIN_R = 9;
int LED_PIN_G = 10;
int LED_PIN_B = 6;

byte LED_R;
byte LED_G;
byte LED_B;
int DIMM_STEP = 15;

bool isOn = true;
short loop_count = 0;
short blink_freq = 0;
short fading = 0;
short fading_LED_R = 255;
short fading_LED_G = 0;
short fading_LED_B = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);

  Serial.begin(9600);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  Serial.println("Enabled IRin");
  Serial.println("#include <IRremote.h>\nhttps://github.com/z3t0/Arduino-IRremote");

    EEPROM.get(ADR_LED_R, LED_R);
  EEPROM.get(ADR_LED_G, LED_G);
  EEPROM.get(ADR_LED_B, LED_B);
  Serial.println("Get RGB from EEPROM: "+String(LED_R)+" "+String(LED_G)+" "+String(LED_B));
  setRGB(LED_R,LED_G,LED_B);
}

void loop() {
  unsigned long ir_code = -1;
  
  if (irrecv.decode(&results) ) {
    ir_code = results.value;  
    //Serial.println(results.value, HEX);

    Serial.println(ir_code);
    Serial.println(ir_code,HEX);


  if(ir_code != 4294967295){
      decodeIR(ir_code);
  }
  irrecv.resume(); // Receive the next value
  }

  if(blink_freq){
    blink_led();
  }

  if(fading){
    fade();
  }
  
  delay(100);
  loop_count++;
}

void fade(){

Serial.println(String(fading_LED_R)+" "+String(fading_LED_G)+" "+String(fading_LED_B));

  if(fading_LED_R>=255 && fading_LED_G<255&& fading_LED_B<=0 ){
     fading_LED_G+=fading;
  }else if(fading_LED_R>0 && fading_LED_G>=255 && fading_LED_B<=0){
    fading_LED_R-=fading;
  }else if(fading_LED_G>=255 && fading_LED_R<=0 && fading_LED_B<255){
    fading_LED_B+=fading;
  }else if(fading_LED_B>=255 && fading_LED_R<=0 && fading_LED_G>0){
    fading_LED_G-=fading;
  }else if(fading_LED_R<255 && fading_LED_G<=0 && fading_LED_B>=255){
    fading_LED_R+=fading;
  }else if(fading_LED_R>=255 && fading_LED_G<=0 && fading_LED_B>0){
    fading_LED_B-=fading;
  }
  
  analogWrite(LED_PIN_R, fading_LED_R);
  analogWrite(LED_PIN_G, fading_LED_G);
  analogWrite(LED_PIN_B, fading_LED_B);
}

void blink_led(){
  if((loop_count%blink_freq)==0){
    power();
  }
}

void decodeIR(unsigned long ir_code){
  Serial.println("DecodeIR");
  
    //R
    if(ir_code == 2833276859){
      setRGB(255,0,0);
    }else if(ir_code == 1535358491){
      setRGB(255,99,71);
    }else if(ir_code == 2962012127){
      setRGB(255,165,0);
    }else if(ir_code == 1217346747){
      setRGB(255,215,0);
    }else if(ir_code == 1033561079){
      setRGB(255,255,0);
    }else
    //G
    if(ir_code == 961851831){
      setRGB(0,255,0);
    }else if(ir_code == 3039890975){
      setRGB(154,205,50);
    }else if(ir_code == 1090587099){
      setRGB(0,139,139);
    }else if(ir_code == 2721879231){
      setRGB(46,139,87);
    }else if(ir_code == 2538093563){
      setRGB(0,100,0);
    }else 
    //B
    if(ir_code == 3810010651){
      setRGB(0,0,255);
    }else if(ir_code == 1942930995){
      setRGB(30,144,255);
    }else if(ir_code == 2126716663){
      setRGB(139,0,139);
    }else if(ir_code == 4131161687){
      setRGB(75,0,130);
    }else if(ir_code == 3691091931){
      setRGB(255,20,147);
    }else
    //W
    if(ir_code == 1386468383){
      setRGB(255,255,255);
    }else if(ir_code == 3814356023){
      setRGB(255,172,68);
    }else if(ir_code == 3998141691){
      setRGB(0,191,255);
    }else if(ir_code == 3877748955){
      setRGB(65,105,225);
    }else if(ir_code == 2259740311){
      setRGB(250,235,215);
    }else 
    
    if(ir_code == 1033561079){
      setRGB(255,90,0);
    }else if(ir_code == 3622325019){
      power();
    }else 
    
    if(ir_code == 324312031){
      // R++
      setRGB(LED_R+DIMM_STEP,LED_G,LED_B);
    }else if(ir_code == 1162296347){
      // R--
      setRGB(LED_R-DIMM_STEP,LED_G,LED_B);
    }else if(ir_code == 2747854299){
      // G++
      setRGB(LED_R,LED_G+DIMM_STEP,LED_B);
    }else if(ir_code == 2666828831){
      // G--
      setRGB(LED_R,LED_G-DIMM_STEP,LED_B);
    }else if(ir_code == 3238126971){
      // B++
      setRGB(LED_R,LED_G,LED_B+DIMM_STEP);
    }else if(ir_code == 4084712887){
      // B--
      setRGB(LED_R,LED_G,LED_B-DIMM_STEP);
    }else if(ir_code == 3017062527){
      // W++
      bright(DIMM_STEP);
    }else if(ir_code == 1145637499){
      // W--
      bright(-DIMM_STEP);
    }else 
    //blink
    if(ir_code == 1541889663){
      // quick
      blink_led(1);
    }else if(ir_code == 2388475579){
      // slow
      blink_led(5);
    }else
    //fade
    if(ir_code == 900285023){
      fading = (fading==1? 0: 1);
      if(fading!=0){
        short fading_LED_R = 255;
        short fading_LED_G = 0;
        short fading_LED_B = 0;
      }
    }else if(ir_code == 3577243675){
      fading = (fading==5? 0: 5);
      if(fading!=0){
        short fading_LED_R = 255;
        short fading_LED_G = 0;
        short fading_LED_B = 0;
      }
    }else if(ir_code == 4034314555){
      fading = (fading==15? 0: 15);
      if(fading!=0){
        short fading_LED_R = 255;
        short fading_LED_G = 0;
        short fading_LED_B = 0;
      }
        
    }
}

void blink_led(int freq){
      Serial.println("Blink freq: "+String(freq));
      if(blink_freq!=0){
        blink_freq = 0;
        if(isOn==false)
        power();
      }else{
        blink_freq = freq;  
      }
}

void setRGB(byte R, byte G, byte B){
  Serial.println("setRGB");
  LED_R = R;
  LED_G = G;
  LED_B = B;
  checkRGBRange(LED_R, LED_G, LED_B);
  Serial.println("Set RGB:"+String(LED_R)+";"+String(LED_G)+";"+String(LED_B));

  Serial.println("analogWrite");
  analogWrite(LED_PIN_R, LED_R);
  analogWrite(LED_PIN_G, LED_G);
  analogWrite(LED_PIN_B, LED_B);

  EEPROM.update(ADR_LED_R, LED_R);
  EEPROM.update(ADR_LED_G, LED_G);
  EEPROM.update(ADR_LED_B, LED_B);
  
}

void bright(int val){
  Serial.println("VAL:"+String(val));
  if(val>0){
    if(LED_R != 0)
    LED_R = (LED_R+val>255 ? 0 : LED_R+val);
    if(LED_G != 0)
    LED_G = (LED_G+val>255 ? 0 : LED_G+val);
    if(LED_B != 0)
    LED_B = (LED_B+val>255 ? 0 : LED_B+val);  
    }

  if(val<0){
    if(LED_R != 0)
    LED_R = (LED_R+val<0 ? 0 : LED_R+val);
    if(LED_G != 0)
    LED_G = (LED_G+val<0 ? 0 : LED_G+val);
    if(LED_B != 0)
    LED_B = (LED_B+val<0 ? 0 : LED_B+val);
  }
  setRGB(LED_R, LED_G, LED_B);
}

void checkRGBRange(byte &R, byte &G, byte &B){
  if(R<0)
  R=0;
  if(R>255)
  R=255;
  
  if(G<0)
  G=0;
  if(G>255)
  G=255;
  
  if(B<0)
  B=0;
  if(B>255)
  B=255;
}

void power(){
  if(isOn){
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 0);
    isOn = false;
  }else{
    analogWrite(LED_PIN_R, LED_R);
    analogWrite(LED_PIN_G, LED_G);
    analogWrite(LED_PIN_B, LED_B);
    isOn = true;
  }
}





