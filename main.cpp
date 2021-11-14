#include <random>
#include <chrono>
#include <iostream>

#include "storage.h"

class Stub {
public:
    int i;

    explicit Stub(int i_) : i(i_) {}

    void inc() {
        i++;
    }
};

const int INSERT_ELEMENT_BEFORE = 0;
const int INSERT_ELEMENT_AFTER = 1;
const int DELETE_ELEMENT = 2;
const int CALL_ELEMENT_METHOD = 3;

int getRandomInRange(int start, int end) {
    static std::default_random_engine gen((std::random_device()()));

    std::uniform_int_distribution<> dis(start, end);
    return dis(gen);
}

void benchmark(int count) {
    Storage<Stub> storage;

    int size = count;
    for (int i = 0; i < count; i++) {
        storage.addBack(Stub(i));
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < count; i++) {
        storage.toFirst();
        storage.nextN(getRandomInRange(0, size - 1));

        auto action = getRandomInRange(0, 3);
        switch (action) {
            case INSERT_ELEMENT_BEFORE:
                storage.addAfter(Stub(i));
                size++;
                break;
            case INSERT_ELEMENT_AFTER:
                storage.addBefore(Stub(i));
                size++;
                break;
            case DELETE_ELEMENT:
                storage.popCurrent();
                size--;
                break;
            case CALL_ELEMENT_METHOD:
                storage.getCurrent().inc();
                break;
            default:
                std::cout << "undefined action: " << action << "\n";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<int64_t, std::nano> ns = end - start;

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(ns);

    std::cout << "benchmark\t" << count << "\t\t" << ms.count() << " ms\n";
}

int main() {
    benchmark(1000000);
    benchmark(5000000);
    benchmark(10000000);

    return 0;
}
