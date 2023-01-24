#include<stdio.h>
#include<map>
#include<list>
#include<vector>
#include<chrono>

#define STRINGIFY(x) #x
#define MACRO(x)     STRINGIFY(x)

using namespace::std;


void test_optimization_fsplit_loops(int num_repeats) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::map<int, int > m;
    for (auto i = 0; i < num_repeats; i++) {
        if (i < num_repeats / 2) {
            m.emplace(std::make_pair(i,i));
        } else {
            m.emplace(std::make_pair(i,i));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("%s (flags: %s): %.3f seconds.\n", __func__, MACRO(FLAGS), elapsed.count() * 1e-9);
}


void test_optimization_fpeel_loops(int num_repeats) {
    auto begin = std::chrono::high_resolution_clock::now();
    float p = 1.0;
    for (auto i = 0; i < num_repeats; i++) {
        std::list<int > l;
        for (auto j = 0; j < 959; j++) {
            p += 1;
            l.push_back(i*j*p);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("%s (flags: %s): %.3f seconds.\n", __func__, MACRO(FLAGS), elapsed.count() * 1e-9);
}

void test_optimization_fpredictive_commoning(int num_repeats) {
    auto begin = std::chrono::high_resolution_clock::now();
    std::vector<int > v;
    v.reserve(num_repeats+3);
    for (auto i = 0; i < num_repeats; i++) {
        for (auto j = 0; j < num_repeats; j++) {
            v[j+2] = v[j] + v[j+1];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("%s (flags: %s): %.3f seconds.\n", __func__, MACRO(FLAGS), elapsed.count() * 1e-9);
}

int main(void)
{
    test_optimization_fsplit_loops(10000000);
    test_optimization_fpeel_loops(100000);
    test_optimization_fpredictive_commoning(100000);

    return 0;
}

