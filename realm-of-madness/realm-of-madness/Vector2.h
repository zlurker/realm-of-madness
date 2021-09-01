#pragma once
struct Vector2
{

public:
	Vector2() {
		x = 0;
		y = 0;
	}

	float operator[](int);

	float x;
	float y;
};
