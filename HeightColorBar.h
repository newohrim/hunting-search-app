#pragma once

#include <wx/control.h>
#include <wx/sizer.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

class HeightColorBar : public wxControl
{
public:
	HeightColorBar(
		wxWindow* parent, 
		wxWindowID winId, 
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize);

	void SetLeftLabelText(const wxString& text) { m_LeftLabel->SetLabelText(text); }
	void SetRightLabelText(const wxString& text) { m_RightLabel->SetLabelText(text); }

protected:
	void Init();

private:
	wxBoxSizer* m_Sizer;
	wxImage* m_ColorBarImage;
	wxStaticBitmap* m_ColorBar;
	wxStaticText* m_LeftLabel;
	wxStaticText* m_RightLabel;
};

