#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "LeitorArquivo.h"
#include "Save.h"

Save save;

LeitorArquivo leitorArquivo;

int main() {

    //Tela de Menu
        // 1 -> Nova Aventura
        // 2 -> Carregar Aventura
    leitorArquivo.exibirCena("menu");
    save.saveGame();
    
    int cena = 1;
    const int totalCenas = 10;

    while (cena <= totalCenas) {
        std::cout << "\n=== Cena " << cena << " ===\n\n";
        leitorArquivo.exibirCena(cena);

        int escolha = leitorArquivo.obterEscolhaUsuario();
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
