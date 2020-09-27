#include "MultiServer.h"

int main(int argc , char *argv[])
{
    MultiServer::instance().start(8888, 30);

    return 0;
}
