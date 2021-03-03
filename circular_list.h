//  "Copyright [2019] <Ezequiel Pilcsuk da Rosa>"
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#define CATCH_CONFIG_MAIN
#include <cstdint>
#include <stdexcept>
namespace structures {

template<typename T>
  //! Minha classe
class CircularList {
 public:
    CircularList();
    //! ...
    explicit CircularList(std::size_t max_size);
    ~CircularList();
    //! ...
    void clear();
    //! ...
    void push_back(const T& data);
    //! ...
    void push_front(const T& data);
    //! ...
    void insert(const T& data, std::size_t index);
    //! ...
    void insert_sorted(const T& data);
    //! ...
    T pop(std::size_t index);
    //! ...
    T pop_back();
    //! ...
    T pop_front();
    //! ...
    void remove(const T& data);
    //! ...
    bool full() const;
    //! ...
    bool empty() const;
    //! ...
    bool contains(const T& data) const;
    //! ...
    std::size_t find(const T& data) const;
    //! ...
    std::size_t size() const;
    //! ...
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

template<typename T>
CircularList<T>::CircularList():
  contents{nullptr},
  size_{0},
  max_size_{DEFAULT_MAX}
{
  contents = new T[ DEFAULT_MAX ];
}

template<typename T>
CircularList<T>::CircularList(std::size_t max_size) {
  contents = nullptr;
  size_ = 0;
  contents = new T[max_size];
  max_size_ = max_size;
}

template<typename T>
CircularList<T>::~CircularList() {
  delete[] contents;
}

template<typename T>
void CircularList<T>::clear() {
  size_ = 0;
}

template<typename T>
bool CircularList<T>::empty() const {
  return ( size_ == 0 );
}

template<typename T>
void CircularList<T>::push_back(const T& data) {
  if (size_ == max_size_) {
    throw std::out_of_range("out of range.");
  } else {
    contents[ size_ ] = data;
  }
  size_++;
}

template<typename T>
bool CircularList<T>::full() const {
  return ( size_ == max_size_ );
}

template<typename T>
T CircularList<T>::pop(std::size_t index) {
  if (size_ <= index) {
    throw std::out_of_range("out of range");
  } else {
    auto rot = contents[ index ];
    for (auto i = index; i != size_ -1; i++) {
        contents[ i ] = contents[ i+1 ];
    }
    size_--;
    return rot;
  }
}
template<typename T>
std::size_t CircularList<T>::find(const T& data) const {
    for (auto i = 0; i != max_size_; i++) {
         if (data == contents[ i ]) {
             return i;
         }
    }
    return size_;
}

template<typename T>
std::size_t CircularList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t CircularList<T>::max_size() const {
    return max_size_;
}

template<typename T>
const T& CircularList<T>::at(std::size_t index) const {
    if (size_ <= index) {
      throw std::out_of_range("out of range");
    } else {
      return contents[ index ];
    }
}
template<typename T>
T& CircularList<T>::at(std::size_t index) {
    if (size_ <= index) {
      throw std::out_of_range("out of range");
    } else {
      return contents[ index ];
    }
}
template<typename T>
T& CircularList<T>::operator[](std::size_t index) {
return at(index);
}
template<typename T>
const T& CircularList<T>::operator[](std::size_t index) const {
return at(index);
}
template<typename T>
bool CircularList<T>::contains(const T& data) const {
  return !(find(data) == size_ );
}
template<typename T>
T CircularList<T>::pop_back() {
  auto rex = contents[size_ - 1 ];
  pop(size_ - 1);
  return rex;
}
template<typename T>
T CircularList<T>::pop_front() {
  auto rex = contents[0];
  pop(0);
  return rex;
}
template<typename T>
void CircularList<T>::remove(const T& data) {
  pop(find(data));
}
template<typename T>
void CircularList<T>::push_front(const T& data) {
  if (size_ == max_size_) {
    throw std::out_of_range("out of range");
  } else {
      for (auto i = size_; i != 0; i--) {
        contents[ i ] = contents[ i-1 ];
      }
      contents[0] = data;
    size_++;
  }
}

template<typename T>
void CircularList<T>::insert(const T& data, std::size_t index) {
  if (size_ == max_size_ || index >= max_size_ || index < 0 || index == 1) {
    throw std::out_of_range("out of range");
  } else {
      for (auto i = size_-1; i != index; i--) {
        contents[ i ] = contents[ i-1 ];
      }
      contents[index] = data;
    size_++;
  }
}
template<typename T>
void CircularList<T>::insert_sorted(const T& data) {
  if (size_ == max_size_) {
    throw std::out_of_range("out of range");
  } else {
    push_back(data);
    for (auto j = 0; j != size_-1; j++) {
      for (auto i = 0; i != size_-1; i++) {
        auto rot = contents[i];
        if (contents[i] > contents[i+1]) {
          rot = contents[i+1];
          contents[i+1] = contents[i];
          contents[i] = rot;
        }
      }
    }
  }
}
}  //! namespace structures
#endif
