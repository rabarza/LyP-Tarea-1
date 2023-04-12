#include "funciones.h"
#include "validadores.h"

persona *leer_archivo(char *nombre_archivo, int *num_personas,int *num_planes, int *num_sedes, plan **planes, sede **sedes) {
    FILE *fp = fopen(nombre_archivo, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }
    //Inicializo la estructura a un puntero NULL para luego hacer realloc de memoria
    persona *personas = NULL; //equivalente a persona *personas;
    *sedes = NULL; // para poder hacer realloc al menos tiene que ser NULL
    *planes = NULL;

    char linea[MAX_LEN];

    int n = 0; // numero temporal de personas
    int s = 0; // numero temporal de sedes
    int p = 0; // numero temporal de planes
    // printf("\nEntrar a leer archivo\n");
    
    
    fgets(linea, MAX_LEN, fp); // Leer la primera línea, que tiene los nombres de las columnas 
    while (fgets(linea, MAX_LEN, fp)) { // Leer el resto de las líneas. Nota: fgets agrega un salto de linea '\n' al final de lo leído

        // Asignar memoria para una nueva persona, nueva sede y nuevo plan
        persona *temp = realloc(personas, (n + 1) * sizeof(persona)); // temp apuntará al nuevo bloque de memoria que contiene el arreglo de estructuras de tipo persona con (n+1) elementos.
        sede *temp_s = realloc(*sedes, (s + 1) * sizeof(sede)); // temp_s apuntará al nuevo bloque de memoria que contiene el arreglo de estructuras sede con (s + 1) elementos.
        plan *temp_p = realloc(*planes, (p + 1) * sizeof(plan)); // temp_p apuntará al nuevo bloque de memoria que contiene el arreglo de estructuras de tipo plan con (p + 1) elementos (planes).

        if (temp == NULL || temp_s == NULL || temp_p == NULL) {
            printf("Error al asignar memoria.\n");
            fclose(fp);
            return NULL;
        }
        personas = temp; //2
        // personas = realloc(personas, (n + 1) * sizeof(persona)); //las lineas 1 y 2 son equivalentes a esta linea, pero es una mala practica
        *sedes = temp_s;
        *planes = temp_p;

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
        
        int validador_rut, validador_fechas, validador_sedes, validador_plan; 

        validador_rut = validar_rut(temp, n, rut_str);
        validador_fechas = validar_orden_fechas(desde_str, hasta_str);
        validador_sedes = validar_sede(temp_s, s, cod_sede_str, ubicacion_sede_str); // validar si se debe agregar la sede o aumentar la cantidad de personas en esta
        validador_plan = validar_plan(temp_p, p, cod_plan_str, descripcion_plan_str); // validar si se debe agregar el plan o aumentar la cantidad de personas suscritas en el

        if (validador_fechas == 0){ // si las fechas estan al reves
            intercambiar_fechas(&desde_str, &hasta_str); // intercambiar fechas					
        } else if (validador_fechas == 2 || validador_fechas == 3){ // si falta una de las fechas
            reformatear_fechas(&desde_str, &hasta_str);
        }

        //validar si se puede agregar la persona al arreglo
		if (validador_rut == 1 && validador_fechas != -1 && validador_sedes != -1 && validador_plan != -1){
            // Guardar los datos en la nueva persona (no modificable)
        	persona p_temp = {
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
        	personas[n++] = p_temp;
        
            if (validador_sedes == 0){ // agregar sede
                sede sede_temp = {
                    .cod_sede = strdup(cod_sede_str),
                    .ubicacion_sede = strdup(ubicacion_sede_str),
                    .n_clientes_sede = 1
                };

                temp_s[s++] = sede_temp;

            } else if (validador_sedes == 1) { // sede existente agregar cliente
                aumentar_clientes_sede(temp_s, s, cod_sede_str); // aumentar cantidad de clientes en la sede
            }

            if (validador_plan == 0){ //agregar plan
                plan plan_temp = {
                    .cod_plan = strdup(cod_plan_str),
                    .descripcion_plan = strdup(descripcion_plan_str),
                    .n_clientes_plan = 1
                };

                temp_p[p++] = plan_temp;
            } else if (validador_plan == 1) { //plan existente agregar cliente
                aumentar_clientes_plan(temp_p, p, cod_plan_str); // aumentar cantidad de clientes en el plan
            }
		}
    }
    fclose(fp);

    *num_personas = n;
    *num_sedes = s;
    *num_planes = p;
    return personas;
}


persona escanear_datos(sede* sedes, int num_sedes, plan *planes, int num_planes){ 
    persona nueva_persona;
    char linea[MAX_LEN];
    int plan_selector, sede_selector;

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

    printf("Seleccionar plan: \n");
    printf("1. Seleccionar plan existente: \n");
    printf("2. Seleccionar plan nuevo: \n");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    plan_selector = atoi(linea);

    while(plan_selector != 0){
        switch (plan_selector){
            case 1: // plan existente
                int idx_plan_elect;
                
                // Mostrar planes y leer opción ingresada
                imprimir_planes(planes, num_planes);

                while ( idx_plan_elect > num_planes || idx_plan_elect <= 0 ) {
                    printf("Ingresar número del plan a elegir: ");
                    fgets(linea, MAX_LEN, stdin);
                    linea[strcspn(linea, "\n")] = '\0';
                    idx_plan_elect= atoi(linea);

                    if (idx_plan_elect > num_planes || idx_plan_elect <= 0){ //sede no se encuentra en los datos
                        printf("\nValidación CÓDIGO PLAN: Plan no registrado\nIngrese número válido\n");
                    } else {
                        printf("\nValidación CÓDIGO PLAN exitosa. Agregando suscripción del cliente... \n");
                    }
                }

                nueva_persona.cod_plan = planes[idx_plan_elect - 1].cod_plan;
                nueva_persona.descripcion_plan = planes[idx_plan_elect - 1].descripcion_plan;
                plan_selector = 0;
                break;
            case 2: // nuevo plan
                // leer datos
                plan nuevo_plan = escanear_datos_plan();
                nueva_persona.cod_plan = nuevo_plan.cod_plan;
                nueva_persona.descripcion_plan = nuevo_plan.descripcion_plan;
                nuevo_plan.n_clientes_plan = 1;
                plan_selector = 0;
                break;
            default:
                break;
        }
    }

    printf("Fecha de inicio (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.desde = strdup(linea);
    
    printf("Fecha de termino (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    nueva_persona.hasta = strdup(linea);
    
    printf("Seleccionar sede: \n");
    printf("1. Seleccionar sede existente: \n");
    printf("2. Seleccionar nueva sede: \n");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    sede_selector = atoi(linea);

    while(sede_selector != 0){
        switch (sede_selector){
            case 1: // plan existente
                int idx_sede_elect = 0;
                // Mostrar planes y leer opción ingresada
                imprimir_sedes(sedes, num_sedes);

                while ( idx_sede_elect > num_sedes || idx_sede_elect <= 0 ) {
                    printf("Ingresar número de la nueva sede a elegir: ");
                    fgets(linea, MAX_LEN, stdin);
                    linea[strcspn(linea, "\n")] = '\0';
                    idx_sede_elect = atoi(linea);

                    if (idx_sede_elect > num_sedes || idx_sede_elect <= 0){ //sede no se encuentra en los datos
                        printf("\nValidación CÓDIGO SEDE: Sede no registrada\nIngrese número válido\n");
                    } else {
                        printf("\nValidación CÓDIGO SEDE exitosa. Agregando cliente en sede... \n");
                    }
                }
                nueva_persona.cod_sede = sedes[idx_sede_elect - 1].cod_sede;
                nueva_persona.ubicacion_sede = sedes[idx_sede_elect - 1].ubicacion_sede;
                sede_selector = 0;

                break;
            case 2: // nuevo plan
                // leer datos
                sede nueva_sede = escanear_datos_sede();
                nueva_persona.cod_sede = nueva_sede.cod_sede;
                nueva_persona.ubicacion_sede = nueva_sede.ubicacion_sede;
                nueva_sede.n_clientes_sede = 1;
                sede_selector = 0;
                break;
            default:
                break;
        }
    }

   return nueva_persona;
}

void agregar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes){
    /* 
    * Funcion agrega personas al arreglo de estructuras de tipo persona.
    Realiza la asignacion en una ubicacion tal que el arreglo se mantiene ordenado alfabeticamente segun el apellido.
    Al agregar una persona, como consecuencia la cantidad de personas incrementa.
    * Parametros: 
     - *personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - *num_personas: puntero a variable de tipo entero que indica el numero de estructuras de personas en el arreglo
    */
    int i;

    persona nueva_persona = escanear_datos(sedes, *num_sedes,  planes, *num_planes);

    // validar si se puede agregar al arreglo de estructuras
    int validador_rut, validador_fechas, validador_sede, validador_plan; 
    validador_rut = validar_rut(personas, *num_personas, nueva_persona.rut);
    validador_fechas = validar_orden_fechas(nueva_persona.desde, nueva_persona.hasta);
    validador_sede = validar_sede(sedes, *num_sedes, nueva_persona.cod_sede, nueva_persona.ubicacion_sede); // validar si se debe agregar la sede o aumentar la cantidad de personas en esta
    validador_plan = validar_plan(planes, *num_planes, nueva_persona.cod_plan, nueva_persona.descripcion_plan); // validar si se debe agregar el plan o aumentar la cantidad de personas suscritas en el

    // CORREGIR ORDEN Y FORMATOS DE FECHA
    if (validador_fechas == 0) {
        intercambiar_fechas(&(nueva_persona.desde), &(nueva_persona.hasta)); // intercambiar fechas
    } else if (validador_fechas == 2 || validador_fechas == 3) { // falta una de las fechas -> AGREGAR LA FECHA FALTANTE +- 3 MESES
        reformatear_fechas(&(nueva_persona.desde), &(nueva_persona.hasta));
    }

    if (validador_rut == 1 && validador_fechas != -1 && validador_sede != -1 && validador_plan != -1) {
        // Reasigno espacio memoria para agregar una nueva persona
        persona *temp = realloc(personas, (*num_personas + 1) * sizeof(persona));
        if (temp == NULL) {
            printf("Error de reasignacion de memoria: funcion (agregar_persona)");
            return;
        }

        char *apellido_1, *apellido_2;

        for (i = 0; i < *num_personas; i++) {
            apellido_1 = strrchr(nueva_persona.nombre_completo, ' ') + 1; // Obtener posicion 1era letra del apellido de la persona j.  Retorna un puntero al primer carácter encontrado en la cadena o un puntero nulo si el carácter no se encuentra.
            apellido_2 = strrchr(temp[i].nombre_completo, ' ') + 1; // Obtener puntero a la 1era letra del apellido de la persona j+1

            // Búsqueda de la posicion donde agregar a la persona
            if (strcmp(apellido_1, apellido_2) < 0) {
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
        
        if (validador_sede == 0) { // agregar sede
            sede *temp_s = realloc(sedes, (*num_sedes + 1) * sizeof(sede)); // temp_s apuntará al nuevo bloque de memoria que contiene el arreglo de estructuras sede con (s + 1) elementos.
            
            // en mostrar clientes debo preguntar si agregar en sede existente o en nueva sede
            sede sede_temp = {
                .cod_sede = strdup(nueva_persona.cod_sede),
                .ubicacion_sede = strdup(nueva_persona.ubicacion_sede),
                .n_clientes_sede = 1
            };
            sedes = temp_s;
            sedes[*num_sedes] = sede_temp;
            *num_sedes += 1;

        } else if (validador_sede == 1) { // sede existente agregar cliente
            aumentar_clientes_sede(sedes, *num_sedes, nueva_persona.cod_sede); // aumentar cantidad de clientes en la sede
        }

        if (validador_plan == 0) { //agregar plan
            plan *temp_p = realloc(planes, (*num_planes + 1) * sizeof(plan));
            plan plan_temp = {
                .cod_plan = strdup(nueva_persona.cod_plan),
                .descripcion_plan = strdup(nueva_persona.descripcion_plan),
                .n_clientes_plan = 1
            };

            planes = temp_p;
            planes[*num_planes] = plan_temp;
            *num_planes += 1;
                // p += 1;
        } else if (validador_plan == 1) { // plan existente agregar cliente
            aumentar_clientes_plan(planes, *num_planes, nueva_persona.cod_plan); // aumentar cantidad de clientes en el plan
        }
    } else if (validador_rut == -1) {
        printf("RUT INVÁLIDO\n");
    } else if (validador_plan == -1) {
        printf("CÓDIGO DE PLAN INVÁLIDO\n");
    } else if (validador_sede == -1) {
        printf("CÓDIGO DE SEDE INVÁLIDO\n");
    } else {
        printf("FORMATO DE FECHAS INVÁLIDO\n");
    }
}

void eliminar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes){
    
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

        // Búsqueda de la posicion donde eliminar a la persona
        if(strcmp(rut_1, rut_2) == 0){
            disminuir_clientes_sede(sedes, *num_sedes, personas[i].cod_sede); // quitar a la persona de la sede
            disminuir_clientes_plan(planes, *num_planes, personas[i].cod_plan); // quitar a la persona del plan
            break; // el for se rompe cuando encuentro la posicion y obtengo el i (indice de la persona a eliminar)
        }
    }

    
    // Mover una posicion a la izquierda a las personas iban a la derecha de la persona i (la que se elimina)
    int j;
    for (j = i; j < *num_personas; j++){
        personas[j] = personas[j+1];
    } 

    *num_personas -= 1; // la cantidad de personas disminuye una unidad
    
    // Reasigno espacio memoria luego de eliminar a la persona (disminuye de acuerdo al nuevo *num_personas)
    persona *temp = realloc(personas, (*num_personas) * sizeof(persona));

    if(temp == NULL){
        printf("Error de reasignación de memoria: funcion (eliminar_persona)\n");
        return;
    } else{
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

void datos_faltantes_personas(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes) {
    for (int i = 0; i < *num_personas; i++) {
        if (personas[i].descripcion_plan == NULL){ // si faltan datos descripcion plan
            plan plan_buscado = encontrar_plan(planes, *num_planes, personas[i].cod_plan);
            personas[i].descripcion_plan = strdup(plan_buscado.descripcion_plan);
        }
        if (personas[i].ubicacion_sede == NULL){ // si faltan datos ubicacion sede
            sede sede_buscada = encontrar_sede(sedes, *num_sedes, personas[i].cod_sede);
            personas[i].ubicacion_sede = strdup(sede_buscada.ubicacion_sede);
        }
    }
}

void cambiar_sede_persona(persona *personas, sede *sedes, int num_personas, int num_sedes){
    char *rut;
    char *cod_sede;
    char *ubicacion_sede;

    char linea[MAX_LEN];    
    printf("Ingrese RUT (sin puntos y con guión): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0'; 
    rut = strdup(linea);    
    
    int validador_rut = validar_rut(personas, num_personas, rut); 
    if (validador_rut == 1){
      printf("\nValidacion RUT: Usuario no registrado\nImposible cambiar sede\n");
      return;
    }    
    printf("\nBuscando a la persona con RUT: %s ...\n", rut);    
    int i;
    for (i = 0; i < num_personas; i++){
        if (strcmp(personas[i].rut, rut) == 0){
            persona lista[1];
            lista[0] = personas[i];
            printf(">>> Usuario localizado en la base de datos\n\n");
            break;
        }  
    }   
    // printf("Ingrese el codigo de la nueva sede para este usuario: ");   
    // fgets(linea, MAX_LEN, stdin);
    // linea[strcspn(linea, "\n")] = '\0';
    // cod_sede = strdup(linea); 
    int idx_sede_elect = 0;
    // Mostrar planes y leer opción ingresada
    imprimir_sedes(sedes, num_sedes);
    while ( idx_sede_elect > num_sedes || idx_sede_elect <= 0 ) {
        printf("Ingresar número de la nueva sede a elegir: ");
        fgets(linea, MAX_LEN, stdin);
        linea[strcspn(linea, "\n")] = '\0';
        idx_sede_elect = atoi(linea);
        
        if (idx_sede_elect > num_sedes || idx_sede_elect <= 0){ //sede no se encuentra en los datos
            printf("\nValidación CÓDIGO SEDE: Sede no registrada\nIngrese número válido\n");
        } else {
            printf("\nValidación CÓDIGO SEDE exitosa --> cambiando sede...\n");
        }
    }

    disminuir_clientes_sede(sedes, num_sedes, personas[i].cod_sede);

    personas[i].cod_sede = sedes[idx_sede_elect - 1].cod_sede;
    personas[i].ubicacion_sede = sedes[idx_sede_elect - 1].cod_sede;
    
    aumentar_clientes_sede(sedes, num_sedes, personas[i].cod_sede);
    
    printf(">>> La sede del cliente fue cambiada con éxito.\n\n");
}

void cambiar_plan_persona(persona *personas, plan *planes, int num_personas, int num_planes){
    char *rut;
    char *cod_plan;
    char *descripcion_plan;

    char linea[MAX_LEN];    
    printf("Ingrese RUT (sin puntos y con guión): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0'; 
    rut = strdup(linea);    
    
    int validador_rut = validar_rut(personas, num_personas, rut); 
    if (validador_rut == 1){
      printf("\nValidacion RUT: Usuario no registrado\nImposible cambiar plan\n");
      return;
    }    
    printf("\nBuscando a la persona con RUT: %s ...\n", rut);    
    int i;
    for (i = 0; i < num_personas; i++){
        if (strcmp(personas[i].rut, rut) == 0){
            persona lista[1];
            lista[0] = personas[i];
            printf(">>> Usuario localizado en la base de datos\n\n");
            break;
        }  
    }   
    int idx_plan_elect = 0;
    // Mostrar planes y leer opción ingresada
    imprimir_planes(planes, num_planes);
    while ( idx_plan_elect > num_planes || idx_plan_elect <= 0 ) {
        printf("Ingresar número del nuevo plan a elegir: ");
        fgets(linea, MAX_LEN, stdin);
        linea[strcspn(linea, "\n")] = '\0';
        idx_plan_elect = atoi(linea);
        
        if (idx_plan_elect > num_planes || idx_plan_elect <= 0){ //sede no se encuentra en los datos
            printf("\nValidación CÓDIGO PLAN: Plan no registrado\nIngrese número válido\n");
        } else {
            printf("\nValidación CÓDIGO PLAN exitosa --> cambiando suscripción...\n");
        }
    }

    disminuir_clientes_plan(planes, num_planes, personas[i].cod_plan);

    personas[i].cod_plan = planes[idx_plan_elect - 1].cod_plan;
    personas[i].descripcion_plan = planes[idx_plan_elect - 1].descripcion_plan;
    
    aumentar_clientes_plan(planes, num_planes, personas[i].cod_plan);

    printf("Ingrese nuevas fechas de inicio y término de la suscripción\n");
    printf("Fecha de inicio (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    personas[i].desde = strdup(linea);
    
    printf("Fecha de termino (AAAA/MM/DD): ");
    fgets(linea, MAX_LEN, stdin);
    linea[strcspn(linea, "\n")] = '\0';
    personas[i].hasta = strdup(linea);
    

    int validador_fechas = validar_orden_fechas(personas[i].desde, personas[i].hasta);
    if (validador_fechas == 0) { // si las fechas estan al reves
        intercambiar_fechas(&(personas[i].desde), &(personas[i].hasta)); // intercambiar fechas
    } else if (validador_fechas == 2 || validador_fechas == 3) { // falta una de las fechas -> AGREGAR LA FECHA FALTANTE +- 3 MESES
        reformatear_fechas(&(personas[i].desde), &(personas[i].hasta));
    }

    printf(">>> La suscripción del cliente fue cambiada con éxito.\n\n");
}