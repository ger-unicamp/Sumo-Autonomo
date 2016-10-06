/*******************************************************************
 * TJR SUMO - GRUPO DE ESTUDOS EM ROBOTICA DA UNICAMP
 * 
 * Codigo do sumo tradicional utilizado na ultima competicao de 2015
 * 
 * Data da ultima modificacao: 09/06/2016
 *******************************************************************/

#include <Ultrasonic.h>

#define SOM_FRENTE_ECHO 12
#define SOM_FRENTE_TRIG 13
#define SOM_DIREITA_ECHO 11
#define SOM_DIREITA_TRIG 10

#define MOTOR_E_F 3
#define MOTOR_E_T 2
#define MOTOR_D_F 4
#define MOTOR_D_T 5

/* distancia maxima de analise do sensor */
#define SOM_MAX_DIST 60

#define FRENTE HIGH
#define TRAS LOW

Ultrasonic sensorSomFrente(SOM_FRENTE_TRIG, SOM_FRENTE_ECHO);   
Ultrasonic sensorSomDireita(SOM_DIREITA_TRIG, SOM_DIREITA_ECHO);  

void controlamotor(int MOTOR_F, int MOTOR_T, boolean direcao)
{
  /* Motor esquerdo pra frente*/ 
  digitalWrite(MOTOR_F, direcao);
  digitalWrite(MOTOR_T, ! direcao);
}

void giraHorario() 
{ 
  /* M
otor esquerdo pra frente*/
  controlamotor(MOTOR_E_F, MOTOR_E_T, FRENTE);

  /* Motor direito pra tras */
  controlamotor(MOTOR_D_F, MOTOR_D_T, TRAS);
  
}

void giraAntiHorario() 
{

  /* Motor esquerdo pra tras*/
  controlamotor(MOTOR_E_F, MOTOR_E_T, TRAS);

  /* Motor direito pra frente */
  controlamotor(MOTOR_D_F, MOTOR_D_T, FRENTE);

}

void avanca() 
{

 /* Motor esquerdo pra frente */
  controlamotor(MOTOR_E_F, MOTOR_E_T, FRENTE);

  /* Motor direito pra frente */
  controlamotor(MOTOR_D_F, MOTOR_D_T, FRENTE);
  
  delay(200);
}

void volta() {

   /* Motor esquerdo pra tras */
  controlamotor(MOTOR_E_F, MOTOR_E_T, TRAS);

  /* Motor direito tras */
  controlamotor(MOTOR_D_F, MOTOR_D_T, TRAS);

}

boolean testaSomDireito() 
{

  /* Teste da leitura do valor analogico do pino do sensor */
  if(sensorSomDireita.Ranging(CM) <= SOM_MAX_DIST) 
  {
    /* enquanto procura obstaculo a frente, gira */
    while(!testaSomFrente())
      giraHorario();    
    delay(10);
    /* encontrando, retorna verdadeiro */
    return true;
  }  
  /* se nao, retorna falso */
  return false;
}

boolean testaSomFrente() 
{
  /* Teste da leitura do valor analogico do pino do sensor */
  if(sensorSomFrente.Ranging(CM) <= SOM_MAX_DIST) 
  {
    /* se ha alguem na frente, retorna verdadeiro */
    return true;
  }
  /* se nao, retorna falso */
  return false;
}


void setup() 
{
  pinMode(MOTOR_D_F, OUTPUT);
  pinMode(MOTOR_D_T, OUTPUT);
  pinMode(MOTOR_E_F, OUTPUT);
  pinMode(MOTOR_E_T, OUTPUT);
  
  pinMode(SOM_FRENTE_ECHO, INPUT);
  pinMode(SOM_FRENTE_TRIG, OUTPUT);
  pinMode(SOM_DIREITA_ECHO, INPUT);
  pinMode(SOM_DIREITA_TRIG, OUTPUT);
}

void loop() 
{  
    /* testa se o sensor frontal tem algo a frente */
    if(testaSomFrente()) 
    {
      /* se sim, avanca nessa direcao */
      avanca();
      delay(10);
    }
    /* caso contrario, verifica o sensor do lado direito */
    else 
    {
      /* se nao encontra ninguem a sua frente */
      if(!testaSomDireito())  
          /* gira */
          giraAntiHorario();
    }
}
