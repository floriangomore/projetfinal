#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

typedef struct sockaddr_in      t_sai;
typedef struct protoent         t_prot;


int     startServer(int port)
{
  int   sockfd = 0;
  t_sai sin;
  t_prot        *pe;

  bzero(&sin, sizeof(sin));
  if ((pe = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(sockfd, (struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      close(sockfd);
      return (-1);
    }
  listen(sockfd, 5);
  return (sockfd);
}
