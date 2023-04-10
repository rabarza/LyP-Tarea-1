#ifndef VALIDADORES
#define VALIDADORES

// incluir 
#include "funciones.h"
#include "tiempo.h"

// Validadores
int validar_rut(persona *personas, int num_personas, char* rut);
int validar_orden_fechas(char *fecha_antes, char *fecha_despues);
int validar_sede(sede *sedes, int num_sedes, char *cod_sede, char *ubicacion_sede_str);
int validar_plan(plan *planes, int num_planes, char *cod_plan, char *descripcion_plan_str);
// Correctores
void intercambiar_fechas(char **fecha_antes, char **fecha_despues);
void reformatear_fechas(char **fecha_antes, char **fecha_despues);

#endif