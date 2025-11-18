# Visualizador OpenGL — Modelos OBJ y Grids

Este proyecto es un **visualizador 3D interactivo en OpenGL** que permite cargar modelos OBJ, visualizar grids paramétricos y alternar entre modos de renderizado, colores por altura, ejes dinámicos y transformaciones básicas.

Incluye un sistema de cámara automático que se ajusta según el modelo actual, así como controles interactivos para navegación, zoom, rotación, cambio de modelo y opciones de visualización.

---

## Características principales
* Carga de modelos OBJ (dragon, bunny, teapot, cube).
* Capacidad de agregar más OBJ.
* Visualización de **grids paramétricos**.
* Renderizado con:
    * **Color por altura (height shader)**
    * Modo **Puntos**, **Líneas**, **Triángulos**
* Ejes fijos y móviles con capacidad de deshabilitarlos.
* Autoajuste de la cámara según el modelo actual.
* Rotación del modelo en tiempo real.
* Zoom incremental.
* Alternancia de modelos y grids.

---

## Dependencias
El proyecto utiliza las siguientes librerías:

* **OpenGL**
* **GLFW**
* **GLEW**
* **GLM**
* Compilador C++ compatible con **C++20**
* CMAKE versión **3.24** o superior

---

## Compilación y ejecución
Desde la carpeta raíz del proyecto:

```bash
mkdir build
cd build
cmake ..
make
./visualizadorOBJ
```
---

## Controles del visualizador

| Tecla | Acción                         |
| :---  | :---                           |
| X     | Rotar sobre eje X              |
| Y     | Rotar sobre eje Y              |
| Z     | Rotar sobre eje Z              |
| G     | Alternar entre modelos y grids |
| N     | Siguiente modelo/grid          |
| P     | Modelo/grid anterior           |
| 1     | Modo `GL_POINTS`               |
| 2     | Modo `GL_LINES`                |
| 3     | Modo `GL_TRIANGLES`            |
| F1    | Zoom in                        |
| F2    | Zoom out                       |
| H     | Mostrar/Ocultar ejes principales |
| J     | Mostrar/Ocultar ejes móviles     |
| ESC   | Cerrar ventana                 |

---

## Cómo agregar un modelo nuevo

Para añadir un nuevo archivo `.obj` al visualizador:

1. Copia el archivo dentro de: assets/obj

2. Edita la función `void Scene::loadModels()` y añade manualmente la ruta siguiendo este formato: "../assets/obj/<NombreDelArchivo>.obj"

