#include "STLExample.h"

using Adaptor::Queue;

int main(void)
{
	Adaptor::Queue<int> q;
	Adaptor::Queue<Game::Character &> q2;

	q.enqueue(42);
	q2.enqueue(*(new Game::Character()));
	q2.enqueue(*(new Game::Alien()));

	return 0;
}