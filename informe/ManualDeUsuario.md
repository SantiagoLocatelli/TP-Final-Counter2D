<img src='img/logo_fiuba.png?raw=true'>

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


## Configuración