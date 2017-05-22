//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyQueue.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


bool MyQueue::SwapBiggestSmallest()//меняет местами наибольший и наименьший элементы списка
{
	if( _length == 0 )
	{
		return false;
	}


	comp_func = &MyQueue::Bigger;
	Node* biggest = GetBiggestSmallest();
	comp_func = &MyQueue::Smaller;
	Node* smallest = GetBiggestSmallest();
	Swap( smallest, biggest );
	return true;

}

Node* MyQueue::GetBiggestSmallest()//возвращает наибольший или наименьший элемент списка в зависимости от того, на какой метод сравнения указывает указатель comp_func
{
	if( _length != 0 )
	{
		Node* slider = _start -> next;
		Node* needed_node = _start;
		for(int i = 1; i < _length; i++)
		{
			if( (this -> *comp_func)( slider, needed_node ) )
			{
				needed_node = slider;
			}

			slider = slider -> next;
		}

		return needed_node;
	}

	return NULL;
}

void MyQueue::Swap(Node* node1, Node* node2)//меняет местами элементы node1 и node2, используя исключительно изменение значений указателей previous и next в некоторых элементах списка{
	if (node1 == node2)
	{
		return;
	}

	Node *node1_prev = node1 -> previous;
	Node *node1_next = node1 -> next;
	Node *node2_prev = node2 -> previous;
	Node *node2_next = node2 -> next;

	if (!node1_prev)
	{
		_start = node2;
	}
	else
	{
		node1_prev -> next = node2;
	}

	if (!node2_prev)
	{
		_start = node1;
	}
	else
	{
		node2_prev -> next = node1;
	}

	if (!node1_next)
	{
		_end = node2;
	}
	else
	{
		node1_next -> previous = node2;
	}

	if (!node2_next)
	{
		_end = node1;
	}
	else
	{
		node2_next -> previous = node1;
	}

	Node *temp = node1 -> previous;
	node1 -> revious = node2 -> previous;
	node2 -> previous = temp;

	temp = node1 -> next;
	node1 -> next = node2 -> next;
	node2 -> next = temp;
}


bool MyQueue::Bigger(Node* node1, Node* node2)//âîçâðàùàåò true, åñëè node1 > node2
{
	if(node1 -> info > node2 -> info)
	{
		return true;
	}

	return false;
}

bool MyQueue::Smaller(Node* node1, Node* node2)//âîçâðàùàåò true, åñëè node1 < node2
{
	if(node1 -> info < node2 -> info)
	{
		return true;
	}

	return false;
}

bool MyQueue::Contains(double number)//âîçâðàùàåò true, åñëè ýëåìåíò ñî çíà÷åíèåì number óæå ñîäåðæèòñÿ â ñïèñêå
{
	Node* slider = _start;
	for(int i = 0; i < _length; i++)
	{
		if( slider -> info == number )
		{
			return true;
		}

		slider = slider -> next;
	}

	return false;
}
