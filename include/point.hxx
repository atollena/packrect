#ifndef POINT_HXX
#define POINT_HXX

namespace packing {
  class Point {
  public:
    Point(int x, int y);
    bool operator==(const Point& other) const;
    Point operator+(const Point& other) const;
    int getX() const;
    int getY() const;
  private:
    int x;
    int y;
  };
}

#endif // POINT_HXX
