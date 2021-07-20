<img src='img/logo_fiuba.png?raw=true'>

# Taller de Programación I - (75.42/95.08)
# Trabajo Práctico Final - Counter-Strike-2D -

# Manual de Proyecto

## Integrantes
- Santiago Locatelli (104107)
- Bautista Xifro (101717)
- Tomás Rodríguez Dala (102361)

## Enunciado

El enunciado consiste en diseñar e implementar una recreación del Counter-Strike en su versión 2D.

Es un juego multijugador, que consta de dos equipos, los terroristas y lo anti-terroristas. Es un juego por rondas, y el objetivo en cada ronda de los terroristas es plantar una bomba, y el de lo anti-terroristas es impedir que los primeros planten la bomba.

Una ronda se da por terminada cuando sucede alguna de las siguientes situciones:

- Explota la bomba.
- Se desactiva la bomba.
- Se muere todo el equipo Anti-Terrorista.
- Se muere todo el equipo Terrorista, y la bomba no está plantada. En caso de que si, se deberá desactivar.
- Por falta de tiempo. En este caso, se le da por ganada a los Anti-Terroristas.

El sistema multijugador se debe realizar a través de un protocolo TCP, junto a un editor de mapas y motor gráfico 2D.

## División de tareas

Algunas tareas realizadas se llevaron a cabo por más de un integrante del grupo, el siguiente listado es un aproximado:

#### Juan Bautista xifro: Editor
- Menú inicial, servidor a unirse.
- Drag and Drop.
- Point and Click.
- Ajustar tamaño del mapa.
- Cargar a memoria archivos tipo yaml.
- Guardar mapas a archivos tipo ymal.
- Renderizado de texturas.
- Encapsulamiento en clases RAII de funciones SDL.
- Manejo de eventos Editor.

#### Tomás Rodriguez Dala

#### Santiago Locatelli

- Animaciones baśicas.
- Renderizado de texturas.
- Inclusión de sonido al juego.
- Renderizado del Hud.
- Armado de menu de compra.
- Menu inicial, crear o unirse a una partida.
- Logica de movimiento de camara.
- Logica del stencil.
- Representación de los objetos en el motor gráfico.
- Encapsulamiento en clases RAII de funciones SDL.

## Evolución del Proyecto

#### Semana 1 (08/06/2021)
- Servidor: Simulación baśica de colisiones.
- Cliente: Renderizado básico de texturas.
- Editor: Encapsulamiento de herramientas SDL.
#### Semana 2 (15/06/2021)
- Servidor: Protocolo básico.
- Cliente: Lógica de camara y movimiento de jugador.
- Editor: Investigación en documentación para el Editor.
#### Semana 3 (22/06/2021)
- Servidor: Envio y recepción de eventos en distintos hilos.
- Cliente: Animaciones, stencil. Primera representación del jugador en el motor gráfico.
- Editor: Primer modelo editor, se puede editar mapas.
#### Semana 4 (29/06/2021)
- Servidor: Integración Servidor-Cliente. Lógica básica de armas. Manejo multiclientes.
- Cliente: Integración Servidor-Cliente. Renderizado de armas, más animaciones. Primeros sonidos.
- Editor: Creación de mapas. Creación de FactoryMap.
#### Semana 5 (06/07/2021)
- Servidor: Manejo de rondas. Lógica de armas y disparos terminado.
- Cliente: Agregado de más sonidos. Primer versión Hud.
- Editor: Integracion Factory-Servidor. Mejora UI. Cambiar el tamaño del mapa.
#### Semana 6 (13/07/2021) 
- Servidor: Lógica de la tienda. Multipartidas.
- Cliente: Hud terminado. Corrección de errores. Integración con TextureManager.
- Editor: Corrección de errores. UI terminada.
#### Semana 7 (20/07/2021)
- Servidor: Corrección de errores. Últimos agregados en el protocolo.
- Cliente: Manejo de mensaje de ronda y partida terminada. Menu de inicio, crear o unirse partida. Corrección de errores. Menu de loading.
- Editor: Menu de inicio, unirse al servidor. Corrección de errores. Agregado de texturas.  


## Inconvenientes Encontrados

La biblioteca Box2D se maneja mejor en metros que en pixeles, y SDL se maneja en pixeles, por lo que esto llevó a una conversión que provocó algunos obtáculos.

Por parte del servidor, el simulamiento de los disparos, armas.

Por parte del editor, el ajuste del tamaño del mapa manteniendo el orden de las texturas.

## Análisis de Puntos Pendientes

Por parte del cliente, un mejor manejo del Stencil. Y mostrar las estadísticas de cada jugador al finalizar la partida.

Por parte del Editor, un mejor uso de las imagenes *tilemaps* y un modelado de las clases un poco mas modularizado.

## Herramientas

- Box2D

Para la simulación de colisiones, disparos y objetos físicos.
- SDL

Para la realización del motor gráfico, y el editor de mapas.
- Yaml

Parseo de archivos.
- CMake

Automatización compilación del proyecto.
- Make

Integración con cmake para la compilación de proyecto.
- Valgrind

Manejo de errores de memoria.
- GDB

Debugg de errores.
- Git/GitHub

Para control de versiones y alojamiento del proyecto.
- Visual Studio Code

Desarrollo del código fuente.
- Discord

Reuniones y discutir sobre cuestiones de interés.

## Conclusiones

Nos encontramos con un proyecto grande, para el tiempo dado, lo cual significó un desafío para nosotros. Las primeras semanas fueron lentas debido a la gran cantidad de documentación a leer, pero a medida que fue pasando el tiempo íbamos agregando más y más features.

Pero podemos decir que nos terminamos llevando una experiencia agradable, ya que como grupo nos entendimos bien, y pudimos afrontar los obstáculos que se fueron dando a medida que se iba avanzando.

Reconocemos que la primer entrega no fue la mejor, pero en esas dos semanas que restaban compensamos mucho los requisitos que faltaban.

Entonces en conclusión, nos llevamos una buena experiencia, en la cual pudimos solidificar los conocimientos dados en la materia, ya sea desde la teoría como la práctica con las nuevas herramientas y técnicas de programación sumándole el conocimiento de las nuevas librerías Box2d y SDL y una gran experiencia de la programación orientada a eventos.
