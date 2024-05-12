#include <iostream>
#include "menu.h"
#include "memoria.h"
#include "frame.h"

using namespace std;

char elegirOperador(int opcionOperador){  //Servira para poder elegir el operador segun la opcion del usuario
    char operador;
    switch(opcionOperador){
        case 1: operador = '+';
                break;
        case 2: operador = '-';
                break;
        case 3: operador = '*';
                break;
        case 4: operador = '/';
                break;
        case 5: operador = '%';
                break;
        default:
            cout<<"Signo no disponible";
    }
    return operador;
}

Proceso* crearProceso(){
    int opcionOperador,TME;
    static int id = 0;
    float operando1, operando2;
    string nombre;
    char operador;

    id++;//Se va sumando el id
    opcionOperador = 1+rand()%(6-1);//Operador random
    operador = elegirOperador(opcionOperador);//Se manda a llamar la funcion 'elegirOperador'
    operando1 = 1+rand()%(1001-1);//operador 1
    operando2 = 1+rand()%(1001-1); //operador 2
    TME = 5+rand()%(19-5); //TME
    int peso =  6 + rand() % 21;
    //int peso = 5;
    Operacion operacion = Operacion(operando1, operando2, operador); //Se crea un objeto tipo 'Operacion'
    Proceso* proceso = new Proceso(nombre, operacion, id, TME, peso);//Se crea un objeto tipo 'Proceso'
    return proceso;
}

int main(){
    Menu::iniciarMenu();
    /*Memoria memoria = Memoria();
    Proceso* proceso;
    for(int i = 0; i < 10; i++){
        proceso = crearProceso();
        cout<<"Peso: "<<proceso->getPeso()<<endl;
        memoria.tomarFrames(proceso);
    }*/
    /*
    memoria.mostrarMatriz();
    cout<<endl<<endl;
*/
   
    
    

    /*
    memoria.buscarFrame(proceso);
    system("cls");
    Proceso* proceso2 = crearProceso();

    memoria.tomarFrames(proceso2);

    memoria.cambiarEstatusFrame(proceso, "Bloqueado");
    memoria.mostrarMatriz();
    cout<<endl<<endl;
    memoria.desocuparFrames(proceso2);
    memoria.mostrarMatriz();*/
    return 0;
}
