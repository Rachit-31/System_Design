#include<bits/stdc++.h>
using namespace std;

class RateLimitter{
    private:
        queue<int>q;

    public:
        bool allowRequest(int timeStamp){
            while(!q.empty() && timeStamp-q.front()>=60){
                q.pop();
            }
            
            if(q.size()>=3){
                return false;
            }

            q.push(timeStamp);
            return true;
        }
};
class RateLimitter2{
    private:
        unordered_map<string, queue<long long>>users;
    
    public:
        bool req(string userId, long long timestamp){
            queue<long long>&q= users[userId];

            while (!q.empty() && timestamp - q.front() >= 60) {
                q.pop();
            }
            if(q.size()>=3){
                return false;
            }
            q.push(timestamp);

            return true;
        }
};
class RateLimiter3 {
private:

    // {timestamp, tokenCost}
    queue<pair<long long, int>> q;

    int usedTokens = 0;

public:

    bool allowRequest(long long timestamp, int tokenCost) {

        // Remove requests outside the 60-second window
        while (!q.empty() && timestamp - q.front().first >= 60) {
            usedTokens -= q.front().second;
            q.pop();
        }

        // Would exceed the 100-token limit
        if (usedTokens + tokenCost > 100) {
            return false;
        }

        // Accept request
        q.push({timestamp, tokenCost});
        usedTokens += tokenCost;

        return true;
    }
};

class RateLimiter4 {
private:

    struct UserData {
        queue<pair<long long, int>> q;
        int usedTokens = 0;
    };

    unordered_map<string, UserData> users;

public:

    bool allowRequest(string userId,long long timestamp, int tokenCost) {

        UserData &user = users[userId];

        // Remove expired requests
        while (!user.q.empty() && timestamp - user.q.front().first >= 60) {
            user.usedTokens -= user.q.front().second;
            user.q.pop();
        }

        // Check limit
        if (user.usedTokens + tokenCost > 100) {
            return false;
        }

        // Accept request
        user.q.push({timestamp, tokenCost});
        user.usedTokens += tokenCost;

        return true;
    }
};
int main(){
    
    RateLimiter3 limiter;
    cout << limiter.allowRequest(1,1) << endl;   
    cout << limiter.allowRequest(2,10) << endl;   
    cout << limiter.allowRequest(3,22) << endl;

    cout<<limiter.allowRequest(62,101)<<endl;

    return 0;
}