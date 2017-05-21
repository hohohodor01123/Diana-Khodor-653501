//---------------------------------------------------------------------------

#ifndef MyQueueH
#define MyQueueH

#include "TemplateQueue.h"



class MyQueue : public TemplateQueue<double>
{
	private:
	typedef bool (MyQueue::*Compare)( Node* node1, Node* node2);
	Compare comp_func;

	Node* GetBiggestSmallest();


	bool Bigger(Node* node1, Node* node2);
	bool Smaller(Node* node1, Node* node2);
	void Swap(Node* node1, Node* node2);

	public:
	MyQueue() : TemplateQueue<double> () {}

	bool SwapBiggestSmallest();
	bool Contains(double number);




};
//---------------------------------------------------------------------------
#endif
