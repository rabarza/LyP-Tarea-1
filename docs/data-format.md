# Data Format

## CSV file — `BigMuscle.csv`

All client data is stored in a comma-separated values (CSV) file. The first row is a header:

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
```

### Column reference

| Column | Type | Description | Example |
|--------|------|-------------|---------|
| `rut` | string | Chilean national ID (RUT). Used as the unique primary key. | `12344613-5` |
| `nombre_completo` | string | Full name of the client (first name, space, last name). | `Roy Abbott` |
| `edad` | integer | Age in years. | `27` |
| `cod_plan` | string | Short code identifying the subscription plan. | `P1` |
| `descripcion_plan` | string | Human-readable description of the plan. | `PROGRAMA PERFECTO PARA PRINCIPIANTES 2 VECES A LA SEMANA` |
| `desde` | string | Subscription start date in `YYYY/MM/DD` format. | `2025/01/31` |
| `hasta` | string | Subscription end date in `YYYY/MM/DD` format. | `2025/04/31` |
| `cod_sede` | string | Short code identifying the branch location. | `REI` |
| `ubicacion_sede` | string | Name of the neighbourhood/commune of the branch. | `La Reina` |

### Example rows

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
12344613-5,Roy Abbott,27,P1,PROGRAMA PERFECTO PARA PRINCIPIANTES 2 VECES A LA SEMANA,2025/01/31,2025/04/31,REI,La Reina
12344572-4,Marjorie Abney,36,THOR101,PREFIERES NO SABERLO,2033/07/31,2036/07/31,BAR,Lo Barnechea
15030-4,Sean Alder,42,PRO1,FULL TODA LA SEMANA,2034/06/30,2034/09/30,INDE,Independencia
```

---

## Date format

Dates are stored and displayed as `YYYY/MM/DD` (e.g. `2025/01/31`).  
The separator may also appear as `-` in legacy data; the application normalises both to `/` on load.

### Missing dates

If one of the two date fields (`desde` / `hasta`) is absent for a record, the application computes the missing value automatically:

- **`desde` missing** → `desde = hasta − 3 months`
- **`hasta` missing** → `hasta = desde + 3 months`

### Out-of-order dates

If `desde` is chronologically later than `hasta`, the two values are swapped automatically.

---

## Plan codes

Plans are identified by a short alphanumeric code (e.g. `P1`, `MED2`, `PRO1`, `THOR101`). Each code must be unique across the dataset. Plans track the number of subscribed clients; a plan cannot be deleted while it still has subscribers.

---

## Branch codes (sedes)

Branches are identified by a short uppercase code (e.g. `REI`, `BAR`, `PIN`, `FLO`). Each code must be unique. Like plans, a branch cannot be deleted while it has assigned clients.
