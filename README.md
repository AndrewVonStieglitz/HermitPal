Cookbooks:

Cloning:
git clone --recurse-submodules https://github.com/AndrewVonStieglitz/HermitPal.git
mkdir build
cd build
cmake ..
cd ..
cmake --build ./build --config Release

Adding a submodule:
git submodule add -b release-2.30.x https://github.com/libsdl-org/SDL.git external/SDL