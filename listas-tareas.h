#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    int TareaID;
    char* Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo* Siguiente;
}Nodo;


//FUNCIONES

Nodo* crearListaTareasVacia(){
    return NULL;
}

Nodo* crearTareaNodo(Tarea tarea){
    Nodo* nuevaTarea = (Nodo*)malloc(sizeof(Nodo));
    nuevaTarea->T.TareaID = tarea.TareaID;
    nuevaTarea->T.Descripcion = (char*)malloc(strlen(tarea.Descripcion) + 1);
    strcpy(nuevaTarea->T.Descripcion, tarea.Descripcion);
    nuevaTarea->T.Duracion = tarea.Duracion;
    nuevaTarea->Siguiente = NULL;
    return nuevaTarea;
}

void insertarTareaNodo(Nodo** cabListaTareas, Tarea tarea){
    Nodo* nuevaTarea = crearTareaNodo(tarea);
    nuevaTarea->Siguiente = *cabListaTareas;
    *cabListaTareas = nuevaTarea;
}

void eliminarTareaNodo(Nodo** listaTareas, int idTarea){
    Nodo* tareaAnt = *listaTareas;
    Nodo* tareaAux = *listaTareas;

    while(tareaAux && tareaAux->T.TareaID != idTarea){
        tareaAnt = tareaAux;
        tareaAux = tareaAux->Siguiente;
    }

    if(tareaAux == *listaTareas){
        *listaTareas = tareaAux->Siguiente;
    }else{
        tareaAnt->Siguiente = tareaAux->Siguiente;
    }
    free(tareaAux);
}


void cargarListaTareasP(Nodo** cabListaTareasP) {
    int ingresarNueva, i = 0;
    Tarea auxT;
    puts("======BIENVENIDO/A======\n");
    do{
        printf("\nIngrese la tarea %d a realizar\n", i);
        fflush(stdin);
        auxT.TareaID = i;
        printf("Descripcion: ");
        auxT.Descripcion = (char*)malloc(200);
        gets(auxT.Descripcion);
        do{
            printf("Duracion: ");
            scanf("%d", &auxT.Duracion);
            if (auxT.Duracion < 10 || auxT.Duracion > 100) printf("\nLa duracion debe estar entre 10 y 100.\n");
        }while(auxT.Duracion < 10 || auxT.Duracion > 100);
        insertarTareaNodo(cabListaTareasP, auxT);
        free(auxT.Descripcion);
        
        printf("\nDesea ingresar otra tarea? Si(1) / No(0): ");
        scanf("%d", &ingresarNueva);
        if (ingresarNueva) i++;
    }while(ingresarNueva);
}

void cargarListaTareasR(Nodo** cabListaTareasR, Nodo** cabListaTareasP){
    Nodo* tareaAux = *cabListaTareasP;
    int tareaRealizada;
    while(tareaAux){
        printf("\nRealizo la tarea de id %d? Si(1) / No(0): ", tareaAux->T.TareaID);
        scanf("%d", &tareaRealizada);
        if(tareaRealizada){
            insertarTareaNodo(cabListaTareasR, tareaAux->T);
            eliminarTareaNodo(cabListaTareasP, tareaAux->T.TareaID);
        }
        tareaAux = tareaAux->Siguiente;
    }
}

void mostrarListaTareasP(Nodo* listaTareasP){
    Nodo* auxT = listaTareasP;
    puts("\n========LISTADO DE TAREAS PENDIENTES=======\n");
    while(auxT){
        printf("\nID de la tarea: %d\n", auxT->T.TareaID);
        printf("Descripcion: %s\n", auxT->T.Descripcion);
        printf("Duracion: %d\n", auxT->T.Duracion);
        auxT = auxT->Siguiente;
    }
}

void mostrarListaTareasR(Nodo* listaTareasR){
    Nodo* auxT = listaTareasR;
    puts("\n========LISTADO DE TAREAS REALIZADAS=======\n");
    while(auxT){
        printf("\nID de la tarea: %d\n", auxT->T.TareaID);
        printf("Descripcion: %s\n", auxT->T.Descripcion);
        printf("Duracion: %d\n", auxT->T.Duracion);
        auxT = auxT->Siguiente;
    }
}

Nodo* buscarTareaPorID(Nodo* listaTareasP, Nodo* listaTareasR, int idTarea){
    Nodo* auxTareasP = listaTareasP;
    Nodo* auxTareasR = listaTareasR;

    while(auxTareasP || auxTareasR){
        if(auxTareasP){
            if(auxTareasP->T.TareaID == idTarea){
                return auxTareasP;
            }
        }

        if(auxTareasR){
            if(auxTareasR->T.TareaID == idTarea){
                return auxTareasR;
            }
        }
    }
}

void buscarTarea(int seBusca, Nodo* listaTareasP, Nodo* listaTareasR){
    int id;
    Nodo* tareaBuscada;
    char* aux;
    if(seBusca){
        fflush(stdin);
        printf("\n%cDe qu%c manera quiere buscar la tarea? id / palabra clave: ", 168, 130);
        aux = (char *)malloc(18);
        gets(aux);
        fflush(stdin);
        if(strcmp(aux, "id") == 0){
            printf("\nIngrese el id de la tarea a buscar: ");
            scanf("%d", &id);
            tareaBuscada = buscarTareaPorID(listaTareasP, listaTareasR, id);
            puts("\n=======TAREA BUSCADA POR ID======\n");
            printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
            printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
            printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
        }
    }
}