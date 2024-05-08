#include <iostream>
#include <string>

#ifndef OPERACION_H_INCLUDED
#define OPERACION_H_INCLUDED

class Operacion{
    private:
        float operando1;
        float operando2;
        char operador;
        std::string resultado;
    public:
        Operacion();
        Operacion(float, float, char);

        void setOperando1(float);
        void setOperando2(float);
        void setOperador(char);
        void setResultado(std::string);

        float getOperador1();
        float getOperador2();
        char getOperador();
        std::string getResultado();
        std::string getOperacion();

        std::string crearResultado(float, float, char);
        std::string toString();
};


#endif
