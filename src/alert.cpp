#include "alert.h"

uint32_t alert::player_threshold = 4;

uint32_t alert::get_threshold() {
    return player_threshold;
}

void alert::set_threshold( uint32_t x ) {
    player_threshold = x;
}
