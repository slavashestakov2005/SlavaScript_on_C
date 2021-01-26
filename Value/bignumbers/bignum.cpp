#include "bignum.h"
#include <sstream>
#include "../../Exception/mathexception.h"

using namespace std;
using namespace SlavaScript::lang;
using SlavaScript::exceptions::MathException;

Bignum::Bignum(){
    neg = false;
    mas.push_back(0);
    exponent = 0;
    tochnost = 10;
}
Bignum::Bignum(string s){
    if (!isCorect(s)){
        exponent = 0;
        neg = false;
        mas.push_back(0);
        return;
    }
    int last = 0;
    if (s[0] == '-') { neg = true; last = 1; }
    else neg = false;
    int coun_exponent = 0;
    bool b = true;
    for(int i = s.size() - 1; i >= last; i -= 9){
        int l = 0;
        string temp;
        for(int j = i; j > i - 9 && j >= last; --j){
            if (s[j] >= '0' && s[j] <= '9'){
                if (b) ++coun_exponent;
                temp = s[j] + temp;
            }
            else{
                b = false;
                --i;
            }
        }
        for(int j = 0; j < temp.size(); ++j){
            l *= 10;
            l += temp[j] - '0';
        }
        mas.push_back(l);
    }
    if (b) coun_exponent = 0;
    exponent = coun_exponent;
    tochnost = max(10, coun_exponent);
    if (exponent) delete_end_zero();
}
Bignum::Bignum(Bignum const& temp){
    mas = temp.mas;
    neg = temp.neg;
    tochnost = temp.tochnost;
    exponent = temp.exponent;
}
Bignum::Bignum(int temp){
    exponent = 0;
    tochnost = 10;
    while(mas.size() > 0) mas.pop_back();
    if (temp < 0) { neg = true; temp = -temp; }
    else neg = false;
    while(temp > 0){
        mas.push_back(temp % BASE);
        temp /= BASE;
    }
}
Bignum::Bignum(long long temp){
    exponent = 0;
    tochnost = 10;
    while(mas.size() > 0) mas.pop_back();
    if (temp < 0) { neg = true; temp = -temp; }
    else neg = false;
    while(temp > 0){
        mas.push_back(temp % BASE);
        temp /= BASE;
    }
}
Bignum::Bignum(double temp){
    ostringstream ss;
    string s;
    ss << temp;
    s = ss.str();
    (*this) = Bignum(s);
    /*
    17 знаков может хранить double с округлением при больших (18) числах начинаются потери точности
    */
}



Bignum& Bignum::operator=(Bignum const& temp){
    mas = temp.mas;
    neg = temp.neg;
    exponent = temp.exponent;
    tochnost = temp.tochnost;
    return (*this);
}
Bignum& Bignum::operator=(string s){
    (*this) = Bignum(s);
    return (*this);
}
Bignum& Bignum::operator=(int temp){
    (*this) = Bignum(temp);
    return (*this);
}
Bignum& Bignum::operator=(long long temp){
    (*this) = Bignum(temp);
    return (*this);
}
Bignum& Bignum::operator=(double temp){
    (*this) = Bignum(temp);
    return (*this);
}



Bignum::operator bool() const{
    if (mas.size() == 1 && mas[0] == 0) return false;
    else return true;
}
Bignum::operator double() const{
    istringstream is(string(*this));
    double result;
    is >> result;
    return result;
}
Bignum::operator string() const{
    string os;
    if (mas.size() == 1 && mas[0] == 0) return "0";
    for(int i = mas.size() - 1; i > -1; --i){
        if (i == mas.size() - 1){
            int l = mas[i];
            string s;
            while(l > 0){
                s = char('0' + l % 10) + s;
                l /= 10;
            }
            os += s;
        }
        else{
            string s = "000000000";
            int l = mas[i], coun = 8;
            while(l > 0){
                s[coun] = '0' + l % 10;
                --coun;
                l /= 10;
            }
            os += s;
        }
    }
    string cop;
    int expr = exponent;
    if (os.size() <= expr) cop += "0";
    if (os.size() > expr){
        for(int i = 0; i < os.size() - expr; ++i)
            cop += os[i];
    }
    if (expr > 0) cop += ".";
    while(expr > os.size()){
        cop += "0";
        --expr;
    }
    for(int i = os.size() - expr; i < os.size(); ++i) if (i >= 0) cop += os[i];
    if (neg) cop = "-" + cop;
    return cop;
}



Bignum Bignum::operator-(){
    Bignum temp(*this);
    temp.neg = !neg;
    return temp;
}
Bignum Bignum::operator+(){
    return (*this);
}
Bignum& Bignum::operator++(){
    (*this) += Bignum("1");
    return *this;
}
Bignum Bignum::operator++(int){
    Bignum temp = (*this);
    ++(*this);
    return temp;
}
Bignum& Bignum::operator--(){
    (*this) -= Bignum("1");
    return *this;
}
Bignum Bignum::operator--(int){
    Bignum temp = (*this);
    --(*this);
    return temp;
}



void Bignum::setTochnost(int n){
    tochnost = n;
}
bool Bignum::isCorect(string s){
    int first = 0;
    bool tch = false;
    if (s[0] == '-') first = 1;
    for(int i = first; i < s.size(); ++i){
        if (s[i] == '.'){
            if (tch) return false;
            else tch = true;
        }
        else if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}
void Bignum::shift(int n){
    vector<int> digits;
    if (n > 0){
        for(int i = 0; i < n / POW; ++i) digits.push_back(0);
        int p = 1, k = 1;
        for(int i = 0; i < POW - n % POW; ++i) p *= 10;
        for(int i = 0; i < n % POW; ++i) k *= 10;
        int carry = 0;
        for(int i = 0; i < mas.size() || carry != 0; ++i){
            int a = 0;
            if (i < mas.size()) a = mas[i];
            digits.push_back(a % p * k + carry);
            carry = a / p;
        }
    }
    else{
        n = -n;
        int p = 1, k = 1;
        for(int i = 0; i < n % POW; ++i) p *= 10;
        for(int i = 0; i < POW - n % POW; ++i) k *= 10;
        int carry = 0;
        for(int i = n / POW; i < mas.size() || carry != 0; ++i){
            digits.push_back(mas[i] / p);
            if (i > n / POW){
                digits[digits.size() - 2] += mas[i] % p * k;
            }
        }
        while(digits.size() > 1 && digits.back() == 0) digits.pop_back();
    }
    mas = digits;
}
void Bignum::delete_end_zero(){
    if (exponent > 0){
        string s = string(*this);
        int coun = 0;
        while(s.size() > 0 && s.back() == '0') { ++coun; s.pop_back(); }
        exponent -= coun;
        shift(-coun);
    }
    else throw domain_error("Wrong exponent");
}



Bignum& Bignum::operator+=(Bignum const& tem){
    Bignum temp(tem);
    if (neg != temp.neg){
        if (!neg){
            Bignum a = temp;
            a.neg = false;
            (*this) -= a;
        }
        else{
            neg = false;
            (*this) -= temp;
            neg = !neg;
        }
    }
    else{
        int exa = exponent, exb = temp.exponent;
        if (exa > exb) temp.shift(exa - exb);
        if (exa < exb) shift(exb - exa);
        vector<int> digits;
        int carry = 0;
        for(int i = 0; i < mas.size() || i < temp.mas.size() || carry != 0; ++i){
            if (i < mas.size()) carry += mas[i];
            if (i < temp.mas.size()) carry += temp.mas[i];
            digits.push_back(carry % BASE);
            carry /= BASE;
        }
        while(digits.size() > 1 && digits.back() == 0) digits.pop_back();
        mas = digits;
        if (neg && temp.neg) neg = true;
        if (mas.size() == 1 && mas[0] == 0) neg = false;
        exponent = max(exponent, temp.exponent);
        if (exponent) delete_end_zero();
    }
    return (*this);
}
Bignum& Bignum::operator-=(Bignum const& temp){
    if (neg != temp.neg){
        if (!neg){
            Bignum a = temp;
            a.neg = false;
            (*this) += a;
        }
        else{
            neg = false;
            (*this) += temp;
            neg = !neg;
        }
    }
    else{
        Bignum a = (*this), b = temp;
        bool flag = false;
        if (!neg && temp > (*this) || neg && temp < (*this)){
            a = temp;
            b = (*this);
            flag = true;
        }
        int exa = a.exponent, exb = b.exponent;
        if (exa > exb) b.shift(exa - exb);
        if (exa < exb) a.shift(exb - exa);
        vector<int> digits;
        int carry = 0;
        for(int i = 0; i < a.mas.size() || i < b.mas.size() || carry != 0; ++i){
            bool take = false;
            if (i < a.mas.size()) { take = true; carry += a.mas[i]; }
            if (i < b.mas.size()) { take = true; carry -= b.mas[i]; }
            int coun = 0;
            if (carry < 0){ carry += BASE; ++coun; }
            digits.push_back(carry % BASE);
            carry = -coun;
            if (!take) break;
        }
        while(digits.size() > 1 && digits.back() == 0) digits.pop_back();
        mas = digits;
        if (neg && temp.neg) neg = true;
        if (flag) neg = !neg;
        if (mas.size() == 1 && mas[0] == 0) neg = false;
        exponent = max(exa, exb);
        if (exponent) delete_end_zero();
    }
    return (*this);
}
Bignum& Bignum::operator*=(Bignum const& temp){
    int exa = exponent, exb = temp.exponent;
    vector<int> digits(mas.size() + temp.mas.size(), 0);
    for(int i = 0; i < mas.size(); ++i){
        int carry = 0;
        for(int j = 0; j < temp.mas.size(); ++j){
            long long l = (long long)mas[i] * temp.mas[j] + digits[i + j] + carry;
            digits[i + j] = l % BASE;
            carry = l / BASE;
        }
        digits[i + temp.mas.size()] = carry;
    }
    while(digits.size() > 1 && digits.back() == 0) digits.pop_back();
    mas = digits;
    if (neg != temp.neg) neg = true;
    else neg = false;
    if (mas.size() == 1 && mas[0] == 0) neg = false;
    exponent = exa + exb;
    if (exponent) delete_end_zero();
    return (*this);
}
Bignum& Bignum::operator/=(Bignum const& temp){
    //if (temp.mas.size() == 1 && temp.mas[0] == 0) throw domain_error("Division by zero");
    if (temp.mas.size() == 1 && temp.mas[0] == 0) throw new MathException("Division by zero");
    Bignum divisor = temp;
    int sh = max(exponent, divisor.exponent);
    int end_exponent = max(tochnost, temp.tochnost);
    shift(sh - exponent);
    divisor.shift(sh - divisor.exponent);
    exponent = 0;
    divisor.exponent = 0;
    int n = (mas.size() - 1) * POW, m = (divisor.mas.size() - 1) * POW;
    int k = mas[mas.size() - 1];
    while(k > 0){ ++n; k /= 10; }
    k = divisor.mas[divisor.mas.size() - 1];
    while(k > 0){ ++m; k /= 10; }
    bool flag = (divisor.neg != neg);
    divisor.neg = false;
    neg = false;
    Bignum ans("0");
    int f = 0;
    if ((*this) < divisor && n > m) { divisor.shift(-1); ++f; }
    bool b = false;
    while(divisor < (*this)){
        b = true;
        divisor.shift(1);
    }
    if (b && divisor > (*this)) divisor.shift(-1);
    int maximal = 0;
    string s = string(divisor);
    while(s.size() > 1 && s.back() == '0') { ++maximal; s.pop_back(); }
    while(f <= maximal && f <= n - m){
        ++f;
        ans.shift(1);
        long long coun = 0;
        while((*this) >= divisor){
            (*this) -= divisor;
            ++coun;
        }
        Bignum t;
        t = coun;
        ans += t;
        if (f <= maximal && f <= n - m) divisor.shift(-1);
    }
    f = 0;
    int znak = string(ans).size();
    if (ans.mas.size() == 1 && ans.mas[0] == 0) znak = 0;
    bool zero = false;
    if (ans.mas.size() == 1 && ans.mas[0] == 0) zero = true;
    int zeros = 0;
    while(f <= max(tochnost, temp.tochnost)){
        if (mas.size() == 1 && mas[0] == 0) break;
        ++f;
        long long coun = 0;
        shift(1);
        while((*this) >= divisor && string(divisor) != "0"){
            (*this) -= divisor;
            ++coun;
        }
        Bignum t;
        t = coun;
        if (f > 1 && ans.mas.size() == 1 && ans.mas[0] == 0) ++zeros;
        ans.shift(1);
        ans += t;
    }
    ans.exponent = string(ans).size() - znak;
    ans.tochnost = ans.exponent;
    (*this) = ans;
    neg = flag;
    if (exponent) delete_end_zero();
    exponent += zeros;
    return (*this);
}
Bignum& Bignum::operator%=(Bignum const& temp){
    //if (temp.mas.size() == 1 && temp.mas[0] == 0) throw domain_error("Modulo by zero");
    if (temp.mas.size() == 1 && temp.mas[0] == 0) throw new MathException("Modulo by zero");
    Bignum divisor = temp;
    int sh = max(exponent, divisor.exponent);
    shift(sh - exponent);
    divisor.shift(sh - divisor.exponent);
    exponent = 0;
    divisor.exponent = 0;
    int n = (mas.size() - 1) * POW, m = (divisor.mas.size() - 1) * POW;
    int k = mas[mas.size() - 1];
    while(k > 0){ ++n; k /= 10; }
    k = divisor.mas[divisor.mas.size() - 1];
    while(k > 0){ ++m; k /= 10; }
    bool flag = neg;
    divisor.neg = false;
    neg = false;
    divisor.shift(n - m);
    int f = 0;
    if ((*this) < divisor && n > m) { divisor.shift(-1); ++f; }
    while(f <= n - m){
        ++f;
        while((*this) >= divisor){
            (*this) -= divisor;
        }
        divisor.shift(-1);
    }
    exponent = sh;
    if (flag){
        neg = flag;
        if (!temp.neg) (*this) += temp;
        else (*this) -= temp;
    }
    if (exponent) delete_end_zero();
    return (*this);
}


namespace SlavaScript{ namespace lang{
    istream& operator>>(istream& is, Bignum& temp){
        string s;
        is >> s;
        temp = Bignum(s);
        return is;
    }
    ostream& operator<<(ostream& os, const Bignum& temp){
        os << string(temp);
        return os;
    }



    Bignum& operator+(Bignum a, Bignum const& b){
        return a += b;
    }
    Bignum& operator-(Bignum a, Bignum const& b){
        return a -= b;
    }
    Bignum& operator*(Bignum a, Bignum const& b){
        return a *= b;
    }
    Bignum& operator/(Bignum a, Bignum const& b){
        return a /= b;
    }
    Bignum& operator%(Bignum a, Bignum const& b){
        return a %= b;
    }


    bool operator==(Bignum const& a, Bignum const& b){
        if (a.mas.size() == b.mas.size() && a.neg == b.neg && a.exponent == b.exponent && a.mas == b.mas) return true;
        else return false;
    }
    bool operator!=(Bignum const& a, Bignum const& b){
        return !(a == b);
    }
    bool operator<(Bignum const& a, Bignum const& b){
        if (a.neg && !b.neg) return true;
        if (!a.neg && b.neg) return false;
        if (!a.neg){
            string s = string(a), s2 = string(b);
            if (s.size() - a.exponent - bool(a.exponent) < s2.size() - b.exponent - bool(b.exponent) || s.size() - a.exponent - bool(a.exponent) == s2.size() - b.exponent - bool(b.exponent) && s[0] == '0' && s2[0] != '0') return true;
            if (s.size() - a.exponent - bool(a.exponent) > s2.size() - b.exponent - bool(b.exponent) || s.size() - a.exponent - bool(a.exponent) == s2.size() - b.exponent - bool(b.exponent) && s2[0] == '0' && s[0] != '0') return false;
            for(int i = 0; i < min(s.size(), s2.size()); ++i){
                if (s[i] == '.' && s2[i] >= '0' && s2[i] <= '9') return true;
                if (s2[i] == '.' && s[i] >= '0' && s[i] <= '9') return false;
                if (s[i] > s2[i]) return false;
                if (s[i] < s2[i]) return true;
            }
            if (s.size() < s2.size()) return true;
            return false;
        }
        else{
            string s = string(a), s2 = string(b);
            if (s.size() - a.exponent - bool(a.exponent) < s2.size() - b.exponent - bool(b.exponent) || s.size() - a.exponent - bool(a.exponent) == s2.size() - b.exponent - bool(b.exponent) && s.size() > 1 && s2.size() > 1 && s[1] == '0' && s2[1] != '0') return false;
            if (s.size() - a.exponent - bool(a.exponent) > s2.size() - b.exponent - bool(b.exponent) || s.size() - a.exponent - bool(a.exponent) == s2.size() - b.exponent - bool(b.exponent) && s.size() > 1 && s2.size() > 1 && s2[1] == '0' && s[1] != '0') return true;
            for(int i = 1; i < min(s.size(), s2.size()); ++i){
                if (s[i] == '.' && s2[i] >= '0' && s2[i] <= '9') return false;
                if (s2[i] == '.' && s[i] >= '0' && s[i] <= '9') return true;
                if (s[i] > s2[i]) return true;
                if (s[i] < s2[i]) return false;
            }
            if (s.size() < s2.size()) return false;
            return false;
        }
    }
    bool operator>(Bignum const& a, Bignum const& b){
        return b < a;
    }
    bool operator<=(Bignum const& a, Bignum const& b){
        return !(b < a);
    }
    bool operator>=(Bignum const& a, Bignum const& b){
        return !(a < b);
    }
}}
