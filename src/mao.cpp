#include <vector>
#include <algorithm>

#include "mao.h"
#include "carta.h"
#include "lixo.h"

Mao::Mao():
    ConjuntoDeCartas(){}

bool Mao::inserir_cartas (std::vector<Carta*> cartas) {
    for (int i=0; i<cartas.size(); i++){
        _cartas.push_back(cartas[i]);
    }
    reordenar_cartas(&_cartas);
    return false;
};

bool Mao::descer_cartas (Jogo* jogo, std::vector<int> indexCartas){
  std::vector<Carta*> cartas;
  for (int i=0; i<indexCartas.size(); i++){
      if (indexCartas[i] >= _cartas.size()){
        std::cout << "indice invalido" << '\n';
        system("PAUSE");
        return true;
      }
    }


  for (int i=0; i<indexCartas.size(); i++){
    cartas.push_back(_cartas[indexCartas[i]]);
  }
  std::cout << "\n";
  if (jogo->inserir_cartas(cartas)){
    return true;
  }
  else {
    for (int i=(indexCartas.size()-1); i>=0 ; i--){
      _cartas.erase(_cartas.begin()+indexCartas[i]);
    }
    return false;
  }
};

bool Mao::descartar_carta (Lixo* lixo, int indexCarta){
  if (indexCarta >= _cartas.size()){
    std::cout << "indice invalido" << '\n';
    system("PAUSE");
    return true;
  }

    if (!lixo->inserir_cartas(_cartas[indexCarta])){
        _cartas.erase(_cartas.begin()+indexCarta);
        return false;
    }
    return true;
};
