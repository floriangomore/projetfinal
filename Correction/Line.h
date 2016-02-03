#ifndef LINE_H_
# define LINE_H_

class		Line
{
 private:
  int		m_nbSticks;
  int		m_numLine;
 public:
  Line(int numLine, int nbSticks);
  ~Line();

  int		getNbSticks(void) const { return (m_nbSticks); }
  int		getNumLine(void) const { return (m_numLine); }

  void		display(void) const;
  bool		takeSticks(int nbSticks);
};

#endif // LINE_H_
