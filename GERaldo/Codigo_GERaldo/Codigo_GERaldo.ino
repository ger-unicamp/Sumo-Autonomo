/* Codigo fonte do robo GERaldo para o TJR-2016.
 * Autores: 
 *          Leonardo Alves de Melo
 *          Marcelo Martimiano Junior
 *          Paulo Grego.
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
#define TEMPO_DE_GIRO 2000

void setup()
{
  inicializa_motores();
}

void loop()
{
  frente(); 
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
