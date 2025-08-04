#include<bits/stdc++.h>
using namespace std;

class User{
public:
    string id, name, email, mobile;
    User(string id, string name, string email, string mobile){
        this->id = id;
        this->name = name;
        this->email = email;
        this->mobile = mobile;
    }
};

class Split {
protected:
    shared_ptr<User>user;
    double amount;
public:
    Split(shared_ptr<User>user, double amount){
        this->user = user;
        this->amount = amount;
    }

    virtual double getAmount(){
        return amount;
    }
    virtual shared_ptr<User> getUser(){
        return user;
    }
    
};

class Expense{
protected:
    string paidBy;
    double amount;
    string type;
    vector<shared_ptr<Split>>splits;
public:
    Expense(string paidby, double amount, string type, vector<shared_ptr<Split>>splits){
        this->paidBy = paidBy;
        this->amount = amount;
        this->type = type;
        this->splits = splits;
    }


    string getPaidBy() const { return paidBy; }
    double getAmount() const { return amount; }
    vector<shared_ptr<Split>> getSplits() const { return splits; }
};

class ExpenseManager{
    // balanceSheet[debtor][creditor] = amount;
    unordered_map<string, shared_ptr<User>> users;
    unordered_map<string, unordered_map<string, double>> balanceSheet;
public:
    void addUser(string id, string name, string email, string mobile) {
        users[id] = make_shared<User>(id, name, email, mobile);
    }

    shared_ptr<User> getUser(string id) {
        return users[id];
    }

    void addExpense(string paidBy, double amount, string type, vector<shared_ptr<Split>> splits){
        Expense exp(paidBy, amount, type, splits);
        for (auto &split : splits){
            string paidTo = split->getUser()->id;
            if (paidTo == paidBy)
                continue;

            balanceSheet[paidTo][paidBy] += split->getAmount();
            balanceSheet[paidBy][paidTo] -= split->getAmount();
        }
    }
    void showBalances() {
        for (auto& userBalances : balanceSheet) {
            string user = userBalances.first;
            for (auto& bal : userBalances.second) {
                if (bal.second > 0)
                    cout << user << " owes " << bal.first << ": " << bal.second << endl;
            }
        }
    }

    void showUserBalance(string userId) {
        for (auto& bal : balanceSheet[userId]) {
            if (bal.second > 0)
                cout << userId << " owes " << bal.first << ": " << bal.second << endl;
        }
    }

};

int main(){
    ExpenseManager manager;

    manager.addUser("u1", "Rachit", "rachit@email.com", "9999999999");
    manager.addUser("u2", "Aman", "aman@email.com", "8888888888");
    manager.addUser("u3", "Neha", "neha@email.com", "7777777777");

    // u1 pays 300 for dinner, split equally between u1, u2, u3
    vector<shared_ptr<Split>> splits = {
        make_shared<Split>(manager.getUser("u1"), 100),
        make_shared<Split>(manager.getUser("u2"), 100),
        make_shared<Split>(manager.getUser("u3"), 100)
    };

    manager.addExpense("u1", 300, "EQUAL", splits);

    manager.showBalances();
    return 0;
}