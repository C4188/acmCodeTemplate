// #include <stdio.h>
// #include <algorithm>
// #include <vector>
// using namespace std;
// typedef pair<double, double> vec;

// // return < 0 则点Q 在以P点和v向量构成的直线上方, return 0 则在直线上,return > 0 则在下方
// int checkPosition(vec P, vec v, vec Q)
// {
//     // 保证方向向量 v 方向向上(保证y为正)
//     if(v.second < 0){
//         v.first *= -1;
//         v.second *= -1;
//     }

//     vec PQ = make_pair(Q.first - P.first, Q.second - P.second);
//     return PQ.first * v.second - v.first * PQ.second;
// }

// // 判断两个线段ab, cd是否相交,相交返回1, 否则返回0
// // a, b分别是线段的两端点,c, d也是.
// int check(vec a, vec b, vec c, vec d)
// {
//     if(a.first > b.first)   swap(a, b);
//     if(c.first > d.first)   swap(c, d);
//     // 判断是否满足互斥实验
//     if(b.first < c.first || d.first < a.first)   return 0;  //x轴方向排斥
//     if(b.second < c.second || d.second < a.second)  return 0;   //y轴方向排斥
//     // 判断是否满足跨立实验
//     vec v = make_pair(b.first - a.first, b.second - a.second);
//     int t1 = checkPosition(a, v, c);
//     int t2 = checkPosition(a, v, d);
//     if(!(t1 == 0 && t1 == t2) && (t1 <= 0 && t2 >= 0) || (t1 >= 0 && t2 <= 0)){
//         v = make_pair(d.first - c.first, d.second - c.second);
//         t1 = checkPosition(c, v, a);
//         t2 = checkPosition(c, v, b);
//         if((t1 < 0 && t2 > 0) || (t1 > 0 && t2 < 0))
//             return 1;
//     }
//     return 0;
// }

// //判断p点在不在线段ep上
// int checkEdge(vec ep1, vec ep2, vec p)
// {
//     vec ep12 = make_pair(ep2.first - ep1.first, ep2.second - ep1.first);
//     vec ep1p = make_pair(p.first - ep1.first, p.second - ep1.second);
//     // 此处相乘可能造成溢出
//     if(ep12.first * ep1p.second == ep1p.first * ep12.second &&\
//         p.first >= min(ep1.first, ep2.first) && p.first <= max(ep1.first, ep2.first) &&\
//         p.second >= min(ep1.second, ep2.second) && p.second <= max(ep1.second, ep2.second)){
//             return 0;
//     }
//     return 1;
//     // if(p.first == ep1.first && p.second == ep1.second)
//     //     return 1;
//     // if(p.first == ep2.first && p.second == ep2.second)
//     //     return 1;
//     // if(ep1.first == ep2.first){
//     //     if(p.first == ep1.first){
//     //         if(abs(p.second - ep1.second) < abs(ep2.second - ep1.second))
//     //             return 1;
//     //     }
//     //     return 0;
//     // }
//     // if(ep1.second == ep2.second){
//     //     if(p.second == ep1.second){
//     //         if(abs(p.first - ep1.first) < abs(ep2.first - ep1.first))
//     //             return 1;
//     //     }
//     //     return 0;
//     // }
//     // if(p.first == ep1.first || p.second == ep2.second)
//     //     return 0;
//     // else{
//     //     if((ep2.first - ep1.first) / (p.first - ep1.first) == (ep2.second - ep1.second) / (p.second - ep1.second) && abs(ep2.first - ep1.first) > abs(p.first - ep1.first))
//     //         return 1;
//     //     return 0;
//     // }
// }

// // 判断点(x, y)是否在 任意多边形 的内部
// int pnpoly(vector<vec> &vertex, double x, double y)
// {
//     int cnt = vertex.size(), i, j, c = 0;
//     for(i = 0; i < cnt; i++)
//         if(vertex[i].first == x && vertex[i].second == y)   return 0;   //如果(x, y)是多边形的端点,则直接返回0
//     vec tPoint(x, y);
//     for(i = 0, j = cnt - 1; i < cnt; j = i++)
//     {
//         if(checkEdge(vertex[j], vertex[i], tPoint) == 1)    return 0;
//         if((vertex[i].second > y) != (vertex[j].second > y) && \
//             (x < (vertex[j].first - vertex[i].first) * (y - vertex[i].second) / (vertex[j].second - vertex[i].second) + vertex[i].first))
//             c = !c;
//     }
//     return c;
// }

#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string.h>
using namespace std;
const double PI = acos(-1.0);
const double eps = 1e-8;
struct Point;
typedef Point Vec;
struct Point{
    double x;
    double y;
    Point(double _x, double _y){
        x = _x;
        y = _y;
    }
    Point(){
        Point(0, 0);
    }
    friend Vec operator+(const Vec &a, const Vec &b){
        return Vec(a.x + b.x, a.y + b.y);
    }
    friend Vec operator-(const Vec &a, const Vec &b){
        return Vec(a.x - b.x, a.y - b.y);
    }
    friend double operator^(Vec a, Vec b){
        return a.x * b.y - b.x * a.y;
    }
};

// 防止卡精度
int sgn(double d)
{
    if (fabs(d) < eps)
        return 0;
    if (d > 0)
        return 1;
    return -1;
}

// 得到直线ab与x轴正方向形成的夹角度数
// 精度方面有点毛病
double GetDegree(Point& a, Point& b)
{
    if(fabs(a.x - b.x) < eps)
        return 90;
    double ans = acos((a.y - b.y) / (a.x - b.x));
    return ans * 180 / PI;
}

// 判断点P在直线AB的位置
// P在向量AB 的顺时针方向返回正数，否则返回负数
int checkPointPositionOfLine(Point A, Point B, Point P)
{
    Vec AB = {B.x - A.x, B.y - A.y};
    Vec AP = {P.x - A.x, P.y - A.y};
    return AP.x * AB.y - AB.x * AP.y;
}

// 判断直线AB与直线CD是否相交
int checkLine_intersection(Point A, Point B, Point C, Point D)
{
    Vec AB = {B.x - A.x, B.y - A.y};
    Vec CD = {D.x - C.x, D.y - C.y};
    return AB.x * CD.y - AB.y * CD.x;   //向量叉乘为0，即平行或重合
}

// 判断直线AB与线段CD是否相交
int checkLineAndSegment_intersection(Point A, Point B, Point C, Point D)
{
    double fC = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
    double fD = (D.y - A.y) * (A.x - B.x) - (D.x - A.x) * (A.y - B.y);
    if((fC > 0 && fD > 0) || (fC < 0 && fD < 0))    //如果C点和D点在直线AB的同侧，则返回0
        return 0;
    else
        return 1;
}

// 判断线段AB与线段CD是否相交
// 只需判断直线AB与线段CD是否相交和直线CD是否与线段AB相交即可
int checkSegment_intersection(Point A, Point B, Point C, Point D)
{
    if(checkLineAndSegment_intersection(A, B, C, D)\
        && checkLineAndSegment_intersection(C, D, A, B)){
            return 1;
        }
    return 0;
}

// 判断P点是否在线段AB上
int checkPointOnSegment(Point A, Point B, Point P)
{
    Vec AP = {P.x - A.x, P.y - A.y};
    Vec AB = {B.x - A.x, B.y - A.y};
    if(P.x >= min(A.x, B.x) && P.x <= max(A.x, B.x)\
        && P.y >= min(A.y, B.y) && P.y <= max(A.y, B.y)\
        && AP.x * AB.y == AB.x * AP.y){
            return 1;
        }
    return 0;
}

// 判断点P(x, y)是否在 任意多边形内部
int pnpoly(vector<Point>& vertexes, Point P)
{
    int cnt = vertexes.size(), i, j, c = 0;
    for(i = 0, j = cnt - 1; i < cnt; j = i++)
    {
        if(checkPointOnSegment(vertexes[i], vertexes[j], P))
            return 0;
        if((vertexes[i].y > P.y) != (vertexes[j].y > P.y) && \
            (P.x < (vertexes[j].x - vertexes[i].x) * (P.y - vertexes[i].y) / (vertexes[j].y - vertexes[i].y) + vertexes[i].x))
                c = !c;
    }
    return c;
}

//返回向量叉乘 u * v
double cross(Vec u, Vec v)
{
    return u.x * v.y - v.x * u.y;
}

// 计算两条直线AB, CD的交点, 如果两直线相交，结果给P， 返回1， 否则返回0
int calculateTwoLines_intersection(Point A, Point B, Point C, Point D, Point &P)
{
    if(!checkLine_intersection(A, B, C, D)) return 0;
    Vec v = {B.x - A.x, B.y - A.y}, w = {D.x - C.x, D.y - C.y};
    Vec u = {A.x - C.x, A.y - C.y};
    double t = cross(w, u) / cross(v, w);
    P = {A.x + v.x * t, A.y + v.y * t};
    return 1;
}

// 计算任意多边形面积
double calculatePolygonArea(vector<Point>& vertexes)
{
    int i, j, cnt = vertexes.size();
    double ans = 0;
    for(int i = 0; i < cnt; i++)
    {
        j = (i + 1) % cnt;
        ans += vertexes[i].x * vertexes[j].y - vertexes[i].y * vertexes[j].x;
    }
    ans /= 2;
    return (ans < 0? -ans: ans);
}

// 求两点之间距离
double calculateTwoPointsDistance(Point A, Point B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

// 求点P与直线的最短距离
// 方向向量为0向量时，返回-1
double calculatePointAndLineDistance(Point A, Vec v, Point P)
{
    if(v.x == 0 && v.y == 0)    return -1;  //无效方向向量
    Vec AP = {P.x - A.x, P.y - A.y};
    double t = calculateTwoPointsDistance({0, 0}, v);
    double ans = cross(AP, v) / t;
    return (ans < 0? -ans: ans);
}
/*********圆与直线相关***********/


int main()
{
    // printf("%d\n", checkPosition(make_pair(0, 0), make_pair(1, 1), make_pair(1, 2)));
    // printf("%d\n", checkPosition(make_pair(0, 0), make_pair(-1, -1), make_pair(1, 2)));
    // printf("%d\n", check(make_pair(1, 2), make_pair(0, 0), make_pair(2, 0), make_pair(3, 2)));
    // printf("%d\n", check(make_pair(1, 2), make_pair(0, 0), make_pair(2, 0), make_pair(0, 2)));
    printf("%d\n", checkSegment_intersection({0, 0}, {3, 1}, {2, 0}, {3, 0}));
    vector<Point> v1 = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    vector<Point> v2 = {{-1, 0}, {0, 1}, {0, 0}, {1, 0}, {0, -1}};
    printf("%d\n", pnpoly(v1, {0, 0.5}));
    Point P;
    if(calculateTwoLines_intersection({0, 0}, {1, 1}, {0, 1}, {1, 0}, P)){
        printf("%lf %lf\n", P.x, P.y);
    }

    printf("%lf\n", calculatePolygonArea(v2));

    printf("%lf\n", calculatePointAndLineDistance({0, 0}, {1, 1}, {2, 0}));

    printf("%d\n", checkPointPositionOfLine({0, 0}, {0, 1}, {1, 0}));
    return 0;
}