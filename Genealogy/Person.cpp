#include <iostream>
#include <string>
#include <vector>
#include "Person.h"
using namespace std;

/**
 * Default constructor
 */
Person::Person()
    : level(0), name(""), spouse_name(""), parent(nullptr)
{
}

/**
 * Constructor
 */
Person::Person(int level, string name)
    : level(level), name(name), spouse_name(""), parent(nullptr)
{
}

/**
 * Constructor
 */
Person::Person(int level, string name, string spouse_name)
    : level(level), name(name), spouse_name(spouse_name), parent(nullptr)
{
}

/**
 * Destructor
 */
Person::~Person()
{
    // Recursively delete the children.
    for (Person *child : children) delete child;
}

/**
 * Have a child.
 * @param child pointer to the new child.
 */
void Person::have_child(Person *child)
{
    children.push_back(child);
    child->parent = this;
}

/**
 * Print a person.
 */
void Person::print() const
{
    if (parent == nullptr) cout << "+---";

    // Print the name and the spouse's name, if any.
    cout << name;
    if (spouse_name.length() > 0)
    {
        cout << " (" << spouse_name << ")";
    }
    cout << endl;

    // Print the children, if any.
    for (Person *child : children)
    {
        // Print any preceding bars.
        print_bar(); cout << "|" << endl;
        print_bar();

        // Recursively print a child.
        child->print();
    }
}

/**
 * Print the vertical bar.
 */
void Person::print_bar() const
{
    if (parent != nullptr)
    {
        // Recursively print my parent's bar.
        parent->print_bar();

        // Am I my parent's last child?
        if (this == parent->children.back()) cout << "    ";  // yes
        else                                 cout << "|   ";  // no
    }
}
