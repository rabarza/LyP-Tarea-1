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

		// char fecha1[11] = "2020/10/20";
		// char fecha2[11] = "2021/05/20";
		// char fecha3[11] = "2023/11/20";
	
		// char *ptr1 = fecha1;
		// char *ptr2 = fecha2;
		// char *ptr3 = fecha3;
  //   int test = validar_orden_fechas("\0", ptr2);
	
		// time tiempo;
	
		// string_to_timestruct(&tiempo, ptr1);
		// tiempo.month -= 10;
		// update_time(&tiempo);

		// printf("El resultado del test es %d\n",test);
		// timestruct_to_string(ptr1, &tiempo);
		// printf("El String Actualizado es: %s", ptr1);		
		// reformatear_fechas(q, char **fecha_despues)
	
    return 0;

}
