# Taller de Programación - Cátedra Veiga - FIUBA
# Trabajo Práctico Counter-Strike-2D

## Link al repositorio: https://github.com/SantiagoLocatelli/TP-Final-Counter2D

## Integrantes
- Santiago Locatelli (104107)
- Bautista Xifro (101717)
- Tomás Rodríguez Dala (102361)

## Instrucciones de instalación

1. Correr `sudo ./install.sh` y esperar a que termine
2. Los ejecutables se encuentran en `/build/bin`
3. Para correr el servidor hacer: `./Server [puerto]`
4. Para correr el cliente hacer: `./Client [puerto]`
5. Para correr el editor hacer: `./Editor`

## Instrucciones de ejecución

Para iniciar el juego hay que seguir estos pasos:

1. Correr el servidor
2. Correr todos los clientes que vayan a jugar (tiene que ser más de uno)
3. Escribir "s" en el servidor para empezar


### Descripción del juego

El juego consiste en una partida multijugador "todos contra todos" que termina cuando queda un sólo jugador vivo. Todos los jugadores empiezan con una pistola y hay un arma poderosa en el medio que mata de un disparo.

Los controles son los siguientes:
- W A S D para moverse
- Mover el mouse para apuntar
- Clic izquierdo para disparar

## Instrucciones del Editor

- ```Click derecho:``` en la textura a cambiar para cambiar la textura por la que se tiene seleccionada.
- ```Scroll rueda del mouse:``` cambia el tipo de textura que se quiere colocar (se puede ver que textura se tiene en el titulo de la ventana).
- ```Mantener presionado la tecla 1:``` muestra los 2 sitios de bombas, estos pueden ser agarrados y soltados con el click izquierdo del mouse.
- ```Mantener presionado la tecla 2:``` muestra los 2 sitios de aparición de los jugadores, estos pueden ser agarrados y soltados con el click izquierdo del mouse.
- ```ESCAPE:``` muestra la pantalla del menú de opciones. Presione nuevamente la tecla para salir del menú.

### Instrucciones del Menú de Opciones:
Este menú permite modificar el largo y el ancho de los sitios de aparición y de bombas.
- ```Click izquierdo:``` sobre los números que se desean modificar para seleccionarlos.
- ```Tecla de borrado <-:``` para borrar en el numero seleccionado.
- ```Teclas del 0 al 9:``` números que se desean introducir en el numero seleccionado.
