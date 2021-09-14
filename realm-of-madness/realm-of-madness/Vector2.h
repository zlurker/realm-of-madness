#pragma once
struct Vector2
{

public:
	Vector2() {
		x = 0;
		y = 0;
	}

	Vector2(float ix, float iy) {
		x = ix;
		y = iy;
	}

	float operator[](int);

	float x;
	float y;
};
