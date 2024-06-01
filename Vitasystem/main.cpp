#include <iostream>
#include <vector>
#include "NeoRec.h"

int main() {
    bool simulate = true;  // false para el modo real
    NeoRec neorec(simulate);

    if (!neorec.open()) {
        std::cerr << "Failed to open device." << std::endl;
        return 1;
    }

    if (!neorec.setup(NR_MODE_DATA, NR_RATE_250HZ, NR_RANGE_mV300)) {
        std::cerr << "Failed to setup device." << std::endl;
        neorec.close();
        return 1;
    }

    if (!neorec.start()) {
        std::cerr << "Failed to start data acquisition." << std::endl;
        neorec.close();
        return 1;
    }

    std::cout << "Reading EEG data..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::vector<int> data = neorec.readEEG(16);
        if (!data.empty()) {
            for (int value : data) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
        Sleep(1000);  // Lee los datos cada segundo
    }

    neorec.stop();
    neorec.close();
    return 0;
}
