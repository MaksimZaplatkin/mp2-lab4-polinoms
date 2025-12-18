#include "polinom.h"
#include <iostream>
#include "monom.h"
#include <string>
#include <math.h>

using namespace std;

void Polinom::Podobniy()
{
    if (IsEmpty() || sz == 1)
    {
        return;
    }
    Sort();
    TSinglyList<Monom> newList;
    TSinglyList<Monom>::Iterator it = begin();
    Monom cur = *it;
    ++it;
    while (it != end())
    {
        if (cur == *it)
        {
            cur = cur + (*it);
        }
        else
        {
            if (!cur.isZero())
            {
                newList.PushBack(cur);
            }
            cur = *it;
        }
        ++it;
    }
    if (!cur.isZero())
    {
        newList.PushBack(cur);
    }
    Clear();
    for (Iterator it = newList.begin(); it != newList.end(); ++it)
    {
        PushBack(*it);
    }
}

void Polinom::Parsing(const string& str)
{
    string s = str + '+';
    size_t i = 0;
    while (i < s.length())
    {
        while (i < s.length() && s[i] == ' ')
        {
            i++;
        }
        if (i >= s.length()) break;

        double sign = 1.0;
        if (s[i] == '+')
        {
            i++;
        }
        else if (s[i] == '-')
        {
            sign = -1.0;
            i++;
        }

        double coef = 1.0;
        string coefStr = "";
        while (i < s.length() && (isdigit(s[i]) || s[i] == '.' || s[i] == 'e' || s[i] == 'E'||(coefStr.size()==0 && s[i]=='-')))
        {
            coefStr += s[i];
            i++;
        }
        if (!coefStr.empty())
        {
            coef = stod(coefStr);
        }

        int xDeg = 0, yDeg = 0, zDeg = 0;
        while (i < s.length() && s[i] != '+' && s[i] != '-')
        {
            char var = s[i];
            i++;

            int deg = 1;
            if (i < s.length() && s[i] == '^')
            {
                i++;
                string degStr = "";
                while (i < s.length() && isdigit(s[i]))
                {
                    degStr += s[i];
                    i++;
                }
                if (!degStr.empty())
                {
                    deg = stoi(degStr);
                }
            }

            switch (var)
            {
            case 'x': case 'X': xDeg = deg; break;
            case 'y': case 'Y': yDeg = deg; break;
            case 'z': case 'Z': zDeg = deg; break;
            }

            if (i < s.length() && s[i] == '*') i++;
        }

        int totalDeg = xDeg * 100 + yDeg * 10 + zDeg;
        if (coefStr.empty() && xDeg == 0 && yDeg == 0 && zDeg == 0)
        {
            coef = 0.0;
        }

        set(Monom(sign * coef, totalDeg));
    }

    Podobniy();
}

void Polinom::set(Monom mono)
{
    if (mono.isZero())
    {
        return;
    }
    if (IsEmpty() || mono < Front())
    {
        PushFront(mono);
    }
    else
    {
        TSinglyList<Monom>::Iterator it = begin();
        size_t pos = 0;
        bool inserted = false;
        while (it != end())
        {
            if (mono < *it)
            {
                if (pos == 0)
                {
                    PushFront(mono);
                }
                else
                {
                    PushAfter(pos - 1, mono);
                }
                inserted = true;
                break;
            }
            ++it;
            ++pos;
        }
        if (!inserted)
        {
            PushBack(mono);
        }
    }
}

void Polinom::erase(Monom mono)
{
    size_t pos = 0;
    TSinglyList<Monom>::Iterator it = begin();
    while (it != end())
    {
        if (*it == mono)
        {
            Remove(pos);
            return;
        }
        ++it;
        ++pos;
    }
}

void Polinom::erase(int index)
{
    Remove(index);
}

int Polinom::find(Monom mono)
{
    int pos = 0;
    TSinglyList<Monom>::Iterator it = begin();
    while (it != end())
    {
        if (*it == mono)
        {
            return pos;
        }
        ++it;
        ++pos;
    }
    return -1;
}

Polinom& Polinom::operator=(const Polinom& other)
{
    if (this != &other)
    {
        TSinglyList<Monom>::operator=(other);
    }
    return *this;
}

Polinom Polinom::operator +(const Polinom& other) const
{
    Polinom res;
    TSinglyList<Monom>::Iterator it1 = begin();
    TSinglyList<Monom>::Iterator it2 = other.begin();
    while (it1 != end() && it2 != other.end())
    {


        if (*it1 == *it2)
        {
            Monom sum = *it1 + *it2;
            if (!sum.isZero())
            {
                res.PushBack(sum);
            }
            ++it1;
            ++it2;
        }
        else if (*it1 < *it2)
        {
            res.PushBack(*it1);
            ++it1;
        }
        else
        {
            res.PushBack(*it2);
            ++it2;
        }
    }
    while (it1 != end())
    {
        res.PushBack(*it1);
        ++it1;
    }
    while (it2 != other.end())
    {
        res.PushBack(*it2);
        ++it2;
    }
    return res;
}

Polinom Polinom::operator *(const Polinom& other) const
{
    Polinom res;
    TSinglyList<Monom>::Iterator it1 = begin();
    while (it1 != end())
    {
        TSinglyList<Monom>::Iterator it2 = other.begin();
        while (it2 != other.end())
        {
            res.set((*it1) * (*it2));
            ++it2;
        }
        ++it1;
    }
    res.Podobniy();
    return res;
}

Polinom Polinom::operator *(double scalar) const
{
    if (abs(scalar - 0) < 1e-6)
    {
        return Polinom();
    }
    Polinom res;
    TSinglyList<Monom>::Iterator it = begin();
    while (it != end())
    {
        res.set((*it) * scalar);
        ++it;
    }
    return res;
}

double Polinom::Evaluate(double x, double y, double z) const
{
    double res = 0.0;
    TSinglyList<Monom>::Iterator it = begin();
    while (it != end())
    {
        Monom& mono = *it;
        double term = mono.getCoef();
        if (mono.getXDegree() > 0)
        {
            term *= pow(x, mono.getXDegree());
        }
        if (mono.getYDegree() > 0)
        {
            term *= pow(y, mono.getYDegree());
        }
        if (mono.getZDegree() > 0)
        {
            term *= pow(z, mono.getZDegree());
        }
        res += term;
        ++it;
    }
    return res;
}

Polinom Polinom::Proizvodnaya_po_perem(char var) const
{
    Polinom res;
    TSinglyList<Monom>::Iterator it = begin();
    while (it != end())
    {
        Monom mono = *it;
        double newCoef = mono.getCoef();
        int x = mono.getXDegree();
        int y = mono.getYDegree();
        int z = mono.getZDegree();
        switch (var)
        {
        case'x':
        case'X':
            if (x > 0)
            {
                newCoef *= x;
                mono.setXDegree(x - 1);
                mono.setCoef(newCoef);
                res.set(mono);
            }
            break;

        case'y':
        case'Y':
            if (y > 0)
            {
                newCoef *= y;
                mono.setYDegree(y - 1);
                mono.setCoef(newCoef);
                res.set(mono);
            }
            break;

        case'z':
        case'Z':
            if (z > 0)
            {
                newCoef *= z;
                mono.setZDegree(z - 1);
                mono.setCoef(newCoef);
                res.set(mono);
            }
            break;
        }
        ++it;

    }
    return res;
}

Polinom Polinom::Proizvodnaya_full() const
{
    Polinom res;
    res = Proizvodnaya_po_perem('x') + Proizvodnaya_po_perem('y') + Proizvodnaya_po_perem('z');
    return res;
}