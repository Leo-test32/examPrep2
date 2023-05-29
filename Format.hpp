#ifndef _FORMAT_
#define _FORMAT_
#include "KitchenBulgaria.hpp"
#include "KitchenFormat.hpp"
#include "TVFormat.hpp"

class Format {
	TVFormat** format;
	unsigned formatSize;

	void create(unsigned, TVFormat**);
	void copy(const Format&);
	void clear();
public:
	Format(TVFormat** format,unsigned formatSize);
	Format(const Format& other);
	Format& operator=(const Format& other);
	~Format();

	void play();
};

void Format::create(unsigned formatSize, TVFormat** format) {
	this->formatSize = formatSize;
	this->format = new TVFormat * [formatSize];

	for (int i = 0; i < formatSize; i++) {
		this->format[i]= format[i]->clone();
	}
}

void Format::copy(const Format& obj) {
	create(obj.formatSize, obj.format);
}

void Format::clear() {
	for (int i = 0; i < formatSize; i++) {
		delete format[i];
	}
	delete[] format;
}

Format::Format(TVFormat** format, unsigned formatSize) {
	create(formatSize, format);
}

Format::Format(const Format& other) {
	copy(other);
}

Format& Format::operator=(const Format& other) {
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
}

Format::~Format() {
	clear();
}

void Format::play() {
	for (int i = 0; i < formatSize; i++) {
		format[i]->doEvent();
		format[i]->printFormatInformation();
	}
}

#endif // !_FORMAT_