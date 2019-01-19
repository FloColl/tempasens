cmake -H. -Bbuild
bear cmake --build build -- -j3
cp ./build/compile_commands.json ./compile_commands.json
