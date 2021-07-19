# Instalo todas las dependencias menos box2d
apt-get update
apt-get -y install libyaml-cpp-dev libsdl2* cmake libx11-dev xorg-dev libglu1-mesa-dev

# Creo una carpeta build
rm -rf build
mkdir build
cd build

# Instalo box2d
git clone https://github.com/erincatto/box2d
cd box2d
rm -rf build
mkdir build
cd build
cmake ..
make
make install


# Vuelvo a la carpeta build y compilo el programa
cd ..
cd ..
cmake ..
make

# Muevo los ejecutables y los recursos a la carpeta compartida
cp ./bin/counter2dEditor /usr/local/bin/
cp ./bin/counter2dClient /usr/local/bin/
cp ./bin/counter2dServer /usr/local/bin/

mkdir -p /usr/local/share/counter2d

cp -r ../resources /usr/local/share/counter2d/

