///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ConfigDialog
///////////////////////////////////////////////////////////////////////////////
class ConfigDialog : public wxDialog
{
private:
	void AddConfigRow(
		wxStaticText*& Label, 
		wxTextCtrl*& Input, 
		const wxString& LabelContent, 
		const wxString& ToolTip, 
		const wxValidator& Validator);

protected:
	wxGridSizer* m_MainSizer;
	wxStaticText* m_Label_NE;
	wxTextCtrl* m_TextCtrl_NE;
	wxStaticText* m_Label_IE;
	wxTextCtrl* m_TextCtrl_IE;
	wxStaticText* m_Label_HGS;
	wxTextCtrl* m_TextCtrl_HGS;
	wxStaticText* m_Label_MML;
	wxTextCtrl* m_TextCtrl_MML;
	wxStaticText* m_Label_HGCR;
	wxTextCtrl* m_TextCtrl_HGCR;
	wxStaticText* m_Label_RaMax;
	wxTextCtrl* m_TextCtrl_RaMax;
	wxStaticText* m_Label_RaMin;
	wxTextCtrl* m_TextCtrl_RaMin;
	wxStaticText* m_Label_ReorgAlpha;
	wxTextCtrl* m_TextCtrl_ReorgAlpha;
	wxStaticText* m_Label_ReorgBeta;
	wxTextCtrl* m_TextCtrl_ReorgBeta;

public:

	ConfigDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	~ConfigDialog();

};
