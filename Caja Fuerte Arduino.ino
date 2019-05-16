#include <Servo.h> 
#include <Keypad.h>
#include <EEPROM.h>


Servo servomotor;//servo seguro
Servo servomotor1;// servo Puerta
char* password = {"1234"}, *puk={"2222"} ;// definicion de la clave
int position = 0;//posicion inicial en 0

const byte rows = 4; //filas
const byte cols = 3 ; //columnas
char keys[rows][cols] = {

  {'1', '2', '3'},//fila 1
  {'4', '5', '6'},//fila 2
  {'7', '8', '9'},//fila 3
  {'*', '0', '#'} //fila 4

};
  int ledState = LOW;
String clave="";
String pukk="";
byte rowPins[rows] = {2, 3, 4, 5}; // Definicion pines filas
byte colPins[cols] = {6, 7, 8}; //Definicion pines columnas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);//Reconocimiento libreria

int greenPin = A1; // Definicion de pines
int greenPin1 = A2; 
int greenPin2 = A3; 
int greenPin3 = A4; 
int redPin = A0;
  int a=0, i=0, j=0, x=0;
void setup()
{
  servomotor.attach(9); //abrir puerta
  servomotor1  .attach(10); //abrir seguro
  pinMode(redPin, OUTPUT); //denotar salida
  pinMode(greenPin, OUTPUT); 
  pinMode(greenPin1, OUTPUT);
  pinMode(greenPin2, OUTPUT); 
  pinMode(greenPin3, OUTPUT); 
  digitalWrite(greenPin, LOW );
  digitalWrite(greenPin1, LOW );
  digitalWrite(greenPin2, LOW );  
  digitalWrite(greenPin3, LOW ); 
  digitalWrite(redPin, HIGH);
  bloqueo(true); // desbloqueo puerta
  void cambio(char[]);
   Serial.begin(9600);
}
void loop()
{
  int n;
//Valor de ingreso de la clave
  char key = keypad.getKey();
    if (key == '*' )//dar posicion a 0 e ingresar la contraseña 
    {
      clave=""; //Posicion 0
      bloqueo(true);
      i=0;
    }  
     if(a==3)
      {
        for(n=0;n<7;n++)
        {
         if (n%2 == 0 )
           {
           ledState = HIGH;
           digitalWrite(redPin, ledState);
           }
           else
           ledState = LOW;
           digitalWrite(redPin, ledState);
           delay(100);
         }
       if(key)
       {
        pukk+=key;
        j++;
         if(j==1)
     {
  digitalWrite(greenPin, HIGH );
     }
     if(j==2)
     {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
     }
     if(j==3)
     {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
     }
     Serial.println("pukk= "); Serial.println(pukk);
     Serial.println("j= "); Serial.println(j);
     if(j==4)
         {
          j=0;
       if(pukk==puk)
       {a=0;
             digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
  digitalWrite(greenPin3, HIGH); 
        bloqueo(false);
        pukk="";
        if (key == '*')
          {
           bloqueo(true);
          a=0;  
          clave="";
          i=0;
          }    
       }
       else
      {
        digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
  digitalWrite(greenPin3, HIGH); 
  delay(100);
        bloqueo(true);
        delay(10000);
        pukk="";
        a=0;
        i=0;
        clave="";
      }clave="";}
      
       }      
  }  
  if(a<3)
  {                                                                     
    if(key!='*'&& key )
    {
     clave+=key;
     i++;
     Serial.println("clave= "); Serial.println(clave);
     Serial.println("i= "); Serial.println(i);
     if(i==1)
     {
  digitalWrite(greenPin, HIGH );
     }
     if(i==2)
     {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
     }
     if(i==3)
     {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
     }
     }   
   if (i == 4)
    {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
  digitalWrite(greenPin3, HIGH); 
    i=0;
    if(clave==password)
    {
    bloqueo(false);
     if (key == '*')
      {
       bloqueo(true);
       a=0;  
      }    
     } 
     else {
  digitalWrite(greenPin, HIGH );
  digitalWrite(greenPin1, HIGH );
  digitalWrite(greenPin2, HIGH );  
  digitalWrite(greenPin3, HIGH); 
  delay(1000);
    bloqueo(true);
    a++;
     Serial.println("a= "); Serial.println(a);
  x=0; } 
  clave="";   
   }
  }
}
void bloqueo(int locked)                                         
{
  
  if (locked) {    
    digitalWrite(redPin, HIGH);    
    digitalWrite(greenPin, LOW);
    digitalWrite(greenPin1, LOW);
    digitalWrite(greenPin2, LOW);
    digitalWrite(greenPin3, LOW);
       
    servomotor.write(10);
    delay(1000); 
    servomotor1.write(10);
    delay(100);                  
   
  }
  else {   
    digitalWrite(redPin, LOW);
  int n;
  for(n=0;n<15;n++){
    if (n%2 == 0 )
    ledState = HIGH;
    else
    ledState = LOW;
    digitalWrite(greenPin, ledState);
    digitalWrite(greenPin1, ledState);
    digitalWrite(greenPin2, ledState);
    digitalWrite(greenPin3, ledState);
    delay(50);
  }   
    servomotor1.write(90);
     delay(1000);
    servomotor.write(90);
    delay(100); 
      
  }
}
