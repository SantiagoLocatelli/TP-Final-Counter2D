sudo apt-get update
sudo apt-get -y install libbox2d-dev libyaml-cpp-dev libsdl2-2.0 cmake

mkdir build
cd build
cmake ..
make