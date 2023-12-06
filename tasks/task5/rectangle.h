#include <stdexcept>

class Rectangle
{
	int Length;
	int Breadth;
public:
	Rectangle(int l, int b)
	{
		Length = l;
		Breadth = b;
		if (l <= 0 || b <= 0) {
			throw std::invalid_argument("not possible to solve");
		}
	}
	int Area()
	{
		return Length * Breadth;
	}
	// отношение длины к ширине
	double RelationsOfTheParties()
	{
		if (Breadth == 0) {
			throw std::runtime_error("zero division");
		}
		return Length / Breadth;
	}
};

int CalculateRectArea(int l, int b)
{
	Rectangle *p = new Rectangle(l, b);
	int area = p->Area();
	delete p;
	return area;
}

double CalculateRectRelationsOfTheParties(int l, int b)
{
	Rectangle *p = new Rectangle(l, b);
	double relation = p->RelationsOfTheParties();
	delete p;
	return relation;
}