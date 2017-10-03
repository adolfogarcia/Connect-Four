#include "connect.h"

void main(void)
{
	Cell gameboard[6][7] = { { { '\0','\0', FALSE,{ 0, 0 } } } };


	run_app(gameboard);
}