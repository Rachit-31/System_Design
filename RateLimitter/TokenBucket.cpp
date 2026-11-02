#include<bits/stdtr1c++.h>
using namespace std;
// Time: O(1) per request.
// Space: O(1) per client.

class TokenBucket{
    double capacity;
    double tokens;
    double refillRate;
    long long lastRefillTime;
public:
    TokenBucket(double capacity, double refillRate){
        this->capacity= capacity;
        this->refillRate= refillRate;
        tokens= capacity;
        lastRefillTime=0;
    }
    bool allowRequest(long long timeStamp){
        long long elapsed = timeStamp - lastRefillTime;
        double newTokens= elapsed* refillRate;
        tokens = min(capacity, tokens + newTokens);
        lastRefillTime = timeStamp;

        if (tokens >= 1) {
            tokens -= 1;
            return true;
        }

        return false;
    }
};
int main(){
    return 0;
}