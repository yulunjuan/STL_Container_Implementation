#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <vector>

using namespace std;

namespace STL_Container
{
    template <class T>
    struct greater
    {   
        bool operator() (const_reference a, const_reference b)
        {
            return a > b;
        }
    };

    template <class T>
    struct less
    {   
        bool operator() (const_reference a, const_reference b)
        {
            return a < b;
        }
    };

    template <class T, class Container = vector<T>, class Compare = Greater<T>>
    class priority_queue
    {
    private:
        Container   base;
    
    private:
        void shift_up(size_type child)
        {
            Compare com;
            size_type father = (child - 1)/2;
            while (child > 0)
            {
                if (com(base[father], base[child]))
                {
                    std::swap(base[child], base[father]);
                    child = father;
                    father = (child - 1)/2;
                }
                else
                    break;
            }
        }
        void shift_down(size_type father)
        {
            Compare com;
            size_type child = father * 2 + 1;
            while (child < base.size())
            {
                if (child + 1 < base.size() && com(base[child], base[child + 1]))
                    child++;
                if (com(base[father], base[child]))
                {
                    std::swap(base[father], base[child]);
                    father = child;
                    child = father * 2 + 1;
                }
                else
                    break;
            }
        }
    public:
        priority_queue() {}

        template <class InputIter>
        priority_queue(InputIter first, InputIter last):base(first, last)
        {
            for (int i = (base.size() - 1)/2; i >= 0; --i)
                shift_down(i);
        }

        bool            empty() const   {   return base.empty();    }
        size_type       size()  const   {   return base.size(); }
        const_reference top()   const   {   return base[0]; }

        void push(const_reference n)
        {
            base.push_back(n);
            shift_up(base.size() - 1);
        }

        void pop()
        {
            std::swap(base[0], base[base.size() - 1]);
            base.pop_back();
            shift_down(0);
        }
    };

}   // namespace STL_Container

#endif /* PRIORITY_QUEUE_H_ */
