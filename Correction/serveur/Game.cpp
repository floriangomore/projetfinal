#include		<iostream>
#include		"Game.h"

Game::Game(int nbLines, int nbPlayers)
{
  m_nbLines = nbLines;
  m_nbPlayers = nbPlayers;
  
  int			sticks = 1;
  for (int i = 1; i <= nbLines; i++) {
    m_lines[i] = new Line(i, sticks);
    sticks += 2;
  }

  for (int i = 1; i <= nbPlayers; i++) {
    m_players[i] = new Player();
  }
}

Game::~Game()
{
  for (int i = 1; i <= m_nbLines; i++) {
    Line *l = m_lines[i];
    delete l;
  }
  for (int i = 1; i <= m_nbPlayers; i++) {
    Player *p = m_players[i];
    delete p;
  }
}

void			Game::displayGame(void)
{
  for (int i = 1; i <= m_nbLines; i++) {
    Line *l = m_lines[i];
    l->display();
  }
  // Boucle de jeu...
}

bool			Game::checkVictory(void)
{
  int			nbTotalSticks = 0;
  for (int i = 1; i <= m_nbLines; i++) {
    Line *l = m_lines[i];
    nbTotalSticks += l->getNbSticks();
  }

  if (nbTotalSticks == 0) {
    return (true);
  }
  return (false);
}

void			Game::playerTurn(Player *p)
{
  int			moves[2];
  
  p->play(moves);
  if (moves[0] < 0 || moves[0] > m_nbLines) {
    // La Line n'existe pas, on passe le tour
    return ;
  }
  Line *l = m_lines[moves[0]];
  l->takeSticks(moves[1]);
}

void			Game::start(void)
{
  displayGame();
  while (1) {
    playerTurn(m_players[1]);
    if (checkVictory() == true) {
      std::cout << m_players[2]->getName() + " a gagné !" << std::endl;
      break;
    }
    displayGame();
    playerTurn(m_players[2]);
    if (checkVictory() == true) {
      std::cout << m_players[1]->getName() + " a gagné !" << std::endl;
      break;
    }
    displayGame();
  }
}
