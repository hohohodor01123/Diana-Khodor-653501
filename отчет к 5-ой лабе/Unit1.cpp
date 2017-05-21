//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "MyQueue.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
MyQueue* queue;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)//������� ������ ������ ���� ������ � ������� ����� "Elements" � ������ ������ �������
{
	ListStringGrid -> Cells[0][0] = "Elements";
	queue = new MyQueue();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)//���������� ������� �� ������ Add,��������� ��������� ������� � ����� ������, ���� �� ��� �� �������� � ������� ��� � �������
{
	float element = 0;
	try
	{
		element = StrToFloat(AddEdit -> Text);
	}
	catch(...)
	{
		ShowMessage("Wrong Input!");
		return;
	}

	if(  ! queue -> Contains( element ) )
	{
		queue -> Push (	element );
		queue -> Show( ListStringGrid );
	}
	else
   {
	  ShowMessage("The queue already contains the element you want to add");
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DeleteButtonClick(TObject *Sender)//���������� ������� ������ Delete,������� ������ ������� �� ������, ���� �� �� ����
{
	try
	{
		queue -> Pop();
		queue -> Show( ListStringGrid );
	}
	catch(std::logic_error& e)
	{
        ShowMessage(e.what());
    }
}

void __fastcall TForm1::SwapButtonClick(TObject *Sender)//���������� ������� ������ Swap biggest and smallest, ������ ������� ���������� � ���������� �������� ������
{
	if( !queue -> SwapBiggestSmallest() )
	{
		ShowMessage("Add elements to the queue");
	}
	else
	{
        queue -> Show( ListStringGrid );
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::CloseButtonClick(TObject *Sender)//���������� ������� ������ Close, ���������� ���������� ��� ������
{
	delete queue;
	Form1 -> Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
