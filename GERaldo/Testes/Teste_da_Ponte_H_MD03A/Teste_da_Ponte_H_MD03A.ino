
#define IN1A 7
#define IN1B 6
#define PWM1 5

#define IN2A 8        
#define IN2B 9        
#define PWM2 10        

#define WAIT 5000     //Constante de tempo
#define VALOR_PWM 255 //Valor

void setup() {
  analogWrite (PWM1, VALOR_PWM);
  analogWrite (PWM2, VALOR_PWM);
}

void loop() {
  
  // Acende os dois LEDs verdes da ponte H.
  digitalWrite  (IN1A, LOW); // quando A é HIGH é vermelho 
  digitalWrite (IN1B, HIGH);
  digitalWrite  (IN2A, LOW); // quando A é HIGH é vermelho 
  digitalWrite (IN2B, HIGH);
  delay(WAIT);

  // Acende os dois LEDs vermelhos da ponte H.
  digitalWrite  (IN1A, HIGH); // quando A é HIGH é vermelho 
  digitalWrite (IN1B, LOW);
  digitalWrite  (IN2A, HIGH); // quando A é HIGH é vermelho 
  digitalWrite (IN2B, LOW);
  delay(WAIT);
}
