// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <sys/wait.h>
// #include <fcntl.h>
// #include <netinet/in.h>
// #include <dirent.h>

// void checkError(int status)
// {
//    if (status < 0) {
//       printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
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
//    /* Create a server socket */
//    int sid = socket(PF_INET,SOCK_STREAM,0);

//    /* Make the server-side socket non-blocking */
//    int flags = fcntl(sid, F_GETFL, 0);
//    checkError(flags);
//    flags = flags | O_NONBLOCK;
//    int status = fcntl(sid, F_SETFL, flags);
//    checkError(status);
//    int enable = 1;
//    status = setsockopt(sid, SOL_SOCKET,SO_REUSEADDR, &enable, sizeof(int));
//    checkError(status);
  
//    /* Setup server address -- will listen on 8025 -- and bind to the socket */
//    struct sockaddr_in addr;
//    addr.sin_family = AF_INET;
//    addr.sin_port   = htons(8025);
//    addr.sin_addr.s_addr = INADDR_ANY;
//    status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
//    checkError(status);

//    /* Listen on that socket for let's connect messages. No more than 10 pending at once. */
//    status = listen(sid,10);
//    checkError(status);
   
//    int nbc = 0;         /* used to track the number of clients connected at any time */
//    int clients[10];     /* an array to store the socket ids for each client */

//    /* TODO (Q2.)
//     * Given n client sockets and the server socket, the server simply needs to listen to all of them using the select API. 
//     * Initially, there are no client sockets. Therefore, the server only listens to sid. As the server accepts connect requests from the clients, it starts to expand the set of file descriptors by including the clients array to listen to.
//     * If the server socket is ready, it implies that another client is trying to join the chat room. The server creates a new socket to communicate with the client, and adds the socket to the array 'clients'. It then goes back to accept.
//     * If any of the client sockets are ready, it reads the message using the readResponse function and sends it to all the other clients. 
//     * If the message is "$exit", the server forwards the message to all the clients and terminates. 
//     * Note: do not forget to free any memory that you allocate to store the message received and do not forget to close the sockets before exiting the program normally.
//    */
   
//    return 0;
// }

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <dirent.h>

void checkError(int status)
{
   if (status < 0) {
      printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
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
   /* Create a server socket */
   int sid = socket(PF_INET,SOCK_STREAM,0);

   /* Make the server-side socket non-blocking */
   int flags = fcntl(sid, F_GETFL, 0);
   checkError(flags);
   flags = flags | O_NONBLOCK;
   int status = fcntl(sid, F_SETFL, flags);
   checkError(status);
   int enable = 1;
   status = setsockopt(sid, SOL_SOCKET,SO_REUSEADDR, &enable, sizeof(int));
   checkError(status);
  
   /* Setup server address -- will listen on 8025 -- and bind to the socket */
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port   = htons(8025);
   addr.sin_addr.s_addr = INADDR_ANY;
   status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
   checkError(status);

   /* Listen on that socket for let's connect messages. No more than 10 pending at once. */
   status = listen(sid,10);
   checkError(status);
   
   int nbc = 0;         /* used to track the number of clients connected at any time */
   int clients[10];     /* an array to store the socket ids for each client */
     /* TODO (Q2.)
    * Given n client sockets and the server socket, the server simply needs to listen to all of them using the select API. 
    * Initially, there are no client sockets. Therefore, the server only listens to sid. As the server accepts connect requests from the clients, it starts to expand the set of file descriptors by including the clients array to listen to.
    * If the server socket is ready, it implies that another client is trying to join the chat room. The server creates a new socket to communicate with the client, and adds the socket to the array 'clients'. It then goes back to accept.
    * If any of the client sockets are ready, it reads the message using the readResponse function and sends it to all the other clients. 
    * If the message is "$exit", the server forwards the message to all the clients and terminates. 
    * Note: do not forget to free any memory that you allocate to store the message received and do not forget to close the sockets before exiting the program normally.
   */
   fd_set readfds;       /* set of file descriptors to listen to */
   int max_sd;           /* maximum file descriptor number */

   /* initialize all clients to 0 */
   for (int i = 0; i < 10; i++) {
      clients[i] = 0;
   }

   while (1) {
      /* clear the file descriptor set */
      FD_ZERO(&readfds);

      /* add the server socket to the set */
      FD_SET(sid, &readfds);
      max_sd = sid;

      /* add all the clients to the set */
      for (int i = 0; i < 10; i++) {
         int sd = clients[i];
         if (sd > 0) {
            FD_SET(sd, &readfds);
            if (sd > max_sd) {
               max_sd = sd;
            }
         }
      }

      /* wait for an activity on any of the sockets */
      int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
      checkError(activity);

      /* if the server socket is ready, it implies that another client is trying to join the chat room */
      if (FD_ISSET(sid, &readfds)) {
         int new_socket = accept(sid, (struct sockaddr *)&addr, (socklen_t*)&addr);
         checkError(new_socket);

         /* add the new socket to the array of clients */
         for (int i = 0; i < 10; i++) {
            if (clients[i] == 0) {
               clients[i] = new_socket;
               nbc++;
               break;
            }
         }
      }

      /* check all the client sockets for activity */
      for (int i = 0; i < 10; i++) {
         int sd = clients[i];
         if (FD_ISSET(sd, &readfds)) {
            char* message = readResponse(sd);

            /* if the message is "$exit", forward the message to all the clients and terminate */
            if (strcmp(message, "$exit\n") == 0) {
               for (int j = 0; j < 10; j++) {
                  int client_sd = clients[j];
                  if (client_sd > 0) {
                     write(client_sd, message, strlen(message));
                     close(client_sd);
                  }
               }
               free(message);
               close(sid);
               exit(0);
            }

            /* send the message to all the other clients */
            for (int j = 0; j < 10; j++) {
               int client_sd = clients[j];
               if (client_sd > 0 && client_sd != sd) {
                  write(client_sd, message, strlen(message));
               }
            }
            free(message);
         }
      }
   }

   /* close all the sockets */
   for (int i = 0; i < 10; i++) {
      int sd = clients[i];
      if (sd > 0) {
         close(sd);
      }
   }
   close(sid);

   return 0;
}

