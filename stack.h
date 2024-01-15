#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include <list>
#include <deque>

namespace STL_Container
{
    template <class T, class Container = deque<T>>
    class stack
    {
    private:
        Container base;
    public:
        bool            empty() const           {   return base.empty(); }
        size_type       size()  const           {   return base.size(); }
        const_reference top()                   {   return base.back(); }
        void            push(const_reference n) {   base.push_back(n);  }
        void            pop()                   {   base.pop_back();    }          
    };

}   // namespace STL_Container


#endif /* STACK_H_ */
