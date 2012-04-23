#ifndef RECTANGLE_SIZE_HXX
#define RECTANGLE_SIZE_HXX

struct RectangleSize {
  RectangleSize(int width, int height);
  
  int computeArea() const;

  int width;
  int height;
};

#endif // RECTANGLE_SIZE_HXX
