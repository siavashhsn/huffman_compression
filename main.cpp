#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <bitset>

using namespace std;

struct Comparer {
    bool operator() (const bitset<4> &b1, const bitset<4> &b2) const {
        return b1.to_ulong() < b2.to_ulong();
    }
};


int main()
{
    string fname = "/home/siavash/Desktop/1.txt", s, ss="";
    cout << "File Location: ";
    //cin >> fname;

    ifstream input(fname, ios::binary );
    vector<bitset<4>> buffer((
        istreambuf_iterator<char>(input)),
        (istreambuf_iterator<char>()));

    map<bitset<4>, int, Comparer> freq;
    for(size_t i=0; i < buffer.size(); i++) {
        bitset<4> c = buffer[i];
        cout << i << " : " << c << endl;
        freq[buffer[i]]++;
    }

    return 0;
}
