#ifndef SET_H_
#define SET_H_

#include "RBtree.h"

namespace STL_Container
{
    template <class K>
    class set
    {   
        struct SetKey
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
    
    private:
        rbtree<K, K, SetKey> rbt;

    public:
        typedef typename rbtree<K, K, SetKey>::iterator iterator;

        iterator begin()
        {
            return rbt.begin();
        }

        iterator end()
        {
            return rbt.end();
        }

        pair<iterator, bool> insert(const K& key)
        {
            return rbt.insert(key);
        }
    };

}   // namespace STL_Container

#endif /* SET_H_ */
