/*
* Bartosz Dobrzycki, 14 Jan 2014
* Doubly Linked List
*/

/* Use this makefile
*
* CC = clang++
* CXXFLAGS = -Wall -std=c++0x
*
* linkuj: kompiluj
*	$(CC) doublyLinkedList.o -o doublyLinkedList $(CXXFLAGS)
*	rm *.o
*
* kompiluj:
*	$(CC) -c doublyLinkedList.cpp $(CXXFLAGS)
*
*/

#include <cmath>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// These objects will be stored on the doubly linked list.
class Foo
{
private:
    int m_data;
    
public:    
    explicit Foo ( int data )
        :m_data( data )
    {}
    
    inline void setData( int newData ) { m_data = newData; }
    inline int getData( void ) const { return m_data; }
};
////////////////////////////////////////////////////////////////////////////////

// List
template <typename T>
class DoublyLinkedList
{
public:
    // List node.
    class Node
    {
    public:
        Node* m_next;
        Node* m_prev;
        T* const m_key; //< Pointer to any type of object (Foo in this example). 
    
        explicit Node( T* key )
            :m_next( nullptr ), m_prev( nullptr ), m_key( key )
        {} 
    };    

    DoublyLinkedList()
        :m_head( nullptr ), m_tail( nullptr )
    {}
  
    inline Node *const getHead() { return m_head; } 
  
    // Insert
    void insert ( T* elem )
    {
        Node* newNode = new Node( elem );
            
        newNode->m_next = m_head;
      
        if ( m_head != nullptr )
        {
            m_head->m_prev = newNode;
        }
      
        m_head = newNode;
      
        newNode->m_prev = nullptr;
    }
    
    // TODO
    void deleteElement ( const T* key )
    {
        Node* node = search( key );
        deleteElement ( node );
    }
    
    void deleteNode ( Node* node )
    {
        if ( node->m_prev != nullptr )
        {
            node->m_prev->m_next = node->m_next;
        }
        else
        {
            m_head = node->m_next;
        }
        
        if ( node->m_next != nullptr )
        {
            node->m_next->m_prev = node->m_prev;
        }
        
        delete node->m_key;
    }
        
private:
    Node* m_head;
    Node* m_tail;
    
    // Search for a node with key.
    Node* search( const T* key )
    {
        Node* node = m_head;
      
        while ( node != nullptr && node->m_key != key )
        {
            node = node->m_next;
        }
      
        return node;
    }
};
////////////////////////////////////////////////////////////////////////////////

// Print
void print( DoublyLinkedList< Foo > & list )
{
    DoublyLinkedList< Foo >::Node* node = list.getHead();
    
    std::cout << "DoublyLinkedList< Foo >: { "; 
    
    while ( node != nullptr )
    {     
        std::cout << node->m_key->getData() << " , ";
           
        node = node->m_next;
    }
    
    std::cout << " }" << std::endl;
}

// Change values for each node in the list.
void update( DoublyLinkedList< Foo >& list )
{
    DoublyLinkedList< Foo >::Node* node = list.getHead();
       
    while ( node != nullptr )
    {     
        node->m_key->setData( 222 );
           
        node = node->m_next;
    }
}

// Erase all elements.
void erase( DoublyLinkedList< Foo >& list )
{
    DoublyLinkedList< Foo >::Node* node = list.getHead();
       
    while ( node != nullptr )
    {     
        list.deleteNode( node );
        node = node->m_next;
    }
}
////////////////////////////////////////////////////////////////////////////////
  
int main ( int argc, char **argv )
{
    DoublyLinkedList< Foo > fooList;
    fooList.insert( new Foo (155) );
    fooList.insert( new Foo (166) ); 
  
    print( fooList ); 
      
    update( fooList );
    print( fooList );
    
    erase( fooList );
    print( fooList );
   
    std::cin.get();
    return 0;
}
