#pragma once
class Spring
{
public:
	Spring();
	~Spring();
	Spring(int point1, int point2, float stiffness, float initialLength);

	int point1;
	int point2;
	float stiffness;
	float initialLength;
	// float currentLength;
};

