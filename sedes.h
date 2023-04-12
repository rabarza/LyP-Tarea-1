#ifndef SEDES
#define SEDES

#include "tiempo.h"
// Estructuras
typedef struct {
    char *cod_sede;
    char *ubicacion_sede;
    int n_clientes_sede;
} sede;

// Funciones
void imprimir_sedes(sede *sedes, int num_sedes);
void aumentar_clientes_sede(sede *sedes, int num_sedes, char *cod_sede);
void disminuir_clientes_sede(sede *sedes, int num_sedes, char *cod_sede);
void agregar_sede(sede *sedes, int *num_sedes);
void eliminar_sede(sede *sedes, int *num_sedes);
sede escanear_datos_sede();

#endif