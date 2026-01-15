#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int main() {
    time_t now;
    struct tm * date;

    time(&now);
    date = localtime(&now);

    cout << date->tm_year + 1900 << "-"
        << setw(2) << setfill('0') << date->tm_mon + 1 << "-" 
        << setw(2) << setfill('0') << date->tm_mday;

    
    return 0;
}