#pragma once

#include<iostream>
#include<linkedlist.h>

using namespace std;

// lower case
string &toLower(string &text);

// lower case and remove space
string &lowerAndRemoveSpace(string &text);

// check if title is okay
bool checkTitle(string title);

// split on basis of delimeiter, store input in linked list
void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output);
