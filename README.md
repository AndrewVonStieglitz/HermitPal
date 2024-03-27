git clone --recurse-submodules https://github.com/AndrewVonStieglitz/HermitPal.git
mkdir build
cd build
cmake ..
cd ..
cmake --build ./build --config Release
