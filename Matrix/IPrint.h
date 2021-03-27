#pragma once
#include <iostream>

class IPrint
{
public:
	virtual void Print(std::ostream& out) const = 0;

	friend std::ostream& operator<< (std::ostream& out, const IPrint& Object);
};