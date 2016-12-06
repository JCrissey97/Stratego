#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::endl;
namespace Adaptor
{
	template <class T>
		class Queue
	{
	public:
		void enqueue(const T &newData)
		{
			mQueue.push_back(newData);
		}
		T dequeue();

	private:
		vector<T> mQueue;

	};
}

namespace Game
{
	class Character
	{

	};

	class Alien : public Character
	{

	};
}