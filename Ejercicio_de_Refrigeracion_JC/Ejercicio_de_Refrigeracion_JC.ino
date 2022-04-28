
/*
 * Administración de servidores
 * Por: Juan Carlos Estrada Gutiérrez
 * Fecha: 20 de abril de 2022
 * 
 * Programa creado a partir de los programas Botón-Led y Ejemplo DHT11
 * 
 * Características
 *   Sensor de temperatura y humedad
 *   Boton1: Manual. Activa la refrigeración al ser presionado
 *   Boton2: Alta demanda
 *   Boton3: Sobre carga de funcionamiento
 *   
 *   Led1: Refrigeracion manual
 *   Led2: Refrigeración automática
 *   
 *   Que se encienda la refrigeracion manual cada que se presione el boton de manual
 *   
 *   La refrigeracion manual tiene prioridad a la refrigeracion automática.
 *   
 *   Si la termperatura es alta (mayor a 28, por ejemplo), se activa la refrigeracion automática
 *   
 *   Si tengo alta demanda o sobre carga, se activa la refrigeración automática
 *   
 *   Si tengo alta demanda o sobrecarga de funcionamiento y ademas temperatura alta, se activan ambas refrigeraciones
 *   
 *   Botones 14, 15, 13
 *   Leds 4, 2
 *   DHT11 12
 */

// Bibliotecas
#include "DHT.h" // Incluuir la biblioteca de DHT11

// Constantes
// Constantes para manejar el DHT11
#define DHTPIN 12       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
const int BOTON1 = 13; // Manual
const int BOTON2 = 15; // Alta Demanda
const int BOTON3 = 14; // Sobrecarga de Funcionamiento

const int LEDM = 2; // Refrigeración MANUAL
const int LEDA = 4; // Refreigeración Automática
const float TemperaturaAlta = 29;

// Variables
int dato1;
int dato2;
int dato3;

// Definición de objetos

DHT dht(DHTPIN, DHTTYPE);   // Objeto para manejar el DHT11

// Condiciones iniciales - Se ejecuta sólo una vez al energizar
void setup() {// Inicio de void setup ()
  // Iniciar comunicación serial
  Serial.begin(115200);
  Serial.println("Hola, inicié");
  pinMode (BOTON1, INPUT_PULLUP);//Configurar el pin del boton como entrada //INPUT, OUTPUT
  pinMode (BOTON2, INPUT_PULLUP);//Configurar el pin del boton como entrada //INPUT, OUTPUT
  pinMode (BOTON3, INPUT_PULLUP);//Configurar el pin del boton como entrada //INPUT, OUTPUT
  
  pinMode (LEDM, OUTPUT); // Configurar el pin del led como salida de voltaje
  pinMode (LEDA, OUTPUT); // Configurar el pin del led como salida de voltaje
  
  dht.begin(); //Inicialización de la comunicación con el sensor DHT11
  dato1=0;
  dato2=0;
  dato3=0;
}// Fin de void setup

// Cuerpo del programa - Se ejecuta constamente
void loop() {// Inicio de void loop
  // put your main code here, to run repeatedly:
  // Wait 2 seconds between measurements.
  delay(2000);

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
  //Para activar la refrigeración Automática
  if (t>=TemperaturaAlta) {
  digitalWrite (LEDA, HIGH);}
  if (t<TemperaturaAlta) {
  digitalWrite (LEDA, LOW);}
  
  //Para activar la refrigeración Manual
  dato1 = digitalRead (BOTON1); //Leer el pin del boton
  digitalWrite (LEDM, !dato1); //Prender el led Refrigeración automática
  Serial.print(F("Dato 1: "));
  Serial.println (dato1);
  delay (200);
   
  // Alta demanda o sobre carga, se activa la refrigeración automática
  dato2 = digitalRead (BOTON2); //Leer el pin del boton
  dato3 = digitalRead (BOTON3); //Leer el pin del boton
  if (!dato2 || !dato3) {
      digitalWrite (LEDA, HIGH); //Prender el led refrigeración automática
      Serial.print(F("Dato 2: "));
      Serial.println (dato2);
      Serial.print(F("Dato 3: "));
      Serial.println (dato3);
      delay (200);
  }
}
// Fin de void loop

// Funcioes del usuario
