//---------------------------------------------------------------------------

#ifndef TemplateQueueH
#define TemplateQueueH


#include <iostream>
#include <vcl.h>
#include <Grids.hpp>
#include <system.hpp>

using namespace std;





template <typename T>
class TemplateQueue//��������� ����� ������
{
	protected:
	struct Node//���������, �������������� ������� ������
	{
		T info;
		Node* previous;
		Node* next;

	};

	Node* _end;
	Node* _start;
	int _length;


	void Push(Node* node, bool to_start)//��������� ������� � ������ ��� � ����� ������ � ����������� �� �������� to_start
	{
     	if (_length == 0)
		{

			_end = node;
			_start = _end;
			node -> previous = NULL;
			node -> next = NULL;

		}
		else
		{

			if(!to_start)
			{
				node -> previous = _end;
				_end -> next = node;
				node -> next = NULL;
				_end = node;
			}
			else
			{
				node -> next = _start;
				_start -> previous = node;
			    node -> previous = NULL;
				_start = node;
			}



		}
	}


	public:
	TemplateQueue()//�����������
	{
		_end = NULL;
		_start = NULL;
		_length = 0;
	}

	void Push(T new_symbol)//������� ����� ������� ������ � ������������ � new_symbol � ��������� ��� � ����� ������
	{
		Node*temp = new Node();
		temp -> info = new_symbol;
		Push( temp, false );
		_length++;
	}



	void Pop()//������� ���� ������� �� ������ ������
	{
		if(_length != 0)
		{
			Node* temp = _start;

			if(_length != 1)
			{
				_start -> next -> previous = NULL;
				_start = _start -> next;
			}
			_length --;

			delete temp;
		}
		else
		{
			throw std::logic_error("Trying to delete an element from empty stack");
		}
	}

	void Show(TStringGrid* StringGrid)//������� ��� �������� ������ � ������ ������� ������� �� �����
	{
		StringGrid -> RowCount = StringGrid -> FixedRows;
		Node* slider = _start;
		if(_length == 0)
		{
			return;
		}
		for(int i = 0; i < _length; i++)
		{
			StringGrid -> RowCount++;
			StringGrid -> Cells[0][i+1] = (slider -> info);
			slider = slider -> next;
		}

	}

	~TemplateQueue()//����������, ������� ������, ���������� ��� ������ �� ��������� ������
	{
		if( _length != 0 )
		{
			Node* slider = _start;
			for(int i = 0; i < _length; i++)
			{
				Node*temp = slider;
				slider = slider -> next;
				delete temp;
			}
		}
    }
};


//---------------------------------------------------------------------------
#endif
