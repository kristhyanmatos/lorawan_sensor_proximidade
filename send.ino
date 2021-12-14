#include <SPI.h>
#include <LoRa.h>

// Pino usado para disparar os pulsos do sensor
int PinTrigger = 2;
 
// pino usado para ler a saida do sensor
int PinEcho = 3; 

float TempoEcho = 0;
// em metros por segundo

const float VelocidadeSom_mpors = 340; 

// em metros por microsegundo
const float VelocidadeSom_mporus = 0.000340;

//Cria um número aleatório para evitar perda de transmissão para o primeiro dígito
long randNumber;

// Distância de objeto detectada
float distancia;

// Contador de pacotes enviados
int counter = 0;

void setup() {
 // Configura pino de Trigger como saída e inicializa com nível baixo
 pinMode(PinTrigger, OUTPUT);
 digitalWrite(PinTrigger, LOW);
 
 // configura pino ECHO como entrada
 pinMode(PinEcho, INPUT); 
 
 Serial.begin(9600);

 while (!Serial);
  
 Serial.println("Sensor de proxomidade transmissor");

 if (!LoRa.begin(915E6)) {
   Serial.println("Falha ao iniciar LoRa!");
   while (1);
 }else{
  Serial.println("LoRa iniciado!");
 }
 
 delay(100);
}
void loop(){
 Serial.println();
 Serial.print("Enviando pacote: ");
 Serial.println(counter);
 randNumber = random(1000);

 
 int randNumber = random(100); Dummyvalue = randNumber;


  // Envia pulso para o disparar o sensor
  DisparaPulsoUltrassonico();
  // Mede o tempo de duração do sinal no pino de leitura(us)
  TempEcho = pulseIn(PinEcho, HIGH);
  Serial.println("Distancia em metros: ");
  distancia = CalculaDistancia(TempoEcho)
  Serial.println(CalculaDistancia(TempoEcho));

  String Datastring = String(distancia)+ (";") + String(distancia) + (";");
 
  Serial.println(Datastring);
  LoRa.beginPacket();      
  LoRa.print(Datastring);
  LoRa.print(counter);
  digitalWrite(Red_Led, HIGH);
  delay(500);
  digitalWrite(Red_Led, LOW);
  LoRa.endPacket();
  counter++;
  
  // aguarda um pouco antes de começar tudo de novo
  delay(3000);
  
}
// Funçao para enviar o pulso de trigger
void DisparaPulsoUltrassonico(){
  // Para fazer o HC-SR04 enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10us de duraçao
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
  }
}

// Função para calcular a distancia em metros
float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}