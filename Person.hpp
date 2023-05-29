#ifndef _PERSON_
#define _PERSON_
#include <string>
#include <stdexcept>
#include <iostream>

using std::string;

const unsigned MAX_ARR_SIZE = 10;

class Person {
	static unsigned id;
	string name;
	unsigned age;
	string businessCard;
	double skills;
public:
	Person(const string, const unsigned, const string, const double);

	friend std::ostream& operator<<(std::ostream& os, const Person& obj);

	unsigned getAge() const {
		return age;
	}

	double getSkills() const {
		return skills;
	}

	const char* getName() const {
		return name.c_str();
	}
};

Person::Person(const string name, const unsigned age, const string businessCard, const double skills) : name(name), age(age), businessCard(businessCard), skills(skills) {
	if (skills > 1 || skills < 0) {
		throw std::invalid_argument("Skill must have a value between 0 and 1");
	}

	if (name.length() > 200 || businessCard.length() > 500) {
		throw std::invalid_argument("Name or business card are too long");
	}

	id++;
}

std::ostream& operator<<(std::ostream& os, const Person& obj) {
	os << obj.id << " " << obj.name << " " << obj.age << " " << obj.businessCard << " " << obj.skills << std::endl;

	return os;
}

unsigned Person::id = 0;

#endif // !
