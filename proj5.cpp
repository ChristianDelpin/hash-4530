#include <iostream>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

void Menu();

//        usrnme  passwd
HashTable<string, string> table;

int main()
{
  char choice = ' ';

  while(choice != 'x')
  {
    Menu();
    cin >> choice;
    switch(choice)
    {
      case 'l':
        break;
      case 'a':
        break;
      case 'r':
        break;
      case 'c':
        break;
      case 'f':
        break;
      case 'd':
        break;
      case 'w':
        break;
      case 'x':
        break;
      default:
        cout << "Invalid input. " << endl;
        break;
    }
  }
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
