///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ConfigDialog.h"

#include <wx/valnum.h>
#include "MainFrame.h"

///////////////////////////////////////////////////////////////////////////

void ConfigDialog::AddConfigRow(
	wxStaticText*& Label, 
	wxTextCtrl*& Input, 
	const wxString& LabelContent, 
	const wxString& ToolTip, 
	const wxValidator& Validator)
{
	Label = new wxStaticText(this, wxID_ANY, LabelContent, wxDefaultPosition, wxDefaultSize, 0);
	Label->SetToolTip(ToolTip);
	m_MainSizer->Add(Label, 0, wxALL, 5);
	Input = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, Validator);
	m_MainSizer->Add(Input, 0, wxALL, 5);
}

ConfigDialog::ConfigDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_MainSizer = new wxGridSizer(0, 2, 0, 0);

	/*
	const HSParams Params = HSParams
	{
		2, // Number of Epochs (NE)
		60, // Iteration per Epoch (IE)
		10, // Hunting Group Size (HGS)
		0.3f, // Maximum movement towards leader (MML)
		0.3f, // Hunting group consideration rate (HGCR)
		1e-2f, // Ra max
		1e-7f, // Ra min
		0.1f, // Reorganization parameter Alpha
		-1.0f // Reorganization parameter Beta
	};
	*/

	{

		AddConfigRow(m_Label_NE, m_TextCtrl_NE, wxT("NE"), wxT("Number of Epochs"), 
			wxIntegerValidator<int>(&MainFrame::Params.m_NumberOfEpochs, 1, 100));
		AddConfigRow(m_Label_IE, m_TextCtrl_IE, wxT("IE"), wxT("Iteration per Epoch"),
			wxIntegerValidator<int>(&MainFrame::Params.m_IterationPerEpoch, 1, 10000));
		AddConfigRow(m_Label_HGS, m_TextCtrl_HGS, wxT("HGS"), wxT("Hunting Group Size"),
			wxIntegerValidator<int>(&MainFrame::Params.m_HGSize, 1, 1000));
		{
			wxFloatingPointValidator<float> MMLValidator(6, &MainFrame::Params.m_MML);
			MMLValidator.SetRange(0.000001f, 100.0f);
			AddConfigRow(m_Label_MML, m_TextCtrl_MML, wxT("MML"), wxT("Maximum Movement Towards Leader"), MMLValidator);
		}
		{
			wxFloatingPointValidator<float> HGCRValidator(3, &MainFrame::Params.m_HGCR);
			HGCRValidator.SetRange(0.0f, 1.0f);
			AddConfigRow(m_Label_HGCR, m_TextCtrl_HGCR, wxT("HGCR"), wxT("Hunting group consideration rate"), HGCRValidator);
		}
		{
			wxFloatingPointValidator<float> RaMaxValidator(10, &MainFrame::Params.m_RaMax);
			RaMaxValidator.SetRange(0.0f, 1.0f);
			AddConfigRow(m_Label_RaMax, m_TextCtrl_RaMax, wxT("Ra Max"), wxT("Ra max"), RaMaxValidator);
		}
		{
			wxFloatingPointValidator<float> RaMinValidator(10, &MainFrame::Params.m_RaMin);
			RaMinValidator.SetRange(0.0f, 1.0f);
			AddConfigRow(m_Label_RaMin, m_TextCtrl_RaMin, wxT("Ra Min"), wxT("Ra min"), RaMinValidator);
		}
		{
			wxFloatingPointValidator<float> ReorgAlphaValidator(3, &MainFrame::Params.m_ReorgAlpha);
			ReorgAlphaValidator.SetRange(-1.0f, 1.0f);
			AddConfigRow(m_Label_ReorgAlpha, m_TextCtrl_ReorgAlpha, wxT("ReorgAlpha"), wxT("Reorganization parameter Alpha"), ReorgAlphaValidator);
		}
		{
			wxFloatingPointValidator<float> ReorgBetaValidator(3, &MainFrame::Params.m_ReorgBeta);
			ReorgBetaValidator.SetRange(-1.0f, 1.0f);
			AddConfigRow(m_Label_ReorgBeta, m_TextCtrl_ReorgBeta, wxT("ReorgBeta"), wxT("Reorganization parameter Beta"), ReorgBetaValidator);
		}
	}

	wxSizer* buttonSizer = CreateButtonSizer(wxOK);
	m_MainSizer->Add(buttonSizer);

	this->SetSizer(m_MainSizer);
	this->Layout();
	m_MainSizer->Fit(this);

	this->Centre(wxBOTH);
}

ConfigDialog::~ConfigDialog()
{
}
