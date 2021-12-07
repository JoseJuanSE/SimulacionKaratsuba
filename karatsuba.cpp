//Problemas en la resta
#include<bits/stdc++.h>
using namespace std;
typedef string BIG_NUM;

string ceros(int n) {
    string s = "";
    for (int i = 0; i < n; i++)
        s += "0";
    return s;
}

BIG_NUM sumBig(BIG_NUM a, BIG_NUM b) {

    int n = a.length();
    int m = b.length();

    if (n > m) {
        b = ceros(n - m) + b;
    } else {
        a = ceros(m - n) + a;
        n = m;
    }

    string ans = "";
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        char cans = (sum % 10) + '0';
        ans = cans + ans;
        carry = sum / 10;
    }

    if (carry) {
        ans = (char)(carry + '0') + ans;
    }

    return ans;
}

BIG_NUM subBig(BIG_NUM a, BIG_NUM b) {

    int n = a.length();
    int m = b.length();
    b = ceros(n - m) + b;
    string ans = "";

    int carry = 0;

    for (int i = n - 1; i >= 0; i--) {
        int sub = (a[i] - '0') - (b[i] - '0') - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        } else
            carry = 0;
        ans = char(sub + '0') + ans;
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] != '0') {
            ans = ans.substr(i);
            break;
        }
    }

    return ans;
}

BIG_NUM karatsuba(BIG_NUM x, BIG_NUM y) {
    if (x.size() < y.size())
        swap(x, y);

    if (x.size() == 1 or y.size() == 1) {
        BIG_NUM ans = "0";
        int n = stoi(y);
        for (int i = 0; i < n; i++)
            ans = sumBig(ans, x);
        return ans;
    }
    int n = x.size();
    int half = n / 2;
    BIG_NUM a = x.substr(0, n - half);
    BIG_NUM b = x.substr(n - half);

    BIG_NUM c = "0", d = y;
    if (y.size() > half) {
        c = y.substr(0, y.size() - half);
        d = y.substr(y.size() - half);
    }

    BIG_NUM ac = karatsuba(a, c);
    BIG_NUM bd = karatsuba(b, d);
    BIG_NUM ad_plus_bc = subBig(subBig(karatsuba(sumBig(a, b), sumBig(c, d)), ac), bd);
    return sumBig(sumBig(ac + ceros(2 * half), ad_plus_bc + ceros(half)), bd);
}

const BIG_NUM operator*(BIG_NUM a, BIG_NUM b) {
    return karatsuba(a, b);
}

int main() {
    BIG_NUM a, b;
    cin >> a >> b;
    cout << a * b << endl;
}