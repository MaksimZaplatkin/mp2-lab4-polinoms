// класс или структура Монома (double коэффициент, целая свернутая степень)
#pragma once
#include <vector>
#include <stdexcept>

#include <iostream>

using namespace std;

template<typename T> class TSinglyList
{
    struct TNode
    {
        T value;
        TNode* pNext;
        TNode(const T& val, TNode* next = nullptr) : value(val), pNext(next) {}
    };
protected:
    TNode* pFirst;
    TNode* pLast;
    size_t sz;
public:
    bool operator ==(const TSinglyList other) const
    {
        if (sz != other.sz)
        {
            return false;
        }
        TNode* cur = pFirst;
        TNode* curp = other.pFirst;
        while (cur)
        {
            if (cur->value != curp->value)
            {
                return false;
            }
            cur = cur->pNext;
            curp = curp->pNext;
        }
        return true;

    }
    TSinglyList()
    {
        pFirst = nullptr;
        pLast = nullptr;
        sz = 0;
    }
    TSinglyList(const vector<T>& v)
    {
        pFirst = nullptr;
        pLast = nullptr;
        sz = 0;
        sz = v.size();
        for (size_t i = 0; i < v.size(); i++)
        {
            PushBack(v[i]);
        }
    }
    TSinglyList(const TSinglyList& list)
    {
        pFirst = nullptr;
        pLast = nullptr;
        sz = 0;
        TNode* cur = list.pFirst;
        while (cur)
        {
            PushBack(cur->value);
            cur = cur->pNext;
        }
    }
    TSinglyList(TSinglyList&& list) noexcept : TSinglyList()
    {
        swap(sz, list.sz);
        swap(pLast, list.pLast);
        swap(pFirst, list.pFirst);
    }
    void Clear()
    {
        while (!IsEmpty())
        {
            PopFront();
        }
    }
    TSinglyList& operator=(const TSinglyList& list)
    {

        if (this != &list)
        {
            Clear();
            TNode* cur = list.pFirst;
            while (cur)
            {
                PushBack(cur->value);
                cur = cur->pNext;
            }
        }
        return *this;
    }
    TSinglyList& operator=(TSinglyList&& list) noexcept
    {
        if (this != &list)
        {
            Clear();
            swap(sz, list.sz);
            swap(pFirst, list.pFirst);
            swap(pLast, list.pLast);
        }
        return *this;
    }
    virtual ~TSinglyList()
    {
        Clear();
    }
    size_t size() const noexcept
    {
        return sz;
    }
    bool IsEmpty() const noexcept
    {
        return(sz == 0);
    }
    T& Front() noexcept
    {
        if (IsEmpty())
        {
            throw out_of_range("Pusto");
        }
        return pFirst->value;
    }
    void PushFront(const T& val)
    {
        TNode* newNode = new TNode(val, pFirst);
        pFirst = newNode;
        if (!pLast)
        {
            pLast = newNode;
        }
        sz++;
    }
    void PushBack(const T& val)
    {
        TNode* newNode = new TNode(val);
        if (!pFirst)
        {
            pLast = newNode;
            pFirst = pLast;
        }
        else
        {
            pLast->pNext = newNode;
            pLast = newNode;
        }
        sz++;
    }
    void PopFront()
    {
        if (pFirst == nullptr)
        {
            throw out_of_range("Nizya tak chtobi udalyat nichto");
        }
        TNode* tmp = pFirst;
        pFirst = tmp->pNext;
        delete tmp;
        sz--;
        if (!pFirst)
        {
            pLast = nullptr;
        }
    }
    void PushAfter(size_t pos, const T& val)
    {
        if (pos >= sz)
        {
            throw out_of_range("perebor");
        }
        TNode* cur = pFirst;
        for (size_t i = 0; i < pos; i++)
        {
            cur = cur->pNext;
        }
        TNode* newNode = new TNode(val, cur->pNext);
        cur->pNext = newNode;
        if (cur == pLast)
        {
            pLast = newNode;
        }
        sz++;
    }
    void EraseAfter(size_t pos)
    {
        if (pos >= sz - 1 || IsEmpty())
        {
            throw out_of_range("Nizya tak chtobi udalyat nichto");
        }
        TNode* cur = pFirst;
        for (size_t i = 0; i < pos; i++)
        {
            cur = cur->pNext;
        }
        TNode* Deleted = cur->pNext;
        if (Deleted)
        {
            cur->pNext = Deleted->pNext;
            if (Deleted == pLast)
            {
                pLast = cur;
            }
            delete Deleted;
            sz--;
        }
    }
    void Remove(size_t pos)
    {
        if (pos >= sz)
        {
            throw out_of_range("Daleko ushel");
        }
        if (pos == 0)
        {
            PopFront();
        }
        else
        {
            EraseAfter(pos - 1);
        }
    }
    struct Iterator
    {
        TNode* current;
        Iterator(TNode* node = nullptr) : current(node) {}
        T& operator*() { return current->value; }
        const T& operator*() const { return current->value; }
        Iterator& operator++()
        {
            if (current)
            {
                current = current->pNext;
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator!=(const Iterator& other)
        {
            return current != other.current;
        }
        bool operator==(const Iterator& other)
        {
            return current == other.current;
        }
    };
    Iterator begin() const
    {
        return Iterator(pFirst);
    }
    Iterator end() const
    {
        return Iterator(nullptr);
    }
    void Sort()
    {
        if (IsEmpty() || sz == 1)
        {
            return;
        }
        bool swapped = true;
        while (swapped)
        {
            swapped = false;
            TNode* prev = nullptr;
            TNode* cur = pFirst;
            while (cur != nullptr && cur->pNext != nullptr)
            {
                if (!(cur->value < cur->pNext->value) && !(cur->value == cur->pNext->value))
                {
                    TNode* next = cur->pNext;
                    cur->pNext = next->pNext;
                    next->pNext = cur;
                    if (prev)
                    {
                        prev->pNext = next;
                    }
                    else
                    {
                        pFirst = next;
                    }
                    if (cur == pLast)
                    {
                        pLast = next;
                    }
                    swapped = true;
                    prev = next;
                }
                else
                {
                    prev = cur;
                    cur = cur->pNext;
                }
            }
        }
    }
};

class Monom
{
private:
    double coef;
    int deg;
public:
    Monom() :coef(0.0), deg(0) {}
    Monom(double coeff, int degr)
    {
        coef = coeff;
        deg = degr;
    }
    double getCoef() const;
    int getDegrees() const;
    void setCoef(double coeff);
    void setDegrees(int degr);
    int getXDegree() const;
    int getYDegree() const;
    int getZDegree() const;
    void setXDegree(int x);
    void setYDegree(int y);
    void setZDegree(int z);
    Monom operator +(const Monom& other) const;
    Monom operator *(double scalar)const;
    Monom operator *(const Monom& other) const;
    bool operator <(const Monom& other) const;
    bool operator ==(const Monom& other) const;
    bool operator !=(const Monom& other)const;
    bool isZero()const;
    friend ostream& operator<<(ostream& os, const Monom& m)
    {
        if (m.isZero())
        {
            os << "0";
            return os;
        }
        bool needCoef = true;
        if (m.getXDegree() == 0 && m.getYDegree() == 0 && m.getZDegree() == 0)
        {
            os << m.coef;
            return os;
        }
        if (m.coef != 1.0 && m.coef != -1.0)
        {
            os << m.coef;
            needCoef = false;
        }
        else if (m.coef == -1.0)
        {
            os << "-";
            needCoef = false;
        }
        if (m.getXDegree() > 0)
        {
            os << "x";
            if (m.getXDegree() > 1)
            {
                os << "^" << m.getXDegree();
            }
            needCoef = false;
        }
        if (m.getYDegree() > 0)
        {
            os << "y";
            if (m.getYDegree() > 1)
            {
                os << "^" << m.getYDegree();
            }
            needCoef = false;
        }
        if (m.getZDegree() > 0)
        {
            os << "z";
            if (m.getZDegree() > 1)
            {
                os << "^" << m.getZDegree();
            }
            needCoef = false;
        }
        return os;
    }
};