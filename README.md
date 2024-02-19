# cc-cpp


```bash
# run

conan install . --build=missing 

cd build/Release
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build .

ctest
```