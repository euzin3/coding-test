#include <iostream>
using namespace std;

int main() {
    long long N, M; 
    long long sub = 0;
    cin >> N >> M;

    sub = N - M;
    if (sub < 0) sub*= -1;
    cout << sub;
    
    return 0;
}