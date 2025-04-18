#include <iostream>
#include <fstream>
#include <string>
#include <limits>

void exibirCena(int cenaAtual) {
    std::string nomeArquivo = "textos/" + std::to_string(cenaAtual) + ".txt";
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cout << "Não foi possível abrir o arquivo da cena " << cenaAtual << ".\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }

    arquivo.close();
}

int obterEscolhaUsuario() {
    int escolha;
    std::cout << "\nEscolha sua ação:\n";
    std::cout << "1 - Continuar para a próxima cena\n";
    std::cout << "0 - Sair do jogo\n";
    std::cout << ">> ";
    std::cin >> escolha;

    while (std::cin.fail() || (escolha != 1 && escolha != 0)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Tente novamente: ";
        std::cin >> escolha;
    }

    return escolha;
}

int main() {
    int cena = 1;
    const int totalCenas = 10;

    while (cena <= totalCenas) {
        std::cout << "\n=== Cena " << cena << " ===\n\n";
        exibirCena(cena);

        int escolha = obterEscolhaUsuario();
        if (escolha == 0) {
            std::cout << "Você abandonou a dungeon. Fim de jogo.\n";
            break;
        }

        cena++;
    }

    if (cena > totalCenas) {
        std::cout << "\nVocê completou a Dungeon de Thal'Zul! Parabéns!\n";
    }

    return 0;
}
