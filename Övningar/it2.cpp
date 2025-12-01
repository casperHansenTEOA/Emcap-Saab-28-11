#include <iostream>
#include <stack>

template <typename T>
class BST
{
    struct Node
    {
        T value;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        Node(const T &v) : value(v) {}
    };

    Node *root = nullptr;

public:
    BST() = default;

    void insert(const T &value)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }
        Node *cur = root;
        Node *prev = nullptr;
        while (cur)
        {
            prev = cur;
            if (value < cur->value)
                cur = cur->left;
            else
                cur = cur->right;
        }
        Node *n = new Node(value);
        n->parent = prev;
        if (value < prev->value)
            prev->left = n;
        else
            prev->right = n;
    }

    class iterator
    {
        Node *current = nullptr;

        // Hjälpfunktioner
        static Node *leftmost(Node *n)
        {
            if (!n)
                return nullptr;
            while (n->left)
                n = n->left;
            return n;
        }

        static Node *rightmost(Node *n)
        {
            if (!n)
                return nullptr;
            while (n->right)
                n = n->right;
            return n;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        iterator() = default;
        explicit iterator(Node *n) : current(n) {}

        reference operator*() const { return current->value; }
        pointer operator->() const { return &current->value; }
        // incrementing a bst is the same as finding the next in-order node
        // this is done by going to the right child and then all the way to the left
        iterator &operator++()
        {
            // Nästa i in-order
            if (!current)
                return *this;
            if (current->right)
            {
                current = leftmost(current->right);
            }
            else
            {
                Node *p = current->parent;
                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p; // kan bli nullptr = end()
            }
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator &operator--()
        {
            // Föregående i in-order
            // Om current == nullptr: gå till största elementet (end()--).
            if (!current)
                return *this;
            if (current->left)
            {
                current = rightmost(current->left);
            }
            else
            {
                Node *p = current->parent;
                while (p && current == p->left)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator==(const iterator &other) const
        {
            return current == other.current;
        }

        bool operator!=(const iterator &other) const
        {
            return !(*this == other);
        }

        friend class BST;
    };

    iterator begin() const
    {
        return iterator(min_node(root));
    }

    iterator end() const
    {
        return iterator(nullptr);
    }

private:
    static Node *min_node(Node *n)
    {
        if (!n)
            return nullptr;
        while (n->left)
            n = n->left;
        return n;
    }
};

// Exempelanvändning
int main()
{
    BST<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);

    for (auto it = tree.begin(); it != tree.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}