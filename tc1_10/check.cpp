#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file1("output");
    ifstream file2("SampleOutput");
    string s1,s2;
    int line=1, event=0;
    do {
    getline(file1,s1);
    getline(file2,s2);
    if(s1[0]=='T' && s1[1]=='E' ) { cout << s1 << endl; event=-1; }
    else if(s1[0]!='-') { 
        if(s1[0]=='N') event++;
        if(s1!=s2) {
            cout << "Different at line " << line << " (event " << event << ")" << endl;
            cout << "\t[YourOP] " << s1 << endl << "\t[Sample] " << s2 << endl;
        }
    }
    line++;
    } while(s2!="--END--" && s1!="--END--");
    file1.close(); file2.close();
    cin.get();
    return 0;
}
