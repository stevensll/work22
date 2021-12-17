#include "pipe_networking.h"

static void sighandler(int sig) {

    if (sig == SIGINT) {
        printf("Exiting server...\n");
        remove(WKP)
        exit(0);
    }

}

int main() {
  
  signal(SIGINT, sighandler);
  while(1){
    int to_client;
    int from_client;

    from_client = server_setup();
    int f = fork();
    if(!f){
        //SUBSERVER
        to_client = server_connect(from_client);
        while(1){
            char *response = malloc(BUFFER_SIZE);
            int fd = read(from_client, response, BUFFER_SIZE);
            //no response
            if (fd == 0) break;
            //process response
            else{
                int i;
                for(i = 0; i < BUFFER_SIZE; i++){
                    if(response[i] >= 'a' && response[i] <= 'z'){
                        response[i]-= 32;
                    }
                }
                write(to_client, response, BUFFER_SIZE);
            }
        }
        printf("Client is disconnected, waiting for a connection.\n");
    } else {
        //SERVER
        close(from_client);
        remove(WKP);
        printf("[server] handshake: removed wkp\n");
    }
  }
  return 0;
}