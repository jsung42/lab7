#if !defined (QUEUELINKED_H)
#define QUEUELINKED_H

#include "NextNode.h"

template < class T >
class QueueLinked
{

   private:
      NextNode<T>* back;
      int sze;

   public:
      QueueLinked();
      ~QueueLinked();
      bool isEmpty();
      int size();
      void dequeueAll(); 
      T* peek();
      T* dequeue();
      void enqueue(T* item);

};

template < class T >
QueueLinked<T>::QueueLinked()
{
   back = NULL;
   sze = 0;
}

template < class T >
QueueLinked<T>::~QueueLinked()
{
   dequeueAll();
}

template < class T >
bool QueueLinked<T>::isEmpty()
{
    return sze == 0;
}

template < class T >
int QueueLinked<T>::size()
{
    return sze;
}

template < class T >
void QueueLinked<T>::dequeueAll()
{
   if (sze == 0) return;

   NextNode<T>* prev = NULL;
   NextNode<T>* curr = back->getNext();  //the head
   back->setNext(NULL);  //break the bridge link

   while (curr != NULL)
   {
      prev = curr;
      curr = curr->getNext();
      delete prev;
   }

   sze = 0;
}

template < class T >
T* QueueLinked<T>::peek()
{
    T* item = NULL;
    if (!isEmpty()) 
    {  
      // queue is not empty; retrieve front
      NextNode<T>* head = back->getNext();
      item = head->getItem();
    }
    return item;
}

template < class T >
void QueueLinked<T>::enqueue(T* item)
{
    NextNode<T>* node = new NextNode<T>(item);

    //DO THIS (enqueueing the first item is a special case)
	if(sze == 0)
	{
		back = node;
		back->setNext(back);
		sze++;
		return;
	}
		
	NextNode<T>* front = back->getNext();
	back->setNext(node);
	node->setNext(front);
	back = node;
    sze++;
}

template < class T >
T* QueueLinked<T>::dequeue()
{
    T* item = NULL;
    //DO THIS (dequeueing the last item is a special case)
    //also, check that there are items before dequeueing
	if(sze == 0)
	{
		return item;
	}
	if(sze == 1)
	{
		item = back->getItem();
		back = NULL;
		sze--;
		return item;	
	}
	NextNode<T>* front = back->getNext();
	item = front->getItem();
	//front = front->getNext();
	back->setNext(front->getNext());
	sze--;
    return item;
}

#endif
