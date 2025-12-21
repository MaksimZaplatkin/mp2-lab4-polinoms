// класс Полином - упорядоченный односвязный список Мономов
// поддерживает операции Печать, Вставка монома, Удаление монома,  
// Поиск монома, Сложение полиномов(слияние упорядоченных списков), 
// Умножение полиномов
#pragma once

#include <iostream>
#include "monom.h"
#include <string>

using namespace std;

class Polinom : public TSinglyList<Monom>
{
public:
    Polinom() :TSinglyList <Monom>() {}
    Polinom(const vector<Monom>& v) : TSinglyList<Monom>(v)
    {
        Sort();
        Podobniy();
    }
    Polinom(const Polinom& other) : TSinglyList<Monom>(other)
    {
        Sort();
        Podobniy();
    }
    Polinom(Polinom&& other) noexcept : TSinglyList<Monom>(std::move(other)) {}
    Polinom(string str)
    {
        Parsing(str);
    }
    virtual ~Polinom() {}

    friend std::ostream& operator << (std::ostream& os, const Polinom& poli)
    {

        if (poli.IsEmpty() || (poli.size() == 1 && abs(poli.pFirst->value.getCoef()) < 1e-6))
        {
            os << "0";
            return os;
        }
        bool first = true;
        TSinglyList<Monom>::Iterator it = poli.begin();

        while (it != poli.end())
        {
            Monom m = *it;
            if (!first && m.getCoef() > 0)
            {
                os << "+";
            }
            if (m.getCoef() != 0)
            {
                os << m;
                first = false;
            }
            ++it;
        }
        return os;
    }
    void Podobniy();
    friend std::istream& operator >> (std::istream& in, Polinom& poli)
    {
        poli.Clear();
        string str;
        getline(in, str);
        poli.Parsing(str);
        return in;
    }
    void Parsing(const string& str);
    void set(Monom mono);
    void erase(Monom mono);
    void erase(int index);
    int find(Monom mono);
    Polinom& operator=(const Polinom& other);
    Polinom& operator=(Polinom&& other) noexcept
    {
        if (this != &other)
        {
            TSinglyList<Monom>::operator=(std::move(other));
        }
        return *this;
    }
    Polinom operator +(const Polinom& other) const;
    Polinom operator *(const Polinom& other) const;
    Polinom operator *(Monom& mono) const
    {
        Polinom res;
        TSinglyList<Monom>::Iterator it1 = begin();
        while (it1 != end())
        {
            res.set((*it1) * (mono));
            ++it1;
        }
        res.Podobniy();
        return res;
    }
    Polinom operator *(double scalar) const;
    friend Polinom operator*(double scalar, const Polinom& poli)
    {
        return (poli * scalar);
    }
    double Evaluate(double x, double y, double z) const;
    Polinom Proizvodnaya_po_perem(char var) const;
    Polinom Proizvodnaya_full() const;
};