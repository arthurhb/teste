// Desenvolvedor Responsável: Rodrigo

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <locale.h>

#include "buraco.h"
#include "jogador.h"
#include "times.h"

void partida (int numeroDeTimes,int numeroDeJogadores,bool valeTrinca,bool lixoFechado,bool usarJoker);
int get_times();
int get_jogadores();
bool get_trinca();
bool get_lixo();
bool get_joker();

int main () {
    srand (time(NULL));
    setlocale(LC_ALL, "Portuguese"); //Para exibir caracteres com acento

    while (true) {
      std::string comando;
      system ("CLS");
      std::cout << "O que deseja fazer?\n(1 - Iniciar nova partida , 2 - Sair)\n";
      std::cin>> comando;
      if (comando == "1") {
        int numeroDeTimes;
        int numeroDeJogadores;
        while(true){
          numeroDeTimes = get_times();
          numeroDeJogadores = get_jogadores();
          if (numeroDeJogadores*numeroDeTimes <= 6) break;
          std::cout << "O numero total de times nao pode ser maior que 6" << '\n';
          system("PAUSE");
        }
        bool valeTrinca = get_trinca();
        bool lixoFechado = get_lixo();
        bool usarJoker = get_joker();
        partida(numeroDeTimes,numeroDeJogadores,valeTrinca,lixoFechado,usarJoker);
      }
      else if (comando == "2") {
        system ("CLS");
        std::cout<< "Obrigado por jogar com a gente\n";
        break;
      }
        else {
            std::cout<< "Comando inválido\n";
            system("PAUSE");
        }
    }
}

void partida (int numeroDeTimes,int numeroDeJogadores,bool valeTrinca,bool lixoFechado,bool usarJoker) {
    Time* timeAtual;
    Jogador* jogadorAtual;
    int comando;
    Buraco buraco (numeroDeTimes,numeroDeJogadores,valeTrinca,lixoFechado,usarJoker);
    while (true){
        // verifica se acabou as cartas da pilha
        if (buraco.get_quantidade_pilha() == 0) {
          buraco.morto_para_pilha();
          if (buraco.get_quantidade_pilha() == 0) break;
        }
        timeAtual = buraco.get_time_atual();
        jogadorAtual = timeAtual->get_jogador_atual();

        buraco.exibir_proximo_jogador ();

        // rotina de compra/lixa
        while (true){
          system ("CLS");
          buraco.exibir_mesa();
          std::cout << "Deseja comprar ou lixar?\n(1 - Comprar , 2 - Lixar)\n";
          std::cin>> comando;
          if (comando == 1) {
            jogadorAtual->inserir_uma_carta(buraco.comprar_carta());
            break;
          }
          if (comando ==2){
            jogadorAtual->inserir_cartas(buraco.pegar_lixo());
            break;
          }
          std::cout << "Comando invalido\n";
          system("PAUSE");
        }
        // rotina de descer jogos
        while (true){
          // verifica se jogador bateu
          if (jogadorAtual->get_numero_de_cartas() == 0){
            if (timeAtual->get_pegou_morto()) {
              timeAtual->bater();
              break;
            }
            if (buraco.get_quantidade_mortos() == 0){
              timeAtual->bater();
              break;
            }
            jogadorAtual->inserir_cartas(buraco.pegar_morto(timeAtual));
          }
          system ("CLS");
          // exibe mesa (times, jogadores, jogos pilhas e morto)
          buraco.exibir_mesa();
          std::cout << "Deseja descer algum jogo?\n(1 - Sim , 2 - Nao)\n";
          std::cin>> comando;
          if (comando == 1) {
            system ("CLS");
            buraco.exibir_mesa();
            std::cout << "Digite as cartas que deseja descer:\n";
            std::vector<int> indexCartas;
            std::string line;
            std::cin.ignore();
            getline(std::cin, line);
            std::istringstream stream2(line);
            while (stream2.good()){
              std::string temp;
              stream2 >> temp;
              indexCartas.push_back(std::stoi(temp));
            }
            std::sort(indexCartas.begin(), indexCartas.end());
            system ("CLS");
            buraco.exibir_mesa();
            std::cout << "Deseja descer em um jogo novo ou em algum existente?\n(1 - Novo , 2 - Existente)\n";
            int comando_aux;
            std::cin>> comando_aux;
            if (comando_aux == 1) {
              timeAtual->descer_jogo_novo(indexCartas);
            }
            else if (comando_aux == 2){
              system ("CLS");
              buraco.exibir_mesa();
              std::cout << "Em qual jogo deseja descer?\n";
              int indexJogo;
              std::cin>> indexJogo;
              timeAtual->descer_jogo_existente(indexCartas, indexJogo);
            }
            else {
              std::cout << "Comando invalido\n";
            system("PAUSE");
            }
          }
          else if (comando ==2){
            break;
          }
          else{
            std::cout << "Comando invalido\n";
            system("PAUSE");
          }
        }
        //rotina de descartar cartas
        while (true){
          int carta;
          system ("CLS");
          buraco.exibir_mesa();
          std::cout << "Selecione a carta que deseja descartar.\n";
          std::cin>> carta;
          if (!buraco.inserir_no_lixo(jogadorAtual, carta)) break;
        }
        // verifica se jogador bateu
        if (jogadorAtual->get_numero_de_cartas() == 0){
          if (timeAtual->get_pegou_morto()) {
            timeAtual->bater();
            break;
          }
          if (buraco.get_quantidade_mortos() == 0){
            timeAtual->bater();
            break;
          }
          jogadorAtual->inserir_cartas(buraco.pegar_morto(timeAtual));
        }
        timeAtual->proximo_jogador();
        buraco.proximo_time();
    }

    system ("CLS");
    Time* timeVencedor = buraco.get_time_vencedor();
    std::cout << "O time vencedor é o " << timeVencedor->get_nome() << "!!! Parabens!!!\n";
    system("PAUSE");
};

int get_times(){
    int aux;
    while (true) {
        system ("CLS");
        std::cout << "Digite o numero de times:\n";
        std::cin>> aux;
        if (aux>1) return aux;
        std::cout << "O numero de times deve ser maior que um\n";
        system("PAUSE");
    }
};

int get_jogadores(){
    int aux;
    while (true) {
        system ("CLS");
        std::cout << "Digite o numero de jogadores de cada equipe:\n";
        std::cin>> aux;
        if (aux>0) return aux;
        std::cout << "O numero de jogadores deve ser maior que zero\n";
        system("PAUSE");
    }
};

bool get_trinca(){
    while (true) {
        int aux;
        system ("CLS");
        std::cout << "Jogar com trincas?\n(1 - Sim , 2 - Nao)\n";
        std::cin>> aux;
        if (aux==1) return true;
        else if (aux==2) return false;
        std::cout << "Comando invalido\n";
        system("PAUSE");
    }
};

bool get_lixo(){
    while (true) {
        int aux;
        system ("CLS");
        std::cout << "Jogar com lixo fechado?\n(1 - Fechado , 2 - Aberto)\n";
        std::cin>> aux;
        if (aux==1) return true;
        else if (aux==2) return false;
        std::cout << "Comando invalido\n";
        system("PAUSE");
    }
};

bool get_joker(){
    while (true) {
        int aux;
        system ("CLS");
        std::cout << "Utilizar baralho com Joker?\n(1 - Sim , 2 - Nao)\n";
        std::cin>> aux;
        if (aux==1) return true;
        else if (aux==2) return false;
        std::cout << "Comando invalido\n";
        system("PAUSE");
    }
};
