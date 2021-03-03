// Copyright [2019] <Ezequiel Pilcsuk da Rosa>
#include <stdexcept>
#include <cstdint>
#include <memory>
#define CATCH_CONFIG_MAIN
namespace structures {

template<typename T>
    //! ..
class LinkedStack {
 public:
    //! ..
    LinkedStack();
    //! ..
    ~LinkedStack();
    //! ..
    void clear();  // limpa pilha
    //! ..
    void push(const T& data);  // empilha
    //! ..
    T pop();  // desempilha
    //! ..
    T& top() const;  // dado no topo
    //! ..
    bool empty() const;  // pilha vazia
    //! ..
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
        data_{data}
        {}
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }
        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }  // getter-constante: próximo

        void next(Node* next) {
            next_ = next;
        }  // setter: próximo

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};
template<typename T>
LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}
template<typename T>
LinkedStack<T>::~LinkedStack() {
clear();
}
template<typename T>
void LinkedStack<T>::clear() {
    auto runner = top_;
    for (int i = 0; i != size_; i++) {
        auto to_kill = runner;
        runner = runner->next();
        delete to_kill;
    }
    size_ = 0;
}
template<typename T>
void LinkedStack<T>::push(const T& data) {
    if (size_ ==  0) {
        Node* new_node = new Node(data);
        top_ = new_node;
        size_++;
    } else {
        Node* new_node = new Node(data, top_);
        top_ = new_node;
        size_++;
    }
}
template<typename T>
T LinkedStack<T>::pop() {
    if (size_ <= 0) {
        throw std::out_of_range("menor ou igual a 0, out of bounds");
    } else {
        auto to_kill = top_;
        auto to_kill_data = top_->data();
        auto next = top_->next();
        top_ = next;
        delete to_kill;
        size_--;
        return to_kill_data;
    }
}
template<typename T>
T& LinkedStack<T>::top() const {
    if (size_ == 0) {
        throw std::out_of_range("no elements in stack");
    } else {
        return top_->data();
    }
}
template<typename T>
bool LinkedStack<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}
template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

}  // namespace structures
