#include "NeoRec.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

NeoRec::NeoRec(bool simulate) : simulate(simulate), hLib(nullptr), id(0), connected(false), running(false) {
    if (!simulate) {
        hLib = LoadLibrary(L"../binNB2/x64/Debug/nb2mcs.dll");  
        if (hLib) {
            _nb2ApiInit = (nb2ApiInit)GetProcAddress(hLib, "nb2ApiInit");
            _nb2ApiDone = (nb2ApiDone)GetProcAddress(hLib, "nb2ApiDone");
            _nb2GetCount = (nb2GetCount)GetProcAddress(hLib, "nb2GetCount");
            _nb2GetId = (nb2GetId)GetProcAddress(hLib, "nb2GetId");
            _nb2Open = (nb2Open)GetProcAddress(hLib, "nb2Open");
            _nb2Close = (nb2Close)GetProcAddress(hLib, "nb2Close");
            _nb2Start = (nb2Start)GetProcAddress(hLib, "nb2Start");
            _nb2Stop = (nb2Stop)GetProcAddress(hLib, "nb2Stop");
            _nb2GetData = (nb2GetData)GetProcAddress(hLib, "nb2GetData");

            if (_nb2ApiInit) {
                _nb2ApiInit();
            }
        }
    }
    std::srand(std::time(nullptr));  // Inicializar generador de números aleatorios para simulación
}

NeoRec::~NeoRec() {
    if (!simulate && _nb2ApiDone) {
        _nb2ApiDone();
    }
    if (hLib) {
        FreeLibrary(hLib);
    }
}

bool NeoRec::open() {
    if (simulate) {
        connected = true;
        return connected;
    }
    if (running) return false;
    if (!hLib) return false;

    while (!connected) {
        int count = _nb2GetCount();
        if (count > 0) {
            id = _nb2GetId(0);
            int err = _nb2Open(id);
            if (err == NR_ERR_OK) {
                connected = true;
            }
        }
    }
    return connected;
}

void NeoRec::close() {
    if (simulate) {
        connected = false;
        return;
    }
    if (running) stop();
    if (connected) {
        _nb2Close(id);
        connected = false;
    }
}

bool NeoRec::setup(int mode, int rate, int range) {
    if (simulate) return true;
    if (!connected) return false;
    // Aquí deberías llamar a la función para configurar el dispositivo
    // como nb2SetDataSettings, nb2SetMode, etc.
    return true;
}

bool NeoRec::start() {
    if (simulate) {
        running = true;
        return true;
    }
    if (running || !connected) return false;
    int err = _nb2Start(id);
    if (err == NR_ERR_OK) {
        running = true;
        return true;
    }
    return false;
}

void NeoRec::stop() {
    if (simulate) {
        running = false;
        return;
    }
    if (!running) return;
    _nb2Stop(id);
    running = false;
}

std::vector<int> NeoRec::readEEG(int channelCount) {
    if (simulate) {
        std::vector<int> simulatedData(channelCount);
        for (int& value : simulatedData) {
            value = std::rand() % 100;  // Genera datos aleatorios para la simulación
        }
        return simulatedData;
    }
    if (!running) return {};

    std::vector<int> buffer(channelCount);
    int bytesRead = _nb2GetData(id, buffer.data(), buffer.size() * sizeof(int));
    if (bytesRead > 0) {
        return buffer;
    }
    return {};
}
