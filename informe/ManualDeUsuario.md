<img src='img/logo_fiuba.png?raw|true'>

# Taller de Programación I - (75.42/95.08)
# Trabajo Práctico Final - Counter-Strike-2D -

# Manual de Usuario

## Instalación
### Requerimientos software
El script `install.sh` instala la mayoría de las dependencias pero como base se necesita:
- Sistema operativo Linux Debian de 64 bits
- `g++` versión 7.5.0 o mayor.
- `git` versión 2.17.0 o mayor.

Dependencias instaladas por el instalador:
- `box2d`
- `SDL2`
- `yaml-cpp`

### Proceso de instalación
1. Clonar el repositorio: `git clone https://github.com/SantiagoLocatelli/TP-Final-Counter2D.git`
2. Dentro del directorio principal hay que darle permisos de ejecución al script `install.sh`: `chmod +x install.sh`
3. Correr el instalador con permisos de super-usuario: `sudo ./install.sh` 
4. El instalador puede tardar unos minutos porque debe instalar todas las dependencias y compilar/instalar los programas.

## Forma de uso
El trabajo práctico consta de tres programas. Un servidor, un cliente y un editor de mapas.

### Servidor
Lo primero que hay que hacer es correr el servidor especificando el puerto a usarse. El comando para hacer eso es `counter2dServer [puerto]`. Cuando se desea cerrar el servidor hay que escribir la letra 'q' por la terminal. El servidor va a esperar a que terminen todas las partidas y se va a cerrar.

### Cliente
Una vez que se corrió el servidor se puede correr el cliente. Para correr el cliente simplemente hay que hacer `counter2dClient`.
Lo primero que hay que hacer es ingresar la IP del dispositivo que está corriendo el servidor ("localhost" si es nuestra propia PC) y luego el puerto especificado al crear el servidor. Una vez hecho esto ya deberíamos estar conectados y se puede crear una partida.

Para crear una partida simplemente seguir las indicaciones en el menu, una vez un cliente creó la partida entonces el resto se puede unir. Mientras todos los clientes se van uniendo el resto queda en una pantalla de espera.

Una vez adentro de la partida los controles son los siguientes:
- `W A S D`: Moverse
- `Mouse`: Apuntar
- `Clic izquierdo`: Disparar. En el caso de la bomba se usa **para plantar**
- `1 2 3 4`: Cambiar de armas
- `R`: Recargar arma
- `G`: Soltar arma actual
- `E`: Desactivar bomba (solo anti-terroristas)
- `8 9 0`: Comprar armas

### Editor
**IMPORTANTE** debido a que se deben tener permisos de súper usuario el editor se debe correr con sudo.
ejemplo de uso: `sudo counter2dEditor`
Una vez inicia los menús se manes con el click izquierdo del mouse.
Si se decide crear un mapa se puede introducir un nombre a este y luego con la tecla ```ENTER``` se podrá empezar a editarlo.
```Click derecho``` para introducir texturas al mapa.
```ESCAPE``` abre el menú de opciones dentro del el para cambiar los números se puede hacer click en ellos y poner o borrar a gusto.
```TAB``` abre el menú donde se encuentran las texturas donde se puede hacer click izquierdo en la que se quiera usar.
```Mantener 1``` para mostrar los bombSites (se pueden arrastrar con click izquierdo).
```Mantener 2``` para mostrar los spawnSites (se pueden arrastrar con click izquierdo).
``Apretar 9``` para pausar o reanudar la musica.
```Apretar 3``` para ocultar o mostrar el texto de ayuda.
```CTRL S``` para guardar.

## Configuración
El archivo de configuración se encuentra en `/usr/local/share/counter2d/resources/server/GameConfig.yaml`. Se pueden modificar todos los valores para cambiar el comportamiento de distintos elementos del juego. A continuación menciono que representa cada valor.

### Game
- `roundTime`: Tiempo de cada ronda.
- `bombTime`: Tiempo para que la bomba explote.
- `bombDefuseDistance`: Distancia para desactivar la bomba.
- `buyTime`: Tiempo de compra al principio de cada ronda.
- `endTime`: Tiempo de descanso al final de cada ronda.
- `roundsPerSide`: Rondas a jugar por cada lado.
- `wonRoundMoney`: Dinero ganado al ganar una ronda.
- `lostRoundMoney`: Dinero ganado al perder una ronda.
- `terrorSkin`: Skin para los terroristas (puede ser 4, 5, 6, 7). 
- `counterSkin`: Skin para los terroristas (puede ser 0, 1, 2, 3).

### Player
- `health`: Vida del jugador.
- `speed`: Velocidad del jugador en metros por segundo.
- `defuseTime`: Tiempo para desactivar la bomba
- `startingMoney`: Dinero inicial.

### Weapons
- `maxDamage`: Daño máximo del arma.
- `minDamage`: Daño mínimo del arma.
- `spread`: Propagación del arma.
- `falloff`: Daño que se pierde por metro que recorre la bala.
- `speed`: Velocidad de disparo. Para el rifle es el tiempo entre ráfagas y para la bomba es el tiempo para plantar.
- `capacity`: Balas por cargador.
- `reloadTime`: Tiempo de recarga.
- `maxRange`: Distancia máxima que recorre la bala.
- `bullets`: (solo para la escopeta) Cantidad de balas por disparo.
- `burstTime`: (solo para el rifle) Tiempo entre balas en una misma ráfaga.