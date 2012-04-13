#ifndef BOUNDING_BOX_HXX
#define BOUNDING_BOX_HXX

namespace packing {
  class BoundingBox {
  public:
    BoundingBox(int width, int height);
    int area() const;
  private:
    int width;
    int height;
  };
}

#endif // BOUNDING_BOX_HXX
