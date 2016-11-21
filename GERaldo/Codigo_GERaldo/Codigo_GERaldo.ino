#include <NewPing.h>

/* Codigo fonte do robo GERaldo para o TJR-2016.
 * Autores: 
 *          Leonardo Alves de Melo
 *          Marcelo Martimiano Junior
 *          Paulo Grego
 *          Beatriz Sechin Zazulla.
 *          Bruno Eduardo Santos de Oliveira
 * GER - Grupo de Estudos em Robótica da Unicamp.
 */

/* As pinagens para o arduino estão com cores deacordo com os jumpers
 *  5V             -  VERMELHO
 *  GND            -  MARROM
 *  IMPUT          - LARANJA , LARANJA E BRANCO
 *  PWM            - VERDE, VERDE E BRANCO
 *  ECHO E TRIGGER - AZUL , AZUL E BRANCO
 */

#define MOTOR_1A 9      // Laranja
#define MOTOR_1B 8     //  Laranja
#define PWM_1 10       //   Verde

#define MOTOR_2A 6     // Laranja e Branco     
#define MOTOR_2B 7    //  Laranja e Branco     
#define PWM_2 5     //   Verde e Branco   

#define WAIT 5000     //Constante de tempo
#define VALOR_PWM 255 //Valor
#define TEMPO_DE_GIRO 1000 // aprox 90 graus

// Sensor Frontal
#define TRIG_F 11     // Azul
#define ECHO_F 12    //  Azul

// Sensor Direito
#define TRIG_D 3  // Azul e Branco
#define ECHO_D 4  //  Azul e Branco


#define MAX_DIST 50

// Tamanho do vetor
#define TAM_VETOR 5

#define FRENTE HIGH
#define TRAS LOW

typedef struct motor{
  int pinoA, pinoB, pinoPWM;
} Motor;

Motor motorEsq, motorDir;

NewPing sensor_frontal(TRIG_F, ECHO_F, MAX_DIST);
//NewPing sensor_direito(TRIG_D, ECHO_D, MAX_DIST);

// vetor de leituras
// tirar mediana 
// dica: não usar um for no loop
// por isso essa variável é global
// a implementação é circular 
// outra dica é entregar outro vetor para a ordenação
int leituras_frontal[TAM_VETOR], i = 0;

void setup()
{
  inicializa_motores();
  inicializa_sensores();
  
  Serial.begin(115200);
}

void loop()
{
  int d, aux_frontal[TAM_VETOR], l; 

  // implementação circular - leitura
  leituras_frontal[i % TAM_VETOR] = sensor_frontal.ping_cm();
  
  Serial.print("i: ");
  Serial.println(i % TAM_VETOR);

  // copia do vetor para o auxiliar 
  for(l = 0; l < TAM_VETOR; l++)
  {
    aux_frontal[l] = leituras_frontal[l];
    Serial.print("pos: ");
    Serial.print(l);
    Serial.print(", valor:");
    Serial.println(aux_frontal[l]);
  }

  // retira a mediana
  d = mediana(aux_frontal);
  Serial.print("D=");
  Serial.println(d);
  // teste para onde o robô seguira 
  // 0 eh considerado distancia maxima

  if (d < MAX_DIST && d > 0)
  {
    frente();
  } else
  {
    direita();
  }

  delay(10);
  i++;
}

void inicializa_motores()
{
  motorEsq.pinoA = MOTOR_1A;
  motorEsq.pinoB = MOTOR_1B;
  motorEsq.pinoPWM = PWM_1;

  motorDir.pinoA = MOTOR_2A;
  motorDir.pinoB = MOTOR_2B;
  motorDir.pinoPWM = PWM_2;
  
  pinMode(motorEsq.pinoA, OUTPUT);
  pinMode(motorEsq.pinoB, OUTPUT);
  pinMode(motorEsq.pinoPWM, OUTPUT);
  
  pinMode(motorDir.pinoA, OUTPUT);
  pinMode(motorDir.pinoB, OUTPUT);
  pinMode(motorDir.pinoPWM, OUTPUT);

  analogWrite (motorEsq.pinoPWM, VALOR_PWM);
  analogWrite (motorDir.pinoPWM, VALOR_PWM);
}

void inicializa_sensores()
{
 
}

void controlaMotor(Motor motorControlado, boolean sentido){
  digitalWrite(motorControlado.pinoA, sentido);
  digitalWrite(motorControlado.pinoB, !(sentido));
}

void frente()
{
  controlaMotor(motorEsq, FRENTE);
  
  controlaMotor(motorDir, FRENTE);
}

void tras()
{
  controlaMotor(motorEsq, TRAS);
  
  controlaMotor(motorDir, TRAS);
}

void esquerda()
{
  controlaMotor(motorEsq, TRAS);
  
  controlaMotor(motorDir, FRENTE);
  
  delay(TEMPO_DE_GIRO);
}

void direita()
{
  controlaMotor(motorEsq, FRENTE);
  
  controlaMotor(motorDir, TRAS);
  
  delay(TEMPO_DE_GIRO);
}

void freia()
{
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, LOW);
  
  digitalWrite(MOTOR_2A, LOW); 
  digitalWrite(MOTOR_2B, LOW);
}

int mediana(int* v)
{  
  // ordenacao dos dados
  insertion_sort(v, TAM_VETOR);

  // tomada da mediana 
 return v[(int)TAM_VETOR/2]; 
}

// custo baixo com vetores quase ordenados 
void insertion_sort(int* array, int tamanho) 
{
  int i, j, tmp;
  for (i = 1; i < tamanho; i++) 
  {
    j = i;
    while (j > 0 && array[j - 1] > array[j]) 
    {
      tmp = array[j];
      array[j] = array[j - 1];
      array[j - 1] = tmp;
      j--;
    }
  }
}
