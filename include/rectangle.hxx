#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

namespace packing {
  class Rectangle {
  public:
    Rectangle (int height, int width);
    Rectangle(const Rectangle & other);
    Rectangle& operator= (const Rectangle & other);
    ~Rectangle();
    
    int getH() const;
    int getW() const;
  private:
    int height;
    int width;
  };
}

#endif // RECTANGLE_HXX
