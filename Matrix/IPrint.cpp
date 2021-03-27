#include "IPrint.h"

std::ostream& operator<< (std::ostream& out, const IPrint& Object)
{
	Object.Print(out);
	return out;
}