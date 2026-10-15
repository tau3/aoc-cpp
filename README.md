```bash
mkdir build
cd build
cmake ..
cmake --build .
./aoc
```

```bash
cd build
cppcheck --project=compile_commands.json --enable=all
```
