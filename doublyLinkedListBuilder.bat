md bin
clang.exe -Iinclude -o bin\doublyLinkedList.lib src\doublyLinkedList.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\doublyLinkedList.exe src\doublyLinkedList.c -Lbin -l doublyLinkedList