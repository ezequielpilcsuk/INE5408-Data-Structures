//! Copyright [2018] <Ezequiel Pilcsuk da Rosa>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! ...
template<typename T>
class ArrayList {
 public:
    //! ...
    ArrayList();
    //! ...
    explicit ArrayList(std::size_t max_size);
    //! ...
    ~ArrayList();

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

 public:
    //! Conteúdo
    T* contents;
    //! Tamanho atual
    std::size_t size_;
    //! Tamanho máximo
    std::size_t max_size_;
    //! Tamanho padrão caso não especificado
    static const auto DEFAULT_MAX = 10u;
};

template<typename T>
ArrayList<T>::ArrayList():
  contents{nullptr},
  size_{0},
  max_size_{DEFAULT_MAX}
{
  contents = new T[ DEFAULT_MAX ];
}

template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size):
  contents{nullptr},
  size_{0},
  max_size_{ max_size }
{
  contents = new T[ max_size ];
}

template<typename T>
ArrayList<T>::~ArrayList() {
  delete[] contents;
}

template<typename T>
void ArrayList<T>::clear() {
  size_ = 0;
}

template<typename T>
bool ArrayList<T>::empty() const {
  return ( size_ == 0 );
}

template<typename T>
void ArrayList<T>::push_back(const T& data) {
  if (size_ == max_size_) {
    throw std::out_of_range("out of range.");
  } else {
    contents[ size_ ] = data;
  }
  size_++;
}

template<typename T>
bool ArrayList<T>::full() const {
  return ( size_ == max_size_ );
}

template<typename T>
T ArrayList<T>::pop(std::size_t index) {
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
std::size_t ArrayList<T>::find(const T& data) const {
    for (auto i = 0; i != size_; i++) {
         if (data == contents[ i ]) {
             return i;
         }
    }
    return size_;
}

template<typename T>
std::size_t ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
    if (size_ <= index) {
      throw std::out_of_range("out of range");
    } else {
      return contents[ index ];
    }
}
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
    if (size_ <= index) {
      throw std::out_of_range("out of range");
    } else {
      return contents[ index ];
    }
}
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
return at(index);
}
template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
return at(index);
}
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
  return !(find(data) == size_ );
}
template<typename T>
T ArrayList<T>::pop_back() {
  return pop(size_ - 1);
}
template<typename T>
T ArrayList<T>::pop_front() {
return pop(0);
}
template<typename T>
void ArrayList<T>::remove(const T& data) {
  pop(find(data));
}
template<typename T>
void ArrayList<T>::push_front(const T& data) {
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
void ArrayList<T>::insert(const T& data, std::size_t index) {
  if (size_ == max_size_ || index >= max_size_) {
    throw std::out_of_range("out of range");
  } else {
      for (auto i = size_; i != index; i--) {
        contents[ i ] = contents[ i-1 ];
      }
      contents[index] = data;
    size_++;
  }
}
template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
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

//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();

    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};

ArrayListString::~ArrayListString() {
  for (auto i = 0; i != static_cast<int>(size_); i++) {
      delete contents[i];
  }
}
void ArrayListString::clear() {
  for (auto i = 0; i != static_cast<int>(size_); i++) {
      delete contents[i];
  }
  ArrayList<char*>::clear();
}
void ArrayListString::push_back(const char* data) {
  char* datanew = new char[strlen(data) + 1];
  snprintf(datanew, strlen(data)+1, "%s", data);
  ArrayList<char*>::push_back(datanew);
}
void ArrayListString::push_front(const char* data) {
  char* datanew = new char[strlen(data) + 1];
  snprintf(datanew, strlen(data)+1, "%s", data);

  ArrayList<char*>::push_front(datanew);
}
void ArrayListString::insert(const char* data, std::size_t index) {
  char* datanew = new char[strlen(data) + 1];
  snprintf(datanew, strlen(data)+1, "%s", data);

  ArrayList<char*>::insert(datanew, index);
}
void ArrayListString::insert_sorted(const char *data) {
  char* datanew = new char[strlen(data) + 1];
  snprintf(datanew, strlen(data)+1, "%s", data);

  ArrayList<char*>::push_back(datanew);

    for (auto j = 0; j != static_cast<int>(size_-1); j++) {
      for (auto i = 0; i != static_cast<int>(size_-1); i++) {
        auto rot = contents[i];
        if (strcmp(contents[i], contents[i+1]) > 0) {
          rot = contents[i+1];
          contents[i+1] = contents[i];
          contents[i] = rot;
        }
      }
    }
}
char* ArrayListString::pop(std::size_t index) {
    if (size_ <= index) {
    throw std::out_of_range("out of range");
  } else {
    char* datanew = new char[strlen(contents[index]) + 1];
    snprintf(datanew, strlen(contents[index])+1, "%s", contents[index]);
    delete[] contents[index];
    for (auto i = index; i != size_ -1; i++) {
        contents[ i ] = contents[ i+1 ];
    }
    size_--;
    return datanew;
  }
}
char* ArrayListString::pop_back() {
  return pop(size_-1);
}
char* ArrayListString::pop_front() {
  return pop(0);
}
void ArrayListString::remove(const char *data) {
  pop(find(data));
}
std::size_t ArrayListString::find(const char* data) {
      for (auto i = 0; i != static_cast<int>(size_); i++) {
         if (strcmp(data, contents[i]) == 0) {
             return i;
         }
    }
    return size_;
}
bool ArrayListString::contains(const char *data) {
  return !(find(data) == size_ );
}

}  // namespace structures

#endif
