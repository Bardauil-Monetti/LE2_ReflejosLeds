//Hecho por Gonzalo Bardauil y Brenda Gamboa
#include <Arduino.h>
int puntos=0;
int leds[7] = {23, 12, 21, 19, 18, 15, 5};
int boton = 26;
int sel;
int verde=3;
volatile bool botonPulsado = false;
int tiempoAnterior = 0;
int intervalo = 500;
int intervaloInicial = 1000;
int intervaloMin = 50;
int ledPrendido = 0;
int direccion = 1;
void IRAM_ATTR botonISR(){
    botonPulsado = true;

}
void setup(){
    Serial.begin(115200);
    for (int i=0; i<7; i++){
        pinMode(leds[i], OUTPUT);
    }
    pinMode(boton, INPUT);
    attachInterrupt(digitalPinToInterrupt(boton), botonISR, FALLING);

}

void loop(){
        int ahora = millis();    
        digitalWrite(1, HIGH);
        if (ahora - tiempoAnterior >= intervalo){
            digitalWrite(ledPrendido, HIGH);
            digitalWrite(ledPrendido-direccion, LOW);
            tiempoAnterior = ahora;
        } 
        for(int i=0; i<7; i++){
            digitalWrite(leds[i], HIGH);
            sel = i; 
            if (botonPulsado){
                botonPulsado=false;
                puntos++;
                Serial.print("Acertaste, tu puntuacion es de: ");
                Serial.println(puntos);
                intervalo = intervalo - intervalo * 0.25;
            }
            else digitalWrite(leds[i], LOW);
            Serial.println("Fallaste, tu puntuacion fue de: ");
            Serial.println(puntos);
            puntos=0;
            intervalo = 500;
        }
        

}
