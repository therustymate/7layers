x86_64-w64-mingw32-g++ -std=c++17 -O2 main.cpp -o listvss.exe \
    -lvssapi -lole32 -loleaut32 -luuid -luser32 \
    -static -static-libgcc -static-libstdc++ -lpthread