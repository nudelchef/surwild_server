#include "MultiServer.h"

int main(int argc , char *argv[])
{
    MultiServer* server = new MultiServer(8888, 30);

    server->start();

    return 0;
}
