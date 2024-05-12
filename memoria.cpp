#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include "memoria.h"
#include "frame.h"
#include "proceso.h"

using namespace std;

int Memoria::posicion = 0;
Memoria::Memoria(){

}

/*void Memoria::agregarElemento(int posicion, int tamano){
    while(tamano != 0){
        if(!(frames[posicion].isOcupado())){//Se verifica si el frame no esta ocupado
            tamano = frames[posicion].aumentarValor(tamano);
        }
        else if(tamano != 0 || frames[posicion].isOcupado()){
            posicion++;
        }
    }
}*/

void Memoria::inicializarMatriz(vector<Proceso*>listaListos){
    /*Operacion operacion = Operacion(0, 0, '+');
    Proceso* proceso = new Proceso("SO", operacion, 10000, 0, "SO");//Se crea un objeto tipo 'Proceso'
    tomarFrames(proceso);*/


    for(int i = 0; i < listaListos.size(); i++){//Controla que proceso le toca de la lista de Listos
        int cantidadFramesAocupar = ceil(listaListos[i]->getPeso() / 5.0);//Se redondea hacia arriba para saber la cantidad de frames a ocupar
        int pesoTemporal = listaListos[i]->getPeso();//Se guarda el peso del proceso actual
        for(int j = 0; j < cantidadFramesAocupar; j++){//Se ecarga de iterar la cantidad de veces de frames
            int posicion = frames[0].getPosicion();//Se obtiene la posicon estatica de la clase Frames 
            if(!(frames[posicion].isOcupado())){
                int n = frames[posicion].asignarProceso(listaListos[i], pesoTemporal);
                ubicacionProceso[listaListos[i]].push_back(&frames[posicion]);
                if(n != 0){//Si entra a esta condicion, significa que aun falta peso por asignar
                    pesoTemporal = n;
                }
            }

        }
    }
}

void Memoria::tomarFrames(Proceso* proceso){
    
    int cantidadFramesAocupar = ceil(proceso->getPeso() / 5.0);//Se redondea hacia arriba para saber la cantidad de frames a ocupar
    int pesoTemporal = proceso->getPeso();//Se guarda el peso del proceso actual
    for(int j = 0; j < cantidadFramesAocupar; j++){//Se ecarga de iterar la cantidad de veces de frames
        for(int i = 0; i < 46; i++){
            int posicion = frames[0].getPosicion();//Se obtiene la posicon estatica de la clase Frames}
            if(!(frames[i].isOcupado()) && pesoTemporal != 0){
                pesoTemporal = frames[i].asignarProceso(proceso, pesoTemporal);
                ubicacionProceso[proceso].push_back(&frames[i]);
                
                if(pesoTemporal == 0){//Si se cumple esta condicion significa que ya se asigno todo el peso
                    break;
                }
            }
        }

    }

}

void Memoria::desocuparFrames(Proceso* proceso){
    /*for(int i = 0; i < frames.size(); i++){
        if(frames[i].getProcesoAsignado() != nullptr && frames[i].getProcesoAsignado()->getId() == proceso->getId()){
            frames[i].desocuparEspacio();
        }
    }*/
    auto iterador = ubicacionProceso.find(proceso);
    if(iterador != ubicacionProceso.end()){
        vector<Frame*>&listaFrames = iterador->second;
        for_each(listaFrames.begin(), listaFrames.end(), [](Frame* frame){
            frame->desocuparEspacio();
        });
        iterador->second.clear();
    }
}

void Memoria::cambiarEstatusFrame(Proceso* proceso, string estatusNuevo){
    /*for(int i = 0; i < frames.size(); i++){
        if(frames[i].getProcesoAsignado() == proceso){
            frames[i].cambiarEstatus(estatusNuevo);
        }
    }*/

    auto iterador = ubicacionProceso.find(proceso);
    if(iterador != ubicacionProceso.end()){
        vector<Frame*>& listaFrames = iterador->second;
        for_each(listaFrames.begin(), listaFrames.end(), [estatusNuevo](Frame* frame){
            frame->cambiarEstatus(estatusNuevo);
        });
    }
}

 bool Memoria::buscarFrame(Proceso* proceso){
    /*for(int i = 0; i < frames.size(); i++){
        if(frames[i].getProcesoAsignado() == proceso){
            return true;
        }
    }
    return false;
    */
    auto iterador = ubicacionProceso.find(proceso);
    if(iterador != ubicacionProceso.end() && !(iterador->second.empty())){
        return true;
    }
    return false;

 }

bool Memoria::isEspacioSuficiente(Proceso* proceso){
    int cantidadFramesAocupar = ceil(proceso->getPeso() / 5.0);//Se redondea hacia arriba para saber la cantidad de frames a ocupar
    int cantidad = 0;
    for(int i = 0; i < frames.size(); i++){
        if(!(frames[i].isOcupado())){
            cantidad++;
            if(cantidad == cantidadFramesAocupar){
                return true;
            }
        }
    }
    return false;
}

bool Memoria::isEspacioSuficiente(){
    for(int i = 0; i < frames.size(); i++){
        if(!frames[i].isOcupado()){
            return true;
        }
    }
    return false;
}

bool Memoria::isMemoriaLLena(){
    int totalFrames = frames.size();
    int framesOcupados = 0;

    for(int i = 0; i < frames.size(); i++){
        if(frames[i].isOcupado()){
            framesOcupados++;
            if(framesOcupados == totalFrames){
                return true;
            }
        }
    }

    return false;
}

bool Memoria::isMemoriaVacia(){
    int totalFrames = frames.size();
    int framesNoOcupados = 0;
    //vector<Proceso*>posicionesOcupadas;

    for(int i = 0; i < frames.size(); i++){
        /*if(!frames[i].isOcupado()){
            framesNoOcupados++;
            if(framesNoOcupados == totalFrames){

                return true;
            }
        }*/
        //posicionesOcupadas.push_back(frames[i].getProcesoAsignado());
    }
    int contador = 0;
    for(Frame frame : frames){
        if(frame.isOcupado()){
            contador++;
        }
    }
    
    return (contador == 5)? true : false;
}

void Memoria::mostrarUbicacionProcesos(){
    cout<<" Pagina    Marco"<<endl;
    for(auto i : ubicacionProceso){
        Proceso* proceso = i.first;

        for(Frame* frame : i.second){
            cout<<"   "<<proceso->getId()<<"        "<<frame->getIdFrame()<<endl;
        }
    }

}



void Memoria::mostrarMatriz(){
    for(Frame f : frames){
        cout<<f.toString()<<endl;
    }
}
