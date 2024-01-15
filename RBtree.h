#ifndef RBTREE_H_
#define RBTREE_H_

namespace STL_Container
{
    enum Color
    {
        black;
        red;
    };

    template <class T>
    struct rbtreeNode
    {   
        typedef rbtreeNode<T> node;
        T val;
        node* parent;
        node* left;
        node* right;
        Color col;

        rbtreeNode(const T& data):
            val(data), left(nullptr), right(nullptr), parent(nullptr), col(red) {}
    };


    template <class T, class ref, class ptr>
    class rbtreeIter
    {
        typedef retreeNode<T>*   node;
        typedef rbtreeIter<T, ref, ptr> Self;
        
        ref operator*()     {   return node -> val; }
        ptr operator->()    {   return &node -> val;}

        bool operator!=(const Self& self)   const   
        {   return node != self.node;   }
        
        bool operator==(const Self& self)   const
        {   return node == self.node;   }

        Self& operator++()
        {
            if (node -> right)
            {
                node tmp = node -> right;
                while (tmp -> left)
                    tmp = tmp -> left;
                node = tmp;
            }
            else
            {
                node cur = node;
                node tmp = cur -> parent;
                while (tmp && tmp -> right == cur)
                {
                    cur = tmp;
                    tmp = tmp-> parent;
                }
                node = parent;
            }
            return *this;
        }

        Self& operator--()  {   return *this;   }
    };

    template <class K, class T, class Key>
    class rbtree
    {
    public:
        typedef rbtreeNode<T>                       node;
        typedef rbtreeIter<T, T&, T*>               iter;
        typedef rbtreeIter<T, const T&, const T*>   const_iter;
    
    private:
        node* root;
    
    public:
        rbtree() : root(nullptr) {}

        iterator begin()
        {
            node* tmp = root;
            while (tmp && tmp -> left)
                tmp = tmp -> left;
            return iterator(tmp);
        }

        iterator end()
        {
            return iterator(nullptr);
        }

        pair<iterator, bool> Insert(const T& data)
        {
            if (root == nullptr)
            {
                root = new node(data);
                root -> col = black;
                return make_pair(iterator(root), true);
            }
            Key k;
            node* par = nullptr;
            node* cur = root;
            while(cur)
            {
                if (k(cur -> data) < k(data))
                {
                    par = cur;
                    cur = cur -> left;
                }
                else if (k(cur -> data) > k(data))
                {
                    parent = cur;
                    cur = cur -> left;
                }
                else               
                    return make_pair(iterator(cur), false);
            }

            cur = new node(data);
            node* nnode = cur;
            cur -> col = red;

            if (k(par -> data) < k(data))
            {
                par -> right = cur;
                cur -> parent = par;
            }
            else
            {
                par -> left = cur;
                cur -> parent = par;
            }

            while (par && par -> col == red)
            {
                node* gfather = par -> parent;
                if (par == gfather -> left)
                {
                    node* uncle = gfather -> right;
                    if (uncle && uncle -> col == red)
                    {
                        par -> col = uncle -> col = black;
                        gfather -> col = red;
                        cur = gfather;
                        par = cur -> parent;
                    }
                    else
                    {
                        if (cur = par -> left)
                        {
                            rRotate(gfather);
                            par -> col = black;
                            gfather -> col = red;
                        }
                        else
                        {
                            lRotate(par);
                            rRotate(gfather);
                            cur -> col = black;

                            gfather -> col = red;
                        }
                        break;
                    }
                }
                else
                {
                    node* uncle = gfather -> left;
                    if (uncle && uncle -> col == red)
                    {
                        par -> col = uncle -> col = black;
                        gfather -> col = red;
                        cur = gfather;
                        par = cur -> parent;
                    }
                    else
                    {
                        if (cur = par -> right)
                        {
                            lRotate(gfather);
                            par -> col = black;
                            gfather -> col = red;
                        }
                        else
                        {
                            rRotate(par);
                            lRotate(gfather);
                            cur -> col = black;
                            gfather -> col = red;
                        }
                        break;
                    }
                }
            }
            root -> col = black;
            return make_pair(iterator(nnode), true);
        }

        void rRotate(node* par)
        {
            node* subL = par -> left;
            node* subLR = subL -> right;
            par -> left = subLR;
            if (subLR)
            {
                subLR -> parent = par;
            }
            node* gpnode = par -> parent;

            subL -> right = par;
            par -> parent = subL;

            if (par == root)
            {
                root = subL;
                subL -> parent = nullptr;
            }
            else
            {
                if (gpnode -> left == par)
                    gpnode -> left = subL;
                else 
                    gpnode -> right = subL;
                subL -> parent = gpnode;
            }
        }

        void lRotate(node* par)
        {
            node* subR = par -> right;
            node* subRL = subR -> left;

            parent -> right = subRL;
            if (subRL)
                subRL -> parent = par;
            node* gpnode = par -> parent;
            subR -> left = par;
            par -> parent = subR;

            if (par == root)
            {
                root = subR;
                subR -> parent = nullptr;
            }
            else
            {
                if (gpnode -> left == par)
                    gpnode -> left = subR;
                else
                    gpnode -> right = subR;
                subR -> parent = gpnode;
            }   
        }
        
        void InOrder_(node* Root)
        {
            if (Root == nullptr)    return;
            InOrder_(Root -> left);
            cout << Root -> kv.first << " ";
            InOrder_(Root -> right);
        }

        void InOrder()
        {
            InOrder_(root);
        }

        bool check(node* cur)
        {
            if (cur == nullptr) 
                return true;
            if (cur -> col == red && cur -> parent -> col == red)
                return false;
            return check(cur -> left) && check(cur -> right);
        }

        bool checkBnum(node* cur, int bnum, int target)
        {
            if (cur == nullptr)
            {
                if (bnum != target)
                    return false;
                return true;
            }
            if (cur -> col == black)
                ++bnum;
            return checkBnum(cur -> left, bnum, target) && checkBnum(cur -> right, bnum, target);
        }

        bool IsBalance()
        {
            if (root == nullptr)    return true;
            if (root -> col == red) return false;
            
            int target = 0;
            node* cur = root;
            while(cur)
            {
                if (cur -> col == black)
                    ++target;
                cur = cur -> left;
            }
            int bnum = 0;
            return check(root) && checkBnum(root, bnum, target);
        }
    };

}   // namespace STL_Container

#endif /* RBTREE_H_ */
