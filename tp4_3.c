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
void insertarTareaNodo(Nodo** cabListaTareas, Nodo* tarea);
void cargarListaTareasP(Nodo** cabListaTareasP);
void cargarListaTareasR(Nodo** cabListaTareasR, Nodo** cabListaTareasP);
void mostrarListaTareas(Nodo* listaTareas);
Nodo* buscarTareaPorID(Nodo* listaTareas, int idTarea);
Nodo* buscarTareaPorPalabra(Nodo* listaTareas, char* palabraClave);

int main() {
    int buscar, idTarea;
    char* aux, *clave;
    //Inicialización de las listas de tareas
    Nodo* listaTareasP = crearListaTareasVacia();
    Nodo* listaTareasR = crearListaTareasVacia();
    puts("======BIENVENIDO/A======\n");

    cargarListaTareasP(&listaTareasP);
    cargarListaTareasR(&listaTareasR, &listaTareasP);
    if(listaTareasR){
        puts("\n========LISTADO DE TAREAS REALIZADAS=======\n");
        mostrarListaTareas(listaTareasR);
    } else{
        printf("\nNo hay tareas realizadas\n");
    }

    if(listaTareasP){
        puts("\n========LISTADO DE TAREAS PENDIENTES=======\n");
        mostrarListaTareas(listaTareasP);
    } else{
        printf("\nNo hay tareas pendientes\n");
    }
    
    //Interfaz de consulta de tareas
    do{
        printf("\n%cNecesita buscar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
        scanf("%d", &buscar);
        if(buscar){
            fflush(stdin);
            int invalido = 0;
            Nodo* tareaBuscada = NULL;
            do{
                aux = (char*)malloc(20);
                printf("\n%cDe qu%c manera quiere buscar la tarea? id / palabra clave: ", 168, 130);
                gets(aux);
                if (strcmp(aux, "id") == 0){
                    invalido = 0;
                    printf("\nIngrese el id de la tarea a buscar: ");
                    scanf("%d", &idTarea);
                
                    if (buscarTareaPorID(listaTareasP, idTarea)){
                        tareaBuscada = buscarTareaPorID(listaTareasP, idTarea);
                    } else{
                        if(buscarTareaPorID(listaTareasR, idTarea)){
                            tareaBuscada = buscarTareaPorID(listaTareasR, idTarea);
                        }
                    }

                    if(tareaBuscada){
                        puts("\n=======TAREA BUSCADA POR ID======\n");
                        printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                        printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                        printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                    } else{
                        printf("\nNo se encontr%c la tarea con el id = %d \n", 162, idTarea);
                    }
            
                } else{
                    if(strcmp(aux, "palabra clave") == 0) {
                        invalido = 0;
                        printf("\nIngrese la palabra clave de la tarea a buscar: ");
                        clave = (char *)malloc(20);
                        gets(clave);
                        if (buscarTareaPorPalabra(listaTareasP, clave)){
                            tareaBuscada = buscarTareaPorPalabra(listaTareasP, clave);
                        } else{
                            if(buscarTareaPorPalabra(listaTareasR, clave)){
                                tareaBuscada = buscarTareaPorPalabra(listaTareasR, clave);
                            }
                        }

                        if(tareaBuscada){
                            puts("\n=======TAREA BUSCADA POR PALABRA CLAVE======\n");
                            printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                            printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                            printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                        } else{
                            printf("\nNo se encontr%c la tarea por la palabra clave \'%s\' \n", 162, clave);
                        }

                        free(clave);
                    } else{
                        invalido = 1;
                    }
            
                }
                free(aux);

            }while(invalido);
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
void insertarTareaNodo(Nodo** cabListaTareas, Nodo* nuevaTarea){
    nuevaTarea->Siguiente = *cabListaTareas;
    *cabListaTareas = nuevaTarea;
}

//Función para cargar las tareas pendientes a una lista
void cargarListaTareasP(Nodo** cabListaTareasP) {
    int ingresarNueva, i = 0;
    Tarea nuevaTarea;
    
    do{
        printf("\nTAREA %d a realizar: ", i);
        fflush(stdin);
        nuevaTarea.TareaID = i;
        nuevaTarea.Descripcion = (char*)malloc(200);
        gets(nuevaTarea.Descripcion);
        do{
            printf("Duraci%cn: ", 162);
            scanf("%d", &nuevaTarea.Duracion);
            if (nuevaTarea.Duracion < 10 || nuevaTarea.Duracion > 100) printf("La duracion debe ser un valor entre 10 y 100\n");
        }while(nuevaTarea.Duracion < 10 || nuevaTarea.Duracion > 100);
        Nodo* nuevoNodo = crearTareaNodo(nuevaTarea);
        insertarTareaNodo(cabListaTareasP, nuevoNodo);
        printf("\n%cDesea ingresar otra tarea? S%c(1) / No(0): ", 168, 161);
        scanf("%d", &ingresarNueva);
        if (ingresarNueva) i++;
    }while(ingresarNueva);
}

//Función para cargar las tareas realizadas a una lista
void cargarListaTareasR(Nodo** cabListaTareasR, Nodo** cabListaTareasP){
    Nodo* tareaAnt = *cabListaTareasP;
    Nodo* tareaAux = *cabListaTareasP;
    int tareaRealizada;
    while(tareaAux){
        printf("\n%cRealiz%c la tarea %d? S%c(1) / No(0): ", 168, 162, tareaAux->T.TareaID, 161);
        scanf("%d", &tareaRealizada);
        if (tareaRealizada){
            if(*cabListaTareasP == tareaAux){
                *cabListaTareasP = tareaAux->Siguiente;
                tareaAnt = tareaAux->Siguiente;
                insertarTareaNodo(cabListaTareasR, tareaAux);
                tareaAux = tareaAnt;
            } else{
                tareaAnt->Siguiente = tareaAux->Siguiente;
                insertarTareaNodo(cabListaTareasR, tareaAux);
                tareaAux = tareaAnt->Siguiente;
            }
        } else{
            tareaAnt = tareaAux;
            tareaAux = tareaAux->Siguiente;
        }
    }
}

//Función para mostrar la lista de tareas pendientes
void mostrarListaTareas(Nodo* listaTareas){
    Nodo* auxT = listaTareas;
    while(auxT){
        printf("\nID de la tarea: %d\n", auxT->T.TareaID);
        printf("Descripcion: %s\n", auxT->T.Descripcion);
        printf("Duracion: %d\n", auxT->T.Duracion);
        auxT = auxT->Siguiente;
    }
}

//Función para buscar una tarea entre las listas de tareas pendientes y realizadas según su ID
Nodo* buscarTareaPorID(Nodo* listaTareas, int idTarea){
    Nodo* auxTareas = listaTareas;

    while(auxTareas && auxTareas->T.TareaID != idTarea){
        auxTareas = auxTareas->Siguiente;
    }

    return auxTareas;
}

//Función para buscar una tarea entre las listas de tareas pendientes y realizadas según una palabra clave
Nodo* buscarTareaPorPalabra(Nodo* listaTareas, char* palabraClave){
    Nodo* auxTareas = listaTareas;
    
    while(auxTareas && strstr(auxTareas->T.Descripcion, palabraClave) == NULL){
        auxTareas = auxTareas->Siguiente;
    }

    return auxTareas;

}