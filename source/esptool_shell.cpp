#include "../includes/FSM.h"

int main()
{
    FSM ServiceFSM;
    int status;
    do
    {
        status = ServiceFSM.Advance();
    } while (status);
    return 0;
}
