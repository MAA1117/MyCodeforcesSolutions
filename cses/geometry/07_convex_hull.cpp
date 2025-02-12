// https://cses.fi/problemset/task/2195/

#include <bits/stdc++.h>
using namespace std;
#define SET_IO()                    \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr);
typedef long long ll;
#define f first
#define s second

struct convex_hull {
  using TYPE = ll;
  using point = pair<TYPE, TYPE>;
  vector<point> points;
  vector<point> hull_up, hull_down, hull_tot;

  void init() { points = hull_up = hull_down = hull_tot = vector<point>(); }

  void add_point(TYPE a, TYPE b) { points.push_back(make_pair(a, b)); }

  /* sort by x, then y */
  static bool point_comp(point a, point b) {
    return a.f < b.f || (a.f == b.f && a.s < b.s);
  }

  /*
  -1 - clockwise
  0 - collinear
  1 - counterclockwise
  */
  int orient(point a, point b, point c) {
    TYPE val = a.f * (b.s - c.s) + b.f * (c.s - a.s) + c.f * (a.s - b.s);

    if (val < 0)
      return -1;
    else if (val > 0)
      return 1;
    return 0;
  }

  void find_hull() {
    if (points.size() == 1) {
      hull_up = hull_down = hull_tot = points;
      return;
    }
    sort(points.begin(), points.end(), point_comp);

    point p1 = points[0], p2 = points.back();

    hull_up.push_back(p1);
    hull_down.push_back(p1);

    int sz = (int)points.size();
    for (int i = 1; i < sz; i++) {
      /* end or clockwise */
      if (i == points.size() - 1 || orient(p1, points[i], p2) != 1) {
        /* while not cw */
        while (hull_up.size() >= 2 && orient(hull_up[hull_up.size() - 2],
                                             hull_up.back(), points[i]) == 1)
          hull_up.pop_back();
        hull_up.push_back(points[i]);
      }

      /* end or ccw */
      if (i == points.size() - 1 || orient(p1, points[i], p2) != -1) {
        /* while not ccw */
        while (hull_down.size() >= 2 &&
               orient(hull_down[hull_down.size() - 2], hull_down.back(),
                      points[i]) == -1)
          hull_down.pop_back();
        hull_down.push_back(points[i]);
      }
    }
    for (int i = 0; i < (int)hull_up.size(); i++)
      hull_tot.push_back(hull_up[i]);
    for (int i = hull_down.size() - 2; i > 0; i--)
      hull_tot.push_back(hull_down[i]);
  }
};

int main() {
  SET_IO();
  int n;
  cin >> n;
  convex_hull ch;
  ch.init();
  for (int i = 0; i < n; ++i) {
    ll a, b;
    cin >> a >> b;
    ch.add_point(a, b);
  }
  ch.find_hull();
  ll k = ch.hull_tot.size();
  cout << k << '\n';
  for (auto pt : ch.hull_tot) {
    cout << pt.f << " " << pt.s << '\n';
  }
}
