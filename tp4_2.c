#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructura de tipo Tarea
typedef struct tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
}Tarea;

void cargarTareasPendientes(Tarea** tareasP, int cantTareas);
void cargarTareasRealizadas(Tarea ** tareasR, Tarea ** tareasP, int cantTareas);
void mostrarTareasPendientes(Tarea** tareasP, int cantTareas);
void mostrarTareasRealizadas(Tarea ** tareasR, int cantTareas);
Tarea* buscarTareaV1(Tarea ** tareasR, Tarea** tareasP, int cantTareas, int tareaIDBuscada);
Tarea* buscarTareaV2(Tarea ** tareasR, Tarea** tareasP, int cantTareas, char* palabraClave);

int main(){
    int cantTareas, buscarTarea, id;
    char * aux, *clave;
    Tarea * tareaBuscada;

    //Se pregunta al usuario la cantidad de tareas a realizar
    printf("Determine la cantidad de tareas a realizar: ");
    scanf("%d", &cantTareas);
    Tarea ** tareasPendientes = (Tarea **)malloc(sizeof(Tarea*) * cantTareas);
    Tarea ** tareasRealizadas = (Tarea **)malloc(sizeof(Tarea*) * cantTareas);

    //Inicializando los arreglos
    for(int i = 0; i < cantTareas; i++){
        tareasPendientes[i] = NULL;
        tareasRealizadas[i] = NULL;
    }

    //Funciones para cargar y mostrar las tareas pendientes y las tareas realizadas
    cargarTareasPendientes(tareasPendientes, cantTareas);
    cargarTareasRealizadas(tareasRealizadas, tareasPendientes, cantTareas);
    mostrarTareasPendientes(tareasPendientes, cantTareas);
    mostrarTareasRealizadas(tareasRealizadas, cantTareas);
    
    //Interfaz para realizar la búsqueda de una tarea específica
    printf("\n%cNecesita buscar alguna tarea espec%cfica? S%c(1) / No(0) : ", 168, 161, 161);
    scanf("%d", &buscarTarea);
    if(buscarTarea) {
        fflush(stdin);
        printf("\n%cDe qu%c manera quiere buscar la tarea? id / palabra clave: ", 168, 130);
        aux = (char *)malloc(18);
        gets(aux);
        fflush(stdin);
        if (strcmp(aux, "id") == 0){
            printf("\nIngrese el id de la tarea a buscar: ");
            scanf("%d", &id);
            tareaBuscada = buscarTareaV1(tareasRealizadas, tareasPendientes, cantTareas, id);
            puts("\n=======TAREA BUSCADA POR ID======\n");
            printf("\nID de la tarea: %d\n", tareaBuscada->TareaID);
            printf("Descripci%cn: %s\n", 162, tareaBuscada->Descripcion);
            printf("Duraci%cn: %d\n", 162, tareaBuscada->Duracion);
        } else{
            printf("\nIngrese la palabra clave de la tarea a buscar: ");
            clave = (char *)malloc(20);
            gets(clave);
            tareaBuscada = buscarTareaV2(tareasRealizadas, tareasPendientes, cantTareas, clave);
            puts("\n=======TAREA BUSCADA POR PALABRA CLAVE======\n");
            printf("\nID de la tarea: %d\n", tareaBuscada->TareaID);
            printf("Descripci%cn: %s\n", 162, tareaBuscada->Descripcion);
            printf("Duraci%cn: %d\n", 162, tareaBuscada->Duracion);
            free(clave);
        }
        free(aux);
    }

    //Liberación de memoria
    for(int i = 0; i < cantTareas; i++){
        free(tareasPendientes[i]->Descripcion);
        free(tareasRealizadas[i]->Descripcion);
        free(tareasRealizadas[i]);
        free(tareasPendientes[i]);
    }
    free(tareasPendientes);
    free(tareasRealizadas);

    return 0;
}


//Función para cargar las tareas pendientes
void cargarTareasPendientes(Tarea** tareasP, int cantTareas) {
    char *Buffer;
    for(int i = 0; i < cantTareas; i++){
        fflush(stdin);
        Buffer = (char*)malloc(200);
        printf("\nTarea %d: ", i);
        gets(Buffer);
        tareasP[i] = (Tarea *)malloc(sizeof(Tarea)* 1);
        tareasP[i]->TareaID = i;
        tareasP[i]->Descripcion = (char*)malloc(strlen(Buffer) + 1);
        strcpy(tareasP[i]->Descripcion, Buffer);
        do{
            printf("Duraci%cn: ", 162);
            fflush(stdin);
            scanf("%d", &tareasP[i]->Duracion);
            if (tareasP[i]->Duracion < 10 || tareasP[i]->Duracion > 100) printf("La duracion debe ser un valor entre 10 y 100\n");
        }while(tareasP[i]->Duracion < 10 || tareasP[i]->Duracion > 100);
        free(Buffer);
    }
}

//Función para cargar las tareas realizadas
void cargarTareasRealizadas(Tarea ** tareasR, Tarea ** tareasP, int cantTareas) {
    int tareaRealizada;
    for(int i = 0; i < cantTareas; i++) {
        printf("\n%cRealiz%c la tarea %d? S%c(1) / No(0): ", 168, 162, i, 161);
        scanf("%d", &tareaRealizada);
        if (tareaRealizada) {
            tareasR[i] = tareasP[i];
            tareasP[i] = NULL;
        }
    }
}

//Función para mostrar las tareas pendientes
void mostrarTareasPendientes(Tarea** tareasP, int cantTareas) {
    puts("\n========LISTADO DE TAREAS PENDIENTES=======\n");
    for(int i = 0; i < cantTareas; i++) {
        if(tareasP[i]) {
            printf("\nID de la tarea: %d\n", tareasP[i]->TareaID);
            printf("Descripci%cn : %s\n", 162, tareasP[i]->Descripcion);
            printf("Duraci%cn: %d\n", 162, tareasP[i]->Duracion);
        }
    }
}

//Función para mostrar las tareas realizadas
void mostrarTareasRealizadas(Tarea ** tareasR, int cantTareas){
    puts("\n========LISTADO DE TAREAS REALIZADAS=======\n");
    for(int i = 0; i < cantTareas; i++) {
        if(tareasR[i]) {
            printf("\nID de la tarea: %d\n", tareasR[i]->TareaID);
            printf("Descripci%cn : %s\n", 162, tareasR[i]->Descripcion);
            printf("Duraci%cn: %d\n", 162, tareasR[i]->Duracion);
        }
    }
}

//Función para buscar una tarea a partir de su ID
Tarea* buscarTareaV1(Tarea ** tareasR, Tarea** tareasP, int cantTareas, int tareaIDBuscada){
    for(int i = 0; i < cantTareas; i++){
        if (tareasP[i]){
            if(tareaIDBuscada == tareasP[i]->TareaID){
                return tareasP[i];
            }
        } else {
            if (tareaIDBuscada == tareasR[i]->TareaID){
                return tareasR[i];
            }
        }
    }
}

//Función para buscar una tarea a partir de una palabra clave
Tarea* buscarTareaV2(Tarea ** tareasR, Tarea** tareasP, int cantTareas, char* palabraClave){

    for(int i = 0; i < cantTareas; i++){
        if(tareasP[i]){
            if(strstr(tareasP[i]->Descripcion, palabraClave)){
                return tareasP[i];
            }
        }else {
            if(strstr(tareasR[i]->Descripcion, palabraClave)){
                return tareasR[i];
            }
        }
    }
}