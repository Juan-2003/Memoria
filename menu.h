#include <vector>
#include <string>
#include <set>
#include "proceso.h"
#include "memoria.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu{
    private:
        static char elegirOperador(int opcionOperador);
        static void comandos(Memoria &memoria,std::set<Proceso*>&listaProcesosTotales, std::vector<Proceso*>& listaListos, std::vector<Proceso*>& listaActual, std::vector<Proceso*>& listaEjecucion, std::vector<Proceso*>& listaBloqueados, std::vector<Proceso*>& listaTerminados, char tecla);
        static void mostrarInfo(std::set<Proceso*>& listaProcesosTotales, std::vector<Proceso*>& listaListos, std::vector<Proceso*>& listaActual, std::vector<Proceso*>& listaEjecucion, std::vector<Proceso*>& listaBloqueados, std::vector<Proceso*>& listaTerminados, int quantum);
        static Proceso* crearProceso();
        static void tablaInformacion(std::vector<Proceso>& listaTerminados);
        static void mostrarBCP(std::set<Proceso*>&listaProcesosTotales);
    public:
        static void iniciarMenu();
};

#endif // MENU_H_INCLUDED
