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
                Proceso* proceso_prueba = crearProceso();
                listaListos.push_back(proceso_prueba);
                listaProcesosTotales.insert(proceso_prueba);
            }else{
                Proceso* proceso_nuevo = crearProceso();
                listaNuevos.push_back(proceso_nuevo);
                listaProcesosTotales.insert(proceso_nuevo);
            }
            break;

        case 'b':
            mostrarBCP(listaProcesosTotales);
            do {
                if(_kbhit()) {
                    otraTecla = _getch(); //Se guarda la tecla seleccionada
                }
            } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
            system("cls");
            break;
    }
}

void Menu::mostrarInfo(set<Proceso*>& listaProcesosTotales, vector<Proceso*>& listaNuevos, vector<Proceso*>& listaListos, vector<Proceso*>& listaEjecucion, vector<Proceso*>& listaBloqueados, vector<Proceso*>& listaTerminados, int quantum){
    Memoria memoria = Memoria();
    Operacion operacion = Operacion(0, 0, '+');
    Proceso* procesoSO = new Proceso("SO", operacion, 10000, 0, "SO");//Se crea un objeto tipo 'Proceso'
    memoria.tomarFrames(procesoSO);
    system("cls");
    //ponerle un posible if porque se estan agregando procesos sin que haya espacio
    //listaListos.assign(listaNuevos.begin(), listaNuevos.end());

    //Añadi esto. A ver si esta bien
    //listaProcesosTotales.insert(listaNuevos.begin(), listaNuevos.end());
    if(!listaNuevos.empty()){
        for(int i=0;i<listaNuevos.size();i++){
            listaProcesosTotales.insert(listaNuevos[i]);
        }
    }

    bool static jala = true;
    if(jala){
        int size = listaNuevos.size();
        for(int i = 0; i < size; i++){
            if(memoria.isEspacioSuficiente(listaNuevos[0])){//Proceso: 1
                listaListos.push_back(listaNuevos[0]);//Lista listos = 1
                listaNuevos.erase(listaNuevos.begin());
                memoria.tomarFrames(listaListos[listaListos.size() - 1]); //Espacio = 4
            }
        }
    }
    jala = false;
    
    
    

    //memoria.inicializarMatriz(listaListos);

    while(!memoria.isMemoriaVacia()){
        cout<<"Nuevos: "<<listaNuevos.size()<<endl;
        //Se crean correctamente pero se borran, y no se imprimen nada, posiblemente no esten sirviendo las condiciones de los frames
        cout<<"SIGUIENTE PROCESO POR ENTRAR   ";
        if(listaNuevos.empty()){
            cout<<"ID: --------"<<endl<<endl;
        }else{
            cout<<"ID: "<<listaNuevos[0]->getId()<<" Peso: "<<listaNuevos[0]->getPeso()<<endl<<endl;
        }
        //Para pasar de nuevos a listos si hay espacio en memoria
        if(!listaNuevos.empty()&&memoria.isEspacioSuficiente(listaNuevos[0])){
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
        if(listaEjecucion.empty()){
            listaEjecucion.push_back(listaListos[0]);
            if(!listaEjecucion[0]->getprimeravez()){
                listaEjecucion[0]->setTRespuesta(contadorGlobal+1);
                listaEjecucion[0]->setprimeravez(true);
            }
            listaListos.erase(listaListos.begin());
        }


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

        if(proceso->getQuantumActual() >= quantum){
            proceso->setQuantumActual(0);
        }
        int quantumActual = proceso->getQuantumActual();

        cout<<endl<<"           MEMORIA      "<<endl;
        memoria.mostrarMatriz();
        cout<<endl;
        cout<<"PROCESO EN EJECUCION"<<endl;
        cout<<listaEjecucion[0]->ejecucion()<<endl<<endl;
        char tecla = ',';
        bool terminarBuclePorBloqueado = false;
        bool banderaQuantumActual = true;
        while(quantumActual < quantum){
            TR--;
            TT++;
            quantumActual++;
            contadorGlobal++;
            cout << "\rTME: " << TME << "TT: " << TT << " TR: " << TR << " Quantum: " << quantum  << " Contador Global: " <<contadorGlobal<<flush;
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
                   // memoria.desocuparFrames(proceso);
                    memoria.cambiarEstatusFrame(proceso, "Bloqueado");
                    listaBloqueados[listaBloqueados.size() - 1]->setTR(TR);
                    listaBloqueados[listaBloqueados.size() - 1]->setTT(TT);
                    break;
                }
                else if(tecla == 'w'){
                    memoria.desocuparFrames(proceso);
                    listaTerminados[listaTerminados.size() - 1]->setTFinalizacion(contadorGlobal);
                    listaTerminados[listaTerminados.size() - 1]->setTRetorno(proceso->getTFinalizacion() - proceso->getTLL());
                    break;
                }
                else if(tecla == 'n'){
                    proceso->setTR(TR);
                    proceso->setTT(TT);
                    proceso->setQuantumActual(quantumActual);
                    banderaQuantumActual = false;
                    //Esto es para verificar si me esta creando bien los procesos
                    /*for(auto& proceso : listaListos){
                        cout<<endl<<"ID: "<<proceso->getId();
                    }
                    system("pause");
                    for(auto& proceso : listaNuevos){
                        cout<<endl<<"ID: "<<proceso->getId();
                    }
                    system("pause");*/
                    break;
                }
                else if(tecla == 'b'){
                    memoria.mostrarMatriz();
                }
                else if(tecla == 't'){
                    system("cls");
                    char otraTecla;
                    memoria.mostrarUbicacionProcesos();
                    do {
                        if(_kbhit()) {
                            otraTecla = _getch(); //Se guarda la tecla seleccionada
                        }
                    } while(otraTecla != 'c'); //El programa seguira pausado mientras no se haga click en 'c'
                    system("cls");
                    memoria.mostrarMatriz();
                }
            }

            for(int i = 0; i < listaBloqueados.size(); i++){
                listaBloqueados[i]->setTTbloqueado(listaBloqueados[i]->getTTbloqueado()+1);
                if(listaBloqueados[i]->getTTbloqueado()==8){
                    memoria.cambiarEstatusFrame(listaBloqueados[i], "Ocupado");
                    listaBloqueados[i]->setTTbloqueado(0);
                    listaListos.push_back(listaBloqueados[i]);
                    listaBloqueados.erase(listaBloqueados.begin());
                    terminarBuclePorBloqueado = true;
                    banderaQuantumActual = false;
                    break;
                }
            }
            if(terminarBuclePorBloqueado){
                break;
            }
        }
        /*Esto fue para verificar que los de nuevos se pasan a listos cuando pasa la segunda corrida, no importa si no hay espacio
        system("cls");
        for(auto& proceso : listaNuevos){
            cout<<endl<<"List Nuevos ID: "<<proceso->getId();
        }
        for(auto& proceso : listaListos){
            cout<<endl<<"Lista Listos ID: "<<proceso->getId();
        }
        system("pause");
        */
        //Si esta bandera esta en 'true' significa que se necesita que se reinicie a 0
        if(banderaQuantumActual){
            proceso->setQuantumActual(0);
        }else{
            proceso->setQuantumActual(quantumActual);
        }

        if(TT != TME && tecla != 'w' && tecla != 'e'){
            listaEjecucion[0]->setTEspera(proceso->getTRetorno() - proceso->getTServicio());
            listaEjecucion[0]->setTR(TR);
            listaEjecucion[0]->setTT(TT);

            if(tecla != 'n' && !terminarBuclePorBloqueado){
                listaListos.push_back(listaEjecucion[0]);
                listaEjecucion.pop_back();
            }
        }
        //system("pause");
        system("cls");
    }
    system("cls");
    for(int i = 0; i < listaTerminados.size(); i++){
        listaTerminados[i]->setEstadoActual("Terminados");
    }
    if(listaNuevos.size() == 0 && listaListos.size()==0 && listaBloqueados.size()==0 && listaEjecucion.size()==0){//Cuando la lista actual este vacia, se mostrara la informacion correspondiente
        mostrarBCP(listaProcesosTotales);

    }else{//Mientras que el tama�o de la lista actual sea mayor que 0, la funcion se llamara asi misma para actualizar lo que se ve en pantalla
        mostrarInfo(listaProcesosTotales, listaNuevos, listaListos, listaEjecucion, listaBloqueados, listaTerminados,quantum);
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
    int peso =  6 + rand() % 21;
    Operacion operacion = Operacion(operando1, operando2, operador); //Se crea un objeto tipo 'Operacion'
    Proceso* proceso = new Proceso(nombre, operacion, id, TME, peso);//Se crea un objeto tipo 'Proceso'
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
    system("cls");
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
