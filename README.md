# BigMuscle — Gym Management System

A command-line application written in C for managing gym memberships, subscription plans, and branch locations. Client data is persisted in a CSV file and all operations are performed in memory during the session, with changes saved back to disk on exit.

---

## Features

- **Client management** — add, remove, edit, search, and sort clients by last name.
- **Subscription plans** — add, remove, and reassign plans to clients.
- **Branch locations (sedes)** — add, remove, and reassign branches to clients.
- **Date validation** — automatically corrects and completes missing subscription dates by adding/subtracting 3 months.
- **CSV persistence** — reads from and writes back to `BigMuscle.csv`.

---

## Project structure

```
.
├── main.c          # Entry point — CLI menu loop
├── funciones.c/h   # Core client (persona) operations
├── planes.c/h      # Subscription plan operations
├── sedes.c/h       # Branch location operations
├── tiempo.c/h      # Date parsing and manipulation utilities
├── validadores.c/h # Input validators (RUT, dates, plans, sedes)
├── BigMuscle.csv   # Client database (CSV)
└── Makefile        # Build configuration
```

See [`docs/architecture.md`](docs/architecture.md) for a detailed description of each module and its responsibilities.

---

## Data format

The CSV file uses the following columns:

```
rut,nombre_completo,edad,cod_plan,descripcion_plan,desde,hasta,cod_sede,ubicacion_sede
```

Dates use the format `YYYY/MM/DD`. See [`docs/data-format.md`](docs/data-format.md) for full details.

---

## Build

Requires **GCC** and **make**.

```bash
make        # compile → produces ./bigmuscle
make clean  # remove object files and binary
```

---

## Run

```bash
./bigmuscle
```

The program reads `BigMuscle.csv` from the current directory, presents an interactive menu, and saves all changes back to the file when option **15 (Cerrar sistema)** is selected.

---

## Menu options

| # | Action |
|---|--------|
| 1 | List all clients |
| 2 | Sort clients by last name |
| 3 | Search client by RUT |
| 4 | Add client |
| 5 | Remove client |
| 6 | Edit client data |
| 7 | List available plans |
| 8 | Add a plan |
| 9 | Remove a plan |
| 10 | Change a client's plan |
| 11 | List available branches |
| 12 | Add a branch |
| 13 | Remove a branch |
| 14 | Change a client's branch |
| 15 | Save & exit |
