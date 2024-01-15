#ifndef LIST_H_
#define LIST_H_

#include <iostream>

using namespace std;

namespace STL_Container
{
    template <calss T>
    class list
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        

    private:
        struct node
        {
            value_type data;
            node* next;
            node* prev;
            node(): next(nullptr), prev(nullptr) {}
        };
        node* head;         // beginning of the list 
        node* tail;         // end of the list
        size_type num;      // number of nodes in the list
    
    public:
        // iterator
        class iterator
        {
            node* cur;
        public:
            iterator(node* pos): cur(pos) {} 
            value_type& operator*()
            {
                return cur -> data;
            }

            // pre-increment
            iterator operator++()
            {
                cur = cur -> next;
                return *this;
            }

            // post-increment
            iterator operator++(int)
            {
                iterator tmp(cur);
                cur = cur -> next;
                return tmp;
            }

            // pre-decrement
            iterator operator--()
            {
                cur = cur -> prev;
                return *this;
            }

            // post-decrement
            iterator operator--(int)
            {
                iterator tmp(cur);
                cur = cur -> prev;
                return tmp;
            }
            bool operator==(const iterator& iter) const
            {
                return cur == iter.cur;
            }
            bool operator!=(const iterator& iter) const
            {
                return cur != iter.cur;
            }
        };

    public:
        // contructor
        list(): num(0)
        {
            head = tail = new node;
        }

        list(const list& l)
        {
            head = tail = new node;
            node* tmp = l.head -> next;
            while (tmp != nullptr)
            {
                push_back(p -> data);
                p = p -> next;
            }
        } 

        // copy contructor
        list& operator=(const list& l)
        {
            if (this == &l) return *this;
            clear();
            node* tmp = l.head -> next;
            while (tmp != nullptr)
            {
                push_back(tmp -> data);
                tmp = tmp -> next;
            }
            return *this;
        }

        void clear()
        {
            node* tmp = head -> next;
            while (tmp != nullptr)
            {
                node* del = tmp;
                tmp = tmp -> next;
                delete del;
            }
            tail = head;
            num = 0;
        }

        // destructor
        ~list()
        {
            node* tmp = head;
            while(tmp != nullptr)
            {
                node* del = tmp
                tmp = tmp -> next;
                delete del;
            }
            num = 0;
        }

        size_type   size()  const   {   return num; }
        bool        empty() const   {   return num == 0;    }
        value_type  front() const   {   return head -> next -> data;    }
        value_type  back()  const   {   return tail -> data;    }

        void push_back(const_reference val)
        {
            node* cur = new node;
            cur -> data = val;
            cur -> next = nullptr;
            cur -> prev = tail;
            tail -> next = cur;
            tail = cur;
            num++;
        }

        void pop_back()
        {
            if (empty())    return;
            node* prev = tail -> prev;
            delete tail;
            prev -> next = nullptr;
            tail = prev;
            num--;
        }
       
        void push_front(const_reference val)
        {
            node* first = head -> next;
            head -> next = first -> next;
            if (first -> next == nullptr)
                tail = head;
            else
                first -> next -> prev = head;
            delete first;
            num--;
        }
    };
}   // namespace STL_Container

#endif 
