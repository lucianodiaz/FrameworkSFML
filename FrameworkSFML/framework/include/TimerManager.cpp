#include "TimerManager.h"
#include <set>

int TimerManager::createTimer(float duration, std::function<void()> callback, bool loop)
{
    int timerID = nextTimerID++;

    timers[timerID] = { sf::Clock(),sf::seconds(duration),loop,callback };

    return timerID;
}

bool TimerManager::isTimerExpired(int timerID)
{
    if (timers.find(timerID) != timers.end())
    {
        return timers[timerID].clock.getElapsedTime() >= timers[timerID].duration;
    }
    return false;
}

void TimerManager::removeTimer(int timerID)
{
    timers.erase(timerID);
}

void TimerManager::update() {
    std::set<int> timersToRemove;

    for (auto it = timers.begin(); it != timers.end(); ++it) {
        int timerID = it->first;
        TimerInfo& timerInfo = it->second;

        if (isTimerExpired(timerID)) {
            if (timerInfo.callback) {
                timerInfo.callback();
            }

            if (timerInfo.loop) {
                timerInfo.clock.restart();
            }
        }
    }

    for (auto it = timers.begin(); it != timers.end(); ++it) {
        int timerID = it->first;
        TimerInfo& timerInfo = it->second;

        if (isTimerExpired(timerID) && !timerInfo.loop) {
            timersToRemove.insert(timerID);
        }
    }

    for (int timerID : timersToRemove) {
        timers.erase(timerID);
    }
}
