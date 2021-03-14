// CH.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "head.h"
using namespace std;

//using Point = std::pair<double, double>;

const int MAXN = 1000;

struct Point {
    double x, y;
    Point(const double& _x = double(), const double& _y = double()) : x(_x), y(_y) {}
}points[MAXN];
//向量
struct Vertex {
    double x, y;
    Vertex(const double& _x = double(), const double& _y = double()) : x(_x), y(_y) {}
};

/* 计算叉积 */
inline double cross(const Vertex& a, const Vertex& b) {
	return a.x * b.y - a.y * b.x;
}
/* 计算叉积<p, p1> * <p, p2> */
inline double cross(const Point& p, const Point& p1, const Point& p2) {
	Vertex vab = Vertex(p1.x - p.x, p1.y - p.y);
	Vertex vac = Vertex(p2.x - p.x, p2.y - p.y);
	return cross(vab, vac);
}
/* 计算两点间的距离 */
inline double dist(const Point& a, const Point& b) {
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

double GH(const int& n) {
    double res = 0.0;
	Point origin(0, 0);
	for (int i = 1; i < n; i++) {
		if (points[i].y < points[0].y) {
			swap(points[i].x, points[0].x);
			swap(points[i].y, points[0].y);
		}
	}
	sort(points + 1, points + n, [=](const Point& p1, const Point& p2) {
		double tmp = cross(points[0],p1,p2);//非0 逆时针 角度排序
		return tmp ? tmp > 0:(dist(origin,p1)<dist(origin,p2));
	});
	int stack[MAXN];
	stack[0] = 0;
	stack[1] = 1;
	int top = 1;//栈内 最大索引
	for (int i = 2; i < n; i++) { //[i]为考察的下一个点  这里逆时针考察 <=0说明在 [top-1]->[top] 右侧
		while (top && cross(points[stack[top - 1]], points[stack[top]], points[i]) <= 0) {
			--top;
		}
		stack[++top] = i;
	}
	stack[++top] = 0;
	for (int i = 0; i < top; ++i) {
		res += dist(points[stack[i]], points[stack[i + 1]]);
	}
    return res;
}


int main()
{
	vector<Point> vec{
		{-4,4},{-4,-4},{4,-4},{4,4},{2,0} 
	};
	int n = vec.size();
	for(int i = 0; i < n; i++){
		points[i].x = vec[i].x;
		points[i].y = vec[i].y;
	}
	cout<<GH(n)<<endl;
    std::cout << "Hello World!\n";
}

