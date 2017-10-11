#include <iostream>
#include <limits>
#include <algorithm>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

int max = 0;

std::vector<std::string> args;
std::vector<std::thread *> threads;
int concurrency = std::thread::hardware_concurrency();

std::mutex num_mutex;
std::mutex out_mutex;
std::priority_queue<int> log;

int current_number = 1;
int inc = 2;

bool simple(int p) {
    if (p <= 1) return false;
    if (p <= 3) return true;
    if (p % 2 == 0 || p % 3 == 0) return false;
    for (int i = 5; i * i <= p; i += 6)
        if (p % i == 0 || p % (i + 2) == 0) return false;
    return true;
}

auto is_prime = simple;

int last_biggest = 0;

void non_sorted(int cp) {
    std::cout << cp << "\n";
}

void sorted(int cp) {
    log.push(cp);
}

auto output = non_sorted;

void next_prime() {
    int cp = 0;
    do {
        num_mutex.lock();
        cp = (current_number += inc);
        num_mutex.unlock();
        if (cp > max) return;
        if (is_prime(cp)) {
            out_mutex.lock();
            log.push(cp);
            out_mutex.unlock();
        }
    } while (cp < max);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv + 1, argv + argc);
    args.insert(args.end(), arguments.begin(), arguments.end());
    if (args.size() == 0 || (max = std::stoi(args[0])) < 2) return 1;

    if (std::count(args.begin(), args.end(), std::string("--sort")) > 0) output = sorted;

    /*
     * TODO: check args[2] for algorithm
     */

    // 1:37 bodge
    std::cout << 2 << "\n";
    for (int i = 0; i < concurrency; i++) threads.push_back(new std::thread(next_prime));

    for (std::thread *t : threads) t->join();
    while (!log.empty()) {
        std::cout << log.top() << "\n";
        log.pop();
    }

    return 0;
}
