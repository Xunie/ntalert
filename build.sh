#!/bin/bash

CFLAGS=( -mwindows
         -std=c++1z
         -Wall
         -Wextra
         -static
         -static-libgcc
         -static-libstdc++ 
         -D SFML_STATIC

#         -DWIN32
         -O3
#         -fopenmp
#         -ffast-math
        );

LDFLAGS=( -l sfml-graphics-s
          -l sfml-audio-s
          -l sfml-window-s
          -l sfml-network-s
          -l sfml-system-s
          -l opengl32
          -l freetype
          -l jpeg

          -l winmm
          -l gdi32

          -l ws2_32

          -l openal32
          -l flac
          -l vorbisenc
          -l vorbisfile
          -l vorbis
          -l ogg

#          -lfltk_jpeg
#          -lfltk
#          -lole32
#          -lcomctl32
#          -lopengl32
#          -lgdi32
#          -lwinmm
#          -luuid
#          -lkernel32
#          -luser32
         );


if   [[ $MSYSTEM = "MINGW32" ]]; then
     CFLAGS+=(-I 'C:\Program Files (x86)\SFML-mingw32\include')
    LDFLAGS+=(-L 'C:\Program Files (x86)\SFML-mingw32\lib')
elif [[ $MSYSTEM = "MINGW64" ]]; then
     CFLAGS+=(-I 'C:\Program Files (x86)\SFML-mingw64\include')
    LDFLAGS+=(-L 'C:\Program Files (x86)\SFML-mingw64\lib')
else
    echo "MINGW required for compilation"
    echo "Or just write your own build script a bit, ya big fat dummy :3"
    exit
fi


# blobs stuff
rm -f objects/*.o blobs.o

pushd "blobs"
for i in `ls`; do
    ld -o "../objects/$i.o" -b binary -r "$i" &
done
wait
popd

ld -r objects/*.o -o blobs.o

# icon stuff
windres icon.rc -O coff -o icon.res

g++ src/*.cpp blobs.o icon.res -o main.exe "${CFLAGS[@]}" "${LDFLAGS[@]}"
