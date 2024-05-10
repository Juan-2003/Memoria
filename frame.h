#include <string>
#include "proceso.h"
using namespace std;

#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

class Frame{
    private:
        //Esta variable ayudara a monitorer las posiciones siguietnes donde se puede insertar un nuevo proceso
        static int posicion;
        static int idClase;
        static int const ESPACIO_TOTAL = 5;
        int espacioDisponible;
        std::string estatus;
        bool ocupado;
        int idFrame;
        Proceso* procesoAsignado;//Ayuda a saber que proceso lo esta ocupando

    public:
        Frame();
        //int aumentarValor(int tamano);
        std::string getEstatus();
        int getIdFrame();
        Proceso* getProcesoAsignado();
        int getPosicion();


        bool isOcupado();
        int asignarProceso(Proceso* proceso, int pesoTemporal);
        bool obtenerEspacio();
        void desocuparEspacio();
        void cambiarEstatus(std::string estatusNuevo);


        void insertarProceso();
        std::string toString();

};


#endif // FRAME_H_INCLUDED
