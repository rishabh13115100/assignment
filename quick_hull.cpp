#include <bits/stdc++.h>
using namespace std;
struct point{
  int x;
  int y;
};
int n;
vector <point> hull;



int distSq(point p1, point p2)
{
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
int orientation(point p, point q, point r)
{
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
  if (val == 0) return 0;  
  return (val > 0)? 1: 2; 
}
int dist_to_line(point p,point q,point r){
    int val = (q.x - p.x) * (r.y - p.y)*(q.x - p.x) * (r.y - p.y) + (q.y - p.y) * (r.x - p.x)*(q.y - p.y) * (r.x - p.x);
    return abs(val);
}
point farthest(vector <point> &S,point A,point B){
    int size = S.size();
    point ans = S[0]; 
    for(int i=0;i<size;i++){
        if(dist_to_line(A,B,S[i]) > dist_to_line(A,B,ans))ans = S[i];
    }
    return ans;
}
void find_hull_cl(vector <point> &S,point A,point B){
    int size = S.size();
    if(size == 0)return ;

    point ans = farthest(S,A,B);
  //cout<<"clock  "<<ans.x<<" "<<ans.y<<endl;
  
    vector <point> cl_A;
    vector <point> cl_B;

    for(int i=0;i<size;i++){
      if( S[i].x == ans.x and S[i].y == ans.y)continue;
      if(orientation(A,ans,S[i])==1)cl_A.push_back(S[i]);
    }

    for(int i=0;i<size;i++){
      if(S[i].x == ans.x and S[i].y == ans.y)continue;
      if(orientation(ans,B,S[i])==1)cl_B.push_back(S[i]);
    }
    

    hull.push_back(ans);
    find_hull_cl(cl_A,A,ans);
    find_hull_cl(cl_B,ans,B);
    
}

void find_hull_ccl(vector <point> &S,point A,point B){
    int size = S.size();
    if(size == 0)return ;

    point ans = farthest(S,A,B);
  //cout<<"A_clock  "<<ans.x<<" "<<ans.y<<endl;
    vector <point> ccl_A;
    vector <point> ccl_B;

    for(int i=0;i<size;i++){
      if(S[i].x == ans.x and S[i].y == ans.y)continue;
      if(orientation(A,ans,S[i])==2)ccl_A.push_back(S[i]);
    }

    for(int i=0;i<size;i++){
      if(S[i].x == ans.x and S[i].y == ans.y)continue;
      if(orientation(ans,B,S[i])==2)ccl_B.push_back(S[i]);
    }
    

    hull.push_back(ans);
    find_hull_ccl(ccl_A,A,ans);
    find_hull_ccl(ccl_B,ans,B);
}

void convexHull(point points[]){
  point left = points[0];point right = points[0];
  
  for(int i=0;i<n;i++){
    if(points[i].x < left.x)left = points[i];
    if(points[i].x > right.x)right =  points[i];
  }
  hull.push_back(left);
  hull.push_back(right);
  vector <point> cl,ccl;

  for(int i=0;i<n;i++){
    if((points[i].x == left.x and points[i].y == left.y) or (points[i].x == right.x and points[i].y == right.y))continue;
    if(orientation(left,right,points[i])==1)cl.push_back(points[i]);
    else ccl.push_back(points[i]);
  }
 

  find_hull_cl(cl,left,right);
  find_hull_ccl(ccl,left,right);

  for(int i=0;i<hull.size();i++){
    cout<<hull[i].x<<" "<<hull[i].y<<endl;
  }
}
int main() {
  freopen("input2_2.txt", "r", stdin);
  freopen("output2_2.txt", "w", stdout);
  cin>>n;
  point points[n];
  for(int i=0;i<n;i++)cin>>points[i].x>>points[i].y;
  convexHull(points);
  return 0;
}