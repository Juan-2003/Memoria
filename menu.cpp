#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
#include <set>
#include <algorithm>
#include "proceso.h"
#include "operacion.h"
#include "menu.h"
#include "memoria.h"

using namespace std;


int contadorGlobal = -1;
char Menu::elegirOperador(int opcionOperador){  //Servira para poder elegir el operador segun la opcion del usuario
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



void Menu::comandos(Memoria &memoria,set<Proceso*>&listaProcesosTotales, vector<Proceso*>&listaNuevos, vector<Proceso*>& listaListos, vector<Proceso*>& listaEjecucion, vector<Proceso*>& listaBloqueados, vector<Proceso*>& listaTerminados, char tecla) {
    char otraTecla;
    switch(tecla) {
        case 'w': //Interrupcion
            listaEjecucion[0]->getOperacion().setResultado("ERROR      ");
            listaEjecucion[0]->setEstadoActual("Error T");
            listaTerminados.push_back(listaEjecucion[0]);
            listaEjecucion.pop_back();
            break;
        case 'p': //Pausa
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            break;

        case 'e': //El proceso se va a Bloqueados
            listaBloqueados.insert(listaBloqueados.end(),listaEjecucion[0]);
            listaBloqueados[listaBloqueados.size()-1]->setEstadoActual("Bloqueado"); //Se establece a la ultima posicion del vector el estado actual de 'Bloqueado'
            listaEjecucion.pop_back();
            break;

        case 'n':
             if(!memoria.isMemoriaLLena()){
                listaListos.push_back(crearProceso());
            }else{
                listaNuevos.push_back(crearProceso());
            }
            break;

        case 'b':
            mostrarBCP(listaProcesosTotales);
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            break;
    }
}

/*
system("cls");
    listaListos.assign(listaNuevos.begin(), listaNuevos.end());

    Memoria memoria = Memoria();
    memoria.inicializarMatriz(listaListos);


    memoria.mostrarMatriz();
    system("pause");
    system("cls");

    memoria.desocuparFrames(listaListos[1]);
    memoria.desocuparFrames(listaListos[3]);
    memoria.mostrarMatriz();
    system("pause");
    system("cls");

    Proceso* proceso = crearProceso();
    proceso->setPeso(11);
    memoria.tomarFrames(proceso);
    memoria.mostrarMatriz();
    system("pause");
*/

void Menu::mostrarInfo(set<Proceso*>& listaProcesosTotales, vector<Proceso*>& listaNuevos, vector<Proceso*>& listaListos, vector<Proceso*>& listaEjecucion, vector<Proceso*>& listaBloqueados, vector<Proceso*>& listaTerminados, int quantum){
    system("cls");
    listaListos.assign(listaNuevos.begin(), listaNuevos.end());
    if(!listaNuevos.empty()){
        for(int i=0;i<listaNuevos.size();i++){
            listaProcesosTotales.insert(listaNuevos[i]);
        }
    }
    listaNuevos.clear();


    Memoria memoria = Memoria();
    memoria.inicializarMatriz(listaListos);


    while(!memoria.isMemoriaVacia()){
        int quantumActual = 0;
        //Para pasar de nuevos a listos si hay espacio en memoria
        if(!listaNuevos.empty()){
            for(int i = 0; i < listaNuevos.size(); i++){
                listaListos.push_back(listaNuevos[0]);
                listaNuevos.erase(listaNuevos.begin());
                if(memoria.isEspacioSuficiente(listaNuevos[i])){
                    memoria.tomarFrames(listaNuevos[i]);
                }
            }

        }
        for(auto& proceso: listaListos){
            proceso->setEstadoActual("Listos");
            if(proceso->getTLL()==-1){
                (contadorGlobal == -1)?proceso->setTLL(contadorGlobal+1): proceso->setTLL(contadorGlobal);
            }
        }
        //Se pasa el primer proceso a la lista de ejecucion y
        //se elima de la lista actual
        //Aqui ya empieza EJECUCION
        listaEjecucion.push_back(listaListos[0]);
        listaListos.erase(listaListos.begin());

        //Si un proceso regresa de nuevo a lista, y no esta bloqueado
        // o algo similar, se verificara si ya esta dentro de memoria.
        //Si no lo esta (false), tomara los frames necesarios para entrar
        for(int i = 0; i < listaListos.size(); i++){
            if(memoria.buscarFrame(listaListos[i]) == false){
                memoria.tomarFrames(listaListos[i]);
            }
        }


        //Se almacena el proceso actual y se obtienen los contadores
        Proceso* proceso = listaEjecucion[0];
        int TME = proceso->getTME();
        int TR = proceso->getTR();
        int TT = proceso->getTT();
        proceso->setEstadoActual("Ejecucion");

        cout<<"PROCESO "<<proceso->getId()<<endl;
        memoria.mostrarMatriz();
        char tecla = ',';
        while(quantumActual < quantum){
            TR--;
            TT++;
            quantumActual++;
            contadorGlobal++;
            cout << "\rTME: " << TME << "TT: " << TT << " TR: " << TR << " Quantum: " << quantum << "Quantum Actual: "<< quantumActual << " Contador Global: " <<contadorGlobal<<flush;
            Sleep(1000);


            if(TR == 0){//Si TR es 0 significa que ya cumplio su tiempo
                memoria.desocuparFrames(proceso);
                listaEjecucion[0]->setTFinalizacion(contadorGlobal);
                listaEjecucion[0]->setTRetorno(proceso->getTFinalizacion() - proceso->getTLL());
                listaTerminados.push_back(listaEjecucion[0]);
                listaTerminados[listaTerminados.size()-1]->setEstadoActual("Terminados");
                listaEjecucion.pop_back();
                break;
            }

            //Deteccion de las teclas
            if(_kbhit()){
                tecla = _getch();

                comandos(memoria,listaProcesosTotales, listaNuevos, listaListos,listaEjecucion, listaBloqueados, listaTerminados, tecla);

                if(tecla == 'e'){
                    memoria.desocuparFrames(proceso);
                    listaBloqueados[listaBloqueados.size() - 1]->setTR(TR);
                    listaBloqueados[listaBloqueados.size() - 1]->setTT(TT);
                    break;
                }
                else if(tecla == 'w'){
                    memoria.desocuparFrames(proceso);
                    break;
                }
                else if(tecla == 'n'){
                    proceso->setTR(TR);
                    proceso->setTT(TT);
                    break;
                }

            }
            bool terminarBuclePorBloqueado = false;
            for(int i = 0; i < listaBloqueados.size(); i++){
                listaBloqueados[i]->setTTbloqueado(listaBloqueados[i]->getTTbloqueado()+1);
                if(listaBloqueados[i]->getTTbloqueado()==8){
                    listaBloqueados[i]->setTTbloqueado(0);
                    listaListos.push_back(listaBloqueados[i]);
                    listaBloqueados.erase(listaBloqueados.begin());
                    terminarBuclePorBloqueado = true;
                    break;
                }
            }
            if(terminarBuclePorBloqueado){
                break;
            }
        }
        cout<<"1"<<endl;
        if(TT != TME && tecla != 'w' && tecla != 'e' && tecla != 'n'){
            listaEjecucion[0]->setTEspera(proceso->getTRetorno() - proceso->getTServicio());
            listaEjecucion[0]->setTR(TR);
            listaEjecucion[0]->setTT(TT);
            listaListos.push_back(listaEjecucion[0]);
            listaEjecucion.pop_back();
        }
        cout<<"2"<<endl;
        cout<<"3"<<endl;
        system("pause");
        system("cls");
    }
    system("cls");

    cout<<"TERMINADOS"<<endl;
    cout<<listaTerminados.size()<<endl;
    for(int i = 0; i < listaTerminados.size(); i++){
        listaEjecucion[i]->setEstadoActual("Terminados");
        cout<<listaTerminados[i]->getId()<<"   "<<listaTerminados[i]->getOperacion().getResultado()<<endl;
    }
    if(listaNuevos.size() == 0 && listaListos.size()==0 && listaBloqueados.size()==0 && listaEjecucion.size()==0){//Cuando la lista actual este vacia, se mostrara la informacion correspondiente
        mostrarBCP(listaProcesosTotales);

    }else{//Mientras que el tama�o de la lista actual sea mayor que 0, la funcion se llamara asi misma para actualizar lo que se ve en pantalla
        mostrarInfo(listaProcesosTotales, listaNuevos, listaListos, listaEjecucion, listaBloqueados, listaTerminados,quantum);
    }

}

void Menu::procesoBloqueados(vector<Proceso*>& listaListos, vector<Proceso*>& listaBloqueados){
    /*for_each(listaBloqueados.begin(), listaBloqueados.end(), [&listaListos, &listaBloqueados](Proceso* proceso){
        proceso->setTTbloqueado(proceso->getTTbloqueado() + 1);
        cout<<proceso->getTTbloqueado()<<endl;
        system("pause");
        if(proceso->getTTbloqueado() == 8){
            proceso->setTTbloqueado(0);
            listaListos.push_back(proceso);
            listaBloqueados.erase(listaBloqueados.begin());
        }
    });*/
    for(int i = 0; i < listaBloqueados.size(); i++){
        listaBloqueados[i]->setTTbloqueado(listaBloqueados[i]->getTTbloqueado()+1);
        if(listaBloqueados[i]->getTTbloqueado()==8){
            listaBloqueados[i]->setTTbloqueado(0);
            listaListos.push_back(listaBloqueados[i]);
            listaBloqueados.erase(listaBloqueados.begin());
        }
    }

}

void Menu::mostrarBCP(set<Proceso*>&listaProcesosTotales){
    system("cls");
    cout<<setw(5)<<left<<"ID";
    cout<<setw(10)<<left<<"Estado";
    cout<<setw(20)<<left<<"TTbloqueado";
    cout<<setw(22)<<left<<"Operacion";
    cout<<setw(15)<<left<<"Resultado";
    cout<<setw(10)<<left<<"TLL";
    cout<<setw(15)<<left<<"TFinalizacion";
    cout<<setw(15)<<left<<"TRetorno";
    cout<<setw(15)<<left<<"TME";
    cout<<setw(15)<<left<<"TServicio";
    cout<<setw(15)<<left<<"TRespuesta"<<endl;

    for(auto& objeto : listaProcesosTotales){
        cout<<objeto->BCP()<<endl;
    }
    /*for(int i = 0; i < listaProcesosTotales.size(); i++){
        cout<<listaProcesosTotales[i]->BCP()<<endl;
    }*/

}

Proceso* Menu::crearProceso(){
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
    //int peso = 5;
    Operacion operacion = Operacion(operando1, operando2, operador); //Se crea un objeto tipo 'Operacion'
    Proceso* proceso = new Proceso(nombre, operacion, id, TME);//Se crea un objeto tipo 'Proceso'
    return proceso;
}


void Menu::iniciarMenu(){
    vector<Proceso*> listaListos;
    vector<Proceso*> listaEjecucion;
    vector<Proceso*> listaTerminados;
    vector<Proceso*> listaBloqueados;
    vector<Proceso*>listaNuevos;
    set<Proceso*>listaProcesosTotales;
    int quantum = 0;

    int cantidadProcesos;
    cout<<"BIENVENIDO"<<endl;
    cout<<"Ingresa la cantidad de procesos que quieres realizar: ";
    cin>>cantidadProcesos;
    cout<<"Ingresa el QUANTUM:  ";
    cin>>quantum;
    srand(time(NULL));
            for(int j = 0; j < cantidadProcesos; j++){//Este 'for' controla que por cada Lote haya 4 procesos
                listaNuevos.push_back(crearProceso());
            }
    cin.ignore();
    mostrarInfo(listaProcesosTotales, listaNuevos, listaListos, listaEjecucion, listaBloqueados, listaTerminados, quantum);
}

/*if(listaListos.size() == 0){//Cuando la lista actual este vacia, se mostrara la informacion correspondiente
        mostrarBCP(listaProcesosTotales);

    }else{//Mientras que el tama�o de la lista actual sea mayor que 0, la funcion se llamara asi misma para actualizar lo que se ve en pantalla
        mostrarInfo(listaProcesosTotales,listaNuevos, listaListos, listaEjecucion, listaBloqueados, listaTerminados, quantum);
    }*/
