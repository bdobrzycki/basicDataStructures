/*
* Bartosz Dobrzycki, 2 Feb 2014
* Doubly Linked List
*/

// Memory leaks detection (WIN).
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <cmath>
#include <iostream>

// These objects will be stored on the doubly linked list.
class Foo
{
private:
    int m_data;

public:
    explicit Foo ( int data )
        :m_data( data )
    {

    }

    ~Foo()
    {

    }

    inline void setData( int newData ) { m_data = newData; }
    inline int getData( void ) const { return m_data; }
};

// List
template <typename T>
class DoublyLinkedList
{
public:
    class Node
    {
    public:
        Node*     m_next;
        Node*     m_prev;
        T* const  m_key;

        explicit Node( T* key )
            :m_next( nullptr ), m_prev( nullptr ), m_key( key )
        {

        }

        ~Node()
        {
            delete m_key;
        }
    };

    DoublyLinkedList()
        : m_head( nullptr ), m_tail( nullptr )
    {

    }

    ~DoublyLinkedList()
    {
        Node* node = getHead();
        while( node != nullptr )
        {
            deleteNode( node );
            Node* nodeNext = node->m_next;
            delete node;
            node = nodeNext;
        }
    }

    inline Node *const getHead() { return m_head; }

    // Insert
    void insert( T* element )
    {
        Node* newNode = new Node( element );
        newNode->m_next = m_head;
        if( m_head != nullptr )
        {
            m_head->m_prev = newNode;
        }
        m_head = newNode;
        newNode->m_prev = nullptr;
    }

private:
    void deleteNode( Node* node )
    {
        if( node->m_prev != nullptr )
        {
            node->m_prev->m_next = node->m_next;
        }
        else
        {
            m_head = node->m_next;
        }

        if( node->m_next != nullptr )
        {
            node->m_next->m_prev = node->m_prev;
        }
    }

    Node* m_head;
    Node* m_tail;
};

// Print
void print( DoublyLinkedList< Foo > & list )
{
    DoublyLinkedList< Foo >::Node* node = list.getHead();
    std::cout << "DoublyLinkedList< Foo >: { ";
    while ( node != nullptr )
    {
        std::cout << node->m_key->getData();
        node = node->m_next;
        if( node )  {
            std::cout << " , ";
        }
    }
    std::cout << " }" << std::endl;
}

int main( int argc, char **argv )
{
    DoublyLinkedList< Foo > fooList;
    for( int i = 0; i < 10; i++ )
    {
        fooList.insert( new Foo( i ) );
    }
    print( fooList );
    fooList.~DoublyLinkedList();
    _CrtDumpMemoryLeaks();
    return 0;
}
