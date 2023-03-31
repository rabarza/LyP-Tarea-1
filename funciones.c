#include "funciones.h"
#include "validadores.h"


persona *leer_archivo(char *nombre_archivo, int *num_personas) {
    FILE *fp = fopen(nombre_archivo, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }
    //Inicializo la estructura a un puntero NULL para luego hacer realloc de memoria
    persona *personas = NULL; //equivalente a persona *personas;
    char linea[MAX_LEN];

    int n = 0;
    // Nota: fgets agrega un salto de linea \n al final de lo leído

    fgets(linea, MAX_LEN, fp); // Leer la primera línea, que tiene los nombres de las columnas

    while (fgets(linea, MAX_LEN, fp)) { // Leer el resto de las líneas

        // 1- Asignar memoria para una nueva persona
        persona *temp = realloc(personas, (n + 1) * sizeof(persona)); // temp apuntará al nuevo bloque de memoria que contiene el arreglo de estructuras persona con n+1 elementos.
        if (temp == NULL) {
            printf("Error al asignar memoria.\n");
            fclose(fp);
            return NULL;
        }
        personas = temp; //2
        // personas = realloc(personas, (n + 1) * sizeof(persona)); //las lineas 1 y 2 son equivalentes a esta linea, pero es una mala practica


        char *rut_str;
        char *nombre_str;
        char *edad_str;
        char *cod_plan_str;
        char *descripcion_plan_str;
        char *desde_str;
        char *hasta_str;
        char *cod_sede_str;
        char *ubicacion_sede_str;

        // Eliminar el carácter de nueva línea al final del búfer que agrega fgets al leer una linea
        linea[strcspn(linea, "\n")] = '\0';

        // Dividir la línea en campos
        char *start = linea; //puntero que apunta al 1er indice de la linea
        char *end;

        // Separar los campos en la línea por posición de las comas
        int campo = 1; //se comienza con la primera columna

        while ((end = strchr(start, ',')) != NULL) { // Eliminar el carácter de coma. strchr entrega la posicion donde se encuentra el parametro, en este caso ',' y lo asigno al puntero end
        //el final de la palabra se encuentra en la coma
            
            *end = '\0'; // reemplazo el valor apuntado donde iba la coma por un '\0' (caracter nulo en C, fin cadena caracteres)

            // Asignar el valor del campo correspondiente en la estructura persona
            switch (campo) {
                case 1:
                    rut_str = start;
                    break;
                case 2:
                    nombre_str = start;
                    break;
                case 3:
                    edad_str = start;
                    break;
                case 4:
                    cod_plan_str = start;
                    break;
                case 5:
                    descripcion_plan_str = start;
                    break;
                case 6:
                    desde_str = start;
                    break;
                case 7:
                    hasta_str = start;
                    break;
                case 8:
                    cod_sede_str = start;

                    // Ultima columna
                    start = end + 1;
                    ubicacion_sede_str = start;
                    break;
                case 9: // Este caso nunca ocurre, pero lo dejo para que se entienda
                    ubicacion_sede_str = start;
                    break;
            }

            // Mover el puntero de inicio al siguiente campo
            start = end + 1; //ahora start comienza en la siguiente columna
            // Incrementar el contador de campos
            campo++;
        }

        int validador_rut, validador_fechas; 

        validador_rut = validar_rut(temp, n, rut_str);
        validador_fechas = validar_orden_fechas(desde_str, hasta_str);

        if (validador_fechas == 0){
            // intercambiar fechas
            // printf("Intercambiar fechas");
			// printf("fecha_antes: %s, fecha_despues %s", desde_str, hasta_str);
            intercambiar_fechas(&desde_str, &hasta_str);
			// printf("fecha_antes: %s, fecha_despues %s", desde_str, hasta_str);
					
					
        } else if (validador_fechas == 2 || validador_fechas == 3){
            // Realizar correccion en formato de fechas
			// printf("\n\nfecha_antes: %s, fecha_despues %s\n", desde_str, hasta_str);
            reformatear_fechas(&desde_str, &hasta_str);
			// printf("\n\nfecha_antes: %s, fecha_despues %s\n", desde_str, hasta_str);
					
        }
		if (validador_rut == 1 && validador_fechas != -1){ // se cumple la validacion requerida
            // Guardar los datos en la nueva persona (no modificable)
        	persona p = {
            	.rut = (rut_str != NULL && strlen(rut_str) != 0) ? strdup(rut_str) : "0000000-0",
            	.nombre_completo = (nombre_str != NULL && strlen(nombre_str) != 0) ? strdup(nombre_str) : "SinNombre SinApellido",
            	.edad = (edad_str != NULL && strlen(edad_str) != 0) ? atoi(edad_str) : 0,
            	.cod_plan = (cod_plan_str != NULL && strlen(cod_plan_str) != 0) ? strdup(cod_plan_str) : NULL,
            	.descripcion_plan = (descripcion_plan_str != NULL && strlen(descripcion_plan_str) != 0) ? strdup(descripcion_plan_str) : NULL,
            	.desde = (desde_str != NULL && strlen(desde_str) != 0) ? strdup(desde_str) : NULL,
            	.hasta = (hasta_str != NULL && strlen(hasta_str) != 0) ? strdup(hasta_str) : NULL,
            	.cod_sede = (cod_sede_str != NULL && strlen(cod_sede_str) != 0) ? strdup(cod_sede_str) : NULL,
            	.ubicacion_sede = (ubicacion_sede_str != NULL && strlen(ubicacion_sede_str) != 0) ? strdup(ubicacion_sede_str) : NULL,
        	};
        	personas[n++] = p;
            
		}
    }
    fclose(fp);

    *num_personas = n;
    return personas;
}


persona escanear_datos(){ 
    persona nueva_persona;
    char linea[MAX_LEN];

    //Lectura de datos
    printf("Ingrese los siguientes datos solicitados por consola\n\n");
    
    printf("RUT (sin puntos y con guión): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.rut = strdup(linea);

    printf("\nNombre completo (Nombre Apellido): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.nombre_completo = strdup(linea);

    printf("Edad (años): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.edad = atoi(linea);

    printf("Codigo del plan: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.cod_plan = strdup(linea);
    
    printf("Descripcion del plan: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.descripcion_plan = strdup(linea);

    printf("Fecha de inicio (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.desde = strdup(linea);
    
    printf("Fecha de termino (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.hasta = strdup(linea);
    
    printf("Codigo de sede: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.cod_sede = strdup(linea);
    
    printf("Ubicacion de sede: ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.ubicacion_sede = strdup(linea);

   return nueva_persona;
}

void agregar_persona(persona *personas, int *num_personas){
    /* 
    * Funcion agrega personas al arreglo de estructuras de tipo persona.
    Realiza la asignacion en una ubicacion tal que el arreglo se mantiene ordenado alfabeticamente segun el apellido.
    Al agregar una persona, como consecuencia la cantidad de personas incrementa.
    * Parametros: 
     - *personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - *num_personas: puntero a variable de tipo entero que indica el numero de estructuras de personas en el arreglo
    */
    int i;
    // Reasigno espacio memoria para agregar una nueva persona
    persona *temp = realloc(personas, (*num_personas + 1) * sizeof(persona));
    if (temp == NULL){
        printf("Error de reasignacion de memoria: funcion (agregar_persona)");
        return;
    }
    //Lectura de datos
    char *rut_str;
    char *nombre_str;
    char *edad_str;
    char *cod_plan_str;
    char *descripcion_plan_str;
    char *desde_str;
    char *hasta_str;
    char *cod_sede_str;
    char *ubicacion_sede_str;

    persona nueva_persona = escanear_datos();

    // validar si se puede agregar al arreglo de estructuras
    int validador_rut, validador_fechas; 
    validador_rut = validar_rut(temp, *num_personas, nueva_persona.rut);
							
    validador_fechas = validar_orden_fechas(nueva_persona.desde, nueva_persona.hasta);

    if (validador_fechas == 0){
        // intercambiar fechas
        intercambiar_fechas(&(nueva_persona.desde), &(nueva_persona.hasta));
    }

    if(validador_rut == 1 && validador_fechas != -1){
        char *apellido_1, *apellido_2;

        for (i = 0; i < *num_personas; i++){
            apellido_1 = strrchr(nueva_persona.nombre_completo, ' ') + 1; // Obtener posicion 1era letra del apellido de la persona j.  Retorna un puntero al primer carácter encontrado en la cadena o un puntero nulo si el carácter no se encuentra.
            apellido_2 = strrchr(temp[i].nombre_completo, ' ') + 1; // Obtener puntero a la 1era letra del apellido de la persona j+1

            // Búsqueda de la posicion donde agregar a la persona
            if(strcmp(apellido_1, apellido_2) < 0){
                break; // el for se rompe cuando encuentro la posicion y obtengo el i
            }
        }
        // Mover a las personas a la derecha a las personas que deben ir a la derecha de la persona i
        for (int j = *num_personas; j > i; j--){
            temp[j] = temp[j-1];
        }

        personas = temp;
        personas[i] = nueva_persona; // insertar la nueva persona en el arreglo en la posicion i
        *num_personas += 1;
    }
    
}

void eliminar_persona(persona *personas, int *num_personas){
    
    char *rut_eliminar;
    char linea[MAX_LEN];

    printf("Ingrese RUT (sin puntos y con guion): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';

    rut_eliminar = strdup(linea);

    bool validador_rut = validar_rut(personas, *num_personas, rut_eliminar); //true si no existe, false si ya existe

    if (validador_rut == true){
        printf("\nValidacion RUT: Usuario no registrado\nImposible eliminar\n");
        return; 
    }
    
    printf("\nValidacion RUT exitosa --> eliminando usuario...\n");
    
    char *rut_1,*rut_2;

    rut_1 = strdup(rut_eliminar); // Obtener posicion 1era letra del apellido de la persona j. Retorna un puntero al primer carácter encontrado en la cadena o un puntero nulo si el carácter no se encuentra.
    int i;
    for (i = 0; i < *num_personas; i++){
        rut_2 = personas[i].rut; // Obtener puntero a la 1era letra del apellido de la persona j+1

        // Búsqueda de la posicion donde agregar a la persona
        if(strcmp(rut_1, rut_2) == 0){
            break; // el for se rompe cuando encuentro la posicion y obtengo el i (indice de la persona a eliminar)
        }
    }
    
    // Mover una posicion a la izquierda a las personas iban a la derecha de la persona i (la que se elimina)
    int j;
    for (j = i; j < *num_personas; j++){
        personas[j] = personas[j+1];
    } 

    *num_personas -=1; // la cantidad de personas disminuye una unidad
    
    // Reasigno espacio memoria luego de eliminar a la persona (disminuye de acuerdo al nuevo *num_personas)
    persona *temp = realloc(personas, (*num_personas) * sizeof(persona));

    if(temp == NULL){
        printf("Error de reasignación de memoria: funcion (eliminar_persona)\n");
        return;
    }else{
        personas = temp; //el puntero del arreglo de personas ahora apunta a la direccion de memoria de temp
        printf("\nEliminacion exitosa: el usuario ya no pertenece a la base de datos\n");
    }
}

void bubble_sort_por_apellido(persona *personas, int num_personas) {
    /* 
    * Funcion ordena el arreglo de estructuras segun el apellido de cada estructura.
    * Parametros: 
     - *personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - *num_personas: puntero a variable de tipo entero que indica el numero de estructuras de personas en el arreglo. 
    */

    int i, j;
    persona temp;
    char *apellido_i, *apellido_j;

    for (i = 0; i < num_personas - 1; i++) {
        for (j = 0; j < num_personas - i - 1; j++) {
            // encontrar posiciones apellido de cada persona
            apellido_i = strrchr(personas[j].nombre_completo, ' ') + 1; // Obtener posicion 1era letra del apellido de la persona j. Retorna un puntero al primer carácter encontrado en la cadena o un puntero nulo si el carácter no se encuentra.
            apellido_j = strrchr(personas[j+1].nombre_completo, ' ') + 1; // Obtener puntero a la 1era letra del apellido de la persona j+1
            if (strcmp(apellido_i, apellido_j) > 0) { // Comparar los apellidos segun su valor ASCII. El menor va antes A-Z.
                temp = personas[j];
                personas[j] = personas[j+1];
                personas[j+1] = temp;
            }
        }
    }
}

void imprimir_personas(persona *personas, int num_personas) {
    if (personas != NULL) {
        for (int i = 0; i < num_personas; i++) {
            printf("RUT: %s\n", personas[i].rut);
            printf("Nombre completo: %s\n", personas[i].nombre_completo);
            printf("Edad: %d\n", personas[i].edad);
            printf("Codigo de plan: %s\n", personas[i].cod_plan);
            printf("Descripcion de plan: %s\n", personas[i].descripcion_plan);
            printf("Desde: %s\n", personas[i].desde);
            printf("Hasta: %s\n", personas[i].hasta);
            printf("Codigo de sede: %s\n", personas[i].cod_sede);
            printf("Ubicacion de sede: %s\n\n", personas[i].ubicacion_sede);
        }
    }
}

void buscar_persona(persona *personas, int num_personas){
    /* 
    * Funcion que imprime en pantalla todos los datos de una persona que coincida con el RUT.
    * Parametros: 
     - *personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - *num_personas: puntero a variable de tipo entero que indica el numero de estructuras de personas en el arreglo. 
    */
    char linea[MAX_LEN];
    char *rut;
   
    printf("Ingrese RUT (sin puntos y con guion): ");
    fgets(linea, MAX_LEN, stdin); //fgets agrega un salto de linea luego de captar una linea 
    linea[strcspn(linea, "\n")] = '\0'; //ese salto de linea se reemplaza por el caracter nulo
    rut = strdup(linea);
    printf("\nBuscando a la persona con RUT: %s...\n", rut);

    for (int i = 0; i < num_personas; i++){
        if (strcmp(personas[i].rut, rut) == 0){ //0 cuando son iguales
            // Creo lista de estructuras de tamaño 1 para poder pasarlo como argumento a la funcion que recibe como parametros una lista de estructuras
            persona lista[1];
            lista[0] = personas[i]; // asigno al unico elemento de esta lista la estructura deseada

            // Imprimir resultados
            printf("Usuario localizado en la base de datos\n\n"); // imprimir mensaje de localizado
            imprimir_personas(lista,1); // imprimir datos del usuario

            return;
        }
    }
    printf("El usuario no se encuentra en la base de datos\n");
}
