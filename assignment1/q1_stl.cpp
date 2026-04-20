#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <numeric>    
#include <algorithm>  
using namespace std;

// Part a:
void part_a() {
    int n;
    cout << "[Part a] Enter N (number of integers, 1 <= N <= 100000): ";
    cin >> n;

    vector<int> v(n);
    cout << "Enter " << n << " space-separated integers: ";
    for (int i = 0; i < n; i++) cin >> v[i];

    cout << "Reversed: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        cout << *it << " ";
    cout << "\n";
}

// Part b:
void part_b() {
    deque<int> dq;
    int q;
    cout << "\n[Part b] Enter number of deque operations: ";
    cin >> q;
    cout << "  Operation codes:\n";
    cout << "    1 <value>  →  push_back  (add to back)\n";
    cout << "    2 <value>  →  push_front (add to front)\n";
    cout << "    3          →  pop_front  (remove from front)\n";

    int op_num = 1;
    while (q--) {
        int op;
        cout << "  Enter operation " << op_num++ << ": ";
        cin >> op;
        if (op == 1) {
            cout << "    Enter value to push_back: ";
            int val; cin >> val;
            dq.push_back(val);
        } else if (op == 2) {
            cout << "    Enter value to push_front: ";
            int val; cin >> val;
            dq.push_front(val);
        } else {
            if (!dq.empty()) dq.pop_front();
            else cout << "  (deque is empty, pop ignored)\n";
        }
    }

    cout << "Deque contents: ";
    for (int x : dq) cout << x << " ";
    cout << "\n";
}

// Part c:
void part_c() {
    const int SIZE = 5;
    array<int, SIZE> arr;
    cout << "\n[Part c] Enter exactly " << SIZE << " integers (space-separated): ";
    for (int i = 0; i < SIZE; i++) cin >> arr[i];

    int sum = accumulate(arr.begin(), arr.end(), 0);
    cout << "Sum of array elements = " << sum << "\n";
}

int main() {
    part_a();
    part_b();
    part_c();

    return 0;
}
