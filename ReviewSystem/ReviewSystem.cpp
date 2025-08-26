#include<bits/stdc++.h>
using namespace std;

class Review{
public:
    string userName;
    int rating;
    string comment;

    Review(string name, int rating, string comment){
        this->userName = name;
        this->rating = rating;
        this->comment = comment;
    }
};

class Product{
public:
    int id;
    string name;
    vector<Review>reviews;

    Product(int id, string name){
        this->id = id;
        this->name = name;
    }

    void addReview(string userName, int rating, string comment){
        reviews.push_back(Review(userName, rating, comment));
    }

    void showReview(){
        cout<<"Reviews for this product-----"<<name<<endl;
        for(auto &r: reviews){
            cout<<"This is given by: "<<r.userName<<endl;
            cout<<"The rating of this review is: "<<r.rating<<endl;
            cout<<"The commment of this product review are: "<<r.comment<<endl;
        }
    }

    double getAverageRating() {
        if(reviews.empty()) return 0.0;
        double sum = 0;
        for(auto &r : reviews) sum += r.rating;
        return sum / reviews.size();
    }
};
int main(){
    Product p1(101, "Wireless Mouse");

    p1.addReview("Alice", 5, "Excellent product!");
    p1.addReview("Bob", 4, "Good but a bit small.");

    p1.showReview();
    cout << "Average rating: " << p1.getAverageRating() << endl;

    return 0;
}