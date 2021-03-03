//! "Copyright [2019] <Ezequiel Pilcsuk da Rosa>"
#include <stdexcept>
#include <cstdint>
#include <memory>

namespace structures {


template<typename T>
//!  Classe Fila Encadeada
class LinkedQueue {
 public:
    LinkedQueue() = default;

    ~LinkedQueue() {
        clear();
    }
//!  Limpar
    void clear() {
        auto runner = head;
        for (int i = 0; i != size_; i++) {
            auto to_kill = runner;
            runner = runner->next();
            delete to_kill;
        }
        size_ = 0;
    }
//!  Enfileirar
    void enqueue(const T& data) {
            auto new_dude = new Node(data);
        if (size_ == 0) {
            head = new_dude;
            tail = new_dude;
        } else {
            tail->next(new_dude);
            tail = new_dude;
        }
        size_++;
    }
    //!  Desenfileirar
    T dequeue() {
        if (size_ == 0) {
            throw std::out_of_range("Empty queue");
        }
        auto return_value = head->data();
        auto new_head = head->next();
        auto to_delete = head;
        head = new_head;
        delete to_delete;
        size_--;
        return return_value;
    }
//!  Frente da Fila
    T& front() const {
        if (size_ == 0) {
            throw std::out_of_range("Empty queue");
        } else {
            return head->data();
        }
    }
//!  Fim da fila
    T& back() const {
        if (size_ == 0) {
            throw std::out_of_range("Empty queue");
        } else {
        return tail->data();
        }
    }
//!  Fila vazia?
    bool empty() const {
        return (size_ == 0);
    }
//!  Tamanho da fila
    std::size_t size() const {
        return size_;
    }

 private:
    class Node{
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
        }
        void next(Node* next) {
            next_ = next;
        }
    
    private:
        Node* next_;
        T data_;
    };
    //!  Nodo cabeça
    Node* head;
    //!  Nodo cauda
    Node* tail;
    //!  Tamanho da fila
    std::size_t size_;
};

} // namespace structures
