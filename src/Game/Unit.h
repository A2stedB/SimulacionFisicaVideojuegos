#pragma once

float operator "" _g(unsigned long long quantity) 
{
	return (float)quantity / 1000.0f;
}

float operator "" _kg(unsigned long long quantity) 
{
	return quantity;
}

float operator "" _m_s(unsigned long long quantity) {
	return quantity;
}

float operator "" _m_s(long double quantity) {
	return quantity;
}

struct ms_t
{
	float value;
};

struct kg_t
{
	float value;
};