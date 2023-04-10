#include "funciones.h"
#include "validadores.h"
#include "sedes.h"
int main() {

    int num_personas;
    int num_planes;
    int num_sedes;

    plan *planes; // puntero a la direccion de memoria de estructuras de tipo plan
    sede *sedes; // puntero a la direccion de memoria de estructuras de tipo sede
    persona *personas = leer_archivo("BigMuscle.csv", &num_personas, &num_planes, &num_sedes, &planes, &sedes);

    bubble_sort_por_apellido(personas, num_personas); // ordenar por apellido
    imprimir_personas(personas, num_personas); // mostrar todas los personas
	printf("\nEl numero de personas es: %d\n", num_personas);

    // FUNCIONES SEDES    
    // agregar_sede(sedes, &num_sedes); // agregar una sede al arreglo notar que se modifica num_sedes
    // imprimir_sedes(sedes, num_sedes); // mostrar todas las sedes
    // eliminar_sede(sedes, &num_sedes); // eliminar sede
    // imprimir_sedes(sedes, num_sedes); // mostrar todas las sedes

    // FUNCIONES PLANES
    // agregar_plan(); //agregar un plan al arreglo
    imprimir_planes(planes , num_planes); //mostrar todos los planes
    // eliminar_plan(planes, &num_planes); // eliminar un plan
    // imprimir_planes(planes , num_planes); //mostrar todos los planes

    // buscar_persona(personas, num_personas); // buscar una persona por rut
    // agregar_persona(personas, &num_personas); //agregar persona, notar que modifica num_personas
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // eliminar_persona(personas, &num_personas); // eliminar persona
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // buscar_persona(personas, num_personas); // buscar una persona por rut
	
    return 0;
}
