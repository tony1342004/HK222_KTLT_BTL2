#include <iostream>
#include<stdlib.h>
#include<string>
#include <cstring>

using namespace std;

int main() {
    system("g++ -o main main.cpp knight2.cpp -I . -std=c++11");
    int numberOfTest=10;
    string s="";
    for(int i=1; i<=numberOfTest; i++) {
        cout << "TESTCASE " << i << " :" << endl;
        #if _WIN32
        s="main tc"+to_string(i)+"_armyknights tc"+to_string(i)+"_events";
        #else
        s="./main tc"+to_string(i)+"_armyknights tc"+to_string(i)+"_events";
        #endif
        system(s.c_str());
    }
    cout << "--END--\n";
    cin.get();
    return 0;
}
