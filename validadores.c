#include "validadores.h"


// Validadores
bool validar_rut(persona *personas, int num_personas, char* rut){
    /* 
    * Funcion que valida el RUT como llave única de una estructura de tipo persona.
    Devuelve 1, si la llave es única (no se encuentra en los datos) y 0 sino (si ya está registrado).
    * Parametros: 
     - *personas: puntero a la direccion de memoria del primer elemento del arreglo de estructuras de tipo `persona`.
     - RUT: llave única a ser validada
     - num_personas: variable entera que indica el numero de personas en el arreglo *personas.
    */

   // validando el rut
    
    for (int i = 0; i < num_personas; i++){
        if (strcmp(personas[i].rut, rut) == 0){ // 0 cuando se encuentra (la llave no es única)
            // printf("El RUT %s ya se encuentra registrado", rut);
            return false;
        }
    }
    return true;
}

int validar_orden_fechas(char *fecha_antes, char *fecha_despues) {
		/* 
		* Funcion que valida el orden de las fechas como creciente, decreciente o invalido. El formato de las fechas es "AAAA/MM/DD"
    Devuelve: 
		- 0 si La fecha_antes ocurre después o es igual que la fecha_despues.
		* 1 La fecha_antes ocurre antes que la fecha_despues.
		* 2 La fecha_despues es nula.
		* 3 La fecha_antes es nula.
		*-1 Formato de fechas invalido.
	
    * Parametros: 
     - *fecha_antes: puntero a la direccion de memoria del primer 			elemento del arreglo de caracteres fecha_antes.
		 
		 - *fecha_despues: puntero a la direccion de memoria del primer 			elemento del arreglo de caracteres fecha_despues.
	 */
    int year_1 = 0, month_1 = 0, day_1 = 0;
    int year_2 = 0, month_2 = 0, day_2 = 0;
    

    if (*fecha_antes != '\0' && *fecha_despues == '\0'){ // falta el despues
        return 2; // fecha antes = fecha despues - 3 meses

    }else if (*fecha_antes == '\0' && *fecha_despues != '\0'){ //falta el antes
        return 3; // fecha despues = fecha antes + 3 meses

    }

    // Obtener año, mes y día de fecha_antes
    int i = 0, j = 0; // i recorre los indices del arreglo, y j recorre si es año, mes, o día
    while (fecha_antes[i] != '\0') { // mientras no haya terminado de recorrer el arreglo
        if (fecha_antes[i] == '/' || fecha_antes[i] == '-') { // se produce cambio de indicador j (año, mes, día)
						//Corregir formato a separador '/' solamente
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
    char *temp = *fecha_antes;
    *fecha_antes = *fecha_despues;
    *fecha_despues = temp;
}

void reformatear_fechas(char **fecha_antes, char **fecha_despues){
    printf("\n\nREFORMATEAR FECHAS\n");
    if (**fecha_antes != '\0' && **fecha_despues == '\0'){ //falta el despues -> Agregar despues = antes + 3meses
        printf("Modificar valores FECHA_DESPUES (Sumar 3 meses)\n");
				*fecha_despues = malloc(sizeof(char)*11); //asignar memoria al puntero de fecha que es vacio
        time tiempo;
			
        printf("Fecha antes: %s\n", *fecha_antes);
        string_to_timestruct(&tiempo, *fecha_antes);

        tiempo.month += 3;
        update_time(&tiempo);

        timestruct_to_string(*fecha_despues, &tiempo);
        // printf("Fecha antes (modificada): %s\n", fecha_antes);
        printf("Fecha despues (modificada): %s\n", *fecha_despues);
			
    }else if (**fecha_antes == '\0' && **fecha_despues != '\0'){ //falta el antes -> Agregar antes = despues - 3meses
        printf("Modificar valores FECHA_ANTES (Restar 3 meses)\n");
				
				*fecha_antes = malloc(sizeof(char)*11);
        time tiempo;
			
        printf("Fecha despues: %s\n", *fecha_despues);
        string_to_timestruct(&tiempo, *fecha_despues);
        tiempo.month -= 3;
        update_time(&tiempo);
	
        timestruct_to_string(*fecha_antes, &tiempo); 
        printf("Fecha antes (modificada): %s\n", *fecha_antes);
			
    }
}

