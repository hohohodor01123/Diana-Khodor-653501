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
void __fastcall TForm1::FormCreate(TObject *Sender)//создает пустой объект типа список и выводит слово "Elements" в первой строке таблицы
{
	ListStringGrid -> Cells[0][0] = "Elements";
	queue = new MyQueue();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)//обработчик нажатия на кнопку Add,добавляет введенный элемент в конец списка, если он еще не добавлен и выводит его в таблицу
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
void __fastcall TForm1::DeleteButtonClick(TObject *Sender)//обработчик нажатия кнопки Delete,удаляет первый элемент из списка, если он не пуст
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

void __fastcall TForm1::SwapButtonClick(TObject *Sender)//обработчик нажатия кнопки Swap biggest and smallest, меняет местами наибольший и наименьший элементы списка
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
void __fastcall TForm1::CloseButtonClick(TObject *Sender)//обработчик нажатия кнопки Close, вызывается деструктор для списка
{
	delete queue;
	Form1 -> Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
