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

//Función para quitar una tarea de una lista
Nodo* quitarTarea(Nodo** listaTareas, Nodo* tareaAQuitar){
    Nodo* tareaAnt = *listaTareas;
    Nodo* tareaAux = *listaTareas;

    while(tareaAux != tareaAQuitar){
        tareaAnt = tareaAux;
        tareaAux = tareaAux->Siguiente;
    }

    if(*listaTareas == tareaAux){
        *listaTareas = tareaAux->Siguiente;
    } else{
        tareaAnt->Siguiente = tareaAux->Siguiente;
    }

    tareaAux->Siguiente = NULL;
    return tareaAux;
}

//Función para eliminar una tarea
void eliminarTarea(Nodo** listaTareas, Nodo* tarea){
    Nodo* tareaAEliminar = quitarTarea(listaTareas, tarea);
    free(tareaAEliminar->T.Descripcion);
    free(tareaAEliminar);
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

//Función para cargar las tareas realizadas a una lista
void moverTarea(Nodo** cabListaTareasR, Nodo** cabListaTareasP, Nodo** cabTareasEnProceso, int idTarea){
    int lista;
    Nodo* nuevaTarea;
    if(buscarTareaPorID(*cabListaTareasP, idTarea)){
        printf("\nA que lista la quieres mover? En Proceso(1) / Realizadas(2): ");
        scanf("%d", &lista);
        nuevaTarea = quitarTarea(cabListaTareasP, buscarTareaPorID(*cabListaTareasP, idTarea));
        if(lista == 1){
            insertarTareaNodo(cabTareasEnProceso, nuevaTarea);
        } else{
            insertarTareaNodo(cabListaTareasR, nuevaTarea);
        }
    } else{
        if(buscarTareaPorID(*cabTareasEnProceso, idTarea)){
            nuevaTarea = quitarTarea(cabTareasEnProceso, buscarTareaPorID(*cabTareasEnProceso, idTarea));
            insertarTareaNodo(cabListaTareasR, nuevaTarea);
        } else{
            if(buscarTareaPorID(*cabListaTareasR, idTarea)) printf("\nLa tarea ha sido realizada.\n");
        }
    }
}

//Función para mostrar la lista de tareas
void mostrarListaTareas(Nodo* listaTareas){
    Nodo* auxT = listaTareas;
    if(auxT == NULL){
        printf("\nNo hay tareas guardadas\n");
    } else{
        while(auxT){
            printf("\nID de la tarea: %d\n", auxT->T.TareaID);
            printf("Descripcion: %s\n", auxT->T.Descripcion);
            printf("Duracion: %d\n", auxT->T.Duracion);
            auxT = auxT->Siguiente;
        }
    }
}

//Función para mostrar la cantidad total de tareas y duración en total de tareas de una lista
void mostrarDatos(Nodo* listaTareas){
    int contTareas = 0, duracionTotal = 0;
    Nodo* auxT = listaTareas;
    if(auxT == NULL){
        printf("\nCantidad total de tareas: %d\n", contTareas);
        printf("\nTiempo total de duracion: %d\n", duracionTotal);
    } else{
        while(auxT){
            contTareas++;
            duracionTotal += auxT->T.Duracion;
            auxT = auxT->Siguiente;
        }

        printf("\nCantidad total de tareas: %d\n", contTareas);
        printf("\nTiempo total de duracion: %d\n", duracionTotal);
    }
}

int estaTareaEnLista(Nodo* listaTareas, int idTarea){
    if(buscarTareaPorID(listaTareas, idTarea)){
        return 1;
    } else{
        return 0;
    }
}

void consultaTareas(Nodo* TareasP, Nodo* TareasR, Nodo* TareasEnProceso){
    int buscar, invalido = 0, idTarea;
    char *clave, *aux, *estado;
    Nodo* tareaBuscada = NULL;
    do{
        fflush(stdin);
        do{
            aux = (char*)malloc(20);
            printf("\n%cDe qu%c manera quiere buscar la tarea? id / palabra clave: ", 168, 130);
            gets(aux);
            
            if(strcmp(aux, "id") == 0){
                invalido = 0;
                printf("\nIngrese el id de la tarea a buscar: ");
                scanf("%d", &idTarea);

                if(buscarTareaPorID(TareasP, idTarea)){
                    tareaBuscada = buscarTareaPorID(TareasP, idTarea);
                    estado = "Pendiente";
                } else{
                    if(buscarTareaPorID(TareasR, idTarea)){
                        tareaBuscada = buscarTareaPorID(TareasR, idTarea);
                        estado = "Realizada";
                    } else{
                        if(buscarTareaPorID(TareasEnProceso, idTarea)){
                            tareaBuscada = buscarTareaPorID(TareasEnProceso, idTarea);
                            estado = "En Proceso";
                        }
                    }
                }

                if(tareaBuscada){
                    puts("\n=======TAREA BUSCADA POR ID======\n");
                    printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                    printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                    printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                    printf("Estado: %s", estado);
                } else{
                    printf("\nNo se encontr%c la tarea con el id = %d \n", 162, idTarea);
                }
            } else{
                if(strcmp(aux, "palabra clave") == 0){
                    invalido = 0;
                    printf("\nIngrese la palabra clave de la tarea a buscar: ");
                    clave = (char *)malloc(20);
                    gets(clave);

                    if(buscarTareaPorPalabra(TareasP, clave)){
                        tareaBuscada = buscarTareaPorPalabra(TareasP, clave);
                        estado = "Pendiente";
                    } else{
                        if(buscarTareaPorPalabra(TareasR, clave)){
                            tareaBuscada = buscarTareaPorPalabra(TareasR, clave);
                            estado = "Realizada";
                        } else{
                            if(buscarTareaPorPalabra(TareasEnProceso, clave)){
                                tareaBuscada = buscarTareaPorPalabra(TareasEnProceso, clave);
                                estado = "En Proceso";
                            }
                        }
                    }

                    if(tareaBuscada){
                        puts("\n=======TAREA BUSCADA POR PALABRA CLAVE======\n");
                        printf("\nID de la tarea: %d\n", tareaBuscada->T.TareaID);
                        printf("Descripci%cn: %s\n", 162, tareaBuscada->T.Descripcion);
                        printf("Duraci%cn: %d\n", 162, tareaBuscada->T.Duracion);
                    } else{
                        printf("\nNo se encontr%c la tarea con el id = %d \n", 162, idTarea);
                    }

                    free(clave);
                } else{
                    invalido = 1;
                }
            }

            free(aux);
        }while(invalido);
        printf("\n%cNecesita buscar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
        scanf("%d", &buscar);
    }while(buscar);
}

void operacionesTarea(Nodo** TareasP, Nodo** TareasR, Nodo** TareasEnProceso){
    int idTarea, modificarOtra, operacion;
    do{
        puts("\n========LISTADO DE TAREAS REALIZADAS=======\n");
        mostrarListaTareas(*TareasR);
        puts("\n========LISTADO DE TAREAS EN PROCESO=======\n");
        mostrarListaTareas(*TareasEnProceso);
        puts("\n========LISTADO DE TAREAS PENDIENTES=======\n");
        mostrarListaTareas(*TareasP);

        do{
            printf("\nQue tarea desea seleccionar? Indique el ID de la tarea: ");
            scanf("%d", &idTarea);
        }while(estaTareaEnLista(*TareasP, idTarea) != 1 && estaTareaEnLista(*TareasR, idTarea) != 1 && estaTareaEnLista(*TareasEnProceso, idTarea) != 1);

        printf("\n*********MENU DE OPERACIONES PARA LA TAREA %d********\n", idTarea);
        puts("1- Mover a otra lista.");
        puts("2- Eliminar tarea.");
        puts("3- No hacer nada\n");
        printf("Elija la operacion: ");
        scanf("%d", &operacion);

        if(operacion == 1) moverTarea(TareasR, TareasP, TareasEnProceso, idTarea);
        if(operacion == 2){
            if(buscarTareaPorID(*TareasP, idTarea)) eliminarTarea(TareasP, buscarTareaPorID(*TareasP, idTarea));
            if(buscarTareaPorID(*TareasR, idTarea)) eliminarTarea(TareasR, buscarTareaPorID(*TareasR, idTarea));
            if(buscarTareaPorID(*TareasEnProceso, idTarea)) eliminarTarea(TareasEnProceso, buscarTareaPorID(*TareasEnProceso, idTarea));
        }

        printf("\n%cNecesita modificar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
        scanf("%d", &modificarOtra);
    }while(modificarOtra);

}

void menuPrincipal(Nodo** TareasP, Nodo** TareasR, Nodo** TareasEnProceso){
    int opcion;
    do{
        puts("\n*********MENU PRINCIPAL********\n");
        puts("1- Consultar una tarea.");
        puts("2- Operar una tarea.");
        puts("3- Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);

        if(opcion == 1) consultaTareas(*TareasP, *TareasR, *TareasEnProceso);
        if(opcion == 2){
            operacionesTarea(TareasP, TareasR, TareasEnProceso);

            puts("\n========LISTADO DE TAREAS REALIZADAS=======\n");
            mostrarListaTareas(*TareasR);
            mostrarDatos(*TareasR);
            puts("\n========LISTADO DE TAREAS EN PROCESO=======\n");
            mostrarListaTareas(*TareasEnProceso);
            mostrarDatos(*TareasEnProceso);
            puts("\n========LISTADO DE TAREAS PENDIENTES=======\n");
            mostrarListaTareas(*TareasP);
            mostrarDatos(*TareasP);
        }

    }while(opcion != 3);

}