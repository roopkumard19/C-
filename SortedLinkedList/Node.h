#ifndef NODE_H_
#define NODE_H_

using namespace std;

template <typename T>
class Node
{
public:
    Node(T value);
    ~Node();

    T data;
    Node *next;
};

template <typename T>
Node<T>::Node(T value) : data(value), next(nullptr)
{
}

template <typename T>
Node<T>::~Node()
{
}

#endif /* NODE_H_ */
