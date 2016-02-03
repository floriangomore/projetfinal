#ifndef GAME_H_
# define GAME_H_

#include			<map>
#include			"Player.h"
#include			"Line.h"

class				Game
{
 private:
  std::map<int, Player*>	m_players;
  std::map<int, Line*>		m_lines;
  int				m_nbLines;
  int				m_nbPlayers;

  void				displayGame(void);
  bool				checkVictory(void);
  void				playerTurn(Player *p);
  
 public:
  Game(int nbLines = 4, int nbPlayers = 2);
  ~Game();

  void				start(void);
};

#endif // GAME_H_
