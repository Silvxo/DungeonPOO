#include "LeitorArquivo.h"


void LeitorArquivo::exibirCena(int cenaAtual) {
    std::string nomeArquivo = "textos/" + std::to_string(cenaAtual) + ".txt";
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cout << "N�o foi poss�vel abrir o arquivo da cena " << cenaAtual << ".\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }

    arquivo.close();
}

void LeitorArquivo::exibirCena(string cenaAtual) {
    std::string nomeArquivo = "textos/" + cenaAtual + ".txt";
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cout << "N�o foi poss�vel abrir o arquivo da cena " << cenaAtual << ".\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }

    arquivo.close();
}

int LeitorArquivo::obterEscolhaUsuario() {
    int escolha;
    std::cout << "\nEscolha sua a��o:\n";
    std::cout << "1 - Continuar para a pr�xima cena\n";
    std::cout << "0 - Sair do jogo\n";
    std::cout << ">> ";
    std::cin >> escolha;

    while (std::cin.fail() || (escolha != 1 && escolha != 0)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inv�lida. Tente novamente: ";
        std::cin >> escolha;
    }

    return escolha;
}