#ifndef POINT_H_
#define POINT_H_

class Point {
private:
	double x,y;

public:
    Point();
    
	double GetX();
	double GetY();
	
	void SetX(double x);
	void SetY(double y);
	void Set(double x, double y);

	Point operator+(Point p);
	Point* operator+=(Point p);			// Should probably be a referece not a pointer
};

#endif /* POINT_H_ */
