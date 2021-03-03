//  Copyright 2019 <Ezequiel Pilcsuk da Rosa>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

const auto DEFAULT_MAX = 10u;


namespace structures {

template<typename T>
//! Classe Lista de elemento T
class ArrayList {
 public:
//! Contrutor da lista
    ArrayList() {
        size_ = 0;
        contents = new T[max_size_];
    }
//! Construtor da lista com tamanho passado como parametro
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        size_ = 0;
        contents = new T[max_size_];
    }
//! Destrutor da lista, desaloca a mesma da memoria
    ~ArrayList() {
        delete [] contents;
    }
//! Limpa a lista
    void clear() {
        size_ = 0;
    }
//! Adiciona um elemento T no fim da lista
    void push_back(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else {
            contents[size_] = data;
            size_++;
        }
    }
//! Adiciona um elemento T no inicio da lista
    void push_front(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else if (empty()) {
            contents[0] = data;
            size_++;
        } else {
            int tam = size();
            while (tam > 0) {
                contents[tam] = contents[tam-1];
                tam--;
            }
            contents[0] = data;
            size_++;
        }
    }
//! Adiciona um elemento T na posicao desejada, caso a mesma seja válida
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else if (index == size()) {
            contents[index] = data;
            size_++;
            } else if (!position(index)) {
            throw std::out_of_range("Posicao invalida");
        } else {
             size_++;
            for (int i = size()-1; i > index ; i--) {
                contents[i] = contents[i-1];
            }
            contents[index] = data;
        }
    }
//! Insere um dado ordenadamente
    void insert_sorted(const T& data) {
      int i;
      if (full()) {
          throw std::out_of_range("Lista cheia");
      } else {
          i = 0;
          while (i < size() && data > contents[i]) {
              i++;
      }
       insert(data, i);
      }
    }
//! Retorna um elemento T de uma posição desejada e re-ordena a fila
    T pop(std::size_t index) {
        if (index >= size_) {
           throw std::out_of_range("Posicao invalida");
        } else {
             T wait = contents[index];
            int actual = index;
            while (actual < size_-1) {
            contents[actual] = contents[actual+1];
            actual++;
            }
            size_--;
            return wait;
        }
    }
//! Remove o último elemento da lista caso a lista nao esteja vazia
    T pop_back() {
        return pop (size_ - 1);
    }
//! Remove o primeiro elemento da lista caso a lista nao esteja vazia
    T pop_front() {
       return pop (0);
    }
//! Remove a primeira ocorrencia do elemento da lista
    void remove(const T& data) {
        int rep = size();
        bool stop = false;
        while (rep > 0 && !stop) {
            if (contents[rep-1] == data) {
                pop(rep-1);
                stop = true;
            }
            rep--;
        }
    }
//! Verifica se a lista está cheia
    bool full() const {
        return size() == max_size();
    }
//! Verifica se a lista está vazia
    bool empty() const {
        return size() == 0;
    }
//!  Verifica se contem o objeto na lista
    bool contains(const T& data) const {
        int tam = size()-1;
        while (tam >= 0) {
            if (contents[tam] == data) {
                return true;
            }
            tam--;
            }
            return false;
    }
//! Procura por um elemento e retorna sua posicao
    std::size_t find(const T& data) const {
        if (!contains(data)) {
            return size();
        } else {
            int posicao = 0;
            while (contents[posicao] != data) {
                posicao++;
            }
            return posicao;
        }
    }
//! Retorna a quantidade de elementos na lista
    std::size_t size() const {
        return size_;
    }
//! Retorna o tamanho da lista
    std::size_t max_size() const {
        return max_size_;
    }
//! Retorna o elemento do indice passado como parametro
    T& at(std::size_t index) {
        if (!position(index)) {
            throw std::out_of_range("Posicao invalida");
        } else {
            return contents[index];
        }
    }
//! Retorna o elemento do indice passado como parametro
    T& operator[](std::size_t index) {
        return at(index);
    }
//! Retorna o elemento do indice passado como parametro
    const T& at(std::size_t index) const {
         return at(index);
    }
//! Retorna o elemento do indice passado como parametro
    const T& operator[](std::size_t index) const {
        return at(index);
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

//! Retorna se a posição é válida ou não
    bool position(std::size_t index) {
        if (index >= 0 && index < size()) {
            return true;
        } else {
            return false;
        }
    }
};

}  // namespace structures

#endif
