#include "lista-tareas.h"

int main() {
    //Inicialización de las listas de tareas
    Nodo* listaTareasP = crearListaTareasVacia();
    Nodo* listaTareasR = crearListaTareasVacia();
    Nodo* TareasEnProceso = crearListaTareasVacia(); //Inicialización de la lista de tareas en proceso
    puts("======BIENVENIDO/A======\n");

    cargarListaTareasP(&listaTareasP);
    menuPrincipal(&listaTareasP, &listaTareasR, &TareasEnProceso);    

    //Eliminación de todas las listas
    while(listaTareasP || listaTareasR || TareasEnProceso){
        if(listaTareasP){
            free(listaTareasP->T.Descripcion);
            free(listaTareasP);
            listaTareasP = listaTareasP->Siguiente;
        }
        
        if(listaTareasR){
            free(listaTareasR->T.Descripcion);
            free(listaTareasR);
            listaTareasR = listaTareasR->Siguiente;
        }

        if(TareasEnProceso){
            free(TareasEnProceso->T.Descripcion);
            free(TareasEnProceso);
            TareasEnProceso = TareasEnProceso->Siguiente;
        }
    }

    return 0;
}
