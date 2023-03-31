#ifndef funciones_tiempo
#define funciones_tiempo

//Incluir librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Declaracion de estructura
typedef struct {
    int year;
    int month;
    int day;
} time;

// Declaracion de funciones
void string_to_timestruct(time *tiempo, char *fecha);
void update_time(time *tiempo);
void timestruct_to_string(char *fecha, time *tiempo);

#endif