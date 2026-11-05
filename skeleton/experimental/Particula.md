La idea es representa de manera logica una particula por un lado.

Luego cuando renderizamos, asociamos esa particula a una entidad visible. Pero lo que me interesa y lo importante es que ambas cosas estan separadas

Con esta idea, a nivel de implementacion, una particula logica se representa son datos que lo forma, tiene:
- Posicion
- Velocidad
- Acceleracion

Con esto ya es suficiente realizar una simulacion fisica con fisica basica de forma no visible a nivel de computo.
Lo separo en una parte logica porque en el futuro si tuviera que hacer una simulacion de fisica, solo tendria que coger la parte logica y ya estaria en disposicion de hacer una simulacion, sin importarme de como se ve visualmente.
Lo guardamos en un namespace para categorizar, para saber que cosas de codigo realmente pertenece a la parte de simulacion de fisica:

```cpp
namespace sim // Espacio de nombre es sim, de simulacion
{
    struct Particle;
}
```

Desde fuera, el tipo de esta estructura de datos se ve como `sim::Particula`, con el fin quitar ambiguedad de "que particula es este".


Ahora queremos que sea visible en la pantalla, para ello podemos utilizar el RenderItem de la plantilla.
La idea no es heredar a partir de los datos de la Particula logica, creo que aqui es mejor decir que entre esos dos tipos de particula mantienen una relacion de asociacion que una relacion de "es una particula".

```cpp
struct ParticulaEntidad
{
    sim::Particula pv_particula;
    RenderItem* pv_renderizable;
}
```

// TODO
Estos nombres son horrorosos y no se entiende, buscar un nombre mejor.

