#ifndef _TVFORMAT_
#define _TVFORMAT_
#include "Person.hpp"
#include <cstring>

class TVFormat {
	Person** people;
	unsigned peopleCount;
	Person* host;
	char** events;
	unsigned eventCount;

	void copy(const TVFormat& other);
	void clear() const;
public:
	TVFormat(unsigned peopleCount, const Person** people, const Person* host, unsigned eventCount);
	TVFormat(const TVFormat& other);
	TVFormat& operator=(const TVFormat& other);
	virtual ~TVFormat();

	virtual void doEvent() = 0;
	void printFormatInformation() const;
	void showEvents(unsigned limit) const;

	virtual TVFormat* clone() const = 0;

	Person* getHost() const {
		return host;
	}

	Person* getParticapant(int index) const {
		return people[index];
	}

	char* getEvent(int index) {
		return events[index];
	}

	void addEvent(char* description) {
		for (int i = 0; i < eventCount; i++) {
			if (events[i] == nullptr) {
				events[i] = new char[strlen(description) + 1];
				strcpy(events[i], description);
				return;
			}
		}
	}

	void nullify(int index) {
		people[index] = nullptr;
	}
};

TVFormat::TVFormat(unsigned peopleCount, const Person** people, const Person* host, unsigned eventCount) {
	if (peopleCount > MAX_ARR_SIZE || eventCount>MAX_ARR_SIZE) {
		throw std::invalid_argument("Exceeded maximum number of array size");
	}
	this->peopleCount = peopleCount;
	this->eventCount = eventCount;

	this->people = new Person * [peopleCount];
	for (int i = 0; i < peopleCount; i++) {
		this->people[i] = people[i] ? new Person(*people[i]) : nullptr;
	}

	this->events = new char* [eventCount];
	for (int i = 0; i < eventCount; i++) {
		this->events[i] = nullptr;
	}

	this->host = new Person(*host);
}

void TVFormat::clear() const {
	delete host;
	for (int i = 0; i < peopleCount; i++) {
		if(people[i]) delete people[i];
	}
	delete[] people;
	for (int i = 0; i < eventCount; i++) {
		if(events[i]) delete events[i];
	}
	delete[] events;
}

void TVFormat::copy(const TVFormat& other)  {
	if (other.peopleCount > MAX_ARR_SIZE || other.eventCount > MAX_ARR_SIZE) {
		throw std::invalid_argument("Exceeded maximum number of array size");
	}
	this->peopleCount = other.peopleCount;
	this->eventCount = other.eventCount;

	this->people = new Person * [peopleCount];
	for (int i = 0; i < peopleCount; i++) {
		this->people[i] = other.people[i] ? new Person(*other.people[i]) : nullptr;
	}

	this->events = new char* [eventCount];
	for (int i = 0; i < eventCount; i++) {
		this->events[i] = nullptr;
	}

	this->host = new Person(*other.host);
}

TVFormat::TVFormat(const TVFormat& other) {
	copy(other);
}

TVFormat& TVFormat::operator=(const TVFormat& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

TVFormat::~TVFormat() {
	clear();
}

void TVFormat::showEvents(unsigned limit) const {
	if (limit > eventCount) {
		std::cout << "Input exceeds number of events";
	}
	for (int i = 0; i < eventCount; i++) {
		if (events[i]) std::cout << *events[i];
	}
}

void TVFormat::printFormatInformation() const {
	std::cout << *host;

	for (int i = 0; i < peopleCount; i++) {
		std::cout << *people[i];
	}
}

#endif // !_TVFORMAT_
