#ifndef INDEX_H
#define INDEX_H

class Index
{
private:
	int index;
	int min, max;
	bool wrap;

public:
	Index();
	Index(int _min, int _max, bool _wrap);
	~Index();
	void set(int _min, int _max, bool _wrap);
	void up();
	void down();
	void setIndex(int _index);
	void setMin(int _min);
	void setMax(int _max);
	void setRange(int _min, int _max);
	void setWrap(bool _wrap);
	int getIndex();
	int getMin();
	int getMax();
	bool getWrap();
};

#endif