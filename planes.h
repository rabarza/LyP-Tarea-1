#ifndef PLANES
#define PLANES

#include "tiempo.h"

typedef struct {
    char *cod_plan;
    char *descripcion_plan;
    int n_clientes_plan;
} plan;


// PLANES
void imprimir_planes(plan *planes, int num_planes);
void agregar_plan(plan *planes, int *num_planes);
void eliminar_plan(plan *planes, int *num_planes);

void aumentar_clientes_plan(plan *planes, int num_planes, char *cod_plan);
void disminuir_clientes_plan(plan *planes, int num_planes, char *cod_plan);

plan encontrar_plan(plan *planes, int num_planes, char *cod_plan);
plan escanear_datos_plan();
#endif