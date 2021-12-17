#include "pipe_networking.h"

static void sighandler(int sig) {

    if (sig == SIGINT) {
        printf("Exiting server...\n");
        exit(0);
    }

}

int main() {

  signal(SIGINT, sighandler);
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server);

  while(1){
    char * input = malloc(BUFFER_SIZE);
    printf("Please enter input:\n");
    fgets(input, BUFFER_SIZE, stdin);
    sscanf(input, "%s", input);
    write(to_server, input, BUFFER_SIZE);

    char * response = malloc(BUFFER_SIZE);
    read(from_server, response, BUFFER_SIZE);
    printf("Server response: %s\n", response);
  }
}