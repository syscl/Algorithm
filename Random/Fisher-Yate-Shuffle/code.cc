#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> fisher_yate_shuffle(const vector<int>& nums) {
    vector<int> ret = nums;
    const int n = nums.size();
    for (int i = 0; i < n; i++) {
        int r = rand() % (i + 1);
        swap(ret[r], ret[i]);
    }
    return ret;
}

void print_vector(const vector<int>& v) {
    cout << "{ ";
    for (const int& a : v) 
        cout << a << ", ";
    cout << " }\n";
}

int main(int argc, char* argv[]) {
    vector<int> org_nums;
    for (int i = 1; i <= 10; i++)
        org_nums.push_back(i);
    // We have to seed the rand, otherwise, we will get the same
    // result from the rand() generator
    srand(time(NULL));
    print_vector(org_nums);
    print_vector(fisher_yate_shuffle(org_nums));
    return 0;
}