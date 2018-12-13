// See also Leetcode 322. Coin Change
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/*
 * Minimal coin change over a given denomination system.
 * 
 * @param denominations
 * @param amount of money 
 * 
 * @return minimal coin change
 */
int change(const vector<int>& d, const int n) {
    vector<int> c(n+1, numeric_limits<int>::max());
    const int k = d.size();
    c[0] = 0;
    for (int p = 1; p <= n; p++) {
        for (int i = 0; i < k; i++) {
            int indx = p - d[i];
            // c[indx]+1 will cause integer overflow
            // a workaround will be initialized all c[] to amount+1
            if (indx >= 0 && c[indx] < c[p] - 1) 
                c[p] = c[indx] + 1;
        }
    }
    return c[n] == numeric_limits<int>::max() ? -1 : c[n];
}

void change_wrap(const vector<int>& d, const int n) {
    auto print = [](const vector<int>& nums) {
        const int size = nums.size();
        cout << "{ ";
        for (int i = 0; i < size; i++) {
            cout << nums[i];
            cout << (i == size-1 ? " }" : ", "); 
        }
    };
    cout << "The minimal coin change for " << n << " over ";
    print(d);
    cout << ": " << change(d, n) << endl;
}


int main(int argc, char* argv[]) 
{
    vector<int> denominations = {1,2,5};
    int amount = 11;
    change_wrap(denominations, amount);
    denominations = {3};
    amount = 2;
    change_wrap(denominations, amount);
    denominations = {186,419,83,408};
    amount = 6249;
    change_wrap(denominations, amount);
    return 0;
}