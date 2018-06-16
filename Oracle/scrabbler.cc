// (c) 2018 syscl
// compile it through g++ -std=c++11 scrabbler.cc 
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << (argv[0]) << " [--prefix][--suffix] word" << endl;
        return -1;
    }

    constexpr int map_sz = 'z' - 'A' + 1;
    int map[map_sz] { 0 };
    char* word = nullptr;
    function<bool(const string&)> letterIsMatch;

    if (argc == 3 && strncmp(argv[1], "--prefix", 8) == 0) {
        letterIsMatch = [&](const string& w) {
            const int ptn_sz = strlen(argv[2]);
            if (ptn_sz > w.size()) return false;   
            for (int i = 0; i < ptn_sz; ++i) 
                if (argv[2][i] != w[i]) return false;
            return true;    
        }; 
    } else if (argc == 3 && strncmp(argv[1], "--suffix", 8) == 0) {
        letterIsMatch = [&](const string& w) {
            const int ptn_sz = strlen(argv[2]);
            if (ptn_sz > w.size()) return false;
            int i = ptn_sz - 1;
            int j = w.size() - 1;
            while (i >= 0) {
                if (argv[2][i] != w[j]) return false;
                i--;
                j--;
            }
            return true;
        };
    } else if (argc == 2 && argv[1]) {
        for (int i = 0; i < strlen(argv[1]); i++) 
            map[argv[1][i] - 'A'] += 1;

        letterIsMatch = [&map](const string& w) {
            int dict[map_sz];
            memcpy(dict, map, map_sz*sizeof(int));
            for (const char& ch : w) 
                if (--dict[ch-'A'] < 0) return false;
            return true;
        };
    }
    
    std::ifstream input("words.txt");
    for (std::string line; getline(input, line); ) 
        if (letterIsMatch(line)) cout << line << endl;

    return 0;
}