# Atari Assault - CPCTelera - Amstrad CPC

Este programa de ejemplo está basada en esta serie de vídeos de [Fran Gallego](https://twitter.com/frangallegobr), también conocido como [Profesor Retroman](https://www.youtube.com/channel/UCSdIAKvPxlB3VlFDCBvI46A) en Youtube:

* [GameEngine ECS: Programando un Atari Assault - part 1](https://www.youtube.com/watch?v=urrSHTzpKyc).
* [GameEngine ECS: Programando un Atari Assault - part 2](https://www.youtube.com/watch?v=dqTYFwjGKqA).
* [GameEngine ECS: Programando un Atari Assault - part 3](https://www.youtube.com/watch?v=MkvuAxukcVY).

Este proyecto se ha desarrollado en macOS, pero se supone que en Linux o Windows funcionará de forma similar.

Para construir el proyecto desde cero, teniendo instalada la [CPCTelera](https://github.com/lronaldo/cpctelera) correctamente, tecleamos `make clean && make`.

Para lanzarlo en el emulador [WinApe](http://winape.net/), tecleamos `cpct_winape -a`.

Para editar los gráficos hemos usado Aseprite, que implementa tanto píxeles horizontales (2:1) como la paleta de colores del Amstrad CPC. No obstante, cualquier herramienta de edición de gráficos que permita dibujar píxel a píxel es perfectamente válida.

## Consideraciones acerca del código

Se explican todas ellas en los vídeos. A continuación se citan las más relevantes (bajo nuestro criterio).

* Por simplicidad, la lectura de teclado se hace desde el sistema de físicas.
* El manager del juego es el encargado de gestionar todas las reglas. Por tanto, también gestionará la creación de entidades, ya que depende de las reglas y de las circunstancias del juego. Los sistemas se hablarán con el manager del juego si necesitan crear entidades.



## Versiones


## Funcionalidades propuestas para desarrollar

