#ifndef HELPER_HXX
#define HELPER_HXX

namespace packing {
  /**
   * Zips two vectors elements into a vector of pairs.  The resulting
   * vector size is min(vector1.size(), vector2.size())
   */
  template<class T1, class T2>
  std::vector<std::pair<T1, T2>>
    zip(const std::vector<T1> & vector1,
        const std::list<T2> & vector2)
  {
    std::vector<std::pair<T1, T2>> result;

    auto i1 = vector1.begin();
    auto i2 = vector2.begin();
    while(i1 != vector1.end() && i2 != vector2.end()){
      result.push_back(std::make_pair(*i1, *i2));
      ++i1;
      ++i2;
    }
    return result;
  }
}

#endif
