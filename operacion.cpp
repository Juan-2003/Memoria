#include <iostream>
#include "operacion.h"
#include <math.h>

using namespace std;

Operacion::Operacion(){}
Operacion::Operacion(float operando1, float operando2, char operador){
    setOperando1(operando1);
    setOperando2(operando2);
    setOperador(operador);
    setResultado(crearResultado(operando1, operando2, operador));

}

void Operacion::setOperando1(float operando1){
    this->operando1 = operando1;
}

void Operacion::setOperando2(float operando2){
    this->operando2 = operando2;
}

void Operacion::setOperador(char operador){
    this->operador = operador;
}

void Operacion::setResultado(string resultado){
    this->resultado = resultado;
}

float Operacion::getOperador1(){
    return operando1;
}

float Operacion::getOperador2(){
    return operando2;
}

char Operacion::getOperador(){
    return operador;
}

string Operacion::getResultado(){
    return resultado;
}

string Operacion::getOperacion(){
    return to_string(operando1) +" " + operador +" " + to_string(operando2);
}

string Operacion::crearResultado(float operando1, float operando2, char operador){
    float resultado;
    switch(operador){
        case '+': resultado = operando1 + operando2;
                break;
        case '-': resultado = operando1 - operando2;
                break;
        case '*': resultado = operando1 * operando2;
                break;
        case '/': resultado = operando1 / operando2;
                break;
        case '%': resultado = fmod(operando1,operando2);
                break;
    }
    return to_string(resultado);
}

string Operacion::toString(){
    return to_string(operando1) +" " + operador +" " + to_string(operando2) +" = "+ resultado;
}
