#include "tiempo.h"

void string_to_timestruct(time *tiempo, char *fecha){
	
    int year = 0, month = 0, day = 0; // inicializar todos en cero (NECESARIO)
		
    // Obtener año, mes y día de fecha_antes
    int i = 0, j = 0; // i recorre los indices del arreglo, y j recorre si es año, mes, o día
    while (fecha[i] != '\0') { // mientras no haya terminado de recorrer el arreglo
        if (fecha[i] == '/' || fecha[i] == '-') { // se produce cambio de indicador j (año, mes, día)
            j++;
        } else {
            switch (j) {
                case 0: // año
                    year = year * 10 + (fecha[i] - '0');
                    break;
                case 1: // mes
                    month = month * 10 + (fecha[i] - '0');
                    break;
                case 2: // día
                    day = day * 10 + (fecha[i] - '0');
                    break;
                default:
                    break;
            }
        }
        i++;
    }
    tiempo->day = day;
    tiempo->month = month;
    tiempo->year = year;
	// printf("String to TimeSruct\n");
	// // printf("Datos del String %s\n", fecha);
	// printf("Datos estructurados\n");
    // printf("YEAR: %d\n", tiempo->year);
    // printf("MONTH: %d\n", tiempo->month);
    // printf("DAY: %d\n", tiempo->day);
    return;
}

void update_time(time *tiempo){
    if (tiempo->month > 0 && tiempo->month % 12 != 0){
        tiempo->year += tiempo->month/12;
        tiempo->month %= 12;
    } else if (tiempo->month < 0){
				float num = tiempo->month;
				float div = 12.0;
			  double division = num/div;
    		int resultado = (int) floor(division); //floor() retorna un valor tipo double. se ocupa el (int) antes para dejarlo como entero
			
        tiempo->year -= abs(resultado); // se le resta el valor absoluto del resultado
        tiempo->month = 12-abs(tiempo->month%12);
    } else if (tiempo->month == 0){
				tiempo->year -= 1;
				tiempo->month = 12;
		}
    // printf("Datos actualizados\n");
    // printf("YEAR: %d\n", tiempo->year);
    // printf("MONTH: %d\n", tiempo->month);
    // printf("DAY: %d\n", tiempo->day);
}

void timestruct_to_string(char *fecha, time *tiempo){
    sprintf(fecha, "%04d/%02d/%02d", tiempo->year, tiempo->month, tiempo->day);
}

