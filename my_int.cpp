/*
 * unsigned non limited bytes integer type
 */
#include <bits/stdc++.h>

using namespace std;

const int MAXBYTES = 32;
const int MAXBITES = MAXBYTES * 8;


class myInt {
public:
    bool *val = (bool *) malloc(sizeof(bool) * MAXBITES);

    void operator+=(const myInt &b) const{
        int buf = 0;
        for (int i = 0; i < MAXBITES; i++) {
            buf += val[i] + b.val[i];
            val[i] = (buf & 1);
            buf >>= 1;
        }
    }

    myInt(unsigned long long a) {
        for (int i = 0; i < MAXBITES; i++) {
            val[i] = (a & 1);
            a >>= 1;
        }
    }

    myInt(const myInt &a) {
        for (int i = 0; i < MAXBITES; i++) {
            val[i] = a.val[i];
        }
    }

    myInt() {
        for (int i = 0; i < MAXBITES; i++) {
            val[i] = false;
        }
    }

};

myInt rev(const myInt &a) {
    myInt res;
    for (int i = 0; i < MAXBITES; i++) {
        res.val[i] = !a.val[i];
    }
    return res;
}

unsigned long long size(const myInt &a) {
    for (int i = MAXBITES - 1; i >= 0; i--) {
        if (a.val[i])
            return i + 1;
    }
    return 1;
}

unsigned long long toull(const myInt &a) {
    unsigned long long res = 0;
    for (int i = 0; i < MAXBITES; i++) { // до 8 байт
        res += a.val[i] * (1LL << i);
    }
    return res;
}

bool operator>(const myInt &a, const myInt &b) {
    for (int i = MAXBITES - 1; i >= 0; i--) {
        if (a.val[i] != b.val[i])
            return a.val[i];
    }
    return false;
}

bool operator<(const myInt &a, const myInt &b) {
    for (int i = MAXBITES - 1; i >= 0; i--) {
        if (a.val[i] != b.val[i])
            return b.val[i];
    }
    return false;
}

bool operator==(const myInt &a, const myInt &b) {
    for (int i = 0; i < MAXBITES; i++) {
        if (a.val[i] != b.val[i])
            return false;
    }
    return true;
}

bool operator!=(const myInt &a, const myInt &b) {
    return !(a == b);
}

bool operator<=(const myInt &a, const myInt &b) {
    return ((a < b) || (a == b));
}

bool operator>=(const myInt &a, const myInt &b) {
    return ((a > b) || (a == b));
}

myInt operator<<(const myInt &a, const unsigned long long &b) {
    myInt res;
    if (b == 0) {
        res = a;
        return res;
    }

    for (unsigned long long i = MAXBITES - 1; i >= b; i--) {
        res.val[i] = a.val[i - b];
    }
    return res;
}

myInt operator>>(const myInt &a, const unsigned long long &b) {
    myInt res;
    for (unsigned long long i = 0; i < MAXBITES - b; i++) {
        res.val[i] = a.val[i + b];
    }
    return res;
}

myInt operator+(const myInt &a, const myInt &b) {
    myInt res;
    int buf = 0;
    for (int i = 0; i < MAXBITES; i++) {
        buf += a.val[i] + b.val[i];
        res.val[i] = (buf & 1);
        buf >>= 1;
    }
    return res;
}



myInt operator-(const myInt &a, const myInt &b) {
    myInt res;
    res += (a + 1);
    res += rev(b);
    return res;
}

myInt operator*(const myInt &a, const myInt &b) {
    myInt res;
    for (unsigned long long i = 0; i < MAXBITES; i++) {
        if (!b.val[i])
            continue;
        res += (a << i);
    }
    return res;
}

myInt operator/(const myInt &a, const myInt &b) {
    myInt res, d = a;
    if (a < b)
        return 0;
    for (unsigned long long i = MAXBITES - size(b);; i--) {
        if (d >= (b << i)) {
            res.val[i] = true;
            d = d - (b << i);
        }
        if (i == 0)
            break;
    }
    return res;
}

myInt operator%(const myInt &a, const myInt &b) {
    return a - (a / b) * b;
}

myInt stomi(const string &s) {
    myInt tmp;
    for (char q : s) {
        tmp = tmp * 10 + (q - '0');
    }
    return tmp;
}

ostream &operator<<(ostream &out, const myInt &a) {

    if (a >= 10) {
        out << a / 10;
    }
    return out << toull(a % 10);

    unsigned long long res = toull(a);
    return out << res << " ";

    for (int i = MAXBITES - 1; i >= 0; i--) {
        out << a.val[i];
    }
    return out;

}

istream &operator>>(istream &in, myInt &a) {
    unsigned long long res;
    in >> res;
    a = res;
    return in;

    string s;
    in >> s;
    a = stomi(s);
    return in;
}

void print(const myInt &a) {
    if (a >= 10) {
        print(a / 10);
    }
    cout << toull(a % 10);
}

int main() {


}
