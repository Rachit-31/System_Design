#include<bits/stdtr1c++.h>
using namespace std;
// Time: O(1) amortized per request.
// Space: O(capacity).

class LeakyBucket{
private:
    queue<int>q;
public:
    bool allowReq(int timeStamp, int capacity, int timewindow){
        while(!q.empty() && timeStamp- q.front()>= timewindow){
            q.pop();
        }
        if(q.size()> capacity){
            return false;
        }
        q.push(timeStamp);
        return true;
    }
};
int main(){
    return 0;
}