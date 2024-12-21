<h1 align="center">Return to the Jungle</h1>

<p align="center">ℹ️ Repositorio para el desarrollo de un videojuego en C++ para la asignatura "Software de Entretenimiento y Videojuegos"</p> 

<p align="center">
  <img src="docs/multimedia/Portada.jpg" alt="Portada Return to the Jungle" />
</p>

## Vídeo

https://github.com/user-attachments/assets/bcb6f4cd-9636-449c-8ff1-1d6ba8606789

## Concepto

El concepto del juego es un plataformas en 2D donde los protagonistas son 5 animales

El objetivo de estos animales es pasar a través de la ciudad para poder volver a la jungla. Para conseguirlo, deberán lidiar con obstáculos y enemigos

## Personajes

Cada uno de nuestros personajes dispone de una habilidad única que le permitirá completar el nivel o obtener ciertos coleccionables

| Personaje | Habilidad                                                            | Sprite                                                                                      |
| ---       | ---                                                                  | ---                                                                                         |
| Mono      | Trepar por lianas                                                    | <img src="docs/multimedia/Mono.png" alt="Mono" style="width:200px; height:auto;">           |
| Elefante  | Destrozar cajas con su trompa                                        | <img src="docs/multimedia/Elefante.png" alt="Elefante" style="width:200px; height:auto;">   |
| Serpiente | Reptar por huecos por los que el resto de personajes no podrán pasar | <img src="docs/multimedia/Serpiente.png" alt="Serpiente" style="width:200px; height:auto;"> |
| Tucán     | Doble salto                                                          | <img src="docs/multimedia/Tucan.png" alt="Tucan" style="width:200px; height:auto;">         |
| Capibara  | Capacidad para nadar                                                 | <img src="docs/multimedia/Capibara.png" alt="Capibara" style="width:200px; height:auto;">   |

Cada personaje, además de sus habilidades únicas, dispone de características diferentes en cuanto a velocidad y capacidad de salto

Cada nivel tendrá un personaje prefijado (necesario para poder completar dicho nivel) y requerirá de dos personajes más que elegirá el jugador. Su elección condicionará la posibilidad de conseguir o no todos los coleccionables del nivel

## Sprites

Todos los sprites de personajes y enemigos han sido desarrollados a mano utilizando herramientas como Piskel

## Niveles

Los niveles se han desarrollado siguiendo un diseño basado en tiles que se representan como caracteres en ficheros de texto

## Controles

| Teclas                                                                                                                         | Función                             |
| ---                                                                                                                            | ---                                 | 
| <p align="center"><img src="docs/multimedia/WASD.png" alt="Teclas de Movimiento" width="200px" heigh="auto" /></p>             | Desplazarse y saltar                | 
| <p align="center"><img src="docs/multimedia/C.png" alt="Tecla de Cambio de Personaje" width="100px" heigh="auto"/></p>         | Cambiar de personaje                | 
| <p align="center"><img src="docs/multimedia/1.png" alt="Tecla Pantalla Completa" width="100px" heigh="auto"/></p>              | Redimensionar la pantalla del juego | 
| <p align="center"><img src="docs/multimedia/Esc.png" alt="Tecla Salir" width="100px" heigh="auto"/></p>                        | Salir del juego                     |
| <p align="center"><img src="docs/multimedia/SpaceBar.png" alt="Tecla Romper Cajas (Elefante)" width="200px" heigh="auto"/></p> | Romper cajas con el elefante        |







## Como Utilizar

El videojuego ha sido desarrollado enteramente en C++ y se ha utilizado la librería de gráficos **SDL2 - Simple DirectMedia Layer**.

Para poder iniciar el juego se requiere que las librerías se ubiquen en una carpeta C:/videojuegos de la siguiente manera:

![LibreriasEnCarpeta.png](docs/multimedia/librerias-carpeta-videojuegos.png)

El juego se inicia en Visual Studio de Microsoft configurando su inicio en `x86`

![Configuracionx86.png](docs/multimedia/x86-vs.png)
