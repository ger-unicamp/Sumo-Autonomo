/* Codigo do robo sumo para TJR-2016 
 * Criado por: Leonardo Alves de Melo
 * GER - Grupo de Estudos em Robótica da Unicamp */

#include <NewPing.h> //biblioteca de leitura do ultrassom

#define MOTOR_L0 5 //pinos de controle do motor esquerdo
#define MOTOR_L1 6

#define MOTOR_R0 7 //pinos de controle do motor direito
#define MOTOR_R1 8

#define TRIG_FRENTE 9 //pinos do sensor ultrassonico da frente
#define ECHO_FRENTE 10

#define TRIG_LADO 12 //pinos de controle do sensor ultrassonico do lado
#define ECHO_LADO 11

#define TAM_VEC 8 //tamanho do vetor para calculos de medias
#define TAM_MAX 50 //tamanho maximo que sera lido pelo sensor ultrassonico

#define HORARIO 0 // sentido de giro do robo
#define ANTI_HORARIO 1

#define DISTANCIA_MAX 50 //distancia maxima para se considerar que se está vendo o inimigo

typedef struct Sensor { //struct que guarda o vetor de medidas, a media, a posicao do vetor de medidas e um ponteiro para um objeto sensor
  int medida[TAM_VEC];  
  int media;
  int posicao;
  NewPing *us;
} Sensor;

Sensor sensor_frente, sensor_lado; //crio as structs de cada sensor, trabalhe apenas com elas

NewPing us_frente(TRIG_FRENTE, ECHO_FRENTE, TAM_MAX);//declaro os objetos do US. Voce nao deve utiliza-los diretamente. Use a struct sensor
NewPing us_lado(TRIG_LADO, ECHO_LADO, TAM_MAX);

void inicializa_motores(); //define como saida os pinos dos motores
void inicializa_sensores(); //inicializa os sensores e as structs

void incrementa_posicao(); //ao atualizar a media, incrementa o ponteiro para a proxima posicao do vetor que deve ser atualizada
void atualiza_media(); //atualiza o valor da media do sensor
void zera_media(); //reinicia a media do sensor

void motor_direita_frente(); //funcoes de giro de uma das rodas especificamente
void motor_direita_tras();
void motor_esquerda_frente();
void motor_esquerda_tras();

void reto(); //faz robo seguir reto
void gira(int sentido); //faz robo girar para um dos lados
int identifica_lado_giro(); //faz a leitura dos dois sensores ultrassonicos, se o sensor do lado identificar, gira para esse lado, se nao, gira para o outro


void setup() {
  inicializa_sensores();
  inicializa_motores();

  Serial.begin(9600);

}

void inicializa_motores() {
  pinMode(MOTOR_L0, OUTPUT);
  pinMode(MOTOR_L1, OUTPUT);
  pinMode(MOTOR_R0, OUTPUT);
  pinMode(MOTOR_R1, OUTPUT);
}

void inicializa_sensores() {
  
  int i;
  
  sensor_frente.us = &us_frente;
  sensor_frente.media = TAM_MAX;
  sensor_frente.posicao = 0;

  sensor_lado.us = &us_lado;
  sensor_lado.media = TAM_MAX;
  sensor_frente.posicao = 0;

  for(i = 0; i < TAM_VEC; i++) {
    sensor_frente.medida[i] = TAM_MAX;
    sensor_lado.medida[i] = TAM_MAX;
  } 
}

/* Como o vetor é cíclico, a posicao deve ser incrementada levando em conta o final do vetor */
void incrementa_posicao(Sensor *sensor) {

  if(sensor->posicao == TAM_VEC - 1) {
    sensor->posicao = 0;
  }
  else {
    sensor->posicao += 1;
  }
  
}

/* Apos a detecçao, zera as medias para esperar outra pessoa */
void zera_medias() {

  int i;

  for(i = 0; i < TAM_VEC; i++) {
    sensor_frente.medida[i] = TAM_MAX;
    sensor_lado.medida[i] = TAM_MAX;
  }

  sensor_frente.media = TAM_MAX;
  sensor_lado.media = TAM_MAX;

}

void atualiza_media() {

  int distancia;


  /* ----- Para o sensor frente ------- */
  incrementa_posicao(&sensor_frente);

  /* Subtrai a consideracao da outra medida */
  sensor_frente.media -= ((float) sensor_frente.medida[sensor_frente.posicao])/TAM_VEC;

  distancia = sensor_frente.us->ping_cm();
  if(distancia == 0) {
    distancia = TAM_MAX;
  }

  sensor_frente.medida[sensor_frente.posicao] = distancia;

  /* Soma a consideração da nova medida */
  sensor_frente.media += ((float) sensor_frente.medida[sensor_frente.posicao])/TAM_VEC;

  incrementa_posicao(&sensor_lado);

  /* Subtrai a consideracao da outra medida */
  sensor_lado.media -= ((float) sensor_lado.medida[sensor_lado.posicao])/TAM_VEC;

  distancia = sensor_lado.us->ping_cm();
  if(distancia == 0) {
    distancia = TAM_MAX;
  }

  sensor_lado.medida[sensor_lado.posicao] = distancia;

  /* Soma a consideração da nova medida */
  sensor_lado.media += ((float) sensor_lado.medida[sensor_lado.posicao])/TAM_VEC;
  
}

void motor_direita_frente() {
  analogWrite(MOTOR_R0, 0);
  analogWrite(MOTOR_R1, 255);
}

void motor_direita_tras() {
  analogWrite(MOTOR_R0, 0);
  analogWrite(MOTOR_R1, 255);
}

void motor_esquerda_frente() {
  analogWrite(MOTOR_L0, 0);
  analogWrite(MOTOR_L1, 255);
}

void motor_esquerda_tras() {
  analogWrite(MOTOR_L0, 255);
  analogWrite(MOTOR_L1, 0);
}

void reto() {

  motor_esquerda_frente();
  motor_direita_frente();  
  
}

void gira(int sentido) {

  if(sentido == HORARIO) {
    motor_direita_tras();
    motor_esquerda_frente();
  }
  else {
    motor_direita_frente();
    motor_esquerda_tras();
  }  
}

int identifica_lado_giro() {

  int i, retorno;

  for(i = 0; i < TAM_VEC; i++) {
    atualiza_media();
  }

  if(sensor_lado.media < sensor_frente.media - 10) {
    retorno = HORARIO;
  }
  else {
    retorno = ANTI_HORARIO;
  }

  return retorno;
  
}


void loop() {

  int i, sentido_giro;

  int distancia_inicial = 0;

  //determina a distancia lateral a partir de uma media sem dividir

  for(i = 0; i < 5; i++) {
    distancia_inicial += sensor_lado.us->ping_cm(); 
  }


  if(sensor_lado.us->ping_cm() != 0) { //se o sensor do lado identificou
    sentido_giro = HORARIO; 
  }
  else {
    sentido_giro = ANTI_HORARIO;
  }

  while(1) {

    /*
    Serial.print("Sensor frente:");
    Serial.print(i);
    i++;
    Serial.print(" - ");
    Serial.print(sensor_frente.us->ping_cm());

    Serial.print("    Sensor lado:");
    Serial.print(i);
    i++;
    Serial.print(" - ");
    Serial.print(sensor_lado.us->ping_cm());
    */
    //delay(200);
    
  
    if(sensor_frente.us->ping_cm() != 0) { //se o sensor da frente identificar algo
      reto();
      //Serial.println("reto");
    }
    else {
      
      //Serial.print("gira: ");
      //Serial.println(sentido_giro);
      gira(sentido_giro);
    }

    delay(2);
    
  } 

  

  
}
