#include "Person.h"

using namespace std;

Person::Person(const std::string& first,const std::string& last) : first_name(first), last_name(last) {}

string Person::get_first_name() const
{
    return this->first_name;
}

string Person::get_last_name() const
{
    return this->last_name;
}