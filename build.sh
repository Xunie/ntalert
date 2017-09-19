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
         -I 'C:\Program Files (x86)\SFML-mingw32\include');


LDFLAGS=( -L 'C:\Program Files (x86)\SFML-mingw32\lib'
          -l sfml-graphics-s
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

rm -f objects/*.o blobs.o

pushd "blobs"
for i in `ls`; do
    ld -o "../objects/$i.o" -b binary -r "$i" &
done
wait
popd

ld -r objects/*.o -o blobs.o
g++ src/*.cpp blobs.o -o main.exe "${CFLAGS[@]}" "${LDFLAGS[@]}"
