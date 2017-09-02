#ifndef NETWORK_H
#define NETWORK_H
#include <atomic>
#include <mutex>
#include <thread>
#include <SFML/Network.hpp>

// yay, crossplatform!
#ifdef _WIN32
#include <Winsock2.h>
#else
#include <arpa/inet.h>
#endif /* WIN32 */

class network {
    static std::thread thrd;

    static std::atomic<bool> running;
    static std::atomic<bool> valid;
    static std::atomic<uint32_t> num_players;

    static std::mutex last_update_mtx;
    static sf::Clock  last_update;

public:
    static void init();
    static void cleanup();
    static uint32_t get_num_players();
    static bool is_valid();
    static sf::Time since_last_update();

private:
    static void grab_loop();
    static void update_num_players();
};

#endif /* NETWORK_H */
