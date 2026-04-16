# BigMuscle — Sistema de Gestión de Gimnasio

Aplicación de línea de comandos escrita en C para gestionar membresías de gimnasio, planes de suscripción y sedes. Los datos de los clientes se persisten en un archivo CSV; todas las operaciones se realizan en memoria durante la sesión y los cambios se guardan en disco al salir.

---

## Funcionalidades

- **Gestión de clientes** — agregar, eliminar, editar, buscar y ordenar clientes por apellido.
- **Planes de suscripción** — agregar, eliminar y reasignar planes a clientes.
- **Sedes** — agregar, eliminar y reasignar sedes a clientes.
- **Validación de fechas** — corrige y completa automáticamente fechas de suscripción faltantes sumando o restando 3 meses.
- **Persistencia CSV** — lee y escribe en `BigMuscle.csv`.

---

## Estructura del proyecto

```
.
├── main.c          # Punto de entrada — menú interactivo
├── funciones.c/h   # Operaciones principales sobre clientes (persona)
├── planes.c/h      # Operaciones sobre planes de suscripción
├── sedes.c/h       # Operaciones sobre sedes
├── tiempo.c/h      # Utilidades de parseo y aritmética de fechas
├── validadores.c/h # Validadores de entrada (RUT, fechas, planes, sedes)
├── BigMuscle.csv   # Base de datos de clientes (CSV)
└── Makefile        # Configuración de compilación
```

Ver [`docs/architecture.md`](docs/architecture.md) para una descripción detallada de cada módulo y sus responsabilidades.

---

## Formato de datos

El archivo CSV usa las siguientes columnas:

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
```

Las fechas usan el formato `AAAA/MM/DD`. Ver [`docs/data-format.md`](docs/data-format.md) para más detalles.

---

## Compilación

### Opción 1 — con `make` (recomendada)

Requiere **GCC** y **make**.

```bash
make        # compila → genera ./bigmuscle
make clean  # elimina archivos objeto y el binario
```

`make` compila cada `.c` por separado en un archivo objeto (`.o`) y luego los enlaza en el ejecutable final. Solo recompila los archivos que hayan cambiado desde la última compilación.

### Opción 2 — con `gcc` directamente

Si no tienes `make` instalado, puedes compilar y enlazar todos los archivos en un solo comando:

```bash
gcc -Wall -Wextra -std=c11 -o bigmuscle main.c funciones.c planes.c sedes.c tiempo.c validadores.c -lm
```

Para limpiar manualmente, elimina el binario generado:

```bash
rm bigmuscle
```

---

## Ejecución

```bash
./bigmuscle
```

El programa lee `BigMuscle.csv` desde el directorio actual, presenta un menú interactivo y guarda todos los cambios al seleccionar la opción **15 (Cerrar sistema)**.

---

## Opciones del menú

| #  | Acción |
|----|--------|
| 1  | Mostrar clientes |
| 2  | Ordenar clientes por apellido |
| 3  | Buscar cliente por RUT |
| 4  | Agregar cliente |
| 5  | Eliminar cliente |
| 6  | Editar datos de cliente |
| 7  | Mostrar planes disponibles |
| 8  | Agregar un plan |
| 9  | Eliminar un plan |
| 10 | Cambiar cliente de plan |
| 11 | Mostrar sedes disponibles |
| 12 | Agregar una sede |
| 13 | Quitar una sede |
| 14 | Cambiar cliente de sede |
| 15 | Guardar y cerrar |
