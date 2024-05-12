#include <string>
#include "operacion.h"
#ifndef PROCESO_H_INCLUDED
#define PROCESO_H_INCLUDED

class Proceso{
    private:
        std::string nombre;
        Operacion operacion;
        int id;
        int idLote;
        int TME;  //Tiempo total estimado
        int TT;   //Tiempo total
        int TR;   //Tiempo restante
        int TTbloqueado; //Tiempo total en Bloqueados
        int TLL; //Tiempo de llegada
        int TFinalizacion;//
        int TServicio;
        int TEspera;
        int TRetorno;
        int TRespuesta;
        std::string estadoActual;
        int peso;
        int quantumActual;
        bool primera_vez= false;

    public:
        Proceso();
        Proceso(std::string nombre,Operacion, int id, int TME, int TT, int TR);
        //Proceso(std::string nombre,Operacion, int id, int TME, int idLote);
        Proceso(std::string nombre,Operacion, int id, int TME);//Este es el constructor que usualmente usamos
        Proceso(std::string nombre,Operacion, int id, int TME, int peso);//Este es el constructor que usualmente usamos
        Proceso(std::string nombre,Operacion, int id, int TME, std::string estadoActual);//Este es el constructor que usualmente usamos

        void setNombre(std::string);
        void setOperacion(Operacion);
        void setId(int);
        void setTME(int);
        void setTT(int);
        void setTR(int);
        void setTTbloqueado(int);
        void setTLL(int);
        void setTFinalizacion(int);//
        void setTServicio(int);
        void setTEspera(int);
        void setTRetorno(int);
        void setTRespuesta(int);
        void setEstadoActual(std::string);
        void setPeso(int);
        void setQuantumActual(int);
        void setprimeravez(bool);

        std::string getNombre();
        Operacion& getOperacion();
        int getId();
        int getTME();
        int getTT();
        int getTR();
        int getIdLote();
        int getTTbloqueado();
        int getTLL();
        int getTFinalizacion();
        int getTServicio();
        int getTEspera();
        int getTRetorno();
        int getTRespuesta();
        std::string getEstadoActual();
        int getPeso();
        int getQuantumActual();
        bool getprimeravez();

        std::string loteActual();
        std::string terminados();
        std::string ejecucion();
        std::string bloqueado();
        std::string BCP();
        std::string toString();
};


#endif // PROCESO_H_INCLUDED
