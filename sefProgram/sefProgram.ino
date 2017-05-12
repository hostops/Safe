#include <EEPROM.h>
#include <Servo.h>
#include <Keypad.h>  
int digitPins[] ={5, 2, 1, A0};
int segPins[]={4, 0,A2,A4,A5,3,A1, A3};
byte rowPins[] = {12, 11, 10, 9};
byte colPins[] = {8, 7, 6, 5};
char hexaKeys[sizeof(rowPins)][sizeof(colPins)] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
Servo ser;
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, sizeof(rowPins), sizeof(colPins)); 
int pass[] ={7,8,8,9};
int disp[]={-1,-1,-1,-1};
boolean opened=false;
void setup()
{
    preberiGeslo();
    pinMode(5,OUTPUT);pinMode(2,OUTPUT);pinMode(0,OUTPUT);pinMode(A0,OUTPUT);pinMode(4,OUTPUT);pinMode(1,OUTPUT);
    pinMode(A2,OUTPUT);pinMode(A4,OUTPUT);pinMode(A5,OUTPUT);pinMode(3,OUTPUT);pinMode(A1,OUTPUT);pinMode(A3,OUTPUT);
    for(int i=0;i<sizeof(digitPins);i++)
    {
        digitalWrite(digitPins[i],HIGH);
    }
    ser.attach(13);
    close();
}
int i =0;
void loop()
{
char k = keypad.getKey();
    if (k) {
      switch(k){
        case '#':
          if(opened)zapisiNovoGeslo();
        break; 
        case '*':
          close();
          disp[0]=-1;disp[1]=-1;disp[2]=-1;disp[3]=-1;
          i=0;
        break; 
        default: 
          disp[i]=k-'0';
          i=(i+1)%4;       
          if(disp[0]==pass[0]&&disp[1]==pass[1]&&disp[2]==pass[2]&&disp[3]==pass[3])
            open();
          else close();
        break;
      }
      
    }
print(disp);
}



void preberiGeslo(){
    int p;
    EEPROM.get(0, p);
    pass[0]=p/1000;
    p=p%1000;
    pass[1]=p/100;
    p=p%100;
    pass[2]=p/10;
    p=p%10;
    pass[3]=p;
}

void zapisiNovoGeslo(){
      while(true){
        boolean z=false;
            char k = keypad.getKey();
            if (k) {
              switch(k){
                case '#':
                z=true;
                break; 
                case '*':
                break; 
                default: 
                  pass[i]=k-'0';
                    i=(i+1)%4;
                break;
              }
              
            }
        print(pass);
        if(z)break;
      
      }
      EEPROM.put(0, pass[0]*1000+pass[1]*100+pass[2]*10+pass[3]);
      
}
void open(){
  ser.write(180);
  opened=true;
  }
void close(){
  ser.write(0);
  opened=false;
  }





/*7 seg display*/
void print(int n[]){
    write(0, n[0]);
    write(1, n[1]);
    write(2, n[2]);
    write(3, n[3]);
}
void print(char c[]){
    write(0, c[0]);
    write(1, c[1]);
    write(2, c[2]);
    write(3, c[3]);
}
void write(int p, int n)
{
    analogWrite(digitPins[p],LOW);
    if (n==9)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[5],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==8)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[4],HIGH);
        digitalWrite(segPins[5],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==7)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[5],HIGH);
    }
    else if (n==6)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[4],HIGH);
        digitalWrite(segPins[5],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==5)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[5],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==4)
    {
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[5],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==3)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==2)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[4],HIGH);
        digitalWrite(segPins[6],HIGH);
    }
    else if (n==1)
    {
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
    }
    else if (n==0)
    {
        digitalWrite(segPins[0],HIGH);
        digitalWrite(segPins[1],HIGH);
        digitalWrite(segPins[2],HIGH);
        digitalWrite(segPins[3],HIGH);
        digitalWrite(segPins[4],HIGH);
        digitalWrite(segPins[5],HIGH);
    }
    digitalWrite(digitPins[p],HIGH);
    clear();
}

void write(int p, char digit){
  analogWrite(digitPins[p],LOW);
  if(digit=='A'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='B'){
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='C'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
  }

  if(digit=='D'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[6], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='E'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='F'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='G'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
  }

  if(digit=='H'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='I'){
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
  }

  if(digit=='J'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='K'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='L'){
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='M'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
  }

  if(digit=='N'){
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='O'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='P'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
    digitalWrite(1, HIGH);
  }

  if(digit=='Q'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);digitalWrite(1, HIGH);
  }

  if(digit=='R'){
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='S'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='T'){
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

 if(digit=='U'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);digitalWrite(1, HIGH);
  }

  if(digit=='V'){
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
  }

  if(digit=='W'){
    digitalWrite(segPins[1], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[5], HIGH);
  }

  if(digit=='X'){
    digitalWrite(segPins[1], HIGH);digitalWrite(1, HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='Y'){
    digitalWrite(segPins[1], HIGH);digitalWrite(1, HIGH);
    digitalWrite(segPins[2], HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[5], HIGH);
    digitalWrite(segPins[6], HIGH);
  }

  if(digit=='Z'){
    digitalWrite(segPins[0], HIGH);
    digitalWrite(segPins[1], HIGH);digitalWrite(1, HIGH);
    digitalWrite(segPins[3], HIGH);
    digitalWrite(segPins[4], HIGH);
    digitalWrite(segPins[6], HIGH);
  }
}


void clear()
{
    digitalWrite(segPins[0],LOW);
    digitalWrite(segPins[1],LOW);
    digitalWrite(segPins[2],LOW);
    digitalWrite(segPins[3],LOW);
    digitalWrite(segPins[4],LOW);
    digitalWrite(segPins[5],LOW);
    digitalWrite(segPins[6],LOW);
    digitalWrite(segPins[7],LOW);
}
