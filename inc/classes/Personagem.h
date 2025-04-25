#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <string>
#include <map>
#include <sstream>
#include "Arquivos.h"
using namespace std;

class Personagem {
public:
	Personagem();

	virtual void carregarPersonagem(string nomePersonagem = "personagem");
	//O melhor seria criar uma nova classe apara implementar esse método nos inimigos

	
	void setNome(string nome);
	void setEnergia(int energia);
	void setSorte(int sorte);
	void setHabilidade(int habilidade);
	void setProvisoes(int provisoes);
	
	string getNome();
	int getEnergia();
	int getSorte();
	int getHabilidade();
	int getProvisoes();

	void addEnergia(int energiaAdicionada);
	void addHabilidade(int energiaAdicionada);
	void addSorte(int sorteAdicionada);
	//void addMagia(Magia novaMagia);
	//void addItem(Item novoItem);
	//void addTesouro(Item novoTesouro);
	void addProvisao(int provisaoAdicionada = 1);

	void removerEnergia(int energiaRemovida);
	void removerSorte(int sorteRemovida);

	bool utilizarProvisao();
	int testeDeAtaque(bool usarSorte);
	int usarSorte();

protected:
	string nome;
	int energia = 12;
	int sorte = 6;
	int habilidade = 6;
	//Grimorio magias;
	//Item inventario[10];
	//Item tesouros[10];
	int quantidadeDeProvisoes;
	int energiaRecuperadaPorProvisao = 4;

	Arquivos arquivo;
};

#endif