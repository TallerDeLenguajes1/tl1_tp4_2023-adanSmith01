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
    eliminarLista(&listaTareasP);
    eliminarLista(&listaTareasR);
    eliminarLista(&TareasEnProceso);
    return 0;
}
