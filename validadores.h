#ifndef VALIDADORES
#define VALIDADORES

// incluir 
#include "funciones.h"
#include "tiempo.h"

// Validadores
int validar_rut(persona *personas, int num_personas, char* rut);
int validar_orden_fechas(char *fecha_antes, char *fecha_despues);
int validar_sede(sede *sedes, int num_sedes, char *cod_sede);

// Correctores
void intercambiar_fechas(char **fecha_antes, char **fecha_despues);
void reformatear_fechas(char **fecha_antes, char **fecha_despues);

#endif