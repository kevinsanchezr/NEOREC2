#ifndef NEOREC_H
#define NEOREC_H

#include <windows.h>
#include <vector>

#define NR_RATE_125HZ 0
#define NR_RATE_250HZ 1
#define NR_RATE_500HZ 2
#define NR_RATE_1000HZ 3

#define NR_RANGE_mV150 0
#define NR_RANGE_mV300 1

#define NR_ERR_OK 0
#define NR_MODE_DATA 0

class NeoRec {
public:
    NeoRec(bool simulate = false);
    ~NeoRec();
    bool open();
    void close();
    bool setup(int mode, int rate, int range);
    bool start();
    void stop();
    std::vector<int> readEEG(int channelCount);

private:
    bool simulate;
    HINSTANCE hLib;
    int id;
    bool connected;
    bool running;

    typedef int(__stdcall* nb2ApiInit)();
    typedef int(__stdcall* nb2ApiDone)();
    typedef int(__stdcall* nb2GetCount)();
    typedef int(__stdcall* nb2GetId)(int index);
    typedef int(__stdcall* nb2Open)(int id);
    typedef int(__stdcall* nb2Close)(int id);
    typedef int(__stdcall* nb2Start)(int id);
    typedef int(__stdcall* nb2Stop)(int id);
    typedef int(__stdcall* nb2GetData)(int id, void* buffer, int length);

    nb2ApiInit _nb2ApiInit;
    nb2ApiDone _nb2ApiDone;
    nb2GetCount _nb2GetCount;
    nb2GetId _nb2GetId;
    nb2Open _nb2Open;
    nb2Close _nb2Close;
    nb2Start _nb2Start;
    nb2Stop _nb2Stop;
    nb2GetData _nb2GetData;
};

#endif // NEOREC_H
