#include "HSApp.h"

#include "MainFrame.h"

wxIMPLEMENT_APP(HSApp);

HSApp::HSApp()
{
}

HSApp::~HSApp()
{
}

bool HSApp::OnInit()
{
	m_MainFrame = new MainFrame(nullptr, wxID_ANY, wxT("HuntingSearch GUI Application"));
	m_MainFrame->Show();

	return true;
}
