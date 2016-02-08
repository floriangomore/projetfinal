#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

typedef struct sockaddr_in	t_sai;
typedef struct protoent		t_prot;

int	server_connect(int port)
{
  int	sockfd = 0;
  t_sai	sin;
  t_prot	*pe;

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
  printf("blatte1\n");
  listen(sockfd, 5);
  printf("blatte2\n");
  return (sockfd);
}

void	client_talk(int sockfd, int count)
{
  int	clientfd;
  char	clientmsg[11] = {0};
  int	msg_len = 0;
  t_sai	sin = {0};
  socklen_t	sin_len;

  sin_len = sizeof(sin);
  if ((clientfd = accept(sockfd, (struct sockaddr *)&sin, &sin_len)) == -1)
    {
      fprintf(stderr, "Client [%d] had a problem\n", count);
      return ;
    }
  fprintf(stdout, "Server sending message to client[%d] on socket[%d]\n",
	  count, clientfd);
  send(clientfd, "Bonjour\n", strlen("Bonjour\n"), MSG_NOSIGNAL);
  msg_len = recv(clientfd, clientmsg, 10, 0);
  clientmsg[msg_len == 10 ? msg_len : msg_len - 1] = 0;
  fprintf(stdout, "Client[%d] on socket[%d] sent [%d] bytes: [%s]\n",
	  count, clientfd, msg_len, clientmsg);
  close(clientfd);
}

int	server(int port)
{
  int	sockfd;
  int	count;

  if ((sockfd = server_connect(port)) == -1)
    return (-1);
  fprintf(stdout, "Server is up and running on port[%d]\n", port);
  for (count = 0; count < 3; count++)
    client_talk(sockfd, count);
  fprintf(stdout, "Server is closing port[%d]\n", port);
  close(sockfd);
  return (0);
}

int	main(int ac, char *av[])
{
  if (ac != 2)
    return (1);
  return (server(atoi(av[1])));
}
