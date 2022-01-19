#include <iostream> 
#include <hashmap.h>
#include <linkedlist.h>
#include <set.h>

using namespace std;

// testing file
struct Article {
  string name;
  Article(string _name = "") {
    name = _name;
  }
};

int main() {

  DoublyLinkedList<int> l;

  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  l.push_back(5);
  l.push_back(4);

  Set<int> s(l);

  l.print();
  s.print();


}
