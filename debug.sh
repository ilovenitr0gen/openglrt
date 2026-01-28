cmake -DCMAKE_BUILD_TYPE=Debug -S src -B build/debug 
(cd build/debug; make)
gdb -tui ./build/debug/project123
