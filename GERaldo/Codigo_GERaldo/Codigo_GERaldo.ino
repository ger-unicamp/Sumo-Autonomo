#include <NewPing.h>

/* Codigo fonte do robo GERaldo para o TJR-2016.
 * Autores: 
 *          Leonardo Alves de Melo
 *          Marcelo Martimiano Junior
 *          Paulo Grego
 *          Beatriz Sechin Zazulla.
 * GER - Grupo de Estudos em Robótica da Unicamp.
 */
 
#define MOTOR_1A 7
#define MOTOR_1B 6
#define PWM_1 5

#define MOTOR_2A 8        
#define MOTOR_2B 9        
#define PWM_2 10        

#define WAIT 5000     //Constante de tempo
#define VALOR_PWM 255 //Valor
#define TEMPO_DE_GIRO 1000 // aprox 90 graus

// Sensor Frontal
#define TRIG_F 3
#define ECHO_F 4

// Sensor Direito
//#define TRIG_D 
//#define ECHO_D 

#define MAX_DIST 50

// Tamanho do vetor
#define TAM_VETOR 5

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
  while(true)
  {
    frente();
  }
  Serial.println(sensor_frontal.ping_cm());
  int d, aux_frontal[TAM_VETOR], l; 

  // implementação circular - leitura
  leituras_frontal[i % TAM_VETOR] = sensor_frontal.ping_cm();

  // copia do vetor para o auxiliar 
  for(l = 0; l < TAM_VETOR; l++)
  {
    aux_frontal[l] = leituras_frontal[l];
  }

  // retira a mediana
  d = mediana(aux_frontal);
  Serial.print("D=");
  Serial.println(d);
  // teste para onde o robô seguira 
  // 0 eh considerado distancia maxima
  if (d < MAX_DIST && d > 0)
  {
    while(true)
    {
      frente();
    }
  } else
  {
    direita();
  }
  
  delay(10);
}

void inicializa_motores()
{
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(PWM_1, OUTPUT);
  
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(PWM_2, OUTPUT);

  analogWrite (PWM_1, VALOR_PWM);
  analogWrite (PWM_2, VALOR_PWM);
}

void inicializa_sensores()
{
 
}

void frente()
{
  digitalWrite(MOTOR_1A, HIGH); // quando A é HIGH o LED vermelho acende.
  digitalWrite(MOTOR_1B, LOW);
  
  digitalWrite(MOTOR_2A, HIGH); // quando A é HIGH o LED vermelho acende.
  digitalWrite(MOTOR_2B, LOW);
}

void tras()
{
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, HIGH);  // quando B é HIGH o LED verde acende. 
  
  digitalWrite(MOTOR_2A, LOW); 
  digitalWrite(MOTOR_2B, HIGH);  // quando B é HIGH o LED verde acende. 
}

void esquerda()
{
  digitalWrite(MOTOR_1A, LOW);
  digitalWrite(MOTOR_1B, HIGH);  // quando B é HIGH o LED verde acende. 
  
  digitalWrite(MOTOR_2A, HIGH); // quando A é HIGH o LED vermelho acende.
  digitalWrite(MOTOR_2B, LOW);
  delay(TEMPO_DE_GIRO);
}

void direita()
{
  digitalWrite(MOTOR_1A, HIGH); // quando A é HIGH o LED vermelho acende.
  digitalWrite(MOTOR_1B, LOW);
  
  digitalWrite(MOTOR_2A, LOW); 
  digitalWrite(MOTOR_2B, HIGH);  // quando B é HIGH o LED verde acende. 
  
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
  
