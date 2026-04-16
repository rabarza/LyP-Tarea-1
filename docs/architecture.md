# Arquitectura

## Visión general

El proyecto está organizado en módulos independientes. Cada módulo es responsable de un tipo de dato específico y expone funciones para crear, consultar y modificar instancias de ese tipo. `main.c` conecta todos los módulos a través de un bucle de menú interactivo.

---

## Descripción de los módulos

### `main.c`

Punto de entrada. Llama a `leer_archivo()` para cargar todos los datos de `BigMuscle.csv` en tres arreglos dinámicos (`persona[]`, `sede[]`, `plan[]`), y luego ejecuta un bucle `while` que presenta el menú de 15 opciones y despacha cada acción a la función correspondiente. Al salir (opción 15) llama a `guardar_csv_personas()` para persistir los cambios.

---

### `funciones.c / funciones.h`

Define la estructura `persona` y todas las operaciones sobre clientes.

**Estructura:**

```c
typedef struct {
    char *rut;
    char *nombre_completo;
    int   edad;
    char *cod_plan;
    char *descripcion_plan;
    char *desde;
    char *hasta;
    char *cod_sede;
    char *ubicacion_sede;
} persona;
```

**Funciones principales:**

| Función | Descripción |
|---------|-------------|
| `leer_archivo()` | Parsea `BigMuscle.csv` y construye los tres arreglos dinámicos. |
| `guardar_csv_personas()` | Serializa todos los clientes de vuelta al CSV. |
| `datos_faltantes_personas()` | Completa los campos `descripcion_plan` y `ubicacion_sede` faltantes cruzando datos con planes y sedes. |
| `agregar_persona()` | Agrega interactivamente un cliente; registra nuevos planes/sedes si es necesario. |
| `eliminar_persona()` | Elimina un cliente por RUT y compacta el arreglo. |
| `buscar_persona()` | Busca un cliente por RUT e imprime su registro. |
| `imprimir_personas()` | Imprime todos los clientes. |
| `bubble_sort_por_apellido()` | Ordena los clientes en su lugar por apellido usando bubble sort. |
| `cambiar_sede_persona()` | Reasigna un cliente a otra sede. |
| `cambiar_plan_persona()` | Reasigna un cliente a otro plan. |
| `editar_datos_cliente()` | Permite editar RUT, nombre o fechas de suscripción. |
| `escanear_datos()` | Solicita interactivamente los datos y retorna una estructura `persona` completa. |

---

### `planes.c / planes.h`

Define la estructura `plan` y las operaciones sobre planes de suscripción.

**Estructura:**

```c
typedef struct {
    char *cod_plan;
    char *descripcion_plan;
    int   n_clientes_plan;
} plan;
```

**Funciones principales:**

| Función | Descripción |
|---------|-------------|
| `agregar_plan()` | Lee un nuevo plan desde stdin y lo agrega si el código es único. |
| `eliminar_plan()` | Elimina un plan solo si no tiene suscriptores. |
| `imprimir_planes()` | Lista todos los planes con el conteo de suscriptores. |
| `encontrar_plan()` | Retorna el `plan` que coincide con un código dado. |
| `aumentar_clientes_plan()` | Incrementa el contador de suscriptores de un plan. |
| `disminuir_clientes_plan()` | Decrementa el contador de suscriptores de un plan. |

---

### `sedes.c / sedes.h`

Define la estructura `sede` y sus operaciones.

**Estructura:**

```c
typedef struct {
    char *cod_sede;
    char *ubicacion_sede;
    int   n_clientes_sede;
} sede;
```

**Funciones principales:**

| Función | Descripción |
|---------|-------------|
| `agregar_sede()` | Lee una nueva sede desde stdin y la agrega si el código es único. |
| `eliminar_sede()` | Elimina una sede solo si no tiene clientes asignados. |
| `imprimir_sedes()` | Lista todas las sedes con el conteo de clientes. |
| `encontrar_sede()` | Retorna la `sede` que coincide con un código dado. |
| `aumentar_clientes_sede()` | Incrementa el contador de clientes de una sede. |
| `disminuir_clientes_sede()` | Decrementa el contador de clientes de una sede. |

---

### `tiempo.c / tiempo.h`

Utilidades de parseo y aritmética de fechas.

**Estructura:**

```c
typedef struct {
    int year;
    int month;
    int day;
} time;
```

**Funciones:**

| Función | Descripción |
|---------|-------------|
| `string_to_timestruct()` | Parsea un string `"AAAA/MM/DD"` en una estructura `time`. |
| `timestruct_to_string()` | Serializa una estructura `time` de vuelta a `"AAAA/MM/DD"`. |
| `update_time()` | Normaliza una estructura `time` tras operaciones aritméticas (maneja desbordamiento de meses). |

---

### `validadores.c / validadores.h`

Funciones de validación de entradas y corrección de fechas.

**Funciones:**

| Función | Descripción |
|---------|-------------|
| `validar_rut()` | Retorna `1` si el RUT no está registrado, `0` si está duplicado, `-1` si está vacío. |
| `validar_plan()` | Retorna `1` si el código de plan existe (y completa la descripción si falta), `0` si no se encuentra. |
| `validar_sede()` | Retorna `1` si el código de sede existe (y completa la ubicación si falta), `0` si no se encuentra. |
| `validar_orden_fechas()` | Verifica el orden cronológico de dos fechas; retorna códigos para fechas invertidas, faltantes o con formato inválido. |
| `intercambiar_fechas()` | Intercambia dos punteros de fecha. |
| `reformatear_fechas()` | Dada una fecha presente y otra ausente, sintetiza la faltante sumando o restando 3 meses. |

---

## Gestión de memoria

Todos los campos de texto dentro de las estructuras se alocan en el heap con `strdup()`. Los arreglos dinámicos crecen con `realloc()` al agregar elementos y se reducen al eliminarlos. No hay una pasada explícita de `free()` al salir; el sistema operativo libera la memoria, lo cual es aceptable para una herramienta CLI de corta duración.
