#ifndef FUNCIONES_PRINCIPALES
#define FUNCIONES_PRINCIPALES

#include "tiempo.h"
#include "sedes.h"
#include "planes.h"

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
persona escanear_datos(sede* sedes, int num_sedes, plan *planes, int num_planes);
persona *leer_archivo(char *nombre_archivo, int *num_personas,int *num_planes, int *num_sedes, plan **planes, sede **sedes); // modificacion planes
void agregar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes);
void eliminar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes);
void bubble_sort_por_apellido(persona *personas, int num_personas);
void imprimir_personas(persona *personas, int num_personas);
void buscar_persona(persona *personas, int num_personas);

#endif