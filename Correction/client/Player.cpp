#include		<iostream>
#include		"Player.h"

Player::Player()
{
  std::cout << "Entrez le nom du joueur: " << std::endl;
  std::cin >> m_name;
}

Player::~Player()
{}

bool			Player::play(int *moves)
{
  std::cout << "Numéro de ligne: ";
  std::cin >> moves[0];

  std::cout << "Nombre de batons: ";
  std::cin >> moves[1];
  return (true);
}
