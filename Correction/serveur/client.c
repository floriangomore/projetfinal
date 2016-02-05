#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct sockaddr_in	t_sai;
typedef struct protoent		t_prot;

int	clt_create_socket()
{
  int		sockfd = 0;
  t_prot	*pe;

  if ((pe = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  return (sockfd);
}

static char	*clt_get_host(char *hostname)
{
  struct hostent	*h;

  if ((h = gethostbyname(hostname)) == NULL)
    return (hostname);
  return (inet_ntoa(*((struct in_addr *)(h->h_addr_list[0]))));
}

int		clt_connect(int clt_sock, int port, char *hostname)
{
  t_sai		sin = {0};
  socklen_t	sin_len = sizeof(sin);

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(clt_get_host(hostname));
  if ((connect(clt_sock, (struct sockaddr *)&(sin), sin_len)) == -1)
    return (-1);
  return (0);
}

void	server_talk(int clt_sock)
{
  int	msg_len = 0;
  char	srv_msg[11] = {0};

  msg_len = recv(clt_sock, srv_msg, 10, 0);
  srv_msg[msg_len == 10 ? msg_len : msg_len - 1] = 0;
  fprintf(stdout, "Received message from server[%s]\n", srv_msg);
  send(clt_sock, "Salut !\n", strlen("Salut !\n"), MSG_NOSIGNAL);
  fprintf(stdout, "Sent message to server\n");
}

int	client(char *hostname, int port)
{
  int clt_sock;

  if ((clt_sock = clt_create_socket()) == -1)
    return (1);
  fprintf(stdout, "Socket created\n");
  if (clt_connect(clt_sock, port, hostname) == -1)
    {
      close(clt_sock);
      return (1);
    }
  fprintf(stdout, "Connected to server\n");
  server_talk(clt_sock);
  close(clt_sock);
  return (0);
}

int	main(int ac, char *av[])
{
  if (ac != 3)
    return (1);
  return (client(av[1], atoi(av[2])));
}
