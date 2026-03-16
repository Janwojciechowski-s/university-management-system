#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
	std::string first_name;
	std::string last_name;
public:
	Person(const std::string& first, const std::string& last);
	virtual ~Person() {};

	std::string get_first_name() const;
	std::string get_last_name() const;
};

#endif // !PERSON_H