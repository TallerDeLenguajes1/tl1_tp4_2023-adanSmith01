#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructura de tipo Tarea
typedef struct{
    int TareaID;
    char* Descripcion;
    int Duracion;
}Tarea;

//Estructura para las listas de tareas
typedef struct Nodo{
    Tarea T;
    struct Nodo* Siguiente;
}Nodo;

Nodo* crearListaTareasVacia();
Nodo* crearTareaNodo(Tarea tarea);
void insertarTareaNodo(Nodo** cabListaTareas, Tarea tarea);
void eliminarTareaNodo(Nodo** listaTareas, int idTarea);
void cargarListaTareasP(Nodo** cabListaTareasP);
void cargarListaTareasR(Nodo** cabListaTareasR, Nodo** cabListaTareasP);
void mostrarListaTareasP(Nodo* listaTareasP);
void mostrarListaTareasR(Nodo* listaTareasR);
Nodo* buscarTareaPorID(Nodo* listaTareasP, Nodo* listaTareasR, int idTarea);
Nodo* buscarTareaPorPalabra(Nodo* listaTareasP, Nodo* listaTareasR, char* palabraClave);

int main() {
    int buscar, idTarea;
    char* aux, *clave;
    Nodo* tareaBuscada;
    Nodo* listaTareasP = crearListaTareasVacia();
    Nodo* listaTareasR = crearListaTareasVacia();
    puts("======BIENVENIDO/A======\n");

    cargarListaTareasP(&listaTareasP);
    cargarListaTareasR(&listaTareasR, &listaTareasP);
    mostrarListaTareasR(listaTareasR);
    mostrarListaTareasP(listaTareasP);
    
    do{
        printf("\n%cNecesita buscar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
        scanf("%d", &buscar);
        if(buscar){
            fflush(stdin);
            printf("\n%cDe qu%c manera quiere buscar la tarea? id / palabra clave: ", 168, 130);
            aux = (char *)malloc(18);
            gets(aux);
            fflush(stdin);
            if (strcmp(aux, "id") == 0){
                printf("\nIngrese el id de la tarea a buscar: ");
                scanf("%d", &idTarea);
                tareaBuscada = buscarTareaPorID(listaTareasP, listaTareasR, idTarea);
                if(tareaBuscada){
                    puts("\n=======TAREA BUSCADA POR ID======\n");
                    printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                    printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                    printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                } else{
                    printf("\nNo se encontr%c la tarea con el id = %d \n", 162, idTarea);
                }
            
            } else{
                printf("\nIngrese la palabra clave de la tarea a buscar: ");
                clave = (char *)malloc(20);
                gets(clave);
                tareaBuscada = buscarTareaPorPalabra(listaTareasP, listaTareasR, clave);
                if(tareaBuscada){
                    puts("\n=======TAREA BUSCADA POR PALABRA CLAVE======\n");
                    printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                    printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                    printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                } else{
                    printf("\nNo se encontr%c la tarea por la palabra clave \'%s\' \n", 162, clave);
                }
                free(clave);
            }
            free(aux);
        }
    }while(buscar);
    

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


// FUNCIONES

//Función para crear una lista de tareas vacía
Nodo* crearListaTareasVacia(){
    return NULL;
}

//Función para crear una tarea
Nodo* crearTareaNodo(Tarea tarea){
    Nodo* nuevaTarea = (Nodo*)malloc(sizeof(Nodo));
    nuevaTarea->T.TareaID = tarea.TareaID;
    nuevaTarea->T.Descripcion = (char*)malloc(strlen(tarea.Descripcion) + 1);
    strcpy(nuevaTarea->T.Descripcion, tarea.Descripcion);
    nuevaTarea->T.Duracion = tarea.Duracion;
    nuevaTarea->Siguiente = NULL;
    return nuevaTarea;
}

//Función para insertar la tarea creada a una lista de tareas
void insertarTareaNodo(Nodo** cabListaTareas, Tarea tarea){
    Nodo* nuevaTarea = crearTareaNodo(tarea);
    nuevaTarea->Siguiente = *cabListaTareas;
    *cabListaTareas = nuevaTarea;
}

//Función para eliminar una tarea de la lista
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

//Función para cargar las tareas pendientes a una lista
void cargarListaTareasP(Nodo** cabListaTareasP) {
    int ingresarNueva, i = 0;
    Tarea auxT;
    
    do{
        printf("\nTAREA %d a realizar: ", i);
        fflush(stdin);
        auxT.TareaID = i;
        auxT.Descripcion = (char*)malloc(200);
        gets(auxT.Descripcion);
        do{
            printf("Duraci%cn: ", 162);
            scanf("%d", &auxT.Duracion);
            if (auxT.Duracion < 10 || auxT.Duracion > 100) printf("La duracion debe ser un valor entre 10 y 100\n");
        }while(auxT.Duracion < 10 || auxT.Duracion > 100);
        insertarTareaNodo(cabListaTareasP, auxT);
        free(auxT.Descripcion);
        
        printf("\n%cDesea ingresar otra tarea? S%c(1) / No(0): ", 168, 161);
        scanf("%d", &ingresarNueva);
        if (ingresarNueva) i++;
    }while(ingresarNueva);
}

//Función para cargar las tareas realizadas a una lista
void cargarListaTareasR(Nodo** cabListaTareasR, Nodo** cabListaTareasP){
    Nodo* tareaAux = *cabListaTareasP;
    int tareaRealizada;
    while(tareaAux){
        printf("\n%cRealiz%c la tarea %d? S%c(1) / No(0): ", 168, 162, tareaAux->T.TareaID, 161);
        scanf("%d", &tareaRealizada);
        if(tareaRealizada){
            insertarTareaNodo(cabListaTareasR, tareaAux->T);
            eliminarTareaNodo(cabListaTareasP, tareaAux->T.TareaID);
        }
        tareaAux = tareaAux->Siguiente;
    }
}

//Función para mostrar la lista de tareas pendientes
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

//Función para mostrar la lista de tareas realizadas
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

//Función para buscar una tarea entre las listas de tareas pendientes y realizadas según su ID
Nodo* buscarTareaPorID(Nodo* listaTareasP, Nodo* listaTareasR, int idTarea){
    Nodo* auxTareasP = listaTareasP;
    Nodo* auxTareasR = listaTareasR;

    while(auxTareasP || auxTareasR){
        if(auxTareasP){
            if(auxTareasP->T.TareaID == idTarea){
                return auxTareasP;
            } else{
                auxTareasP = auxTareasP->Siguiente;
            }
        }

        if(auxTareasR){
            if(auxTareasR->T.TareaID == idTarea){
                return auxTareasR;
            } else{
                auxTareasR = auxTareasR->Siguiente;
            }
        }
        
    }

    if (auxTareasP == NULL & auxTareasR == NULL){
        return NULL;
    }
}

//Función para buscar una tarea entre las listas de tareas pendientes y realizadas según una palabra clave
Nodo* buscarTareaPorPalabra(Nodo* listaTareasP, Nodo* listaTareasR, char* palabraClave){
    Nodo* auxTareasP = listaTareasP;
    Nodo* auxTareasR = listaTareasR;
    
    while(auxTareasP || auxTareasR){
        if(auxTareasP){
            if(strstr(auxTareasP->T.Descripcion, palabraClave)){
                return auxTareasP;
            } else{
                auxTareasP = auxTareasP->Siguiente;
            }
        }

        if(auxTareasR){
            if(strstr(auxTareasR->T.Descripcion, palabraClave)){
                return auxTareasR;
            } else{
                auxTareasR = auxTareasR->Siguiente;
            }
        }
        
    }

    if(auxTareasR == NULL && auxTareasR == NULL){
        return NULL;
    }

}