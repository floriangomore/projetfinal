#ifndef PLAYER_H_
# define PLAYER_H_

#include		<string>

class			Player
{
 private:
  std::string		m_name;
 public:
  Player();
  ~Player();

  const std::string&	getName(void) const { return (m_name); }
  bool			play(int *);
};

#endif // PLAYER_H_
