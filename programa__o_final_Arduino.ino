#include <Stepper.h>
const int stepsPerRevolution = 2048; 
float dteta = 5.0;        // variação angular do motor em graus
int idtet = dteta;
float tetav = 0.;
float dtetav;
float passo;
int npassos;
int cont = 0;
int voltar;
int dig;
int button;
//Inicializa a biblioteca motor utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 
void setup() 
{ 
//Determina a velocidade inicial do motor 
    myStepper.setSpeed(10);
// Velocidade da porta serial --------------------------------------------------------
    Serial.begin(9600);
Serial.println("CLEARSHEET");     //Excel
Serial.println("CLEARDATA");       //Excel
Serial.println("LABEL,Angle (graus),Voltage (V)");      //Excel
button = LOW;
} 

void loop() 
{ 
do  {
button = digitalRead(5);
delay (100);
}  while (button != HIGH);
     if(button = HIGH)
     {
passo = 360./2048.;
npassos = (dteta/passo)+0.5;
dtetav = npassos*passo;   //  em graus

if(tetav != 0.) 
{
// contador de ângulo -----------------------------------------------------------------
// Gira o motor no sentido horário 
myStepper.step(npassos);
cont = cont + 1;
     }
     if(tetav <= 184.0)
     {
// leitura do sensor de luz ----------------------------------------------------------
     dig = 2;
     float sensorValue0 = analogRead(A1);
     float voltage0 = sensorValue0 * 5.0 / 1024.0;
     Serial.print("DATA,");         //Excel
     Serial.print(tetav);
     Serial.print(",");
     Serial.println(voltage0,dig);
     tetav = tetav + dtetav;       // em graus
     delay(500);
     } 
  else
  {
    int npasstot = npassos*cont;

    for (voltar = npasstot; voltar >= 0; voltar -= 1)
    {
    myStepper.step(-1);
    delay(10);
    }
      tetav = 0.;
      cont = 0;
  }
     }
     
     button = digitalRead(5);
     //delay (300);
    
}
