sudo apt-get update
sudo apt-get -y install libyaml-cpp-dev libsdl2* cmake libx11-dev xorg-dev libglu1-mesa-dev

rm -rf build
mkdir build
cd build

#instalo box2d
git clone https://github.com/erincatto/box2d
cd box2d
rm -rf build
mkdir build
cd build
cmake ..
make
make install


cd ..
cd ..
cmake ..
make