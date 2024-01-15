#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <cassert>
#include <algorithm>

using namespace  std;

namespace STL_Container
{
    template <class T>
    class vector
    {
    public:
        typedef T           value_type;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef T*          iterator;
        typedef const T*    const_iterator;
        iterator        begin();
        iterator        end();
        const_iterator  cbegin()    const;
        const_iterator  cend()      const;

        // constructor and destructor
        vector();
        vector(size_type n, const value_type& val);
        template <class InputIter>
        vector(InputIter first, InputIter last);
        vector(const vector& v);
        vector& operator=(vector& v);
        ~vector();

        // capacity related operations
        size_type   size()      const;
        size_type   capacity()  const;
        bool        empty()     const;
        void        reserve(size_type n);
        void        resize(size_type n, const value_type& val);

        // access
        reference       operator[](size_type n);
        const_reference operator[](size_type n) const;

        // modify
        void push_back(const value_type& val);
        void pop_back();
        void swap(vector& v);

        // insert
        iterator insert(iterator pos, const value_type& val);
        iterator erase(iterator pos);

    private:
        iterator start;    // the beginning of the data
        iterator end;     // the end of the data
        iterator cap;     // the end of the storage
    };

    // constructors
    vector():start(nullptr), end(nullptr), cap(nullptr) {}

    template <class InputIter>
    vector(InputIter first, InputIter last):
        start(nullptr), end(nullptr), cap(nullptr)
    {
        for (InputIter iIter = first; iIter != last; iIter++)
            push_back(*iIter);
    }

    vector(const vector<T>& v):
        start(nullptr), end(nullptr), cap(nullptr)
    {
        vector<T> tmp(v.begin(), v.end());
        swap(tmp);
    }

    // swap
    void swap(vector<T>& v)
    {
        std::swap(start, v.start);
        std::swap(end, v.end);
        std::swap(cap, v.cap);
    }

    vector<T>& operator=(vector<T> v)
    {
        swap(v);
        return *this;
    }

    // destructor
    ~vector()
    {
        delete [] start;
        start = end = cap = nullptr;
    }

    // size 
    size_type size() const
    {
        return end - start;
    }

    // capacity
    size_type capacity() const
    {
        return cap - start;
    }

    bool empty()
    {
        return size() == 0;
    }

    // reserve
    void reserve(size_type n)
    {
        if (n > capacity())
        {
            size_type num = end - start;
            iterator tmp = new value_type[num];
            if (start)
            {
                for (int i = 0; i < num; ++i)
                    tmp[i] = start[i];
                delete [] start;
            }
            start = tmp;
            end = tmp + num;
            cap = start + n;
        }
    }

    // resize
    void resize(size_type n,  const value_type& val)
    {
        if (n > size())
        {
            reserve(n);
            while (end != start + n)
            {
                *end = val;
                end++;
            }
        }
        else
            end = start + n;
    }

    // operator []
    reference operator[](size_type n)
    {
        return *(start + n);
    }

    // push_back
    void push_back(const value_type& val)
    {
        if (end == cap)
        {
           reserve(capacity() == 0? 16 : capacity()*2);
        }
        *end = val;
        end++;
    }
    
    // pop_back
    void pop_back()
    {
        assert(end > start);
        end--;
    }

    // insert
    iterator insert(iterator iter, const value_type& val)
    {
        assert(iter >= start);
        assert(iter <= end);
        if (end == cap)
        {
            size_type num = iter - start;
            reserve(capacity() == 0 ? 16 : capacity()*2);
            iter = start + num;
        }
        iterator it = end - 1;
        while (it != iter)
        {
            *(it + 1) = *it;
            it--;
        }
        *end = val;
        end++;
        return iter;
    }

    // erase
    iterator erase(iterator iter)
    {
        assert(iter >= start);
        assert(iter < end);
        iterator it = iter + 1;
        while(it != end)
        {
            *(it - 1) = *it;
            it++;
        }
        end--;
        return iter;
    }
    
}   // namespace STL_Container







#endif 