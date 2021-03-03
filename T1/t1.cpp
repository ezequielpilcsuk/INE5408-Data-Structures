// Ezequiel Pilcsuk da Rosa
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <list>
#include <map>
#include <queue>
 //!  Gets file name from input stream
std::string get_file_name() {
    std::string xmlfilename;
    //!  Entrada
    std::cin >> xmlfilename;
    return xmlfilename;
};
  //!  Insere o nome de cada imagem na lista e depois fecha o arquivo
int get_atribute_name(std::fstream& file, std::list<std::string>& name_list_);
  //!  Insere a altura de cada imagem na lista e depois fecha o arquivo
int get_atribute_height(std::fstream& file, std::list<std::string>& height_list_);
  //!  Insere a largura de cada imagem na lista e depois fecha o arquivo
int get_atribute_width(std::fstream& file, std::list<std::string>& width_list_);
  //!  Insere os dados de cada imagem na lista e depois fecha o arquivo
int get_atribute_data(std::fstream& file, std::list<std::string>& data_list_, std::list<std::string> height_list_);
  //!  Função de contágem de objetos, retorna número de objetos na imagem
int labelling(std::string name, std::string height, std::string width, std::string data);
  //!  Verifica integridade do arquivo XML
bool verify_xml(std::fstream& file);

//!  Inicio da função Main
int main() {
    // Armazena o nome do arquivo
    auto file_name = get_file_name();
    // Abre o arquivo com determinado nome
    std::fstream file(file_name);
    // Verifica se XML é válido
    if (verify_xml(file) == true) {
        std::cout << "error";
        return 0;
    }

    //  ::cout << "passou da verificação" << std::endl;

    // Listas com os atributos de cada imágem
    std::list<std::string> name_list;
    std::list<std::string> height_list;
    std::list<std::string> width_list;
    std::list<std::string> data_list;

    //!  Pega o nome das imagens
    file.open(file_name);
    get_atribute_name(file, name_list);
    //  std::cout << "passou da listagem de nomes" << std::endl;

    //!  Pega altura das imagens
    file.open(file_name);
    get_atribute_height(file, height_list);
    //  std::cout << "passou da listagem de alturas" << std::endl;

    //!  Pega largura das imagens
    file.open(file_name);
    get_atribute_width(file, width_list);
    //  std::cout << "passou da listagem de larguras" << std::endl;

    //!  Pega dados (matriz de zeros)
    file.open(file_name);
    get_atribute_data(file, data_list, height_list);// pega a matriz de zeros
    //  std::cout << "passou da listagem de dados" << std::endl;

    //!  Define número de imagens a serem analisadas
    auto size = name_list.size();
    for (int i = 0; i != size; i++) {
        //  std::cout << "antes da chamada de labelling :" << i << std::endl;
        //!  Imprime na saída o nome da lista seguido pelo número de objetos
        //!  Passando os primeiros elementos de cada lista como parâmetro de labelling
        std::cout << name_list.front() << " " << labelling(name_list.front(),
        height_list.front(), width_list.front(), data_list.front()) << std::endl;
        //!  Remove os primeiros elementos de cada Lista
        //!  Poderia só passar removendo, com pop_front direto?
        name_list.pop_front();
        height_list.pop_front();
        width_list.pop_front();
        data_list.pop_front();
    }

    return 0;
}

// Translates the setting af an element in a 2d matrix to a vector

//!  Função Labelling
//!  Cria uma matriz referencia e adiciona novos eleme0ntos nela com um indice incremental
//!  de acordo com o número de objetos, depois retorna valor do contador indicando número de objetos
int labelling(std::string name, std::string height, std::string width, std::string data) {
  //!  Conversão String para inteiro dos parâmetros
    auto _height = stoi(height);
    auto _width = stoi(width);
    std::cout << "before first big allocation" << std::endl;
    bool copy[_height * _width];
    bool reference[_height * _width];


    std::cout << "1" << std::endl;
    for (int i = 0; i != _height*_width; i++)
        copy[i] = '0';


    int j = 0;
    for (int i = 0; i < data.size(); i++) {
      //! Se cheguei numa borda lateral diretia incremento J
        if (i%_width == 0 && i != 0) {
            j++;
        }
        std::cout << "2" << std::endl;
        reference[j+((i%_width) * _width)] = data.at(i);
    }

    //! Inicia contador de objetos com 0
    int num = 0;
    char label = '1';
    std::queue<std::pair<int, int>> pair_list;// cria uma lista de pares
    for (int i = 0; i != _height; i++) {
        for (int k = 0; k != _width; k++) {
            //! Caso este pixel esteja na referencia mas não na copia, o adiciona
            //! a lista de pares
            if (reference[i + (k * _width)] == '1' &&
            copy[i + (k * _width)] == '0') {
              //! Enfileira o par referente ao pixel
                pair_list.push(std::make_pair(i, k));

                //! Se encontrei um pixel que está na referencia mas não na cópia,
                //! adiciono-o à lista e checo se seus vizinhos estão na cópia
                //! Enquanto eu tiver algo na lista de pares estarei no mesmo objeto
                while(!pair_list.empty()){//
                  //! Armazena temporariamente as coordenadas do último píxel verificado
                    auto temp = pair_list.front();
                    pair_list.pop();// tira da primeira posição da fila

                    // Se esse vizinho não está do outro lado da imagem (pós borda)
                    if (temp.first-1 >= 0)
                      //! Se esse objeto está na referencia mas não na copia
                        if(reference[temp.first-1 + (temp.second * _width)] == '1' &&
                            copy[temp.first-1 + (temp.second * _width)] == '0') {
                              //! enfileira pixel para ter seus vizinhos checados
                            pair_list.push(std::make_pair(temp.first-1, temp.second));
                              //! Põe o rotulo referente ao objeto na cópia
                            copy[temp.first-1 + (temp.second * _width)] = label;
                        }

                    // Se esse vizinho não está do outro lado da imagem (pós borda)
                    if (temp.first+1 < _height)
                      //! Se esse objeto está na referencia mas não na copia
                        if(reference[temp.first+1 + (temp.second * _width)] == '1' &&
                             copy[temp.first+1 + (temp.second * _width)] == '0') {
                               // enfileira se na matriz copia for igual a zero
                               pair_list.push(std::make_pair(temp.first+1, temp.second));
                            copy[temp.first+1 + (temp.second * _width)] = label;
                        }

                    // Se esse vizinho não está do outro lado da imagem (pós borda)
                    if (temp.second-1 >= 0)
                      //! Se esse objeto está na referencia mas não na copia
                        if (reference[temp.first + ((temp.second-1) * _width)] == '1' &&
                            copy[temp.first + ((temp.second-1) * _width)] == '0') {
                            pair_list.push(std::make_pair(temp.first, temp.second-1));// enfileira se na matriz copia for igual a zero
                            copy[temp.first + ((temp.second-1) * _width)] = label;
                        }

                    // Se esse vizinho não está do outro lado da imagem (pós borda)
                    if (temp.second+1 < _width)
                      //! Se esse objeto está na referencia mas não na copia
                        if (reference[temp.first + (temp.second+1 * _width)] == '1' &&
                            copy[temp.first + ((temp.second+1) * _width)] == '0') {
                            pair_list.push(std::make_pair(temp.first, temp.second+1));// enfileira se na matriz copia for igual a zero
                            copy[temp.first + ((temp.second+1) * _width)] = label;
                        }

                    // Por fim copia o pixel checado atualmente
                    copy[temp.first + (temp.second * _width)] = label;


                }

                //! Após percorrer todos os pixeis adjacentes ao primeiro encontrado
                //! incremento o número de objetos
                num++;
            }
        }
    }


    return num;// retorna o valor do label
}
bool verify_xml(std::fstream& file) {// verifica os tres erros propostos no xml
    std::stack<std::string> stack;

    bool read = false;
    bool error = false;
    int m = 0;
    std::string temp_data = "";
    if (file.is_open()) {
        std::string line = "";
        while(std::getline(file, line)) {
            // for para percorrer a string da linha obtida com getline
            for (std::string::size_type i = 0; i < line.size(); ++i) {
                if (line[i] == '<') {
                    auto desempilha = false;
                    if(line[i+1] == '/') {
                        i++;
                        desempilha = true;
                    }
                    std::string info ="";
                    for(std::string::size_type j = i+1; j < line.size(); ++j) {
                        if (line[j] == '>' && desempilha) {  ///< se encontrou o fechamento e desempilhar for vdd
                            if (!stack.empty()) {
                                if (stack.top().compare(info) == 0) {  //< checa se o alvo a desempilhar é o topo
                                    stack.pop();  //< se for o topo desempilha
                                    break;
                                } else {  //< se não, lança erro
                                    error = true;
                                    break;
                                }
                            } else {
                                break;
                                error = true;
                            }
                        } else if (line[j] == '>' && !desempilha) {  //< se encontrou fechamento e desempilhar for falso
                                stack.push(info);  //< empilha o tag
                                break;
                            }
                        info = info + (line[j]);
                    }
                }
            }
        }
    } else {
            printf("didnt open!\n");// nao conseguiu abrir o xml
        }
    if (!stack.empty()) {// caso abriu uma tag mas nao fechou
        error = true;
    }
    file.close();// fecha o arquivo
    return error;
}
//!  pega o name de cada imagem
int get_atribute_name(std::fstream& file, std::list<std::string>& name_list_) {
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string name;
            while (line.find("<name>") != line.npos) {
                auto position = line.find("<name>");
                for (std::string::size_type i = position+6; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        name = name + line[i];
                    }
                }
            }
            if (name != "") {
                name_list_.push_back(name);
            }
        }
    }
    file.close();
    return name_list_.size();// retorna os nomes das imagens binarias
}
// pega a altura de cada imagem
int get_atribute_height(std::fstream& file, std::list<std::string>& height_list_) {

    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string height;
            while (line.find("<height>") != line.npos) {
                auto position = line.find("<height>");
                for (std::string::size_type i = position+8; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        height = height + line[i];
                    }
                }
            }
            if (height != "") {
                height_list_.push_back(height);
            }
        }
    }
    file.close();
    return height_list_.size();// retorna as alturas das imagens binarias
}
// pega o comprimento de cada imagem
int get_atribute_width(std::fstream& file, std::list<std::string>& width_list_) {

    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            std::string width;
            while (line.find("<width>") != line.npos) {
                auto position = line.find("<width>");
                for (std::string::size_type i = position+7; i < line.size(); ++i) {
                    if (line[i] == '<') {
                        line[position+1] = '@';
                        break;
                    } else {
                        width = width + line[i];
                    }
                }
            }
            if (width != "") {
                width_list_.push_back(width);
            }
        }
    }
    file.close();
    return width_list_.size();// retorna os comprimentos das imagens binarias
}
// pega o nome de cada imagem
int get_atribute_data(std::fstream& file, std::list<std::string>& data_list_, std::list<std::string> height_list_) {
    std::list<std::string> aux;
    if (file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            if (line.find('<') == line.npos && line != "") {
                    aux.push_back(line);
            }
        }
    }
    auto size = height_list_.size();
    for (auto i = 0; i != size; i++) {
        std::string empilha;
        for (int j = 0; j != stoi(height_list_.front()); j++) {
                empilha = empilha + aux.front();

            aux.pop_front();
        }
        data_list_.push_back(empilha);
        height_list_.pop_front();
    }

    file.close();
    return data_list_.size();/// retorna os nomes das imagens binarias
}
