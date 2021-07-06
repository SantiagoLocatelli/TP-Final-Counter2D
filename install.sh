# Instalo todas las dependencias menos box2d
sudo apt-get update
sudo apt-get -y install libyaml-cpp-dev libsdl2* cmake libx11-dev xorg-dev libglu1-mesa-dev

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


# Vuelvo a la carpeta build y compilo el TP
cd ..
cd ..
cmake ..
make