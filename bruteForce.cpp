#include<bits/stdc++.h>
#define BIG_NUM string

using namespace std;

string ceros(int x) {
    string ans = "";
    for(int i=0; i<x; i++) {
        ans += '0';
    }
    return ans;
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
    
    if(carry) {
        ans = (char)(carry + '0') + ans;
    }
    
    return ans;
}


BIG_NUM operator*(BIG_NUM a, BIG_NUM b) {
    BIG_NUM ans = "0";
    for(int i=a.size()-1; i>=0; i--) {
        int carry = 0;
        for(int j=b.size()-1; j>=0; j--) {
            int dummy = (a[i]-'0') * (b[j]-'0') + carry;
            carry = dummy / 10;
            if(j!=0)
                dummy %= 10;
            BIG_NUM actual = to_string(dummy) + ceros(a.size() + b.size() - i - j -2);
            ans = sumBig(ans, actual);
        }   
    }
    return ans;
}

int main() {
    BIG_NUM a, b;
    cin>>a>>b;
    cout<<a*b;
    return 0;
}