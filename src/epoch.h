#include "network.h"
#include "time.h"

const char *ntpServer = "pool.ntp.org";

void initNtp() {
    configTime(0, 0, ntpServer);
}

unsigned long getTimeSinceEpoch() {
    time_t currentTime;
    struct tm timeInfo;

    if (!getLocalTime(&timeInfo)) {
        return 0;
    }
    time(&currentTime);

    return currentTime;
}
