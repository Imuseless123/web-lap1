#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

vector<vector<char> > generateKeyMatrix(string key) {
    vector<vector<char> > a(5, vector<char>(5, ' '));
    map<char, int> mp;
    int i, j, k = 0, n = 5;

    transform(key.begin(), key.end(), key.begin(), ::tolower);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            while (mp[key[k]] > 0 && k < key.size()) {
                k++;
            }
            if (k < key.size() && key[k] != 'j') {  // Exclude 'j'
                a[i][j] = key[k];
                mp[key[k]]++;
            }
            if (k == key.size())
                break;
        }
        if (k == key.size())
            break;
    }

    k = 0;
    for (; i < n; i++) {
        for (; j < n; j++) {
            while (mp[char(k + 'a')] > 0 && k < 26) {
                k++;
            }
            if (char(k + 'a') == 'j') {
                k++; // Skip j
            }
            if (k < 26) {
                a[i][j] = char(k + 'a');
                mp[char(k + 'a')]++;
            }
        }
        j = 0;
    }
    return a;
}

string prepareInput(string input) {
    string prepared;
    for (char c : input) {
        if (isalpha(c)) {
            c = tolower(c);
            if (c == 'j') c = 'i';  // Thay j i
            prepared += c;
        }
    }
    return prepared;
}

string encryptPlayfair(string origin, string key) {
    string s = prepareInput(origin);
    int i, n = 5;

    vector<vector<char> > a = generateKeyMatrix(key);
    string ans;

    for (i = 0; i < s.size() - 1; i += 2) {
        if (s[i] == s[i + 1]) {
            s.insert(i + 1, "x");
        }
    }
    if (s.size() % 2 == 1) s += "x"; //Thêm x

    map<char, pair<int, int> > mp2;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mp2[a[i][j]] = make_pair(i, j);
        }
    }

    // Encrypt the message
    for (i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first;
        int x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first;
        int x2 = mp2[s[i + 1]].second;

        if (y1 == y2) {
            ans += a[y1][(x1 + 1) % 5];
            ans += a[y1][(x2 + 1) % 5];
        }
        else if (x1 == x2) {
            ans += a[(y1 + 1) % 5][x1];
            ans += a[(y2 + 1) % 5][x2];
        }
        else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }

    return ans;
}

string decryptPlayfair(string s, string key) {
    int i, n = 5;
    vector<vector<char> > a = generateKeyMatrix(key);
    string ans;

    map<char, pair<int, int> > mp2;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mp2[a[i][j]] = make_pair(i, j);
        }
    }

    for (i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first;
        int x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first;
        int x2 = mp2[s[i + 1]].second;

        if (y1 == y2) {
            ans += a[y1][(x1 - 1 + 5) % 5];  
            ans += a[y1][(x2 - 1 + 5) % 5];
        }
        else if (x1 == x2) {
            ans += a[(y1 - 1 + 5) % 5][x1];  
            ans += a[(y2 - 1 + 5) % 5][x2];
        }
        else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }

    // Xóa x
    for (i = 1; i < ans.size(); i++) {
        if (ans[i] == 'x' && ans[i - 1] == ans[i + 1]) {
            ans.erase(i, 1);
        }
    }
    if (ans[ans.size() - 1] == 'x') {
        ans.erase(ans.size() - 1); 
    }

    return ans;
}

int main() {
    int choice;
    string message, key;

    do {
        cout << "Playfair Cipher\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Exit\n";
        cout << "Enter [1-3] : ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter plain text: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter key: ";
                cin >> key;
                cout << "Encrypted text: " << encryptPlayfair(message, key) << endl;
                break;

            case 2:
                cout << "Enter encrypted text: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter key: ";
                cin >> key;
                cout << "Decrypted text: " << decryptPlayfair(message, key) << endl;
                break;

            case 3:
                cout << "Exit." << endl;
                break;

            default:
                cout << "Invalid choice..\n";
        }
    } while (choice != 3);

    return 0;
}
