#ifndef _KITCHENFORMAT_
#define _KITCHENFORMAT_
#include "TVFormat.hpp"


class KitchenFormat : public TVFormat {
private:
	 // not sure how to implement teams
public:
	KitchenFormat(const Person** people, const Person* host, unsigned eventCount) : TVFormat(12, people, host, eventCount) {
		for (int i = 0; i < 12; i++) {
			if (this->getParticapant(i) == nullptr) {
				throw std::invalid_argument("Participant can't be nullptr");
			}
		}
	}

	TVFormat* clone() const;
	void doEvent();
};

TVFormat* KitchenFormat::clone() const {
	return new KitchenFormat(*this);
}

#endif // !_KITCHENFORMAT_
