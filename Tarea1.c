#include "funciones.h"
#include "validadores.h"

int main() {
    int num_personas;
	
    persona *personas = leer_archivo("BigMuscle.csv", &num_personas);
    bubble_sort_por_apellido(personas, num_personas); // ordenar por apellido
    imprimir_personas(personas, num_personas); // mostrar todas los personas
	printf("El numero de personas es %d\n",num_personas);
		
    // buscar_persona(personas, num_personas); // buscar una persona por rut
    agregar_persona(personas, &num_personas); //agregar persona, notar que modifica num_personas
    imprimir_personas(personas, num_personas); // mostrar todas los personas
    // eliminar_persona(personas, &num_personas); // eliminar persona
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // buscar_persona(personas, num_personas); // buscar una persona por rut
	
    return 0;

}
