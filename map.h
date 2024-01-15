#ifndef MAP_H_
#define MAP_H_

#include "RBtree.h"

namespace STL_Container
{
    template <class K, class V>
    class map
    {
        struct MapKey
        {
            const K& operator()(const pair<const K, V>& kv)
            {
                return kv.first;
            }
        };

    private:
        rbtree<K, pair<const K, V>, MapKey> rbt;

    public:
        typedef typename rbtree<K, pair<const K, V>, MapKey>::iterator iterator;
        
        iterator begin()    
        {
            return rbt.begin();
        }

        iterator end()
        {
            return rbt.end();
        }

        pair<iterator, bool> insert(const pair<const K, V>& kv)
        {
            return rbt.insert(kv);
        }

        V& operator[](const K& key)
        {
            pair<iterator, bool> ret = rbt.insert(make_pair(key, V()));
            return ret.first -> second;
        }
    };

}   // namespace STL_Container

#endif /* MAP_H_ */
