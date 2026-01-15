#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int A,B;

    while(1){
        cin >> A >> B;
        if(A==0 && B==0) break;
        cout << A+B << "\n";
    }
    return 0;
}