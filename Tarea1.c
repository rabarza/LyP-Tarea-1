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

	// printf("\nEl numero de personas es: %d\n", num_personas);

    int option = 0;
    while(option != 15) {
        printf("1. Mostrar clientes\n");
        printf("2. Ordenar clientes por apellido\n");
        printf("3. Buscar cliente por RUT\n");
        printf("4. Agregar cliente\n");
        printf("5. Eliminar cliente\n");
        printf("6. Editar datos cliente\n");
        printf("7. Mostrar planes disponibles\n");
        printf("8. Agregar un plan\n");
        printf("9. Eliminar un plan\n");
        printf("10. Cambiar cliente de plan\n");
        printf("11. Mostrar sedes disponibles\n");
        printf("12. Agregar una sede\n");
        printf("13. Quitar una sede\n");
        printf("14. Cambiar a un cliente de sede\n");
        printf("15. Cerrar sistema\n");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                imprimir_personas(personas, num_personas); // mostrar todas los personas
                break;
            case 2:
                bubble_sort_por_apellido(personas, num_personas); // ordenar por apellido
                break;
            case 3:
                buscar_persona(personas, num_personas); // buscar una persona por rut
                break;
            case 4:
                agregar_persona(personas, &num_personas); // agregar una sede al arreglo notar que se modifica num_sedes
                break;
            case 5:
                eliminar_persona(personas, &num_personas); // eliminar persona
                break;
            case 6:
                // editar datos cliente
                break;          
            case 7:
                imprimir_planes(planes, num_planes); //agregar un plan al arreglo
                break;            
            case 8:
                agregar_plan(planes, &num_planes); //agregar un plan al arreglo
                break;            
            case 9:
                eliminar_plan(planes, &num_planes); // eliminar un plan
                break;            
            case 10:
                // cambiar cliente de plan
                break;            
            case 11:
                imprimir_sedes(sedes, num_sedes); // agregar una sede al arreglo notar que se modifica num_sedes
                break;            
            case 12:
                agregar_sede(sedes, &num_sedes); // agregar una sede al arreglo notar que se modifica num_sedes
                break;            
            case 13:
                eliminar_sede(sedes, &num_sedes); // eliminar sede
                break;            
            case 14:
                // cambiar a un cliente de sede
                break;            
            case 15:
                // cerrar el programa
                break;            

            default:
                break;
        }
    }

    // FUNCIONES SEDES    
    // agregar_sede(sedes, &num_sedes); // agregar una sede al arreglo notar que se modifica num_sedes
    // imprimir_sedes(sedes, num_sedes); // mostrar todas las sedes
    // eliminar_sede(sedes, &num_sedes); // eliminar sede
    // imprimir_sedes(sedes, num_sedes); // mostrar todas las sedes

    // FUNCIONES PLANES
    // agregar_plan(planes, &num_planes); //agregar un plan al arreglo
    // imprimir_planes(planes , num_planes); //mostrar todos los planes
    // eliminar_plan(planes, &num_planes); // eliminar un plan
    // imprimir_planes(planes , num_planes); //mostrar todos los planes

    // FUNCIONES PERSONAS
    // bubble_sort_por_apellido(personas, num_personas); // ordenar por apellido
    // buscar_persona(personas, num_personas); // buscar una persona por rut
    // agregar_persona(personas, &num_personas); //agregar persona, notar que modifica num_personas
    // imprimir_personas(personas, num_personas); // mostrar todas los personas
    // eliminar_persona(personas, &num_personas); // eliminar persona
	
    return 0;
}
