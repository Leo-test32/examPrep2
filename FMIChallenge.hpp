#ifndef _FMICHALLENGE_
#define _FMICHALLENGE_
#include "TVFormat.hpp"

class FMIChallenge : public TVFormat {
	char** games;
	int counter;

	void copy(const FMIChallenge& other);
	void clear() const;

	double findRatio(int index) {
		double ratio = -1;
		ratio = this->getParticapant(index)->getSkills() / this->getParticapant(index)->getAge();

		return ratio;
	}

	int findPlayerIndex() {
		int indexToRemove = -1;
		int ratio = 1;

		for (int i = 0; i < MAX_ARR_SIZE; i++) {
			if (findRatio(i) < ratio) {
				ratio = findRatio(i);
				indexToRemove = i;
			}
		}
		return indexToRemove;
	}

public:
	FMIChallenge(const char** games, const Person** people, const Person* host) : TVFormat(14, people, host, 10) {
		this->games = new char* [10];

		for (int i = 0; i < 10; i++) {
			if (games[i]) {
				this->games[i] = new char[strlen(games[i]) + 1];
				strcpy(this->games[i], games[i]);
			}
			else {
				this->games[i] = nullptr;
			}
		}

		counter = 0;
	}

	FMIChallenge(const FMIChallenge& other);
	FMIChallenge& operator=(const FMIChallenge& other);
	~FMIChallenge();

	TVFormat* clone() const;
	void doEvent();
};

TVFormat* FMIChallenge::clone() const {
	return new FMIChallenge(*this);
}

void FMIChallenge::clear() const {
	for (int i = 0; i < 10; i++) {
		if (games[i]) delete games[i];
	}
	delete[] games;
}

void FMIChallenge::copy(const FMIChallenge& other) {
	this->games = new char* [10];

	for (int i = 0; i < 10; i++) {
		if (other.games[i]) {
			this->games[i] = new char[strlen(other.games[i]) + 1];
			strcpy(this->games[i], other.games[i]);
		}
		else {
			this->games[i] = nullptr;
		}
	}
}

FMIChallenge::FMIChallenge(const FMIChallenge& other) : TVFormat(other) {
	copy(other);
}

FMIChallenge& FMIChallenge::operator=(const FMIChallenge& other) {
	if (this != &other) {
		TVFormat::operator=(other);
		clear();
		copy(other);
	}
	return *this;
}

FMIChallenge::~FMIChallenge() {
	clear();
}

void FMIChallenge::doEvent() {

	char tempString[1024] = "Game was ";
	strcat(tempString, games[counter]);

	delete games[counter];
	games[counter] = nullptr;

	counter++;

	int index = findPlayerIndex();

	strcat(tempString,this->getParticapant(index)->getName());
	strcat(tempString, " was eliminated.");
	this->addEvent(tempString);

	delete this->getParticapant(index);
	this->nullify(index);
}

#endif // !_FMICHALLNGE_
