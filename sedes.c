#include "sedes.h"
#include "validadores.h"

void imprimir_sedes(sede *sedes, int num_sedes) {
    if (sedes != NULL){
        printf("Mostrando sedes disponibles: \n\n");
        printf("Número de sedes disponibles: %d\n\n", num_sedes);
        for (int i = 0; i < num_sedes; i++) {
            printf("Sede: %d\n", i + 1);
            printf("Código sede: %s\n", sedes[i].cod_sede);
            printf("Ubicación sede: %s\n", sedes[i].ubicacion_sede);
            printf("Personas en sede: %d\n\n", sedes[i].n_clientes_sede);
        }
    }
}

sede encontrar_sede(sede *sedes, int num_sedes, char *cod_sede) {
    for (int i = 0; i < num_sedes; i++){
        if(strcmp(cod_sede, sedes[i].cod_sede) == 0) {
            return sedes[i]; // retornar la sede correspondiente
        }
    }
}

void aumentar_clientes_sede(sede *sedes, int num_sedes, char *cod_sede) {
    for (int i = 0; i < num_sedes; i++){
        if(strcmp(cod_sede, sedes[i].cod_sede) == 0) {
            sedes[i].n_clientes_sede += 1; // aumentar cantidad de personas en sede
            return;
        }
    }
}

void disminuir_clientes_sede(sede *sedes, int num_sedes, char *cod_sede) {
    for (int i = 0; i < num_sedes; i++){
        if(strcmp(cod_sede, sedes[i].cod_sede) == 0) {
            sedes[i].n_clientes_sede -= 1; // disminuir cantidad de personas en sede
            return;
        }
    }
}

sede escanear_datos_sede(){
    /*
    Función que entrega una sede a partir de los datos escaneados
    */
    sede nueva_sede;
    char linea[MAX_LEN];

    //Lectura de datos
    printf("Ingrese los siguientes datos solicitados por consola\n\n");
    
    printf("Código de sede: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_sede.cod_sede = strdup(linea);

    printf("\nUbicación de sede: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_sede.ubicacion_sede = strdup(linea);

    nueva_sede.n_clientes_sede = 0;

    return nueva_sede;
}

void agregar_sede(sede *sedes, int *num_sedes){
    /* 
    * Funcion agrega una sede al arreglo de estructuras de tipo sede.
    Realiza la inserción en la última posición del arreglo de sedes (posición *num_sedes+1).
    Al agregar una sede, como consecuencia la cantidad de sedes incrementa.
    * Parametros: 
     - *sedes: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `sede`.
     - *num_sedes: puntero a variable de tipo entero que indica el numero de estructuras de sedes en el arreglo
    */
    sede nueva_sede = escanear_datos_sede();
    // validar si se puede agregar al arreglo de estructuras
    int validador_sede; 
    validador_sede = validar_sede(sedes, *num_sedes, nueva_sede.cod_sede, '\0');
    
    if(validador_sede == 0){ // la sede no existe
        // Reasigno espacio memoria para agregar una nueva sede
        sede *temp = realloc(sedes, (*num_sedes + 1) * sizeof(sede));
        if (temp == NULL){
            printf("Error de reasignacion de memoria: funcion (agregar_sede)");
            return;
        }
        temp[*num_sedes] = nueva_sede; // insertar la nueva_sede al final del arreglo

        sedes = temp;
        *num_sedes += 1;
    } else {
        printf("La sede ya existe\n");
    }
}

void eliminar_sede(sede *sedes, int *num_sedes){
    char *cod_sede_eliminar;
    char linea[MAX_LEN];

    printf("Ingrese código de sede a eliminar: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    cod_sede_eliminar = strdup(linea);

    int validador_sede = validar_sede(sedes, *num_sedes, cod_sede_eliminar, '\0'); //0 si no existe, 1 si ya existe

    if (validador_sede == 0){
        printf("\nValidación CÓDIGO SEDE: Sede no registrada\nImposible eliminar\n");
        return; 
    }
    
    printf("\nValidación CÓDIGO SEDE exitosa --> eliminando sede...\n");
    
    char *cod_2;

    int i;
    for (i = 0; i < *num_sedes; i++){
        cod_2 = sedes[i].cod_sede;

        // Búsqueda de la posicion donde eliminar a la sede
        if(strcmp(cod_sede_eliminar, cod_2) == 0){
            break; // el for se rompe cuando encuentro la posicion y obtengo el i (indice de la sede a eliminar)
        }
    }
    
    // Mover una posicion a la izquierda a las sedes que iban a la derecha de la persona i (la que se elimina)
    int j;
    if (sedes[i].n_clientes_sede == 0){ // si la sede tiene 0 clientes se puede borrar
        for (j = i; j < *num_sedes; j++){
            sedes[j] = sedes[j+1];
        } 
        *num_sedes -= 1; // la cantidad de sedes disminuye una unidad
        // Reasigno espacio memoria luego de eliminar a la sede (disminuye de acuerdo al nuevo *num_sedes). Si no se elimina la sede, todo queda igual

        sede *temp = realloc(sedes, (*num_sedes) * sizeof(sede));

        if(temp == NULL){
            printf("Error de reasignación de memoria: funcion (eliminar_persona)\n");
            return;
        } else{
            sedes = temp; //el puntero del arreglo de sedes ahora apunta a la direccion de memoria de temp
            printf("\nEliminacion exitosa: la sede ya no pertenece a la base de datos\n");
        }

    } else { // si la sede tiene clientes en su interior, entonces no se puede borrar
        printf("La sede tiene clientes suscritos --> no se puede eliminar\n\n");
    }
}