#ifndef POINT_HXX
#define POINT_HXX

namespace packing {
  class Point {
  public:
    Point(int x, int y)
      :x(x), y(y)
    {}
    
    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
    
    Point operator+(const Point& other) const {
      return Point(getX() + other.getX(), getY() + other.getY());
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
  private:
    int x;
    int y;
  };
}

#endif // POINT_HXX
