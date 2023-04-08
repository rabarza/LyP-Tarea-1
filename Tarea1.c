#include "funciones.h"
#include "validadores.h"

int main() {

    int num_personas;
    int num_planes;
    int num_sedes;

    plan *planes; // puntero a la direccion de memoria de estructuras de tipo plan
    sede *sedes; // puntero a la direccion de memoria de estructuras de tipo sede

    persona *personas = leer_archivo("BigMuscle.csv", &num_personas, &num_planes, &num_sedes, &planes, &sedes);
    bubble_sort_por_apellido(personas, num_personas); // ordenar por apellido
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
	printf("El numero de personas es %d\n", num_personas);
    printf("Numero de sedes %d", num_sedes);
    
    for (int i = 0; i < num_sedes; i++) {
        printf("Cod Sede: %s\n", sedes[i].ubicacion_sede);
    }
    // buscar_persona(personas, num_personas); // buscar una persona por rut
    // agregar_persona(personas, &num_personas); //agregar persona, notar que modifica num_personas
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // eliminar_persona(personas, &num_personas); // eliminar persona
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // buscar_persona(personas, num_personas); // buscar una persona por rut
	
    return 0;
}
