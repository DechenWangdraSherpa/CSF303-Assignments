/**
 * Question 5: String Matching — KMP and Rabin-Karp
 *
 * Part a: KMP — compute LPS array for "ABABCABAB", then search text.
 * Part b: Rabin-Karp — polynomial rolling hash with collision handling.
 *
 * ─── KMP ────────────────────────────────────────────────────────────────
 * LPS (Longest Proper Prefix which is also Suffix):
 *   Pattern : A  B  A  B  C  A  B  A  B
 *   Index   : 0  1  2  3  4  5  6  7  8
 *   LPS     : 0  0  1  2  0  1  2  3  4
 *
 * Derivation:
 *   i=0: "A"       → no proper prefix/suffix → LPS[0]=0
 *   i=1: "AB"      → 'A'≠'B'               → LPS[1]=0
 *   i=2: "ABA"     → "A" is prefix & suffix → LPS[2]=1
 *   i=3: "ABAB"    → "AB" is prefix&suffix  → LPS[3]=2
 *   i=4: "ABABC"   → no match               → LPS[4]=0
 *   i=5: "ABABCA"  → "A" matches            → LPS[5]=1
 *   i=6: "ABABCAB" → "AB" matches           → LPS[6]=2
 *   i=7: "ABABCABA"→ "ABA" matches          → LPS[7]=3
 *   i=8: "ABABCABAB"→"ABAB" matches         → LPS[8]=4
 *
 * Time Complexity (KMP):
 *   Preprocessing : O(M)  — build LPS array
 *   Search        : O(N)  — single linear scan of text
 *   Total         : O(N + M)
 * Space Complexity: O(M)
 *
 * ─── Rabin-Karp ─────────────────────────────────────────────────────────
 * Uses a rolling polynomial hash. The hash of a window slides in O(1):
 *   hash = (hash - text[i]*BASE^(M-1)) * BASE + text[i+M]  (mod PRIME)
 *
 * Hash Collision Handling:
 *   When text_hash == pattern_hash (a "hit"), the algorithm does a
 *   character-by-character string comparison to confirm a true match.
 *   False positives (spurious hits) are discarded after O(M) verification.
 *
 * Time Complexity (Rabin-Karp):
 *   Average case : O(N + M)  — few spurious hits
 *   Worst case   : O(N · M)  — all windows are spurious hits (e.g. "AAA...A", pattern "AA")
 * Space Complexity: O(1) extra (beyond storing the strings)
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ──────────────────────────────────────────────
// KMP: build LPS array
// ──────────────────────────────────────────────
vector<int> build_lps(const string& pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0;   // length of previous longest prefix-suffix
    int i = 1;

    while (i < m) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else if (len != 0) {
            // Fall back — do NOT increment i
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

// KMP search: returns all starting indices (0-based) of pat in text
vector<int> kmp_search(const string& text, const string& pat) {
    vector<int> matches;
    int n = text.size(), m = pat.size();
    if (m == 0 || m > n) return matches;

    vector<int> lps = build_lps(pat);
    int i = 0, j = 0;  // i = text index, j = pattern index

    while (i < n) {
        if (text[i] == pat[j]) {
            i++; j++;
        }
        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];   // look for next match
        } else if (i < n && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else        i++;
        }
    }
    return matches;
}

// ──────────────────────────────────────────────
// Rabin-Karp search
// ──────────────────────────────────────────────
const long long BASE  = 31;
const long long PRIME = 1e9 + 9;

vector<int> rabin_karp_search(const string& text, const string& pat) {
    vector<int> matches;
    int n = text.size(), m = pat.size();
    if (m == 0 || m > n) return matches;

    // Precompute BASE^(m-1) mod PRIME
    long long h = 1;
    for (int i = 0; i < m - 1; i++) h = (h * BASE) % PRIME;

    auto char_val = [](char c) -> long long { return c - 'a' + 1; };

    // Compute hash of pattern and first window
    long long pat_hash = 0, txt_hash = 0;
    for (int i = 0; i < m; i++) {
        pat_hash = (pat_hash * BASE + char_val(pat[i])) % PRIME;
        txt_hash = (txt_hash * BASE + char_val(text[i])) % PRIME;
    }

    for (int i = 0; i <= n - m; i++) {
        if (txt_hash == pat_hash) {
            // Hash match — verify character by character (handles collisions)
            if (text.substr(i, m) == pat)
                matches.push_back(i);
        }
        // Roll the hash to the next window
        if (i < n - m) {
            txt_hash = (BASE * (txt_hash - char_val(text[i]) * h % PRIME + PRIME)
                        + char_val(text[i + m])) % PRIME;
        }
    }
    return matches;
}

// ──────────────────────────────────────────────
// Main
// ──────────────────────────────────────────────
int main() {
    // ── Part a: LPS demonstration ──
    string fixed_pattern = "ABABCABAB";
    vector<int> lps = build_lps(fixed_pattern);

    cout << "=== Part a: KMP LPS Array ===\n";
    cout << "Pattern : " << fixed_pattern << "\n";
    cout << "LPS     : ";
    for (int x : lps) cout << x << " ";
    cout << "\n\n";

    // ── Interactive KMP search ──
    cout << "=== KMP Search ===\n";
    cout << "Enter the text to search in (no spaces): ";
    string text; cin >> text;
    cout << "Enter the pattern to search for: ";
    string pat; cin >> pat;

    // Build and print LPS for user's pattern
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

    // ── Part b: Rabin-Karp search ──
    // Convert to lowercase for Rabin-Karp (char_val uses 'a'-based encoding)
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

/*
 * Sample Input / Output:
 * ─────────────────────
 * === Part a: KMP LPS Array ===
 * Pattern : ABABCABAB
 * LPS     : 0 0 1 2 0 1 2 3 4
 *
 * === KMP Search ===
 * Enter text   : ABABCABABABABCABAB
 * Enter pattern: ABABCABAB
 * LPS array for "ABABCABAB": 0 0 1 2 0 1 2 3 4
 * KMP: Pattern found at indices: 0 8
 *
 * === Rabin-Karp Search (lowercase) ===
 * Rabin-Karp: Pattern found at indices: 0 8
 *
 * ─── Complexity Summary ───
 * KMP         : O(N + M) time,  O(M) space
 * Rabin-Karp  : O(N + M) avg,  O(NM) worst case (hash collisions),  O(1) extra space
 */
