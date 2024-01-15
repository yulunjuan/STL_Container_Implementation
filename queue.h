#ifndef QUEUE_H_
#define QUEUE_H_

#include <deque>
#include <list>

namespace STL_Container
{
    template <class T, class Container = deque<T>>
    class queue
    {
    private:
        Container   base;
    public:
        bool            empty() const           {   return base.empty();}
        size_type       size()  const           {   return base.size(); }
        const_reference front()                 {   return base.front();}
        const_reference back()                  {   return base.back(); }
        void            push(const_reference n) {   base.push_front(x); }
        void            pop()                   {   base.pop_front();   }
    };
}   // namespace STL_Container

#endif /* QUEUE_H_ */
