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

g++ src/*.cpp audio/sounds.o img/images.o -o main.exe "${CFLAGS[@]}" "${LDFLAGS[@]}"
