#include <iostream>
#include <iomanip>
#include <random>

#define DO_PRINT    1
#define ITERS       100
#define MY_RAND_MAX 10

int main() {
    std::random_device rd; // use hardware entropy if available, PRNG otherwise
    std::mt19937_64 mersenne(rd()); // initialize mersenne twister
    int count[MY_RAND_MAX] = {0};
    double iter_sum[MY_RAND_MAX] = {0.0};

    // generate random numbers in [0, MY_RAND_MAX)
    std::cout << "* Generating random numbers (mersenne twister)...\n";
    for (int i = 0; i < ITERS; i++) {
        int random = mersenne() % MY_RAND_MAX;
#ifdef DO_PRINT
        std::cout << std::setw(2) << random << " ";
        if ((i+1) % 10 == 0) {
            std::cout << std::endl;
        }
#endif
        count[random]++; // count # of occurences
        iter_sum[random] += i; // sum up occurence iteration
    }
    std::cout << std::endl;

    // verify uniform distribution (counts should be similar)
    std::cout << "* Verifying uniform distribution..." << std::endl;
    for (int i = 0; i < MY_RAND_MAX; i++) {
        std::cout << "Count for " << i << ": " << count[i] << "\n";
    }
    std::cout << std::endl;

    // verify dimensionality (average of iter_sum should be half of ITERS)
    std::cout << "* Verifying dimensionality..." << std::endl;
    for (int i = 0; i < MY_RAND_MAX; i++) {
        std::cout << "Occurence iteration average for " << i << ": " <<
            (iter_sum[i] / count[i]) << "\n";
    }
    std::cout << std::endl;

    return 0;
}
