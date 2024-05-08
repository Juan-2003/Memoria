#include <string>
#include <iostream>
#include "frame.h"
#include "proceso.h"
using namespace std;

int Frame::idClase = 0;
int Frame::posicion = 0;
Frame::Frame(){
    espacioDisponible = 0;
    ocupado = false;
    idFrame = ++idClase;
    estatus = "Liberado";
    procesoAsignado = nullptr;
}


string Frame::getEstatus(){
    return estatus;
}


int Frame::getIdFrame(){
    return idFrame;
}

Proceso* Frame::getProcesoAsignado(){
    return procesoAsignado;
}

int Frame::getPosicion(){
    return posicion;
}

bool Frame::isOcupado(){
    return ocupado;
}

void Frame::cambiarEstatus(string estatusNuevo){
    this->estatus = estatusNuevo;
}

int Frame::asignarProceso(Proceso* proceso, int pesoTemporal){
    procesoAsignado = proceso;
    estatus = "Ocupado";
    ocupado = true;

    //Si el peso del proceso es menor o igual que ESPACIO TOTAL se le asignara su valor a espacio disponible
    if(pesoTemporal <= ESPACIO_TOTAL){
        espacioDisponible = pesoTemporal;
        pesoTemporal = 0;
    }else{//Si es mayor, se asigna al frame automaticamente 5
        espacioDisponible = ESPACIO_TOTAL;
        pesoTemporal -= ESPACIO_TOTAL;//Para despues hacer la resta y saber 'cuanto Peso' queda por asignar
    }
    posicion++;//En cada iteracion se recorre la posicion
    return pesoTemporal;
    
}

void Frame::desocuparEspacio(){
    espacioDisponible = 0;
    estatus = "Liberado";
    ocupado = false;
    procesoAsignado = nullptr;
}

void Frame::insertarProceso(){
    estatus = "Ocupado";
}

bool Frame::obtenerEspacio(){
    
    /*if(espacioDisponible < ESPACIO_TOTAL){
        espacioDisponible++;
    }
    if(espacioDisponible != ESPACIO_TOTAL){
        return false; //Todavia no se llena el frame
    }*/
    //En caso de pasar significa que el frame esta lleno
    //return true;
}

string Frame::toString(){
    return to_string(espacioDisponible) + "/" + to_string(ESPACIO_TOTAL)
            + "  " + estatus + "  " + "Proceso ID: " 
            + (procesoAsignado != nullptr ? to_string(procesoAsignado->getId()): "------");

}