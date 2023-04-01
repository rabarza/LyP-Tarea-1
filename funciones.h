#ifndef FUNCIONES_PRINCIPALES
#define FUNCIONES_PRINCIPALES

#include "tiempo.h"


#define MAX_LEN 200

typedef struct {
    char *rut;
    char *nombre_completo;
    int edad;
    char *cod_plan;
    char *descripcion_plan;
    char *desde;
    char *hasta;
    char *cod_sede;
    char *ubicacion_sede;
} persona;


// Declaracion funciones
persona escanear_datos();
persona *leer_archivo(char *nombre_archivo, int *num_personas);
void bubble_sort_por_apellido(persona *personas, int num_personas);
void imprimir_personas(persona *personas, int num_personas);
void agregar_persona(persona *personas, int *num_personas);
void eliminar_persona(persona *personas, int *num_personas);
void buscar_persona(persona *personas, int num_personas);

#endif