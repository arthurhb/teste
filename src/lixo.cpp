#include "lixo.h"

Lixo::Lixo (bool lixoFechado):
  ConjuntoDeCartas(), _lixoFechado (lixoFechado){}



bool Lixo::inserir_cartas (Carta* cartas){
  if (_cartaLixada == cartas){
    std::cout << "nao descarte a mesma carta que lixou" << '\n';
    system("PAUSE");
    return true;
  }
  _cartas.push_back(cartas);
  _cartaLixada=nullptr;
  return false;
};

std::vector<Carta*> Lixo::pegar_lixo (){
  if (_cartas.size() == 1)
      _cartaLixada = _cartas[0];
  else
      _cartaLixada = nullptr;
  auto aux_cartas = _cartas;
  _cartas.clear();
  return aux_cartas;
};


void Lixo::exibir_cartas() const {
  if (_lixoFechado){
    if (_cartas.size()>0) _cartas.back()->exibir_carta();
  }
  else {
    for(int i=0; i< _cartas.size(); i++){
      _cartas[i]->exibir_carta();
    }
  }
 std::cout << '\n';
}
