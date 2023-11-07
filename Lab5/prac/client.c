// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <sys/select.h>
// #include <assert.h>

// void checkError(int status,int line)
// {
//    if (status < 0) {
//       printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
//       exit(-1);
//    }
// }

// /* Reads input till end of line from the socket */
// char* readResponse(int fd) {
//    int sz = 8;
//    char* buf = malloc(sz);
//    int ttl = 0,at = 0;
//    int recvd;
//    do {
//       recvd = read(fd,buf+at,1);
//       ttl += recvd;
//       at  += recvd;
//       if (recvd > 0 && ttl == sz) {
//          buf = realloc(buf,sz*2);
//          sz *= 2;
//       }
//       buf[ttl] = 0;
//    } while (buf[ttl-1] != '\n' && recvd > 0);
//    return buf;
// }

// int main(int argc,char* argv[]) 
// {
//    if (argc < 2) {
//       printf("Usage is: client <hostname>\n");
//       return 1;
//    }

//    /* Specify the server address and connect with the server on port 8025 */
//    int sid = socket(PF_INET,SOCK_STREAM,0);
//    struct sockaddr_in srv;
//    struct hostent *server = gethostbyname(argv[1]);
//    if (server==NULL) {
//       printf("Couldn't find a host named: %s\n",argv[1]);
//       return 2;
//    }
//    srv.sin_family = AF_INET;
//    srv.sin_port   = htons(8025);
//    memcpy(&srv.sin_addr,server->h_addr_list[0],server->h_length);
//    int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
//    checkError(status,__LINE__);

//     /* TODO (Q2.) 
//      * The client simply listens to two file descriptors using the select API:
//         * stdin: to read strings from the stdin and send them to the server.
//         * sid: to read the response from the server and print it out on stdout.
//      * If the string is $exit in either case, the client terminates.
//      * Note: do not forget to free any memory that you allocate to store the message and do not forget to close the sockets before exiting the program normally.
//     */


//    return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>

void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

/* Reads input till end of line from the socket */
char* readResponse(int fd) {
   int sz = 8;
   char* buf = malloc(sz);
   int ttl = 0,at = 0;
   int recvd;
   do {
      recvd = read(fd,buf+at,1);
      ttl += recvd;
      at  += recvd;
      if (recvd > 0 && ttl == sz) {
         buf = realloc(buf,sz*2);
         sz *= 2;
      }
      buf[ttl] = 0;
   } while (buf[ttl-1] != '\n' && recvd > 0);
   return buf;
}

int main(int argc,char* argv[]) 
{
   if (argc < 2) {
      printf("Usage is: client <hostname>\n");
      return 1;
   }

   /* Specify the server address and connect with the server on port 8025 */
   int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   struct hostent *server = gethostbyname(argv[1]);
   if (server==NULL) {
      printf("Couldn't find a host named: %s\n",argv[1]);
      return 2;
   }
   srv.sin_family = AF_INET;
   srv.sin_port   = htons(8025);
   memcpy(&srv.sin_addr,server->h_addr_list[0],server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);

    /* TODO (Q2.) 
     * The client simply listens to two file descriptors using the select API:
        * stdin: to read strings from the stdin and send them to the server.
        * sid: to read the response from the server and print it out on stdout.
     * If the string is $exit in either case, the client terminates.
     * Note: do not forget to free any memory that you allocate to store the message and do not forget to close the sockets before exiting the program normally.
    */
    fd_set readfds;
    char* buf = NULL;
   int maxfd = STDIN_FILENO;
   if (sid > maxfd) {
      maxfd = sid;
   }
    while(1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(sid, &readfds);
        int status = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        checkError(status,__LINE__);
      if (FD_ISSET(STDIN_FILENO, &readfds)) {
         buf = readResponse(STDIN_FILENO);
         if (strcmp(buf, "$exit\n") == 0) {
            status = write(sid, buf, strlen(buf));
            checkError(status,__LINE__);
            free(buf);
            break;
         }
         status = write(sid, buf, strlen(buf));
         checkError(status,__LINE__);
         free(buf);
      } else if (FD_ISSET(sid, &readfds)) {
         buf = readResponse(sid);
         if (strcmp(buf, "$exit\n") == 0) {
            free(buf);
            break;
         }
         printf("%s", buf);
         free(buf);
      }
    }
    close(sid);
    return 0;
}
