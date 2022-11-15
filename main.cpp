#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

double pi = atan(1) * 4;
int thread_count = 16;
long long int known_range = 0 * thread_count;
long long int range = 1000000 * thread_count;
double opr_time = 0.000000034; // manually calculated average time per operation in ms


void calc(std::pair<int, int>& closest_pair, double& smallest_diff, int index) {
    for (long long int x = known_range; x < range; x += thread_count) {
        for (long long int y = 0; y < range; y += thread_count) {
            double diff = abs(1 - ((x + index) * pi - (y + index) * 5));
            if (diff < smallest_diff) {
                closest_pair.first = x + index;
                closest_pair.second = y + index;
                smallest_diff = diff;
                //std::cout << std::to_string(index) + " found new low: " + std::to_string(diff) + "\n";
            }
        }
    }

    std::cout << std::to_string(index) + " is finished!\n";
}

int main(int argc, char **argv) {
    std::pair<int, int> closest;
    double smallest_diff = 2;

    std::cout << "ETA: " + std::to_string((range * range - known_range * known_range)*opr_time) + "ms\n";
    auto start = std::chrono::steady_clock::now();

    std::thread* myThreads = new std::thread[thread_count];
    for (int i = 0; i < thread_count; i++) {
    	myThreads[i] = std::thread(calc, std::ref(closest), std::ref(smallest_diff), i);
    }

    for (int i = 0; i < thread_count; i++) {
    	myThreads[i].join();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms\n";

    std::cout << std::to_string(smallest_diff) + ": (" + std::to_string(closest.first) + ", " + std::to_string(closest.second) + ")\n";
    return 1;
}
