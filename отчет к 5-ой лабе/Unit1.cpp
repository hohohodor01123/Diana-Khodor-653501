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

//создает пустой объект типа список и выводит слово "Elements" в первой строке таблицы
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	ListStringGrid -> Cells[0][0] = "Elements";
	queue = new MyQueue();
}
//---------------------------------------------------------------------------

//обработчик нажатия на кнопку Add,добавляет введенный элемент в конец списка, если он еще не добавлен и выводит его в таблицу
void __fastcall TForm1::AddButtonClick(TObject *Sender)
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

//обработчик нажатия кнопки Delete,удаляет первый элемент из списка, если он не пуст
void __fastcall TForm1::DeleteButtonClick(TObject *Sender)
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
//---------------------------------------------------------------------------

//обработчик нажатия кнопки Swap biggest and smallest, меняет местами наибольший и наименьший элементы списка
void __fastcall TForm1::SwapButtonClick(TObject *Sender)
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

//обработчик нажатия кнопки Close, вызывается деструктор для списка
void __fastcall TForm1::CloseButtonClick(TObject *Sender)
{
	delete queue;
	Form1 -> Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
