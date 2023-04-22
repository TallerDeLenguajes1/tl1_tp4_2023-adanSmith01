#include "lista-tareas.h"

int main() {
    //Inicialización de las listas de tareas
    Nodo* listaTareasP = crearListaTareasVacia();
    Nodo* listaTareasR = crearListaTareasVacia();
    Nodo* TareasEnProceso = crearListaTareasVacia(); //Inicialización de la lista de tareas en proceso
    puts("======BIENVENIDO/A======\n");

    cargarListaTareasP(&listaTareasP);
    menuPrincipal(&listaTareasP, &listaTareasR, &TareasEnProceso);    

    //Eliminación todas las tareas de las listas de tareas pendientes y realizadas
    while(listaTareasP || listaTareasR){
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
    }

    return 0;
}
