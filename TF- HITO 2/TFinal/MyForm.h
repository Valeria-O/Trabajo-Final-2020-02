#pragma once
#include "Juego.h"
namespace TFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics^ g;
		BufferedGraphics^ buffer;
	private: System::Windows::Forms::Timer^ timer1;
		   Juego^ j;

	public:
		MyForm(void)
		{
			InitializeComponent();
			g = CreateGraphics();
			buffer = BufferedGraphicsManager::Current->Allocate(g, this->ClientRectangle);
			j = gcnew Juego(this->ClientRectangle,buffer->Graphics);
			
		}

	protected:
		
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete g, buffer;
		}

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		


#pragma region Windows Form Designer generated code
		
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(545, 423);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		j->MoverJugador(true,e->KeyCode);
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		j->MoverJugador(false, e->KeyCode);
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		j->Jugar(buffer->Graphics);
		buffer->Render();
	}
	};
}
