#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

typedef std::chrono::duration<int> seconds_t;
typedef std::chrono::duration<int,std::ratio<60>> minutes_t;
typedef std::chrono::duration<int,std::ratio<60*60>> hours_t;

bool paused = false;

void readthread()
{
    while(true) {
        std::this_thread::sleep_for (chrono::milliseconds(500));

        // check input
        (void)std::cin.get();
        paused ^= 1;
    }
}

int main()
{
    auto t0 = chrono::steady_clock::now();
    auto t1 = chrono::steady_clock::now();
    auto diff = t0-t0;

    // create IO thread
    std::thread thr(readthread);
    while(true) {
        std::this_thread::sleep_for (chrono::milliseconds(100));
        
        if(!paused) {
            // new time
            t0 = t1;
            t1 = chrono::steady_clock::now();
            diff += (t1-t0);

            // compute duration
            int h = chrono::duration_cast<chrono::hours>(diff).count();
            int m = chrono::duration_cast<chrono::minutes>(diff).count();
            int s = chrono::duration_cast<chrono::seconds>(diff).count();
            int ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
            cerr << setw(10) << h << ":" << m << ":" << s << ":" << ms << "\r";
        }

    }
}
