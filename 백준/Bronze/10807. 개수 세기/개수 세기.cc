#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, v, num, sum=0;
    cin >> N;
    vector<int> arr;

    for (int i=0; i<N; i++){
        cin >> num;
        arr.push_back(num);
    }
    cin >> v;
    for_each(arr.begin(), arr.end(), [&](int& n){
        if (n==v) sum+=1;
    });
    cout << sum;
    
    return 0;
}