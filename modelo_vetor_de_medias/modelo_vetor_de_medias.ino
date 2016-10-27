/* Programa exemplo de utilizacao de medias para o calculo do sensor */

#include <NewPing.h> //lib do ultrassom 

#define ECHO_PIN_A 11
#define TRIG_PIN_A 12

#define ECHO_PIN_B 9
#define TRIG_PIN_B 8

#define MAX_DISTANCE_A 80
#define MAX_DISTANCE_B 80


#define THRESHOLD_A 10
#define THRESHOLD_B 10


#define MAX_VEC 32

typedef struct Sensor {
  
  float media;
  int medidas[MAX_VEC];
  int posicao;
  NewPing *us;
  
} Sensor;

Sensor sensor_A, sensor_B;

//Construcao dos objetos sensores
NewPing us_A(TRIG_PIN_A, ECHO_PIN_A, MAX_DISTANCE_A);
NewPing us_B(TRIG_PIN_B, ECHO_PIN_B, MAX_DISTANCE_B);

/* Define os valores iniciais do sensor */
void inicializaSensores() {

  int i;
  
  /* Define qual o sensor de cada */
  sensor_A.us = &us_A;
  sensor_B.us = &us_B;

  /* Outras definicoes dos sensores */
  for(i = 0; i < MAX_VEC; i++) {
    sensor_A.medidas[i] = 0;
    sensor_B.medidas[i] = 0;
  }

  sensor_A.posicao = 0;
  sensor_B.posicao = 0;

  sensor_A.media = 0;
  sensor_B.media = 0;
  
}

/* Como o vetor é cíclico, a posicao deve ser incrementada levando em conta o final do vetor */
void incrementaPosicao(Sensor *sensor) {

  if(sensor->posicao == MAX_VEC - 1) {
    sensor->posicao = 0;
  }
  else {
    sensor->posicao += 1;
  }
  
}

//imprime a media dos sensores
void imprime() {

  /* Imprime o sensor A */
  Serial.print("sensorA: ");
  Serial.println(sensor_A.media); 

  /* Imprime o sensor B */
  Serial.print("sensorB: ");   
  Serial.println(sensor_B.media);

  Serial.println("------------------------------------");


}


/* Le um novo valor do ultrassonico e atualiza a media */
void media(Sensor *sensor) {

  int i, medida;

  incrementaPosicao(sensor);

  /* Subtrai a consideracao da outra medida */
  sensor->media -= ((float) sensor->medidas[sensor->posicao])/MAX_VEC;

  medida = sensor->us->ping_cm();

  /* Se o sensor nao detectar, entao coloca a distancia maxima */
  if(medida == 0) {
    medida = MAX_DISTANCE_A;
  }

  sensor->medidas[sensor->posicao] = medida;

  /* Soma a consideração da nova medida */
  sensor->media += ((float) sensor->medidas[sensor->posicao])/MAX_VEC;

  
  
}


//Retorna o valor bruto de um sensor, tratando o dado de modo a que todo zero seja considerado distancia maxima
int medida_simples(Sensor *sensor) {
  int medida = sensor->us->ping_cm();

  if(medida == 0) {
    medida = MAX_DISTANCE_A;
  }

  return medida;
}

void setup() {  

  Serial.begin(115200);

  inicializaSensores();

}



void loop() {  



}
