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

int	launchGame()
{
  int		sockfd = 0;
  int		win = 0;
  t_sai		sin = {0};
  t_prot	*pe;

  int		clientfd1;
  int		clientfd2;
  char		clientmsg[11] = {0};
  int		msg_len = 0;
  socklen_t	sin_len;

  //Server Connect
  bzero(&sin, sizeof(sin));
  if ((pe = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(4252);
  sin.sin_addr.s_addr = INADDR_ANY;
  if ((bind(sockfd, (struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      close(sockfd);
      return (-1);
    }
  listen(sockfd, 5);
  printf("SERVER UP\n");

  //Connect client 1
  sin_len = sizeof(sin);
  write(1, "a", 1);
  if ((clientfd1 = accept(sockfd, (struct sockaddr *)&sin, &sin_len)) == -1)
    {
      fprintf(stderr, "Client had a problem\n");
      return (-1);
    }
  write(1, "b", 1);
  send(clientfd1, "Connected", strlen("Connected") + 1, MSG_NOSIGNAL);


  //Game
  while (win < 4)
    {

      msg_len = recv(clientfd1, clientmsg, 10, 0);
      clientmsg[msg_len == 10 ? msg_len : msg_len - 1] = 0;
      fprintf(stdout, "%s\n", clientmsg);
      
      win+=1;
    }

  // End Server
  close(clientfd1);
  close(clientfd2);
  fprintf(stdout, "server will down\n");
  close(sockfd);
  fprintf(stdout, "server closed\n");
  return (0);
}
