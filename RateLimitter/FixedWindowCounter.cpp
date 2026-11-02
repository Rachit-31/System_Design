#include<bits/stdtr1c++.h>
using namespace std;
// Time: O(1) amortized per request.
// Space: O(capacity).

class FixedWindow {
    int limit;
    int windowSize;

    long long windowStart;
    int count;

public:
    FixedWindow(int limit, int windowSize) {
        this->limit = limit;
        this->windowSize = windowSize;
        windowStart = -1;
        count = 0;
    }

    bool allowRequest(long long timestamp) {

        long long currentWindow = timestamp / windowSize;

        if (windowStart != currentWindow) {
            windowStart = currentWindow;
            count = 0;
        }

        if (count < limit) {
            count++;
            return true;
        }

        return false;
    }
};
int main(){
    return 0;
}
// Problem: Boundary burst
// This is the biggest disadvantage of Fixed Window.

// Suppose the limit is 5 requests per minute.
// 10:00:59 → 5 requests
// 10:01:00 → 5 requests

// The user can send 10 requests within approximately 1 second, even though the limit is 5 requests per minute.

// This happens because the counter resets at the window boundary.

// When to use: Simple APIs where occasional bursts around window boundaries are acceptable.