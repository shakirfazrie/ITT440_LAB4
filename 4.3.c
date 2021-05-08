<<<<<<< HEAD
#include <stdio.h>
#include <string.h>      //strlen
#include <sys/socket.h>
#include <arpa/inet.h>   //inet_addr
#include <unistd.h>      //write
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
        int socket_desc , new_socket , c;
        struct sockaddr_in server , client;
        char *message;
        int optval;
        socklen_t optlen = sizeof(optval);

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }


      /* Check the status for the keepalive option */
       if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
        perror("getsockopt()");
        close(socket_desc);
        exit(EXIT_FAILURE);
        }
        printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

        /* Set the option active */
        optval = 1;
        optlen = sizeof(optval);
        if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
          perror("setsockopt()");
          close(socket_desc);
          exit(EXIT_FAILURE);
         }
         printf("SO_KEEPALIVE set on socket\n");


        /* Check the status again */
       if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
       perror("getsockopt()");
       close(socket_desc);
       exit(EXIT_FAILURE);
       }
       printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 8888 );
        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("bind failed");
                return 1;
        }
        puts("bind done");

        //Listen
        listen(socket_desc , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
        while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
        {
                puts("Connection accepted");

                //Reply to the client
                message = "Hello Client , I have received your connection. But I have to go now, bye\n";
                write(new_socket , message , strlen(message));
        }

        if (new_socket<0)
        {
                perror("accept failed");
                return 1;
        }

        return 0;
=======
#include <stdio.h> //printf
#include <string.h> //strcpy
#include <sys/socket.h>
#include <netdb.h>	//hostent
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
		
	if ( (he = gethostbyname( hostname ) ) == NULL) 
	{
		//gethostbyname failed
		herror("gethostbyname");
		return 1;
	}
	
	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr **) he->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}
	
	printf("%s resolved to : %s \n" , hostname , ip);
	return 0;
>>>>>>> 0befff59e66da2d8f6e71d6f43f431aaca9e964a
}
