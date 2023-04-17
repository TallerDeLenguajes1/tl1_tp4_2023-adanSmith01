#include "listas-tareas.h"


int main() {
    int buscar;
    Nodo* listaTareasP = crearListaTareasVacia();
    Nodo* listaTareasR = crearListaTareasVacia();
    
    cargarListaTareasP(&listaTareasP);
    cargarListaTareasR(&listaTareasR, &listaTareasP);
    mostrarListaTareasR(listaTareasR);
    mostrarListaTareasP(listaTareasP);
    
    printf("\n%cNecesita buscar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
    scanf("%d", &buscar);
    buscarTarea(buscar, listaTareasP, listaTareasR);
    return 0;
}
