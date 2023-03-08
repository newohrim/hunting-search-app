#pragma once

#include "wx/wx.h"

class MainFrame;

class HSApp : public wxApp
{
public:
	HSApp();
	~HSApp();

	virtual bool OnInit() override;

private:
	MainFrame* m_MainFrame = nullptr;
};

