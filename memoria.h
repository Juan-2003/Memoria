#include "frame.h"
#include "proceso.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED

class Memoria{

    private:
        static int posicion;
        static const int ESPACIO = 10;
        std::vector<Frame>frames = std::vector<Frame>(ESPACIO);
        std::map<Proceso*, std::vector<Frame*>> ubicacionProceso;
    public:
        Memoria();
        //svoid agregarElemento(int posicion, int tamano);//Le debe de llegar como parametro el tama�o del proceso
        void inicializarMatriz(std::vector<Proceso*>listaListos);
        //bool iniciarEjecucion(std::vector<Proceso*>listaListos, int posicion);
        //void obtenerFrame(Proceso* proceso);
        void tomarFrames(Proceso* proceso);
        void desocuparFrames(Proceso* proceso);
        void cambiarEstatusFrame(Proceso* proceso, string estatusNuevo);
        bool buscarFrame(Proceso* proceso);
        void mostrarMatriz();
        bool isEspacioSuficiente(Proceso* proceso);
        bool isEspacioSuficiente();
        bool isMemoriaVacia();
        bool isMemoriaLLena();
        void mostrarUbicacionProcesos();



};

#endif // MEMORIA_H_INCLUDED
