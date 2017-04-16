#include <bits/stdc++.h>
using namespace std;
struct point
{
    int x, y;
};
vector <point> hull;
int n;

int orientation(point p,point q,point r){
	 int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; 
    return (val > 0)? 1: 2;
}

void convex_hull(point points[]){
	if (n < 3) return;
	int l = 0;
    for (int i = 1; i < n; i++)if (points[i].x < points[l].x)l = i;
    
    int p = l, q;
    do{
    	 hull.push_back(points[p]);
    	 q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)q = i;
        }
    	p = q;
    }while(p != l);
    for (int i = 0; i < hull.size(); i++) cout << "(" << hull[i].x << ", "<< hull[i].y << ")\n";
}
int main() {
    freopen("input1_1.txt", "r", stdin);
    freopen("output1_1.txt", "w", stdout);

	cin>>n;
	point points[n];
	for(int i=0;i<n;i++)cin>>points[i].x>>points[i].y;
	
	convex_hull(points);
	return 0;
}