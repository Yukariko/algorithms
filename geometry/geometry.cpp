#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;

struct vector2
{
	double x, y;

	explicit vector2(double x = 0, double y = 0) : x(x), y(y) {}

	bool operator == (const vector2& rhs) const 
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) const 
	{
		return x != rhs.x? x < rhs.x: y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const 
	{
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const 
	{
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const 
	{
		return vector2(x * rhs, y * rhs);
	}

	// 벡터의 길이
	double norm() const {return hypot(x, y);}

	vector2 normalize() const
	{
		return vector2(x / norm(), y / norm());
	}

	// x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	double polar() const {return fmod(atan2(y, x) + 2 * PI, 2 * PI);}

	// 내적
	double dot(const vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	// 외적
	double cross(const vector2& rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}

	// rhs에 사영
	vector2 project(const vector2& rhs) const
	{
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

// 점 q가 다각형 p 안에 포함되어 있을 경우 true, 아닌경우 false
// q가 다각형의 경계위에 있는 경우는 정의되어 있지 않음
bool isInside(vector2 q, const vector<vector2>& p)
{
	int crosses = 0;
	for(int i=0; i < p.size(); i++)
	{
		int j = (i + 1) % p.size();

		if((p[i].y > q.y) != (p[j].y > q.y))
		{
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if(q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}

// 주어지는 다각형의 넓이를 구함
double area(const vector<vector2>& p)
{
	double ret = 0;
	for(int i=0; i < p.size(); i++)
		ret += p[i].cross(p[(i + 1) % p.size()]);
	return fabs(ret) / 2.0;
}

// 두 직선의 교차점을 계산
bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2 & x)
{
	double det = (b-a).cross(d-c);
	if(fabs(det) < EPSILON)
		return false;
	x = a + (b-a) * ((c-a).cross(d-c) / det);
	return true;
}

// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0 반환
double ccw(vector2 a, vector2 b)
{
	return a.cross(b);
}

// 원점 대신 점 p를 기준으로 ccw
double ccw(vector2 p, vector2 a, vector2 b)
{
	return ccw(a-p,b-p);
}

// 두 평행한 선분의 교차점을 계산
bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p)
{
	if(b < a)
		swap(a, b);
	if(d < c)
		swap(d, c);

	if(ccw(a, b, c) != 0 || b < c || d < a)
		return false;

	if(a < c)
		p = c;
	else
		p = a;
	return true;
}

// p가 (a, b)를 감싸면서 각 변이 x,y축에 평행한 최소 사각형 내부에 있는지 확인
// a, b, p는 일직선 상에 있다고 가정
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b)
{
	if(b < a)
		swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// (a,b) 선분과 (c,d) 선분의 교점 x를 구함
// 교점이 여러개일 경우 아무거나, 없을경우 false를 반환
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
	if(!lineIntersection(a,b,c,d,x))
		return parallelSegments(a,b,c,d,x);
	return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}

typedef vector<vector2> polygon;

// 반평면과 단순 다각형의 교집합을 구한다.
// (a,b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a, b)의 왼쪽에 있는 부분들을 반환한다.
polygon cutPoly(const polygon& p, const vector2& a, const vector2& b)
{
	int n = p.size();

	vector<bool> inside(n);
	for(int i=0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;

	polygon ret;

	for(int i=0; i < n; i++)
	{
		int j = (i + 1) % n;

		if(inside[i])
			ret.push_back(p[i]);

		if(inside[i] != inside[j])
		{
			vector2 cross;
			assert(lineIntersection(p[i],p[j],a,b,cross));
			ret.push_back(cross);
		}
	}
	return ret;
}

// Sutherland-Hodgman 다각형 클리핑
polygon intersection(const polygon& p, double x1, double y1, double x2, double y2)
{
	vector2 a(x1,y1), b(x2,y1), c(x2,y2), d(x1,y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}

// points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾음 O(N^2)
polygon giftWrap(const vector<vector2>& points)
{
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while(true)
	{
		vector2 ph = hull.back(), next = points[0];
		for(int i=1; i < n; i++)
		{
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if(cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}

		if(next == pivot)
			break;

		hull.push_back(next);
	}
	return hull;
}

// 두 다각형이 서로 닿거나 겹치는지 여부를 반환
bool polygonIntersects(const polygon& p, const polygon& q)
{
	int n = p.size(), m = q.size();
	if(isInside(p[0],q) || isInside(q[0], p))
		return true;

	vector2 t;
	for(int i=0; i < n; i++)
		for(int j=0; j < m; j++)
			if(segmentIntersection(p[i], p[(i+1)%n], q[j], q[(j+1)%m], t))
				return true;
	return false;
}

int main()
{

	return 0;
}