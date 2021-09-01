#include "Vector2.h"

float Vector2::operator[](int index) {
	if (index == 0)
		return x;

	return y;
}