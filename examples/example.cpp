#include <string>
#include <iostream>

#include "catalogue.h"

int main () {
    using namespace std;
    using namespace catalogue;
    
    {
        vector<int> container;
        for(auto i = 0; i < 1000; ++i)
            container.push_back(i);

        HashCatalogue<int> catalogue([](const void* dataBucket) {
            return *((int*) dataBucket);
        });

        catalogue.create(container);

        {
            int* value = catalogue.index<int>(9);
            std::cout << *value << "\n";
        }

        {
            int* value = catalogue.index<int>(2000); //Null
            std::cout << value << "\n";
        }
    }

    {
        vector<int> container;
        for(auto i = 0; i < 1000; ++i)
            container.push_back(i);

        TreeCatalogue<int> catalogue([](const void* dataBucket) {
            return *((int*) dataBucket);
        });

        catalogue.create(container);

        {
            int* value = catalogue.index<int>(9);
            std::cout << *value << "\n";
        }

        {
            int* value = catalogue.index<int>(2000); //Null
            std::cout << value << "\n";
        }
    }

    return 0;
}