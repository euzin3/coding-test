#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N,f=1;
    cin >> N;

    for(int i=1; i<=N; i++){
        f*=i;
    }
    cout << f;
    return 0;
}