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


void    clientTalk(int sockfd)
{
  int   clientfd;
  char  clientmsg[11] = {0};
  int   msg_len = 0;
  t_sai sin = {0};
  socklen_t     sin_len;

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
