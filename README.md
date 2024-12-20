# Return to the Jungle

> __ℹ️ **Repositorio para el desarrollo de un videojuego en C++ para la asignatura "Software de Entretenimiento y Videojuegos"**__

![Fondo_menu.jpg](docs/imagenes/Portada.jpg)

## Concepto

El concepto del juego es un plataformas en 2D donde los protagonistas son 5 animales

El objetivo de estos animales es pasar a través de la ciudad para poder volver a la jungla. Para conseguirlo, deberán lidiar con obstáculos y enemigos

## Personajes

Cada uno de nuestros personajes dispone de una habilidad única que le permitirá completar el nivel o obtener ciertos coleccionables

| Personaje | Habilidad                                                            | Sprite                                                                                    |
| ---       | ---                                                                  | ---                                                                                       |
| Mono      | Trepar por lianas                                                    | <img src="docs/imagenes/Mono.png" alt="Mono" style="width:200px; height:auto;">           |
| Elefante  | Destrozar cajas con su trompa                                        | <img src="docs/imagenes/Elefante.png" alt="Elefante" style="width:200px; height:auto;">   |
| Serpiente | Reptar por huecos por los que el resto de personajes no podrán pasar | <img src="docs/imagenes/Serpiente.png" alt="Serpiente" style="width:200px; height:auto;"> |
| Tucán     | Doble salto                                                          | <img src="docs/imagenes/Tucan.png" alt="Tucan" style="width:200px; height:auto;">         |
| Capibara  | Capacidad para nadar                                                 | <img src="docs/imagenes/Capibara.png" alt="Capibara" style="width:200px; height:auto;">   |

Cada personaje, además de sus habilidades únicas, dispone de características diferentes en cuanto a velocidad y capacidad de salto

Cada nivel tendrá un personaje prefijado (necesario para poder completar dicho nivel) y requerirá de dos personajes más que elegirá el jugador. Su elección condicionará la posibilidad de conseguir o no todos los coleccionables del nivel

## Sprites

Todos los sprites de personajes y enemigos han sido desarrollados a mano utilizando herramientas como Piskel

## Niveles

Los niveles se han desarrollado siguiendo un diseño basado en tiles que se representan como caracteres en ficheros de texto

## Como Utilizar

El videojuego ha sido desarrollado enteramente en C++ y se ha utilizado la librería de gráficos **SDL2 - Simple DirectMedia Layer**.

Para poder iniciar el juego se requiere que las librerías se ubiquen en una carpeta C:/videojuegos de la siguiente manera:

![LibreriasEnCarpeta.png](docs/imagenes/librerias-carpeta-videojuegos.png)

El juego se inicia en Visual Studio de Microsoft configurando su inicio en `x86`

![Configuracionx86.png](docs/imagenes/x86-vs.png)
