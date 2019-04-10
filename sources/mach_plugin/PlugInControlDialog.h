#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace mach_plugin {

	/// <summary>
	/// Summary for PlugInControlDialog
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class PlugInControlDialog : public System::Windows::Forms::Form
	{
	public:
		PlugInControlDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PlugInControlDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::Label^   label1;
	public: System::Windows::Forms::TextBox^  Address;
	public: System::Windows::Forms::CheckBox^  EnableDebugCB;


	private: 



	public: 






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Address = (gcnew System::Windows::Forms::TextBox());
			this->EnableDebugCB = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// OKButton
			// 
			this->OKButton->Location = System::Drawing::Point(178, 132);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(88, 23);
			this->OKButton->TabIndex = 0;
			this->OKButton->Text = L"OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &PlugInControlDialog::OKButton_Click);
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(27, 132);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(98, 23);
			this->CancelButton->TabIndex = 1;
			this->CancelButton->Text = L"Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(209, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Device network path (name or IP address )";
			// 
			// Address
			// 
			this->Address->Location = System::Drawing::Point(27, 49);
			this->Address->Name = L"Address";
			this->Address->Size = System::Drawing::Size(239, 20);
			this->Address->TabIndex = 3;
			this->Address->Text = L"169.254.1.3";
			this->Address->TextChanged += gcnew System::EventHandler(this, &PlugInControlDialog::Address_TextChanged);
			// 
			// EnableDebugCB
			// 
			this->EnableDebugCB->Location = System::Drawing::Point(27, 75);
			this->EnableDebugCB->Name = L"EnableDebugCB";
			this->EnableDebugCB->Size = System::Drawing::Size(121, 17);
			this->EnableDebugCB->TabIndex = 4;
			this->EnableDebugCB->Text = L"Enable debug mode";
			this->EnableDebugCB->UseVisualStyleBackColor = true;
			// 
			// PlugInControlDialog
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 172);
			this->Controls->Add(this->EnableDebugCB);
			this->Controls->Add(this->Address);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->MinimizeBox = false;
			this->Name = L"PlugInControlDialog";
			this->Text = L"Step2Mach Configuration";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
			 this->Close();
		 }


private: System::Void ChangeLicenseB_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::Abort;
			 this->Close();
		 }

private: System::Void Address_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
