// vim: set foldmethod=marker :
// vim: set foldlevel=0 :
#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <cmath>
#include <atomic>
#include <new>

namespace primer {
    int concurrency = std::thread::hardware_concurrency();
    std::vector<std::thread *> threads;
    int max = 1;
    std::mutex locker;
    std::atomic_bool *sieve;

    void runner(unsigned long long startpoint, unsigned long long maximum) {
        for (int i = startpoint; i < maximum; i += concurrency) {
            unsigned long long i2 = i * i;
            for (int j = 0;; j++) {
                unsigned long long current = i2 + j * i;
                if (current >= max) break;
                sieve[current] = true;
            }
        }
    }
} // namespace primer

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() == 0 || (primer::max = std::stoll(args[0])) < 2) return 1;
    primer::sieve = new std::atomic_bool[primer::max];
    std::fill_n(primer::sieve, primer::max, false);
    unsigned long long maximum = ceil(sqrt(primer::max));
    for (int i = 0; i < primer::concurrency; i++) primer::threads.push_back(new std::thread(primer::runner, i + 2, maximum));
    for (std::thread *t : primer::threads) t->join();

    for (int i = 2; i < primer::max; i++) {
        if (!primer::sieve[i]) std::cout << i << '\n';
    }

    return 0;
}
