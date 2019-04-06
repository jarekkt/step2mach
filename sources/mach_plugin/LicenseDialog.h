#pragma once

#include <string>
#include "license\Mylicense.h"
#include "MylicenseKey.h"


namespace mach_plugin {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LicenseDialog
	/// </summary>
	public ref class LicenseDialog : public System::Windows::Forms::Form
	{
	public:
		LicenseDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		int CheckLicense(String^ * LicenseKey,String^ * LicenseOwner,bool ShowDialog)
		{
			MyLicense::LicenseFile^					lfile		  = gcnew (MyLicense::LicenseFile);
			System::Windows::Forms::DialogResult	dResult;
			bool									return_result = false;
			int										license_ok;


			

			// Well , since distributing as open source we skip the hard part
			// You can enable it in your commercial code

			*LicenseOwner  = gcnew String("Demo code. Copyright Kartech 2011.");
			return 0;


			*LicenseOwner  = gcnew String("");
			if(ShowDialog == false)
			{
				if(lfile->CheckLicensePrintout(*LicenseKey,GetPublicKey(),LicenseOwner)==0)
				{
					return  0;
				}
				else
				{
					return -1;
				}
			}
			else
			{

				while(1)
				{
					license_ok = lfile->CheckLicensePrintout(*LicenseKey,GetPublicKey(),LicenseOwner);
					if(license_ok == 0)
					{
						LicenseRTB->Text	 = *LicenseOwner;
						LicenseRTB->ReadOnly = true;
						VerificationL->Text  = "Current license is valid";
						MessageL->Text       = "License is valid. *Clear license* first if you want to change it";

						if(return_result)
						{
							return 0;
						}
					}
					else
					{
						LicenseRTB->Text      = *LicenseKey;
						LicenseRTB->ReadOnly  = false;
						VerificationL->Text   = "Current license is invalid.Please register!!";
						MessageL->Text		  = "Please paste valid license here";	 

						return_result		  = false;
					}

					dResult = this->ShowDialog();

					if ( dResult == System::Windows::Forms::DialogResult::OK)
					{
						if(LicenseRTB->ReadOnly == false)
						{
							*LicenseKey = LicenseRTB->Text;
						}
						return_result = true;
					}
					else if ( dResult == System::Windows::Forms::DialogResult::Abort)
					{
						*LicenseKey = "";
						return -1;
					}
					else
					{
						// Cancel - returns previous state of license
						return license_ok;
					}
				}
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LicenseDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  LicenseRTB;
	protected: 

	protected: 
	
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Label^  MessageL;



	public:  System::Windows::Forms::Label^   VerificationL;
	public:  String^						  Fingerprint;
	private: System::Windows::Forms::Button^  ClearLicenseB;

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
			this->LicenseRTB = (gcnew System::Windows::Forms::RichTextBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->MessageL = (gcnew System::Windows::Forms::Label());
			this->VerificationL = (gcnew System::Windows::Forms::Label());
			this->ClearLicenseB = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// LicenseRTB
			// 
			this->LicenseRTB->Location = System::Drawing::Point(12, 38);
			this->LicenseRTB->Name = L"LicenseRTB";
			this->LicenseRTB->Size = System::Drawing::Size(588, 96);
			this->LicenseRTB->TabIndex = 1;
			this->LicenseRTB->Text = L"";
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(525, 140);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(75, 23);
			this->buttonOK->TabIndex = 2;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &LicenseDialog::button1_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(419, 140);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 23);
			this->buttonCancel->TabIndex = 3;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// MessageL
			// 
			this->MessageL->AutoSize = true;
			this->MessageL->Location = System::Drawing::Point(17, 13);
			this->MessageL->Name = L"MessageL";
			this->MessageL->Size = System::Drawing::Size(128, 13);
			this->MessageL->TabIndex = 4;
			this->MessageL->Text = L"Please paste license here";
			// 
			// VerificationL
			// 
			this->VerificationL->AutoSize = true;
			this->VerificationL->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->VerificationL->Location = System::Drawing::Point(121, 150);
			this->VerificationL->Name = L"VerificationL";
			this->VerificationL->Size = System::Drawing::Size(61, 13);
			this->VerificationL->TabIndex = 5;
			this->VerificationL->Text = L"Not verified";
			// 
			// ClearLicenseB
			// 
			this->ClearLicenseB->Location = System::Drawing::Point(12, 144);
			this->ClearLicenseB->Name = L"ClearLicenseB";
			this->ClearLicenseB->Size = System::Drawing::Size(94, 23);
			this->ClearLicenseB->TabIndex = 2;
			this->ClearLicenseB->Text = L"Clear license";
			this->ClearLicenseB->UseVisualStyleBackColor = true;
			this->ClearLicenseB->Click += gcnew System::EventHandler(this, &LicenseDialog::ClearLicenseB_Click);
			// 
			// LicenseDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(619, 179);
			this->Controls->Add(this->VerificationL);
			this->Controls->Add(this->MessageL);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->ClearLicenseB);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->LicenseRTB);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"LicenseDialog";
			this->Text = L"License Dialog";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->DialogResult		  = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}

	private: System::Void ClearLicenseB_Click(System::Object^  sender, System::EventArgs^  e)
	{
		this->DialogResult = System::Windows::Forms::DialogResult::Abort;
		this->Close();
	}
};
}
