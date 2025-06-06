#include "../inc/classes/OrquestradorCenas.h"

OrquestradorCenas::OrquestradorCenas(Heroi *heroi){
    this->heroi = heroi;
}

string OrquestradorCenas::getUltimaCena(){
    return ultimaCena;
}

void OrquestradorCenas::setUltimaCena(string ultimaCena){
    this->ultimaCena = ultimaCena;
}

void OrquestradorCenas::clearTheTerminal(){
    #ifdef _WIN32
    system("cls"); // For Windows
    #else
        system("clear"); // For Unix-like systems (Linux, macOS)
    #endif

}

void OrquestradorCenas::carregarDescricao(string cena){
    istringstream stream(cena);
    string descricao;
    string linha;
    while(getline(stream, linha)){
        if(linha.rfind("N:", 0) == 0 || linha.rfind("m", 0) == 0){
            break;
        } else if (linha.rfind("I:", 0) == 0 || linha.rfind("P:", 0) == 0 || isdigit(linha[0])){

        } else {
            descricao += linha + "\n";
        }
    }
    cout << descricao << endl;
}

string OrquestradorCenas::lerAtributosDoInimigo(string cena){
    istringstream stream(cena);
    string atributos;
    string linha;
    while(getline(stream, linha)){
        if (linha.find(':') != string::npos) {
            atributos += linha + "\n"; // apenas adiciona a linha à string
        }
    }
    return atributos;
}

void OrquestradorCenas::getProximasCenas(string cena){
    istringstream stream(cena);
    string ultimaLinhaNumeros;
    string linha;
    while (getline(stream, linha)) {
        if (linha.find(';') != string::npos && linha.find(':') == string::npos) {
            ultimaLinhaNumeros = linha; // armazena a última que parece ser "NumeroA;NumeroB"
        }
    }

    // Extrai os dois números da última linha encontrada
    if (!ultimaLinhaNumeros.empty()) {
        size_t pos = ultimaLinhaNumeros.find(';');
        proximaCenaA = ultimaLinhaNumeros.substr(0, pos);
        proximaCenaB = ultimaLinhaNumeros.substr(pos + 1);

    }
}

void OrquestradorCenas::getItensDaCena(string cena){
    stringstream ss(cena);
    string linha;
    quantidadeDeItensNaCena = 0;

    while(getline(ss, linha)){
        if (linha.find("I:", 0) == 0){
            quantidadeDeItensNaCena++;
            itensDaCena[quantidadeDeItensNaCena] = linha.substr(2);
            break;
        }
    }
}



void OrquestradorCenas::limparItensDaCena(){
    for(int i = 0; i < 5; i++){
        itensDaCena[i] = "";
    }
}

bool OrquestradorCenas::hasItemNaCena(string cena){
    stringstream ss(cena);
    string linha;

    while(getline(ss, linha)){
        if (linha[0] == 'I'){
            return true;
        }
    }
    return false;
}

void OrquestradorCenas::getProvisaoDaCena(string cena){
    stringstream ss(cena);
    string linha;

    while(getline(ss, linha)){
        if (linha.rfind("P:", 0) == 0){
            if(stoi(linha.substr(3, 1)) == 0){
                return;
            }
            heroi->getProvisao(stoi(linha.substr(3, 1)));
            return;
        }
    }
    return;
}



void OrquestradorCenas::runCena(){
    clearTheTerminal();
    heroi->printStats();
    string cena = arquivo.lerArquivo(this->ultimaCena);
    getProvisaoDaCena(cena);
    carregarDescricao(cena);
    getProximasCenas(cena);
    if(hasItemNaCena(cena)) getItensDaCena(cena);

    if(ultimaCena.at(0) == 'm'){
        Inimigo inimigo;

        inimigo.carregarPersonagem(lerAtributosDoInimigo(cena));

        Batalha batalha(heroi, &inimigo);
        bool resultadoDaBatalha = batalha.run();
        if(resultadoDaBatalha == false){
            cout << "Infelizmente " << heroi->getNome() << " sucumbiu na luta contra " << inimigo.getNome() << "..." << endl;
            cout << "Tente novamente! (reinicie o jogo e vá em carregar)" << endl;
            while(true){}
            //Modificar para verificar próxima cena
        } else {
            ultimaCena = proximaCenaA;
        }
        clearTheTerminal();
        // Cena de batalha
        // print da cena
        // print opções padrao
        // espera resposta de usuário
    } else {
        bool cenaCompleta = false;
        bool itemColetado = false;
        while(cenaCompleta == false){
            clearTheTerminal();
            heroi->printStats();
            carregarDescricao(cena);
            int maximoDeOpcoes = hasItemNaCena(cena) ? 5 : 4;
            int opcaoSelecionada = userInput.rangedReadNumber(1, maximoDeOpcoes);
            if(opcaoSelecionada == maximoDeOpcoes - 3){
                ultimaCena = proximaCenaA;
                cenaCompleta = true;
            } else if(opcaoSelecionada == maximoDeOpcoes - 2){
                ultimaCena = proximaCenaB;
                cenaCompleta = true;
            } else if(opcaoSelecionada == maximoDeOpcoes - 1){
                heroi->usarProvisao();
            } else if(opcaoSelecionada == maximoDeOpcoes){
                heroi->mostrarInventario();
            } else {
                int posicaoMarcadorNomeDoItem = itensDaCena[opcaoSelecionada].find(';');
                if(itemColetado == true){
                    cout << itensDaCena[opcaoSelecionada].substr(0, posicaoMarcadorNomeDoItem) << " já está no seu inventário..." << endl;
                } else {
                    heroi->adicionarItemAoInventario(itensDaCena[opcaoSelecionada]);
                    cout << itensDaCena[opcaoSelecionada].substr(0, posicaoMarcadorNomeDoItem) << " adicionado ao inventário de " << heroi->getNome() << endl;      
                    itemColetado = true;
                }
            }
        }

        limparItensDaCena();
        heroi->setUltimaCena(ultimaCena);
        clearTheTerminal();
        
        // Cena de escolha ou interação
        // print da cena
        // print das opções descritas na cena
        // espera resposta de usuário
    }
}