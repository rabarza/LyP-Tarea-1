# Formato de datos

## Archivo CSV — `BigMuscle.csv`

Todos los datos de clientes se almacenan en un archivo de valores separados por comas (CSV). La primera fila es el encabezado:

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
```

### Referencia de columnas

| Columna | Tipo | Descripción | Ejemplo |
|---------|------|-------------|---------|
| `rut` | string | RUT chileno. Se usa como llave primaria única. | `12344613-5` |
| `nombre_completo` | string | Nombre completo del cliente (nombre, espacio, apellido). | `Roy Abbott` |
| `edad` | entero | Edad en años. | `27` |
| `cod_plan` | string | Código corto que identifica el plan de suscripción. | `P1` |
| `descripcion_plan` | string | Descripción legible del plan. | `PROGRAMA PERFECTO PARA PRINCIPIANTES 2 VECES A LA SEMANA` |
| `desde` | string | Fecha de inicio de la suscripción en formato `AAAA/MM/DD`. | `2025/01/31` |
| `hasta` | string | Fecha de término de la suscripción en formato `AAAA/MM/DD`. | `2025/04/31` |
| `cod_sede` | string | Código corto que identifica la sede. | `REI` |
| `ubicacion_sede` | string | Nombre del barrio o comuna de la sede. | `La Reina` |

### Filas de ejemplo

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
12344613-5,Roy Abbott,27,P1,PROGRAMA PERFECTO PARA PRINCIPIANTES 2 VECES A LA SEMANA,2025/01/31,2025/04/31,REI,La Reina
12344572-4,Marjorie Abney,36,THOR101,PREFIERES NO SABERLO,2033/07/31,2036/07/31,BAR,Lo Barnechea
15030-4,Sean Alder,42,PRO1,FULL TODA LA SEMANA,2034/06/30,2034/09/30,INDE,Independencia
```

---

## Formato de fechas

Las fechas se almacenan y muestran como `AAAA/MM/DD` (p. ej. `2025/01/31`).  
El separador también puede aparecer como `-` en datos heredados; la aplicación normaliza ambos a `/` al cargar.

### Fechas faltantes

Si uno de los dos campos de fecha (`desde` / `hasta`) está ausente en un registro, la aplicación calcula el valor faltante automáticamente:

- **`desde` ausente** → `desde = hasta − 3 meses`
- **`hasta` ausente** → `hasta = desde + 3 meses`

### Fechas invertidas

Si `desde` es cronológicamente posterior a `hasta`, los dos valores se intercambian automáticamente.

---

## Códigos de plan

Los planes se identifican mediante un código alfanumérico corto (p. ej. `P1`, `MED2`, `PRO1`, `THOR101`). Cada código debe ser único en el conjunto de datos. Los planes llevan el conteo de clientes suscritos; un plan no puede eliminarse mientras tenga suscriptores.

---

## Códigos de sede

Las sedes se identifican mediante un código corto en mayúsculas (p. ej. `REI`, `BAR`, `PIN`, `FLO`). Cada código debe ser único. Al igual que los planes, una sede no puede eliminarse mientras tenga clientes asignados.
