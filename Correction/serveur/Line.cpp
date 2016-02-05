#include		<iostream>
#include		"Line.h"

Line::Line(int numLine, int nbSticks) :
  m_numLine(numLine), m_nbSticks(nbSticks)
{
  
}

Line::~Line()
{}

void			Line::display(void) const
{
  std::cout << m_numLine << ": ";
  for (int i = 0; i < m_nbSticks; i++) {
    std::cout << "|";
  }
  std::cout << std::endl;
}

bool			Line::takeSticks(int nbSticks)
{
  if (nbSticks <= 0 || nbSticks > m_nbSticks) {
    return (false);
  }
  m_nbSticks -= nbSticks;
  return (true);
}
