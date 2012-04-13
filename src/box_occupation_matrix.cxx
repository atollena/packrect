#include "box_occupation_matrix.hxx"

#include "rectangle.hxx"
#include "rectangle_position.hxx"

namespace packing {
  
  BoxOccupationMatrix::BoxOccupationMatrix(int width, int height)
    :matrix(width*height), width(width), height(height)
  {}

  auto BoxOccupationMatrix::query(const RectanglePosition & position) const -> Content
  {
    return at(position.getX(), position.getY());
  }

  void BoxOccupationMatrix::set(const Rectangle & rectangle,
                                const RectanglePosition & position)
  {
    set(rectangle, position, OCCUPIED);
  }

  void BoxOccupationMatrix::unset(const Rectangle & rectangle,
                                  const RectanglePosition & position)
  {
    set(rectangle, position, FREE);
  }

  void BoxOccupationMatrix::set(const Rectangle & rectangle,
                                const RectanglePosition & position,
                                Content value)
  {
    for(int i = 0; i < rectangle.getH(); ++i) {
      std::fill_n(at(position.getX(), position.getY() + i),
                  rectangle.getW(),
                  value);
    }
  }

  void BoxOccupationMatrix::reset()
  {
    // TODO (do we need that ?)
  }

  auto BoxOccupationMatrix::at(int x, int y) -> std::vector<Content>::iterator
  {
    return matrix.begin() + (y*width + x);
  }

  auto BoxOccupationMatrix::at(int x, int y) const -> Content
  {
    return matrix[y*width + x];
  }

  std::ostream& operator<<(std::ostream& out, const BoxOccupationMatrix& box)
  {
    out << std::endl;
    for(int y = box.height - 1; y >= 0; y--) {
      for(int x = 0; x < box.width; x++) {
        if(box.at(x, y) == BoxOccupationMatrix::Content::FREE)
          out << 'o';
        else
          out << 'x';
      }
      out << std::endl;
    }
    return out;
  }
}
