#include "HeightColorBar.h"

HeightColorBar::HeightColorBar(wxWindow* parent, wxWindowID winId, const wxPoint& pos, const wxSize& size) 
	: wxControl(parent, winId, pos, size)
{
	Init();
}

void HeightColorBar::Init()
{
	const auto lerp = [](float v0, float v1, float t) -> float
	{
		return (1 - t) * v0 + t * v1;
	};
	m_ColorBarImage = new wxImage(wxSize(96, 12));
	uint8_t* imgData =  m_ColorBarImage->GetData();
	for (int j = 0; j < m_ColorBarImage->GetWidth(); ++j) 
	{
		const float normValue = (float)j / m_ColorBarImage->GetWidth();
		const wxColor color = 
			wxColor(lerp(0, 255, normValue), lerp(255, 0, normValue), 0);
		const int index = j * 3;
		imgData[index + 0] = color.GetRed();
		imgData[index + 1] = color.GetGreen();
		imgData[index + 2] = 0;
	}
	for (int i = 1; i < m_ColorBarImage->GetHeight(); ++i) 
	{
		for (int j = 0; j < m_ColorBarImage->GetWidth(); ++j) 
		{
			const int index = i * m_ColorBarImage->GetWidth() * 3 + j * 3;
			imgData[index + 0] = imgData[j * 3 + 0];
			imgData[index + 1] = imgData[j * 3 + 1];
			imgData[index + 2] = imgData[j * 3 + 2];
		}
	}
	m_ColorBar = new wxStaticBitmap(this, wxID_ANY, *(new wxBitmap(*m_ColorBarImage)));
	m_LeftLabel = new wxStaticText(this, wxID_ANY, wxT("0000000"));
	m_RightLabel = new wxStaticText(this, wxID_ANY, wxT("1000000"));
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_Sizer->Add(m_LeftLabel, 0, wxALL, 5);
	m_Sizer->Add(m_ColorBar, 1, wxALL, 5);
	m_Sizer->Add(m_RightLabel, 0, wxALL, 5);
	this->SetSizerAndFit(m_Sizer);
}
