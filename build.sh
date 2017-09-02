#!/bin/bash

CFLAGS=( -mwindows
         -std=c++17
         -Wall
         -Wextra
         -D SFML_STATIC
#         -DWIN32
         -O3
#         -fopenmp
#         -ffast-math
         -I 'C:\Program Files (x86)\SFML\include');


LDFLAGS=( -L 'C:\Program Files (x86)\SFML\lib'
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

#          -l ws2_32

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

rm -f objects/*.o

for folder in audio images blobs
    for i in `ls $folder`; do
        objcopy -I binary -O pe-x86-64 -B i386:x86-64 "$folder/$i" "objects/$i.o"
    done
done

ld -r objects/*.o -o blobs.o
g++ src/*.cpp blobs.o -o main.exe "${CFLAGS[@]}" "${LDFLAGS[@]}"







