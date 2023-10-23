#include "list.h"


List::List()
{
    first = nullptr;
    last = nullptr;
}


bool
List::is_empty()
{
  if (first == nullptr) 
  {
    return true;
  } 
  else
  {
    return false;
  }
}


void
List::clear()
{
    while (first != nullptr){
        remove_back();
    }
}



void
List::push_front(int _val)
{
    Node* push = new Node (_val);
    if (is_empty()== true) 
    {
        first = push;
        last = push;
    }
    else 
    {
        push -> next = first;
        first = push;
    }
}


void
List::push_back(int _val)
{
     Node* push = new Node (_val);
    if (is_empty()== true) 
    {
        first = push;
        last = push;
    }
    else
    {
        last -> next = push;
        last = push;
    }

}


Node*
List::find(int _val)
{
    if (is_empty())
    {
        return nullptr;
    }
    Node* ind = first;
    while (ind != nullptr){
        if (ind -> val == _val){
            return ind;
        }
        ind = ind ->next;
    }
    return nullptr;

}


void
List::remove_front()
{
    if (is_empty()){
        return;
    }
    if (first == last)
    {
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* _first = first;
    first = first -> next;
    delete _first;

}


void
List::remove_back()
{
    if (is_empty()){
        return;
    }
    if (first == last)
    {
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* prelast = first;
    while (prelast -> next != last){
        prelast = prelast ->next;
    }
    prelast -> next = nullptr;
    last = prelast;
}


bool
List::remove(const Node* _node)
{
     if (is_empty() || _node == nullptr || find(_node -> val) == nullptr){
        return false;
    }
    if (_node == first){
        remove_front();
        return true;
    }
    if (_node == last){
        remove_back();
        return true;
    }
    Node* ind = first;
    while (ind ->next != _node){
        ind = ind ->next;
    }
    ind->next = _node->next;
    delete _node;
    return true;
}
