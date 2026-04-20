#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter N (number of elements): ";
    cin >> n;

    vector<int> a(n);
    cout << "Enter " << n << " integers (space-separated): ";
    for (int i = 0; i < n; i++) cin >> a[i];

    int k;
    cout << "Enter K (subsets whose sum is divisible by K will be counted): ";
    cin >> k;

    int total_subsets = 1 << n;  
    int divisible_count = 0;

    cout << "\nAll subsets:\n";
    for (int mask = 0; mask < total_subsets; mask++) {
        int sum = 0;
        cout << "{ ";
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {  
                cout << a[i] << " ";
                sum += a[i];
            }
        }
        cout << "}  sum = " << sum;

        if (sum % k == 0) {
            cout << "  ✓ (divisible by " << k << ")";
            divisible_count++;
        }
        cout << "\n";
    }

    cout << "\nTotal subsets            : " << total_subsets << "\n";
    cout << "Subsets with sum div by " << k << ": " << divisible_count << "\n";

    return 0;
}