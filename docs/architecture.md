# Architecture

## Overview

The project is organised into self-contained modules. Each module owns a specific data type and exposes functions for creating, querying, and mutating instances of that type. `main.c` ties all modules together through a menu-driven loop.

---

## Module descriptions

### `main.c`

Entry point. Calls `leer_archivo()` to load all data from `BigMuscle.csv` into three dynamic arrays (`persona[]`, `sede[]`, `plan[]`), then runs a `while` loop that presents a 15-option menu and dispatches to the appropriate function. On exit (option 15), calls `guardar_csv_personas()` to persist changes.

---

### `funciones.c / funciones.h`

Defines the `persona` struct and all client-level operations.

**Struct:**

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

**Key functions:**

| Function | Description |
|----------|-------------|
| `leer_archivo()` | Parses `BigMuscle.csv` and builds the three dynamic arrays. |
| `guardar_csv_personas()` | Serialises all clients back to CSV. |
| `datos_faltantes_personas()` | Fills in missing `descripcion_plan` and `ubicacion_sede` fields by cross-referencing plans and branches. |
| `agregar_persona()` | Interactively adds a client; also registers new plans/branches if needed. |
| `eliminar_persona()` | Removes a client by RUT and shifts the array. |
| `buscar_persona()` | Searches for a client by RUT and prints their record. |
| `imprimir_personas()` | Prints all clients. |
| `bubble_sort_por_apellido()` | Sorts clients in-place by last name using bubble sort. |
| `cambiar_sede_persona()` | Reassigns a client to a different branch. |
| `cambiar_plan_persona()` | Reassigns a client to a different plan. |
| `editar_datos_cliente()` | Allows editing RUT, name, or subscription dates. |
| `escanear_datos()` | Interactive prompt to read a full `persona` from stdin. |

---

### `planes.c / planes.h`

Defines the `plan` struct and operations on subscription plans.

**Struct:**

```c
typedef struct {
    char *cod_plan;
    char *descripcion_plan;
    int   n_clientes_plan;
} plan;
```

**Key functions:**

| Function | Description |
|----------|-------------|
| `agregar_plan()` | Reads a new plan from stdin and appends it if the code is unique. |
| `eliminar_plan()` | Removes a plan only when it has zero subscribers. |
| `imprimir_planes()` | Lists all plans with subscriber counts. |
| `encontrar_plan()` | Returns the `plan` matching a given code. |
| `aumentar_clientes_plan()` | Increments the subscriber counter for a plan. |
| `disminuir_clientes_plan()` | Decrements the subscriber counter for a plan. |

---

### `sedes.c / sedes.h`

Defines the `sede` struct (branch location) and its operations.

**Struct:**

```c
typedef struct {
    char *cod_sede;
    char *ubicacion_sede;
    int   n_clientes_sede;
} sede;
```

**Key functions:**

| Function | Description |
|----------|-------------|
| `agregar_sede()` | Reads a new branch from stdin and appends it if the code is unique. |
| `eliminar_sede()` | Removes a branch only when it has zero clients. |
| `imprimir_sedes()` | Lists all branches with client counts. |
| `encontrar_sede()` | Returns the `sede` matching a given code. |
| `aumentar_clientes_sede()` | Increments the client counter for a branch. |
| `disminuir_clientes_sede()` | Decrements the client counter for a branch. |

---

### `tiempo.c / tiempo.h`

Date parsing and arithmetic utilities.

**Struct:**

```c
typedef struct {
    int year;
    int month;
    int day;
} time;
```

**Functions:**

| Function | Description |
|----------|-------------|
| `string_to_timestruct()` | Parses a `"YYYY/MM/DD"` string into a `time` struct. |
| `timestruct_to_string()` | Serialises a `time` struct back to `"YYYY/MM/DD"`. |
| `update_time()` | Normalises a `time` struct after arithmetic (handles month overflow/underflow). |

---

### `validadores.c / validadores.h`

Input validation and date correction functions.

**Functions:**

| Function | Description |
|----------|-------------|
| `validar_rut()` | Returns `1` if a RUT is not yet registered, `0` if duplicate, `-1` if empty. |
| `validar_plan()` | Returns `1` if a plan code exists (and fills missing description), `0` if not found. |
| `validar_sede()` | Returns `1` if a branch code exists (and fills missing location), `0` if not found. |
| `validar_orden_fechas()` | Checks chronological ordering of two date strings; returns codes for out-of-order, missing, or invalid dates. |
| `intercambiar_fechas()` | Swaps two date string pointers. |
| `reformatear_fechas()` | Given one present and one absent date, synthesises the missing date as ±3 months. |

---

## Memory management

All string fields inside structs are heap-allocated with `strdup()`. Dynamic arrays are grown with `realloc()` as items are added and shrunk after items are removed. There is no explicit `free()` pass on exit (the OS reclaims memory), which is acceptable for a short-lived CLI tool.
