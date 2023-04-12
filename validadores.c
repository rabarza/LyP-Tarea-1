#include "validadores.h"


// Validadores
int validar_rut(persona *personas, int num_personas, char* rut){
    /* 
    * Funcion que valida el RUT como llave única de una estructura de tipo persona.
    Devuelve: 
        true: si la llave es única (no se encuentra en los datos) y, 
        false: la llave no es única (si el usuario de ID RUT ya está registrado).
    * Parametros: 
     -*personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - rut: llave única a ser validada (puntero al arreglo de caracteres que representa la llave única).
     - num_personas: variable entera que indica el numero de personas en el arreglo *personas.
    */

   // validando el rut
    if (*rut != '\0'){
        for (int i = 0; i < num_personas; i++){
            if (strcmp(personas[i].rut, rut) == 0){ // 0 cuando se encuentra (la llave no es única)
                // printf("El RUT %s ya se encuentra registrado", rut);
                return 0;
            }
        }
        return 1;
    }
    else{
        return -1;
    }
}

int validar_plan(plan *planes, int num_planes, char *cod_plan, char *descripcion_plan_str){
    if (*cod_plan != '\0'){
        for (int i = 0; i < num_planes; i++){
            if(strcmp(cod_plan, planes[i].cod_plan) == 0) {
                if (*planes[i].descripcion_plan == '\0' && *descripcion_plan_str != '\0'){ // si la sede existe y falta información de la ubicación (=> llenar información faltante)
                    planes[i].descripcion_plan = strdup(descripcion_plan_str); // llenar la información faltante
                }
                return 1; // el plan ya existe
            }
        }
        return 0; // el plan no existe
    } else {
        return -1; // plan inválido
    }
}

int validar_sede(sede *sedes, int num_sedes, char *cod_sede, char *ubicacion_sede_str){
    if (*cod_sede != '\0'){
        for (int i = 0; i < num_sedes; i++){
            if(strcmp(cod_sede, sedes[i].cod_sede) == 0) {
                if (*sedes[i].ubicacion_sede == '\0' && *ubicacion_sede_str != '\0'){ // si la sede existe y falta información de la ubicación (=> llenar información faltante)
                    sedes[i].ubicacion_sede = strdup(ubicacion_sede_str); // llenar la información faltante
                }
                return 1; // la sede ya existe
            }
        }
        return 0; // la sede no existe
    } else {
        return -1; // sede inválida
    }
}


int validar_orden_fechas(char *fecha_antes, char *fecha_despues) {
	/* 
	* Funcion que valida el orden de las fechas como creciente, decreciente o invalido. El formato de las fechas es "AAAA/MM/DD"
    Devuelve: 
		* 0 si La fecha_antes ocurre después o es igual que la fecha_despues.
		* 1 La fecha_antes ocurre antes que la fecha_despues.
		* 2 La fecha_despues es nula.
		* 3 La fecha_antes es nula.
		*-1 Formato de fechas invalido.
	
    * Parametros: 
    - *fecha_antes: puntero a la direccion de memoria del primer elemento del arreglo de caracteres fecha_antes.
	- *fecha_despues: puntero a la direccion de memoria del primer elemento del arreglo de caracteres fecha_despues.
	*/
    int year_1 = 0, month_1 = 0, day_1 = 0;
    int year_2 = 0, month_2 = 0, day_2 = 0;
    

    if (*fecha_antes != '\0' && *fecha_despues == '\0'){ // falta el despues
        return 2; // fecha antes = fecha despues - 3 meses

    } else if (*fecha_antes == '\0' && *fecha_despues != '\0'){ // falta el antes
        return 3; // fecha despues = fecha antes + 3 meses
    }

    // Obtener año, mes y día de fecha_antes
    int i = 0, j = 0; // i recorre los indices del arreglo, y j recorre si es año, mes, o día
    while (fecha_antes[i] != '\0') { // mientras no haya terminado de recorrer el arreglo
        if (fecha_antes[i] == '/' || fecha_antes[i] == '-') { // se produce cambio de indicador j (año, mes, día)
						// Corregir formato a separador '/' solamente
						fecha_antes[i] = '/'; 
						fecha_despues[i] = '/';
            j++; // cambiar el tipo de dato (año, mes, dia)
        } else {
            switch (j) {
                case 0: // año
                    year_1 = year_1 * 10 + (fecha_antes[i] - '0');
                    year_2 = year_2 * 10 + (fecha_despues[i] - '0');
                    break;
                case 1: // mes
                    month_1 = month_1 * 10 + (fecha_antes[i] - '0');
                    month_2 = month_2 * 10 + (fecha_despues[i] - '0');
                    break;
                case 2: // día
                    day_1 = day_1 * 10 + (fecha_antes[i] - '0');
                    day_2 = day_2 * 10 + (fecha_despues[i] - '0');
                    break;
                default:
                    break;
            }
        }
        i++;
    }
	
    // validar formato
    if (((fecha_antes[4] != '/' && fecha_antes[4] != '-') || (fecha_antes[7] != '/' && fecha_antes[7] != '-')) || ((fecha_despues[4] != '/' && fecha_antes[4] != '-') || (fecha_despues[7] != '/' && fecha_antes[7] != '-')) || (*fecha_antes == '\0' && *fecha_despues == '\0')){
        return -1; // formato de fechas invalido
    }
    // Comparar fechas
    if (year_1 < year_2 || (year_1 == year_2 && month_1 < month_2) || (year_1 == year_2 && month_1 == month_2 && day_1 < day_2)) {
        return 1; // La fecha 1 ocurre antes que la fecha 2
    } else {
        return 0; // La fecha 1 ocurre después o es igual que la fecha 2
    }
}

// CORREGIR FORMATOS

// Arreglar problemas fechas al reves
void intercambiar_fechas(char **fecha_antes, char **fecha_despues){
    /*
    * Función que intercambia dos punteros de formato fecha.
    * Parámetros:
        -**fecha_antes: puntero a la direccion de memoria del puntero *fecha_antes.
        -**fecha_despues: puntero a la direccion de memoria del puntero *fecha_despues.
    */
    char *temp = *fecha_antes;
    *fecha_antes = *fecha_despues;
    *fecha_despues = temp;
}

void reformatear_fechas(char **fecha_antes, char **fecha_despues){
    /*
    * Funcion que dados dos arreglos de caracteres de formato fecha (y uno faltante), corrige aquel que falta. 
      Se considera que aquella fecha que falta ocurre 3 meses antes (o después) que la que no falta, dependiendo del caso.
    * Parametros: 
    - *fecha_antes: puntero a la direccion de memoria del primer elemento del arreglo de caracteres fecha_antes.
    - *fecha_despues: puntero a la direccion de memoria del primer elemento del arreglo de caracteres fecha_despues.
    */
    // printf("\n\nREFORMATEAR FECHAS\n");
    if (**fecha_antes != '\0' && **fecha_despues == '\0'){ //falta el despues -> Agregar despues = antes + 3meses
        // printf("Modificar valores FECHA_DESPUES (Sumar 3 meses)\n");

		*fecha_despues = malloc(sizeof(char)*11); // asignar memoria al puntero de fecha que es vacio
        time tiempo; // crear estructura de tipo time
			
        // printf("Fecha antes: %s\n", *fecha_antes);
        string_to_timestruct(&tiempo, *fecha_antes); // llevar los datos del string que no falta a la estructura de tiempo

        tiempo.month += 3; // sumar tres meses a la estructura de tiempo
        update_time(&tiempo); // se actualizan los datos de la estructura de tiempos a un formato de fecha valido

        timestruct_to_string(*fecha_despues, &tiempo); // llevar la estructura de tiempo al string que falta (*fecha_despues)
        // printf("Fecha despues (modificada): %s\n", *fecha_despues);
			
    } else if (**fecha_antes == '\0' && **fecha_despues != '\0'){ //falta el antes -> Agregar antes = despues - 3meses
        // printf("Modificar valores FECHA_ANTES (Restar 3 meses)\n");
				
		*fecha_antes = malloc(sizeof(char)*11);
        time tiempo;
			
        // printf("Fecha despues: %s\n", *fecha_despues);
        string_to_timestruct(&tiempo, *fecha_despues);

        tiempo.month -= 3; // restar tres meses a la estructura de tiempo
        update_time(&tiempo);
	
        timestruct_to_string(*fecha_antes, &tiempo); // llevar la estructura de tiempo al string que falta (*fecha_antes)
        // printf("Fecha antes (modificada): %s\n", *fecha_antes);	
    }
}