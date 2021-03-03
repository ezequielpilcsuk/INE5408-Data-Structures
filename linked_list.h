//! Copyright [2019] <Ezequiel Pilcsuk da Rosa>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <stdexcept>
#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 protected:
    //!...
    class Node {  // Elemento
     public:
     //!...
        explicit Node(const T& data):
            data_{data}
        {}
        //!...
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        //!...
        T& data() {  // getter: dado
            return data_;
        }
        //!...
        const T& data() const {  // getter const: dado
            return data_;
        }
        //!...
        Node* next() {  // getter: próximo
            return next_;
        }
        //!...
        const Node* next() const {  // getter const: próximo
            return next_;
        }
        //!...
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    //!...
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    //!...
    Node* head{nullptr};
    //!...
    std::size_t size_{0u};
};

template <typename T>
LinkedList<T>::LinkedList() {
  Node* head{nullptr};
  std::size_t size_{0u};
  head = head;
  size_ = size_;
}
template <typename T>
LinkedList<T>::~LinkedList() {
  auto whatever = head;
  for (int i = 0; i != size_; i++) {
    whatever = whatever->next();
    delete whatever;
  }
  delete[] head;
}
template <typename T>
void LinkedList<T>::clear() {
  auto whatever = head;
  for (int i = 0; i != size_; i++) {
    whatever = whatever->next();
    delete[] whatever;
  }
  size_ = 0;
}
template <typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
  if (index > size_) {
    throw std::out_of_range("bigger than size");
  } else if (empty()) {
    push_front(data);
  } else if (index == size_) {
    push_back(data);
  } else {
    auto newNode = new Node(data);
    auto runner = head;
    for (auto i = 0; i != index-1; i++) {
      runner = runner->next();
    }
    newNode->next(runner->next());
    runner->next(newNode);
    size_++;
  }
}
template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    push_back(data);
    T* a = reinterpret_cast<T*>(malloc(sizeof(T)*size_));
    auto temp = head;
    for (auto i = 0; i != size_; i++) {
      a[i] = temp->data();
      temp = temp->next();
  }
  for (auto l = 0; l != size_; l++) {
    for (auto i = 0; i != size_-1; i++) {
      if (a[i+1] < a[i]) {
        auto k = a[i+1];
        a[i+1] = a[i];
        a[i] = k;
      }
    }
  }
  auto siz = size_;
  clear();
  for (int i = 0; i != siz; i++) {
    push_back(a[i]);
  }
  free(a);
}
template <typename T>
bool LinkedList<T>::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}
template <typename T>
void LinkedList<T>::push_front(const T& data) {
  Node* newNode = new Node(data);
  if (!empty()) {
    //! o próximo de newNode será para quem head está apontando
    newNode->next(head);
  }
    head = newNode;  // head passa a apontar pro novo
    size_++;
}
template <typename T>
std::size_t LinkedList<T>::size() const {
  return size_;
}
template <typename T>
T& LinkedList<T>::at(std::size_t index) {
  if (index >= size_ || index < 0) {
    throw std::out_of_range("too big");
  } else {
    auto runner = head;
    for (auto i = 0; i != index; i++) {
      runner = runner->next();
    }
    return runner->data();
  }
}
template<typename T>
void LinkedList<T>::push_back(const T& data) {
  Node* newNode = new Node(data);
  if (empty()) {
    push_front(data);
  } else {
    auto runner = head;
    for (auto i = 0; i != size_-1; i++) {
      runner = runner->next();
    }
    runner->next(newNode);
    size_++;
  }
}
template<typename T>
T LinkedList<T>::pop_back() {
  auto value = at(static_cast<int>(size_-1));
  auto naba = head;
  for (int i = 0; i != size_; i++) {
    naba = naba->next();
  }
  delete[] naba;
  size_--;
  return value;
}
template<typename T>
T LinkedList<T>::pop_front() {
  auto naba = head;
  auto value = at(0);
  head = head->next();
  delete[] naba;
  size_--;
  return value;
}
template<typename T>
T LinkedList<T>::pop(std::size_t index) {
  if (index == 0) {
    return pop_front();
  } else if (index == size_-1) {
    return pop_back();
  } else {
    auto result = at(index);
    auto runner = head;
    auto to_delete = runner->next();
    for (auto i = 0; i != index-1; i++) {
      runner = runner->next();
      to_delete = to_delete->next();
    }
    runner->next(to_delete->next());
    size_--;
    return result;
  }
}
template<typename T>
void LinkedList<T>::remove(const T& data) {
  auto hm = find(data);
  if (hm != size()) {
    pop(hm);
  }
}
template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
  auto runner = head;
  for (auto i = 0; i != size_; i++) {
    if (data == runner->data()) {
      return i;
    }
    runner = runner->next();
  }
  return size_;
}
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
  return !(find(data) == size());
}

}  // namespace structures

#endif
