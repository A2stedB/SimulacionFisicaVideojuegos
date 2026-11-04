La idea es representa de manera logica una particula por un lado.

Luego cuando renderizamos, asociamos esa particula a una entidad visible. Pero lo que me interesa y lo importante es que ambas cosas estan separadas

Con esta idea, a nivel de implementacion, una particula logica se representa son datos que lo forma, tiene:
- Posicion
- Velocidad
- Acceleracion

Con esto ya es suficiente realizar una simulacion fisica con fisica basica de forma no visible.
Lo separo en una parte logica porque en el futuro si tuviera que hacer una simulacion de fisica, solo tendria que coger la parte logica y ya estaria en disposicion de hacer una simulacion, sin importarme de como se ve visualmente.

