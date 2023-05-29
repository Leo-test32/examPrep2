#ifndef _KITCHENBULGARIA_
#define _KITCHENBULGARIA_
#include "KitchenFormat.hpp"

template <typename T>
class KitchenBulgaria : public KitchenFormat {
private:
	T hiddenChallenge;
public:
	KitchenBulgaria(T hiddenChallenge, const Person** people, const Person* host, unsigned eventCount) : KitchenFormat(12, people, host, eventCount) {
		this->hiddenChallenge = hiddenChallenge;

		for (int i = 0; i < 12; i++) {
			if (this->getParticapant(i) == nullptr) {
				throw std::invalid_argument("Participant can't be nullptr");
			}
		}
	}

	TVFormat* clone() const;

	void printFormatInformation() const;
};

template <typename T>
TVFormat* KitchenBulgaria<T>::clone() const {
	return new KitchenBulgaria(*this);
}

template <typename T>
void KitchenBulgaria<T>::printFormatInformation() const {
	std::cout << *host;
	std::cout << hiddenChallenge << std::endl;

	for (int i = 0; i < peopleCount; i++) {
		std::cout << *people[i];
	}
}
#endif // !_KITCHENBULGARIA_
