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

```cpp
namespace sim // Espacio de nombre es sim, de simulacion
{
    struct Particle;
}
```

Desde fuera, el tipo de esta estructura de datos se ve como `sim::Particula`, con el fin quitar ambiguedad de "con que tipo (a nivel de codigo) de particula estamos trabajando".


Ahora queremos que sea visible en la pantalla, para ello podemos utilizar el RenderItem de la plantilla.
La idea no es heredar a partir de los datos de la Particula logica, creo que aqui es mejor decir que entre esos dos tipos de particula mantienen una relacion de asociacion que una relacion de "es una particula".

```cpp
struct ParticulaEntidad
{
    sim::Particula pv_particula;
    RenderItem* pv_renderizable;
    PxTransform transform; //???, justo abajo
}
```

// TODO
Estos nombres son horrorosos y no se entiende, buscar un nombre mejor.


Ahora... En el RendetItem necesita un puntero de PxTransform para poder operar sobre la posicion directamente (y luego para la rotacion), porque dentro de PxTransform tiene una posicion y una rotacion.

La posicion ya lo tengo en la particula logica, el asunto ahora es, a nivel de implementacion, como hacer que la posicion de PxTransform sea una referencia a la posicion de la particula logica?

Una forma fea pero mas o menos entendible y simple es hacer que cada vez que se actualiza la posicion logica, actualizar tambien el valor de la posicion de PxTransform, aunque supone un pequeño coste de 3 numeros flotantes, porque tendriamos una duplicacion de datos.

Otra forma seria tirar el PxTransform, y hacer algo como esto:
```cpp
struct Transform 
{
	union {
		Position struc;
		Pointer<Position> pointer;
	}position;

	union {
		Vector4D struc;
		Pointer<Vector4D> pointer;
	}quaternion;

};
```

Si queremos utilizar la posicion de transform directamente, podemos utilizarlo, pero si queremos utilizar de un lugar externo, podemos pasar un puntero. A coste de 2 punteros