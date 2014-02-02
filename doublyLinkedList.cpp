/*
* Bartosz Dobrzycki, 2 Feb 2014
* Doubly Linked List
*/

// Memory leaks detection (WIN).
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

// These objects will be stored on the doubly linked list.
class Foo
{
private:
    int m_data;

public:
    explicit Foo( int data )
        : m_data( data )
    {

    }

    ~Foo()
    {
        std::cout << "~Foo() " << m_data << std::endl;
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
            : m_next( nullptr ), m_prev( nullptr ), m_key( key )
        {

        }

        ~Node()
        {
            std::cout << "~Node()" << std::endl;
            delete m_key;
        }
    };

    DoublyLinkedList()
        : m_head( nullptr ), m_tail( nullptr )
    {

    }

    ~DoublyLinkedList()
    {
        deallocate();
    }

    void deallocate( void )
    {
        Node* node = getHead();
        while( node != nullptr )
        {
            Node* nodeNext = node->m_next;
            deleteNode( node );
            node = nodeNext;
        }
        m_head = nullptr;
        m_tail = nullptr;
    }

    inline Node* const getHead() const { return m_head; }
    inline Node* const getTail() const { return m_tail; }

    // Insert
    void insert( T* element )
    {
        Node* newNode = new Node( element );
        newNode->m_next = m_head;
        if( m_head != nullptr )
        {
            m_head->m_prev = newNode;
        }
        else
        {
            m_tail = newNode;
        }
        m_head = newNode;
        newNode->m_prev = nullptr;
    }

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
        else
        {
            m_tail = node->m_prev;
        }

        delete node;
    }

private:
    Node* m_head;
    Node* m_tail;
};

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

    if( list.getHead() )
    {
        std::cout << "head: " << list.getHead()->m_key->getData() << std::endl;
    }

    if( list.getTail() )
    {
        std::cout << "tail: " << list.getTail()->m_key->getData() << std::endl;
    }
}

void deleteElement( DoublyLinkedList< Foo > & list, int data )
{
    DoublyLinkedList< Foo >::Node* node = list.getTail();
    while( node != 0 && node->m_key->getData() != data )
    {
        node = node->m_prev;
    }

    if( node )
    {
        std::cout << "deleting: " << node->m_key->getData() << std::endl;
        list.deleteNode( node );
    }
    else
    {
        std::cout << data << " not found!" << std::endl;
    }
}

int main( int argc, char **argv )
{
    DoublyLinkedList< Foo > fooList;
    fooList.insert( new Foo( 1 ) );
    fooList.insert( new Foo( 4 ) );
    fooList.insert( new Foo( 16 ) );
    fooList.insert( new Foo( 9 ) );
    fooList.insert( new Foo( 25 ) );

    print( fooList );
    deleteElement( fooList, 4 );
    print( fooList );
    deleteElement( fooList, 1 );
    print( fooList );
    deleteElement( fooList, 25 );
    print( fooList );
    deleteElement( fooList, 25 );
    print( fooList );

    fooList.deallocate();

    fooList.insert( new Foo( 1 ) );
    print( fooList );
    deleteElement( fooList, 1 );
    print( fooList );

    // _CrtDumpMemoryLeaks returns TRUE if a memory leak is found.
    // Otherwise, the function returns FALSE.
    if( _CrtDumpMemoryLeaks() )
    {
        std::cout << "Warning: memory leak found!" << std::endl;
    }
    else
    {
        std::cout << "Memory OK" << std::endl;
    }
    std::cin.get();
    return 0;
}
