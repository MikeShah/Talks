// @file: explicit.cpp
#include <print>
#include <vector>
struct ExplicitPoint2f{
    explicit ExplicitPoint2f(float value) :  x(value),y(value) { }
    explicit ExplicitPoint2f(float _x, float _y) :  x(_x),y(_y) { }
    float x,y;
};
struct Point2f{
    Point2f(float value) :  x(value),y(value) { }
    Point2f(float _x, float _y) :  x(_x),y(_y) { }
    float x,y;
};
 
int main()
{
	Point2f p1 = 1.0f; 			// copy-initialization allowed
	Point2f p2(1.0);			// directly initialize from constructor
	Point2f p3{1.0};			// directly initialize from constructor
    Point2f p4 = {1.0f,2.0f};   // copy-list initialization

    std::println("{} {}", p1.x, p1.y);
    std::println("{} {}", p2.x, p2.y);
    std::println("{} {}", p3.x, p3.y);
    std::println("{} {}", p4.x, p4.y);

//	ExplicitPoint2f p5 = 1.0f; 		// Not allowed with 'explicit'
	ExplicitPoint2f p6(1.0);		// directly initialize from constructor
	ExplicitPoint2f p7{1.0};		// directly initialize from constructor
//    ExplicitPoint2f p8 = {1.0f,2.0f};   // Not allowed with 'exlicit'
	ExplicitPoint2f p9{1.0f,2.0f};	// Allowed with list-initialization

    //std::println("{} {}", p5.x, p5.y);
    std::println("{} {}", p6.x, p6.y);
    std::println("{} {}", p7.x, p7.y);
	//std::println("{} {}", p8.x, p8.y);
    std::println("{} {}", p9.x, p9.y);

    return 0;
}
