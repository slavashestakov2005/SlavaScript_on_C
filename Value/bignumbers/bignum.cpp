#include "bignum.h"
#include <sstream>
#include <algorithm>
#include "../values.h"
#include "../../Exception/mathexception.h"
#include "../../Exception/typeexception.h"
#include "../../Lib/utils.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::MathException;
using SlavaScript::exceptions::TypeException;

UnsignedBig UnsignedBig::pow_10_to_n(int n){
    UnsignedBig b = UnsignedBig::ONE;
    b.shift(n);
    return b;
}

void UnsignedBig::delete_end_zero(){
    while(digits.size() && !digits.back()) digits.pop_back();
    if (digits.empty()) digits.push_back(0);
}

void UnsignedBig::shift(int position){
    if (digits.size() == 1 && digits[0] == 0) return;
    if (position > 0){
        int x = 1;
        for(int i = 0; i < position % UnsignedBig::POW; ++i) x *= 10;
        (*this) *= UnsignedBig(x);
        shift10(position / UnsignedBig::POW);
    }
    if (position < 0){
        shift(UnsignedBig::POW - (-position % UnsignedBig::POW));
        shift10(position / UnsignedBig::POW - bool(position));
    }
}

void UnsignedBig::shift10(int position){
    if (digits.size() == 1 && digits[0] == 0) return;
    if (position > 0){
        std::vector<int> new_digits(position, 0);
        for(int x : digits) new_digits.push_back(x);
        digits = new_digits;
    }
    if (position < 0){
        std::vector<int> new_digits;
        for(int i = -position; i < digits.size(); ++i) new_digits.push_back(digits[i]);
        if (new_digits.empty()) new_digits.push_back(0);
        digits = new_digits;
    }
}

int UnsignedBig::size() const{
    int cur = digits.back(), cnt = 0;
    while(cur) ++cnt, cur /= 10;
    return UnsignedBig::POW * (digits.size() - 1) + cnt;
}

int UnsignedBig::get_sign() const{
    return digits.size() > 1 || digits[0];
}

UnsignedBig::UnsignedBig(){
    digits.push_back(0);
}

UnsignedBig::UnsignedBig(UnsignedBig const& b){
    digits = b.digits;
}

UnsignedBig::UnsignedBig(int n){
    digits.clear();
    while(n){
        digits.push_back(n % UnsignedBig::BASE);
        n /= UnsignedBig::BASE;
    }
    if (digits.empty()) digits.push_back(0);
}

UnsignedBig::UnsignedBig(long long n){
    digits.clear();
    while(n){
        digits.push_back(n % UnsignedBig::BASE);
        n /= UnsignedBig::BASE;
    }
    if (digits.empty()) digits.push_back(0);
}

UnsignedBig::UnsignedBig(std::string s){
    for(int i = s.size() - 1; i > -1; i -= UnsignedBig::POW){
        int current = 0;
        for(int j = std::max(0, i - UnsignedBig::POW + 1); j <= i; ++j){
            current *= 10;
            current += s[j] - '0';
        }
        digits.push_back(current);
    }
}

UnsignedBig& UnsignedBig::operator=(UnsignedBig const& temp){ digits = temp.digits; return *this; }
UnsignedBig& UnsignedBig::operator=(int temp){ return *this = UnsignedBig(temp); }
UnsignedBig& UnsignedBig::operator=(long long temp){ return *this = UnsignedBig(temp); }
UnsignedBig& UnsignedBig::operator=(std::string s){ return *this = UnsignedBig(s); }

UnsignedBig::operator bool() const{
    if (digits.size() == 1 && digits[0] == 0) return false;
    else return true;
}

UnsignedBig::operator std::string() const{
    std::ostringstream str;
    str << digits.back();
    for(int i = digits.size() - 2; i > -1; --i){
        std::string s = UnsignedBig::EXAMPLE;
        int l = digits[i], coun = UnsignedBig::POW - 1;
        while(l > 0){
            s[coun] += l % 10;
            --coun;
            l /= 10;
        }
        str << s;
    }
    return str.str();
}

UnsignedBig& UnsignedBig::operator++(){
    return *this += UnsignedBig::ONE;
}

UnsignedBig UnsignedBig::operator++(int){
    UnsignedBig temp = *this;
    ++*this;
    return temp;
}

UnsignedBig& UnsignedBig::operator--(){
    return *this -= UnsignedBig::ONE;
}

UnsignedBig UnsignedBig::operator--(int){
    UnsignedBig temp = *this;
    --*this;
    return temp;
}

UnsignedBig& UnsignedBig::operator+=(UnsignedBig const& temp){
    std::vector<int> new_digits;
    int carry = 0;
    for(int i = 0; i < digits.size() || i < temp.digits.size() || carry; ++i){
        if (i < digits.size()) carry += digits[i];
        if (i < temp.digits.size()) carry += temp.digits[i];
        new_digits.push_back(carry % UnsignedBig::BASE);
        carry /= UnsignedBig::BASE;
    }
    digits = new_digits;
    delete_end_zero();
    return *this;
}

UnsignedBig& UnsignedBig::operator-=(UnsignedBig const& temp){
    std::vector<int> new_digits;
    int carry = 0;
    for(int i = 0; i < digits.size() || i < temp.digits.size() || carry; ++i){
        bool take = false;
        if (i < digits.size()) { take = true; carry += digits[i]; }
        if (i < temp.digits.size()) { take = true; carry -= temp.digits[i]; }
        int coun = 0;
        if (carry < 0){ carry += UnsignedBig::BASE; ++coun; }
        new_digits.push_back(carry % UnsignedBig::BASE);
        carry = -coun;
        if (!take) break;
    }
    digits = new_digits;
    delete_end_zero();
    return *this;
}

UnsignedBig& UnsignedBig::operator*=(UnsignedBig const& temp){
    std::vector<int> new_digits(digits.size() + temp.digits.size(), 0);
    for(int i = 0; i < digits.size(); ++i){
        int carry = 0;
        for(int j = 0; j < temp.digits.size(); ++j){
            long long l = (long long)digits[i] * temp.digits[j] + new_digits[i + j] + carry;
            new_digits[i + j] = l % UnsignedBig::BASE;
            carry = l / UnsignedBig::BASE;
        }
        new_digits[i + temp.digits.size()] = carry;
    }
    digits = new_digits;
    delete_end_zero();
    return *this;
}

UnsignedBig& UnsignedBig::operator/=(UnsignedBig const& temp){
    if (!temp) throw new MathException("Division by zero");
    if ((*this) < temp){
        digits.clear();
        digits.push_back(0);
        return *this;
    }
    UnsignedBig divisior(temp);
    int steps = size() - temp.size();
    divisior.shift(steps);
    ++steps;
    std::string result;
    if (*this < divisior) divisior.shift(-1), --steps;
    for(int i = 0; i < steps; ++i){
        int cnt = 0;
        while(*this >= divisior){
            *this -= divisior;
            ++cnt;
        }
        result += char('0' + cnt);
        divisior.shift(-1);
    }
    *this = UnsignedBig(result);
    delete_end_zero();
    return *this;
}

UnsignedBig& UnsignedBig::operator%=(UnsignedBig const& temp){
    if (!temp) throw new MathException("Modulo by zero");
    UnsignedBig divisior(temp);
    int steps = size() - temp.size();
    divisior.shift(steps);
    ++steps;
    if (*this < divisior) divisior.shift(-1), --steps;
    for(int i = 0; i < steps; ++i){
        while(*this >= divisior){
            *this -= divisior;
        }
        divisior.shift(-1);
    }
    delete_end_zero();
    return *this;
}


namespace SlavaScript::lang{
    std::istream& operator>>(std::istream& is, UnsignedBig& temp){
        std::string s;
        is >> s;
        temp = UnsignedBig(s);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const UnsignedBig& temp){
        os << std::string(temp);
        return os;
    }

    CMP(UnsignedBig){
        CHECK(a.size(), b.size());
        RCHECK(std::string(a), std::string(b));
    }

    CLS_OPS(UnsignedBig)
}


void Bignum::delete_end_zero(){
    std::string s = std::string(value);
    if (s == "0"){ dot = 0; return; }
    int cnt = 0, pos = s.size() - 1;
    while(pos > -1 && s[pos] == '0') --pos, ++cnt;
    value.shift(-std::min(cnt, dot));
    dot -= std::min(cnt, dot);
}

int Bignum::get_sign() const{
    if (sign == Bignum::MINUS) return -1;
    return value.get_sign();
}

Bignum::Bignum() : value(UnsignedBig::ZERO), sign(PLUS), dot(0) {}

Bignum::Bignum(std::string s){
    std::string r;
    int pos = 0;
    if (s[0] == '-') sign = MINUS, ++pos;
    else sign = PLUS;
    dot = 0;
    for(; pos < s.size(); ++pos){
        if (dot) ++dot;
        if (s[pos] != '.'){
            if ('0' <= s[pos] && s[pos] <= '9') r += s[pos];
            else throw new TypeException(std::string("Cannot cast symbol \"") + s[pos] + "\" to number");
        }
        else dot = 1;
    }
    dot = std::max(dot - 1, 0);
    value = r;
    delete_end_zero();
}

Bignum::Bignum(Bignum const& temp){
    value = temp.value;
    sign = temp.sign;
    dot = temp.dot;
}

Bignum::Bignum(int temp){
    dot = 0;
    sign = (temp >= 0 ? PLUS : MINUS);
    value = abs(temp);
}

Bignum::Bignum(long long temp){
    dot = 0;
    sign = (temp >= 0 ? PLUS : MINUS);
    value = abs(temp);
}

Bignum::Bignum(double temp){
    std::ostringstream ss;
    std::string s;
    ss << std::fixed << temp;
    s = ss.str();
    *this = Bignum(s);
}

Bignum& Bignum::operator=(Bignum const& temp){
    value = temp.value;
    sign = temp.sign;
    dot = temp.dot;
    return *this;
}

Bignum& Bignum::operator=(std::string s){ return *this = Bignum(s); }
Bignum& Bignum::operator=(int temp){ return *this = Bignum(temp); }
Bignum& Bignum::operator=(long long temp){ return *this = Bignum(temp); }
Bignum& Bignum::operator=(double temp){ return *this = Bignum(temp); }

Bignum::operator bool() const{ return bool(value); }

Bignum::operator double() const{
    std::istringstream is(std::string(*this));
    double result;
    is >> result;
    return result;
}

Bignum::operator std::string() const{
    std::string s = std::string(value), r;
    std::reverse(s.begin(), s.end());
    while(s.size() <= dot) s += "0";
    std::reverse(s.begin(), s.end());
    if (sign == MINUS) r += "-";
    for(int i = 0; i < s.size() - dot; ++i) r += s[i];
    if (dot) r += ".";
    for(int i = s.size() - dot; i < s.size(); ++i) r += s[i];
    return r;
}

Bignum Bignum::operator-(){
    Bignum temp(*this);
    temp.sign = !sign;
    return temp;
}

Bignum Bignum::operator+(){
    return *this;
}

Bignum& Bignum::operator++(){
    if (sign == PLUS) ++value;
    else --value;
    if (!value) sign = PLUS;
    return *this;
}

Bignum Bignum::operator++(int){
    Bignum temp = *this;
    ++*this;
    return temp;
}

Bignum& Bignum::operator--(){
    if (!value) sign = MINUS;
    if (sign == PLUS) --value;
    else ++value;
    return *this;
}

Bignum Bignum::operator--(int){
    Bignum temp = *this;
    --*this;
    return temp;
}

Bignum& Bignum::operator+=(Bignum const& temp){
    Bignum t(temp);
    int dots = std::max(dot, t.dot);
    value.shift(dots - dot);
    t.value.shift(dots - t.dot);
    if (sign == t.sign) value += t.value;
    else{
        if (value == t.value) sign = PLUS;
        else sign = (value > t.value ? sign : !sign);
        value = std::max(value, t.value) - std::min(value, t.value);
    }
    dot = dots;
    delete_end_zero();
    return *this;
}

Bignum& Bignum::operator-=(Bignum const& temp){
    Bignum t(temp);
    int dots = std::max(dot, t.dot);
    value.shift(dots - dot);
    t.value.shift(dots - t.dot);
    if (sign != t.sign) value += t.value;
    else{
        if (value == t.value) sign = PLUS;
        else sign = (value > t.value ? sign : !sign);
        value = std::max(value, t.value) - std::min(value, t.value);
    }
    dot = dots;
    delete_end_zero();
    return *this;
}

Bignum& Bignum::operator*=(Bignum const& temp){
    value *= temp.value;
    sign = (sign == temp.sign ? PLUS : MINUS);
    dot += temp.dot;
    delete_end_zero();
    return *this;
}

Bignum& Bignum::operator/=(Bignum const& temp){
    Bignum t(temp);
    int dots = std::max(dot, t.dot);
    value.shift(dots - dot + EPS);
    t.value.shift(dots - t.dot);
    value /= t.value;
    sign = (sign == t.sign ? PLUS : MINUS);
    dot = EPS;
    delete_end_zero();
    return *this;
}

Bignum& Bignum::operator%=(Bignum const& temp){
    Bignum t(temp);
    int dots = std::max(dot, t.dot);
    value.shift(dots - dot);
    t.value.shift(dots - t.dot);
    value %= t.value;
    if (sign == MINUS) value = t.value - value;
    sign = PLUS;
    dot = dots;
    delete_end_zero();
    return *this;
}


namespace SlavaScript::lang{
    std::istream& operator>>(std::istream& is, Bignum& temp){
        std::string s;
        is >> s;
        temp = Bignum(s);
        return is;
    }

    std::ostream& operator<<(std::ostream& os, const Bignum& temp){
        os << std::string(temp);
        return os;
    }

    CMP(Bignum){
        std::string s = std::string(a), t = std::string(b);
        int n = s.find('.'), m = t.find('.');
        n = (n == std::string::npos ? s.size() : n);
        m = (m == std::string::npos ? t.size() : m);
        std::string s1 = s.substr(0, n), s2 = s.substr(n), t1 = t.substr(0, m), t2 = t.substr(m);
        if (s[0] == '-' && t[0] != '-') return -1;
        if (t[0] == '-' && s[0] != '-') return 1;
        if (s[0] == '-'){
            CHECK(t1, s1);
            RCHECK(s2, t2);
        }
        CHECK(s1, t1);
        RCHECK(s2, t2);
    }

    CLS_OPS(Bignum)
}


Bignum RationalBig::div() const{
    return numerator / denominator;
}

RationalBig::RationalBig() : numerator(Bignum::ZERO), denominator(Bignum::ONE) {}
RationalBig::RationalBig(RationalBig const& temp) : numerator(temp.numerator), denominator(temp.denominator) {}
RationalBig::RationalBig(Bignum numerator) : numerator(numerator), denominator(Bignum::ONE) {}
RationalBig::RationalBig(Bignum numerator, Bignum denominator) : numerator(numerator), denominator(denominator) {
    if (!denominator) throw new MathException("Division by zero");
}

RationalBig::operator bool() const{ return bool(numerator); }
RationalBig::operator std::string() const{ return div(); }
std::string RationalBig::frac() const{ return "(" + std::string(numerator) + "/" + std::string(denominator) + ")"; }
RationalBig::operator Bignum() const{ return div(); }

RationalBig RationalBig::operator-(){
    RationalBig r(*this);
    r.numerator = -r.numerator;
    return r;
}

RationalBig& RationalBig::operator+=(RationalBig const& temp){
    numerator = numerator * temp.denominator + temp.numerator * denominator;
    denominator *= temp.denominator;
    return *this;
}

RationalBig& RationalBig::operator-=(RationalBig const& temp){
    numerator = numerator * temp.denominator - temp.numerator * denominator;
    denominator *= temp.denominator;
    return *this;
}

RationalBig& RationalBig::operator*=(RationalBig const& temp){
    numerator *= temp.numerator;
    denominator *= temp.denominator;
    return *this;
}

RationalBig& RationalBig::operator/=(RationalBig const& temp){
    numerator *= temp.denominator;
    denominator *= temp.numerator;
    if (!denominator) throw new MathException("Division by zero");
    return *this;
}


namespace SlavaScript::lang{
    CMP(RationalBig){
        RCHECK(Bignum(a), Bignum(b));
    }

    BINARY_OP(RationalBig, +) BINARY_OP(RationalBig, -) BINARY_OP(RationalBig, *) BINARY_OP(RationalBig, /)
    DEF_CMP(RationalBig)
}
