#include "benchmark.h"

#define TEST_DATA_SAMPLE_SIZE 1'000'000

int main() {
    using namespace std;
    using namespace catalogue;

    vector<int> container;

    cout << "\nSample container";
    cout << "    Data amount: " << TEST_DATA_SAMPLE_SIZE << "\n";
    measure_operation("Generation", [&]() {
        fill_with_random_values(container, TEST_DATA_SAMPLE_SIZE);
    }, "    ");

    {
        cout << "\nDefault c++ std::find()\n";
        measure_operation("find(container.begin(), container.end(), 512'321)", [&]() {
            auto it = find(container.begin(), container.end(), 512'321);
        }, "    ");
        measure_operation("find(container.begin(), container.end(), 1)", [&]() {
            auto it = find(container.begin(), container.end(), 1);
        }, "    ");
        measure_operation("find(container.begin(), container.end(), 12)", [&]() {
            auto it = find(container.begin(), container.end(), 12);
        }, "    ");
    }

    {
        std::cout << "\ncatalogue::HashCatalogue\n";
        HashCatalogue<int> catalogue([](const void* dataBucket) {
            return *((int*) dataBucket);
        });

        measure_operation("Generation", [&]() {
            catalogue.create(container);
        }, "    ");

        measure_operation("catalogue.index<int>(512'321)", [&]() {
            int* ptr = catalogue.index<int>(512'321);
        }, "    ");
        measure_operation("catalogue.index<int>(1)", [&]() {
            int* ptr = catalogue.index<int>(1);
        }, "    ");
        measure_operation("catalogue.index<int>(12)", [&]() {
            int* ptr = catalogue.index<int>(12);
        }, "    ");
    }

    {
        std::cout << "\ncatalogue::TreeCatalogue\n";
        TreeCatalogue<int> catalogue([](const void* dataBucket) {
            return *((int*) dataBucket);
        });

        measure_operation("Generation", [&]() {
            catalogue.create(container);
        }, "    ");

        measure_operation("catalogue.index<int>(512'321)", [&]() {
            int* ptr = catalogue.index<int>(512'321);
        }, "    ");
        measure_operation("catalogue.index<int>(1)", [&]() {
            int* ptr = catalogue.index<int>(1);
        }, "    ");
        measure_operation("catalogue.index<int>(12)", [&]() {
            int* ptr = catalogue.index<int>(12);
        }, "    ");
    }

    return 0;
}