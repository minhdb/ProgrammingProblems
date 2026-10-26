#include <stdio.h>
#include <vector>
#include <string.h>
#include <map>
#include <iostream>
#define FOR(x, size) for (int x = 0; x < size; x++)
#define gc getchar_unlocked

using namespace std;

string flip(string s) {
    string r = s;
    if (s[0] == '-') r[0] = '+';
    else r[0] = '-'; 
    return r;
}

int main() {
    int l = 1, n = 0; 
    string s, op, last, mid;
    /*
     * map< string, map< string, string > > table;
     * table["+x"]["+y"]["+z"] = "+z";
     * table["+x"]["+y"]["-z"] = "-z";
     * table["+x"]["-y"]["+z"] = "+z";
     * table["+x"]["-y"]["-z"] = "-z";
     *
     * table["+y"]["+x"]["+z"] = "+z";
     * table["+y"]["+x"]["-z"] = "-z";
     * table["+y"]["-x"]["+z"] = "+z";
     * table["+y"]["-x"]["-z"] = "-z";
     *
     * table["+z"]["+y"]["+z"] = "-z";
     * table["+z"]["+y"]["-z"] = "+z";
     * table["+z"]["-y"]["+z"] = "-z";
     * table["+z"]["-y"]["-z"] = "+z";
     */
    while (l != 0) {
    	cin >> l;
    	last = "+x"; mid = "+x"; op = "";
        for (int i = 0; i < l - 1; i++) {
            cin >> s;
            op += s;
        }
        for (int i = 0; i < op.size(); i += 2) {
            bool fl = false;
            string ins = op.substr(i, 2);
            if (!i) {last = ins; continue;}
            if (ins != "No") {
                if (ins != last && last != mid && ins != mid) continue;
                else if (ins == last) { last = flip(mid); }
                else if (ins[0] == '-') { fl = true; ins[0] = '+'; }
                else {
                    if (ins != last && last != mid && ins != mid) continue;
                    if (ins == last) last = flip(mid);
                }
                mid = ins;
                if (fl) last = flip(last);
            }           
        }
        cout << last << endl;
    }
    return 0;
}
