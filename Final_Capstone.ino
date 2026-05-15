#include <LiquidCrystal_I2C.h> //Thư viện LiquidCrystal_I2C
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonup=7;
int buttondown=6;
int buttonselect=5;
int led1=12;
int led2=11;

int deviceCount=0;

int relay1=8; //khai báo relay 1
int relay2=9; //khai báo relay 2

int i=0; int j=0; //biến menu
int manualstate;

double temp=0;
double setTemp;
double tempTemp=0;

String menu[]={"16 Degree","20 Degree","25 Degree","Manual"};

double tempCtrl(double value){
  do{
    lcd.noBlink();
    sensors.requestTemperatures();
    temp=sensors.getTempCByIndex(0);
    delay(20);
    if (temp == -127.00){
      temp=tempTemp;
    }
    if (temp > value+0.5){
      digitalWrite(relay1,0);digitalWrite(relay2,0); //bật relay
    }
    if (temp<=value+0.5 && temp>value){
      do {
        digitalWrite(relay1,0);digitalWrite(relay2,1);
        delay(5000);
        digitalWrite(relay1,1);digitalWrite(relay2,0);
        delay(5000);
        if(digitalRead(buttonselect)==0){
          while(digitalRead(buttonselect)==0){
            digitalWrite(led1,1);delay(100);
            digitalWrite(relay1,1);
            digitalWrite(relay2,1);
            setup();
          }digitalWrite(led1,0);
        }
      }while (temp<=value+0.5 && temp>value);
    }
    if (temp <= value){
      digitalWrite(relay1,1);digitalWrite(relay2,1); //tắt relay
    }
    tempTemp=temp;
    lcd.setCursor(0,0);
    lcd.print("Set temp:");lcd.print(value);lcd.print((char)223);lcd.print("C  ");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");lcd.print(temp);lcd.print((char)223);lcd.print("C  ");
    Serial.print(value);Serial.print(" ");Serial.println(temp);Serial.println("");
    digitalWrite(led2,1);delay(50);digitalWrite(led2,0);
  }while(digitalRead(buttonselect)!=0);

  if(digitalRead(buttonselect)==0){
    while(digitalRead(buttonselect)==0){
      digitalWrite(led1,1);delay(100);
      digitalWrite(relay1,1);
      digitalWrite(relay2,1);
      setup();
    }digitalWrite(led1,0);
  }
}

void menu1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu[0]);
  lcd.setCursor(0,1);
  lcd.print(menu[1]);
}

void menu2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu[1]);
  lcd.setCursor(0,1);
  lcd.print(menu[2]);
}

void menu3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menu[2]);
  lcd.setCursor(0,1);
  lcd.print(menu[3]);
}

void setup() {
  Serial.begin(9600);
  
  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  sensors.setResolution(0,10);

  pinMode(buttonup,INPUT_PULLUP);
  pinMode(buttondown,INPUT_PULLUP);
  pinMode(buttonselect,INPUT_PULLUP);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.blink();
  lcd.setCursor(0,0);lcd.print("Capstone Design");
  lcd.setCursor(4,1);lcd.print("Group 2");
  delay(1000);lcd.clear();

  menu1();
  manualstate=0;
  setTemp=0.00;
  i=0;j=1;
  Serial.print(setTemp);Serial.print(" ");Serial.println(temp);Serial.println("");
  digitalWrite(relay1,1);digitalWrite(relay2,1);
}

void loop() {
  while(1){
    Serial.print(setTemp);Serial.print(" ");Serial.println(temp);Serial.println("");
    if(digitalRead(buttonup)==0 && i==0 && j==1){
      while(digitalRead(buttonup)==0){
        i=0;j=0;
        menu1(); lcd.setCursor(menu[0].length(),j);
        digitalWrite(led1,1); delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttonup)==0 && i==0 && j==0){
      while(digitalRead(buttonup)==0){
        i=1;j=1;
        menu3(); lcd.setCursor(menu[3].length(),j);
        digitalWrite(led1,1); delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttonup)==0 && i==1 && j==1){
      while(digitalRead(buttonup)==0){
        i=1;j=0;
        menu3(); lcd.setCursor(menu[2].length(),j);
        digitalWrite(led1,1); delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttonup)==0 && i==1 && j==0){
      while(digitalRead(buttonup)==0){
        i=0;j=1;
        menu2(); lcd.setCursor(menu[1].length(),i);
        digitalWrite(led1,1); delay(100);
      }digitalWrite(led1,0);
    }


    if(digitalRead(buttondown)==0 && i==0 && j==1){
      while(digitalRead(buttondown)==0){
        i=1;j=0;
        menu2(); lcd.setCursor(menu[2].length(),i);
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttondown)==0 && i==1 && j==0){
      while(digitalRead(buttondown)==0){
        i=1;j=1;
        menu3(); lcd.setCursor(menu[3].length(),i);
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttondown)==0 && i==1 && j==1){
      while(digitalRead(buttondown)==0){
        i=0;j=0;
        menu1(); lcd.setCursor(menu[0].length(),i);
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttondown)==0 && i==0 && j==0){
      while(digitalRead(buttondown)==0){
        i=0;j=1;
        menu1(); lcd.setCursor(menu[1].length(),j);
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }

    if(digitalRead(buttonselect)==0 && i==0 && j==0){
      while(digitalRead(buttonselect)==0){
        digitalWrite(led1,1);delay(100);digitalWrite(led1,0);
        tempCtrl(16.00);
      }
    }

    if(digitalRead(buttonselect)==0 && i==0 && j==1){
      while(digitalRead(buttonselect)==0){
        digitalWrite(led1,1);delay(100);digitalWrite(led1,0);
        tempCtrl(20.00);
      }
    }

    if(digitalRead(buttonselect)==0 && i==1 && j==0){
      while(digitalRead(buttonselect)==0){
        digitalWrite(led1,1);delay(100);digitalWrite(led1,0);
        tempCtrl(25.00);
      }
    }
    
    if(digitalRead(buttonselect)==0 && i==1 && j==1){
      while(digitalRead(buttonselect)==0){
        digitalWrite(led1,1);delay(100);digitalWrite(led1,0);
        setTemp=30.00;
        Manual();
      }
    }
  }// end while(1)
}


void Manual(){
  lcd.noBlink();
  lcd.clear();lcd.setCursor(0,0);lcd.print("Set temp: ");
  do{
    lcd.setCursor(10,0);
    lcd.print(setTemp);lcd.print((char)223);lcd.print("C ");
    if(digitalRead(buttonup)==0){
      while(digitalRead(buttonup)==0){
        setTemp+=0.5;
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }
    
    if(digitalRead(buttondown)==0){
      while(digitalRead(buttondown)==0){
        setTemp-=0.5;
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }
    delay(100);
  }while(digitalRead(buttonselect)!=0);

  if(digitalRead(buttonselect)==0 && manualstate==0){
      while(digitalRead(buttonselect)==0){
        manualstate=1;
        tempCtrl(setTemp);
        digitalWrite(led1,1);delay(100);
      }digitalWrite(led1,0);
    }
  
  if(digitalRead(buttonselect)==0 && manualstate==1){
    while(digitalRead(buttonselect)==0){
      digitalWrite(led1,1);delay(100);
      digitalWrite(relay1,1);
      digitalWrite(relay2,1);
      setup();
    }digitalWrite(led1,0);
  }
}
