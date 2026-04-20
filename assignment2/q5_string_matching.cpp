#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<int> build_lps(const string& pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0;   
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> kmp_search(const string& text, const string& pat) {
    vector<int> matches;
    int n = text.size(), m = pat.size();
    if (m == 0 || m > n) return matches;

    vector<int> lps = build_lps(pat);
    int i = 0, j = 0; 

    while (i < n) {
        if (text[i] == pat[j]) {
            i++; j++;
        }
        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];   
        } else if (i < n && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else        i++;
        }
    }
    return matches;
}


const long long BASE  = 31;
const long long PRIME = 1e9 + 9;

vector<int> rabin_karp_search(const string& text, const string& pat) {
    vector<int> matches;
    int n = text.size(), m = pat.size();
    if (m == 0 || m > n) return matches;

    long long h = 1;
    for (int i = 0; i < m - 1; i++) h = (h * BASE) % PRIME;

    auto char_val = [](char c) -> long long { return c - 'a' + 1; };

    long long pat_hash = 0, txt_hash = 0;
    for (int i = 0; i < m; i++) {
        pat_hash = (pat_hash * BASE + char_val(pat[i])) % PRIME;
        txt_hash = (txt_hash * BASE + char_val(text[i])) % PRIME;
    }

    for (int i = 0; i <= n - m; i++) {
        if (txt_hash == pat_hash) {
            if (text.substr(i, m) == pat)
                matches.push_back(i);
        }
        if (i < n - m) {
            txt_hash = (BASE * (txt_hash - char_val(text[i]) * h % PRIME + PRIME)
                        + char_val(text[i + m])) % PRIME;
        }
    }
    return matches;
}


int main() {
    string fixed_pattern = "ABABCABAB";
    vector<int> lps = build_lps(fixed_pattern);

    cout << "=== Part a: KMP LPS Array ===\n";
    cout << "Pattern : " << fixed_pattern << "\n";
    cout << "LPS     : ";
    for (int x : lps) cout << x << " ";
    cout << "\n\n";

    cout << "=== KMP Search ===\n";
    cout << "Enter the text to search in (no spaces): ";
    string text; cin >> text;
    cout << "Enter the pattern to search for: ";
    string pat; cin >> pat;

    vector<int> user_lps = build_lps(pat);
    cout << "LPS array for \"" << pat << "\": ";
    for (int x : user_lps) cout << x << " ";
    cout << "\n";

    auto kmp_res = kmp_search(text, pat);
    if (kmp_res.empty()) cout << "KMP: Pattern not found.\n";
    else {
        cout << "KMP: Pattern found at indices: ";
        for (int idx : kmp_res) cout << idx << " ";
        cout << "\n";
    }

    string text_lc = text, pat_lc = pat;
    for (char& c : text_lc) c = tolower(c);
    for (char& c : pat_lc)  c = tolower(c);

    cout << "\n=== Rabin-Karp Search (lowercase) ===\n";
    auto rk_res = rabin_karp_search(text_lc, pat_lc);
    if (rk_res.empty()) cout << "Rabin-Karp: Pattern not found.\n";
    else {
        cout << "Rabin-Karp: Pattern found at indices: ";
        for (int idx : rk_res) cout << idx << " ";
        cout << "\n";
    }

    return 0;
}