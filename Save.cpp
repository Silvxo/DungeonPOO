#include "Save.h"

void Save::saveGame() {
    std::string nome;
    int energia;
    int sorte;
    int habilidade;
    int quantidadeDeProvisoes;
    const int energiaRecuperadaPorProvisao = 4;

    // Recebendo os dados do personagem
    std::cout << "Nome do personagem: ";
    std::getline(std::cin, nome);

    std::cout << "Energia: ";
    std::cin >> energia;

    std::cout << "Sorte: ";
    std::cin >> sorte;

    std::cout << "Habilidade: ";
    std::cin >> habilidade;

    std::cout << "Quantidade de provisões: ";
    std::cin >> quantidadeDeProvisoes;

    // Salvando em arquivo
    std::ofstream arquivo("personagem.txt");

    if (arquivo.is_open()) {
        arquivo << "N:" << nome << ";";
        arquivo << "E:" << energia << ";";
        arquivo << "S:" << sorte << ";";
        arquivo << "H:" << habilidade << ";";
        arquivo << "P:" << quantidadeDeProvisoes << ";";
        arquivo.close();
        std::cout << "Personagem salvo com sucesso!" << std::endl;
    }
    else {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }
}
