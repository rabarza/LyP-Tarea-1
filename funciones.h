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
void datos_faltantes_personas(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes); // llenar datos desc_plan y ubicacion_sede faltantes

void agregar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes);
void eliminar_persona(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_sedes, int *num_planes);

void imprimir_personas(persona *personas, int num_personas);
void buscar_persona(persona *personas, int num_personas);

void cambiar_sede_persona(persona *personas, sede *sedes, int num_personas, int num_sedes);
void cambiar_plan_persona(persona *personas, plan *planes, int num_personas, int num_planes);
void editar_datos_cliente(persona *personas, sede *sedes, plan *planes, int *num_personas, int *num_planes, int *num_sedes);

void bubble_sort_por_apellido(persona *personas, int num_personas);

#endif