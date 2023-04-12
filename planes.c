#include "planes.h"
#include "validadores.h"

plan escanear_datos_plan(){
    /*
    Función que entrega un plan a partir de los datos escaneados
    */
    plan nuevo_plan;
    char linea[MAX_LEN];

    //Lectura de datos
    printf("Ingrese los siguientes datos solicitados por consola\n\n");
    
    printf("Código de plan: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nuevo_plan.cod_plan = strdup(linea);

    printf("\nDescripción del plan: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nuevo_plan.descripcion_plan = strdup(linea);

    nuevo_plan.n_clientes_plan = 0;

    return nuevo_plan;
}

void agregar_plan(plan *planes, int *num_planes){
    /* 
    * Funcion agrega un plan al arreglo de estructuras de tipo plan.
    Realiza la inserción en la última posición del arreglo de planes (posición *num_planes+1).
    Al agregar un plan, como consecuencia la cantidad de planes incrementa (num_planes).
    * Parametros: 
     - *sedes: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `sede`.
     - *num_planes: puntero a variable de tipo entero que indica el numero de estructuras de sedes en el arreglo
    */
    plan nuevo_plan = escanear_datos_plan();

    // validar si se puede agregar al arreglo de estructuras
    int validador_plan; 
    validador_plan = validar_plan(planes, *num_planes, nuevo_plan.cod_plan, '\0');
    
    if(validador_plan == 0){ // el plan no existe
        // Reasigno espacio memoria para agregar un nuevo plan
        plan *temp = realloc(planes, (*num_planes + 1) * sizeof(sede));
        if (temp == NULL){
            printf("Error de reasignacion de memoria: funcion (agregar_plan)");
            return;
        }
        temp[*num_planes] = nuevo_plan; // insertar el nuevo_plan al final del arreglo

        planes = temp;
        *num_planes += 1;
    } else {
        printf("El plan ya existe\n");
    }
}

void imprimir_planes(plan *planes, int num_planes){
    if (planes != NULL){
        printf("Mostrando planes disponibles: \n\n");
        printf("Número de planes disponibles: %d\n\n", num_planes);
        for (int i = 0; i < num_planes; i++){
            printf("Plan: %d\n", i + 1);
            printf("Código del plan: %s\n", planes[i].cod_plan);
            printf("Descripción del plan: %s\n", planes[i].descripcion_plan);
            printf("Clientes con el plan: %d\n\n", planes[i].n_clientes_plan);
        }
    }
}

void aumentar_clientes_plan(plan *planes, int num_planes, char *cod_plan) {
    for (int i = 0; i < num_planes; i++){
        if(strcmp(cod_plan, planes[i].cod_plan) == 0) {
            planes[i].n_clientes_plan += 1; // aumentar cantidad de personas en plan
            return;
        }
    }
}

void disminuir_clientes_plan(plan *planes, int num_planes, char *cod_plan) {
    for (int i = 0; i < num_planes; i++){
        if(strcmp(cod_plan, planes[i].cod_plan) == 0) {
            planes[i].n_clientes_plan -= 1; // disminuir cantidad de personas en plan
            return;
        }
    }
}

void eliminar_plan(plan *planes, int *num_planes){
    char *cod_plan_eliminar;
    char linea[MAX_LEN];

    printf("Ingrese código de plan a eliminar: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    cod_plan_eliminar = strdup(linea);

    int validador_plan = validar_plan(planes, *num_planes, cod_plan_eliminar, '\0'); //0 si no existe, 1 si ya existe

    if (validador_plan == 0){
        printf("\nValidación CÓDIGO PLAN: plan no registrado\nImposible eliminar\n");
        return; 
    }
    
    printf("\nValidación CÓDIGO PLAN exitosa --> eliminando plan...\n");
    
    char *cod_2;

    int i;
    for (i = 0; i < *num_planes; i++){
        cod_2 = planes[i].cod_plan;
        // Búsqueda de la posicion donde eliminar al plan
        if(strcmp(cod_plan_eliminar, cod_2) == 0){
            break; // el for se rompe cuando encuentro la posicion y obtengo el i (indice del plan a eliminar)
        }
    }
    // Mover una posicion a la izquierda a los planes iban a la derecha del plan i (el que se elimina)
    int j;
    if (planes[i].n_clientes_plan == 0){ // si el plan tiene 0 clientes suscritos se puede borrar
        for (j = i; j < *num_planes; j++){
            planes[j] = planes[j+1];
        } 
        *num_planes -= 1; // la cantidad de personas disminuye una unidad
        // Reasigno espacio memoria luego de eliminar el plan (disminuye de acuerdo al nuevo *num_planes). Si no se elimina el plan, todo queda igual

        plan *temp = realloc(planes, (*num_planes) * sizeof(plan));

        if(temp == NULL){
            printf("Error de reasignación de memoria: función (eliminar_plan)\n");
            return;
        } else{
            planes = temp; //el puntero del arreglo de planes ahora apunta a la direccion de memoria de temp
            printf("\nEliminación exitosa: el plan ya no pertenece a la base de datos\n");
        }

    } else { // si el plan tiene clientes suscritos, entonces no se puede borrar
        printf("El plan tiene clientes suscritos --> no se puede eliminar\n\n");
    }
}
