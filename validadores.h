#ifndef VALIDADORES
#define VALIDADORES

// incluir 
#include "funciones.h"
#include "tiempo.h"

// Validadores
bool validar_rut(persona *personas, int num_personas, char* rut);
int validar_orden_fechas(char *fecha_antes, char *fecha_despues);

// Correctores
void intercambiar_fechas(char **fecha_antes, char **fecha_despues);
void reformatear_fechas(char **fecha_antes, char **fecha_despues);

#endif