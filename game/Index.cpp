#include "Index.h"

//CONSTRUCTOR
Index::Index()
{
	index = 0;
	min = 0;
	max = 0;
	wrap = 0;
}

//CONSTRUCTOR W/ min and max
Index::Index(int _min, int _max, bool _wrap)
{
	min = _min;
	max = _max;
	wrap = _wrap;
}

Index::~Index()
{
}

//SET
void Index::set(int _min, int _max, bool _wrap)
{
	min = _min;
	max = _max;
	wrap = _wrap;
}

//INDEX DOWN
void Index::up()
{
	index++;
	if (index > max)
	{
		if (wrap)
			index = min;
		else
			index = max;
	}
}

//INDEX DOWN
void Index::down()
{
	index--;
	if (index < min)
	{
		if (wrap)
			index = max;
	}
}

//SET INDEX
void Index::setIndex(int _index)
{
	index = _index;
}

//SET MIN
void Index::setMin(int _min)
{
	min = _min;
}

//SET MAX
void Index::setMax(int _max)
{
	max = _max;
}

//SET RANGE
void Index::setRange(int _min, int _max)
{
	min = _min;
	max = _max;
}

//SET WRAP
void Index::setWrap(bool _wrap)
{
	wrap = wrap;
}

//GET VALUE
int Index::getIndex()
{
	return index;
}
//GET MIN
int Index::getMin()
{
	return min;
}

//GET MAX
int Index::getMax()
{
	return max;
}

//GET WRAP
bool Index::getWrap()
{
	return wrap;
}
