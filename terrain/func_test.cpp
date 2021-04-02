#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void printVector(vector<int> vec){
    for(auto item : vec){
        cout << item << ", ";
    } cout << endl;
}

int main() {
    std::vector<int> toVisit;
    toVisit.push_back(1);
    toVisit.push_back(2);
    toVisit.push_back(3);
    toVisit.push_back(4);
    toVisit.push_back(5);
    toVisit.push_back(6);

    printVector(toVisit);
    
    cout << endl;
    cout << toVisit.back() << endl;
    toVisit.pop_back();

    toVisit.push_back(6);
    printVector(toVisit);
    
    return 0;
}
