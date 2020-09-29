cmake_minimum_required( VERSION 3.0 )

project( ntalert )

# this 'ere function adds the file as a blob to the target
function( blobber_file filename )
    #message( WARNING ${CMAKE_CURRENT_BINARY_DIR}/${filename}.o )
    add_custom_target( ${filename}.o
        ld -o "${CMAKE_CURRENT_BINARY_DIR}/${filename}.o" -b binary -r "${filename}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/blobs 
    )

    add_dependencies( ntalert ${filename}.o )

    target_link_libraries( ntalert
        "${CMAKE_CURRENT_BINARY_DIR}/${filename}.o"
    )
endfunction()

find_package( Threads )

add_subdirectory( git-submodules/sfml )

add_executable( ntalert
    src/main.cpp
    src/hud.cpp
    src/alert.cpp
    src/sound.cpp
    src/blobs.cpp
    src/network.cpp
)

target_link_libraries( ntalert
    sfml-graphics
    sfml-audio
    sfml-window
    sfml-network
    sfml-system

    Threads::Threads
)

blobber_file( ghost_equip.wav )
blobber_file( ghost_equip2.wav )
blobber_file( ghost_equip3.wav )
blobber_file( ghost_equip4.wav )
blobber_file( ghost_equip5.wav )
blobber_file( ghost_idle_loop.wav )
blobber_file( ghost_ping.wav )
blobber_file( background.png )
blobber_file( hud_blur.png )
blobber_file( hud_left.png )
blobber_file( hud_right.png )
blobber_file( hud_text.png )
blobber_file( hud_fill.png )
blobber_file( greenm03.ttf )

set_property( TARGET ntalert PROPERTY CXX_STANDARD 17 )
