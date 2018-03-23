// vim: set foldmethod=marker :
// vim: set foldlevel=0 :
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <new>
#include <string>
#include <thread>
#include <vector>

namespace primer {
    static unsigned concurrency = std::thread::hardware_concurrency();
    static uint64_t max = 1;
    static std::atomic_bool *sieve;

    static void runner(uint64_t startpoint, uint64_t maximum) {
        for (uint64_t i = startpoint; i < maximum; i += concurrency) {
            uint64_t i2 = i * i;
            for (uint64_t j = 0;; j++) {
                uint64_t current = i2 + j * i;
                if (current >= max) break;
                sieve[current] = true;
            }
        }
    }
} // namespace primer

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() == 0 || (primer::max = std::stoull(args[0])) < 2) return 1;

    primer::sieve = new std::atomic_bool[primer::max];
    std::fill_n(primer::sieve, primer::max, false);
    uint64_t maximum = uint64_t(floor(sqrt(primer::max)));

    std::vector<std::thread *> threads;
    for (unsigned i = 0; i < primer::concurrency; i++)
        threads.push_back(new std::thread(primer::runner, i + 2, maximum));
    for (std::thread *t : threads) t->join();

    for (uint64_t i = 2; i < primer::max; i++) {
        if (!primer::sieve[i]) std::cout << i << '\n';
    }

    return 0;
}
