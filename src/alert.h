#ifndef ALERT_H
#define ALERT_H
#include <cstdint>

class alert {
    static uint32_t player_threshold;
public:
    static uint32_t get_threshold();
    static void set_threshold( uint32_t x );
};

#endif /* ALERT_H */
