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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/timer.h>

#include "wxchartsgridoptions.h"
#include "wxscatterplotoptions.h"
#include <unordered_map>
#include "HuntingSearchSpace.h"
#include "HuntingSearchSolver.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////

class ScatterRegionPlotCtrl;
class wxScrolledWindow;
class HeightColorBar;

struct VariableRow 
{
	int m_index;
	wxCheckBox* m_VarCheckBox;
	wxSlider* m_VarSlider;
	wxTextCtrl* m_VarText;
};

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:
		std::vector<VariableRow> m_VarRows;
		int m_ActiveVars[2] = { 0, 1 };
		HuntingSearchSpace* m_SelectedFunc = nullptr;
		HSResult m_LastResult;
		size_t m_CurrentStep = 0;

		void InitializeFuncs();
		void UpdateActiveVars(int index1, int index2);
		ScatterRegionPlotCtrl* CreatePlotCtrl(wxWindow* parent, const HuntingSearchSpace& func);
		wxBoxSizer* CreateVarRows(
			wxWindow* parent, const HuntingSearchSpace& func, std::vector<VariableRow>& rowsOut);
		void UpdatePlotAxisLimits(const HuntingSearchSpace& func);
		DecisionVars GetVarValues() const;
		void EnableVarRow(bool Value, const VariableRow& VarRow);
		void VarCheckBoxChanged_Handle(wxCheckBox* checkBox, const VariableRow& VarRow);
		HSResult MinimizeFunction(const HuntingSearchSpace& func) const;
		void ResetDynamicVisuals();
		void ResetScatterPlot(size_t Step);

		static double SliderValueToDouble(const FRange varRange, wxSlider* slider);
		static int DoubleToSliderValue(double Value, FRange varRange, wxSlider* slider);

	protected:
		wxMenuBar* m_MenuBar;
		wxMenu* FileOption;
		wxMenu* AboutOption;
		wxToolBar* m_ToolBar;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox21;
		wxCheckBox* m_checkBox22;
		wxStaticBitmap* m_bitmap4;
		wxStatusBar* m_StatusBar;
		wxComboBox* m_comboBox1;

		wxScrolledWindow* m_scrolledWindow;
		wxSlider* m_HeightSlider;
		HeightColorBar* colorBar;
		wxSlider* m_StepSlider;
		wxTimer* m_StepTimer = nullptr;

		ScatterRegionPlotCtrl* m_Plot;
		wxScatterPlotOptions* m_PlotOptions;

		std::unordered_map<wxString, HuntingSearchSpace> m_FunctionsMap;

		// Virtual event handlers, override them in your derived class
		void OnConfigureMenuItemSelected(wxCommandEvent& event);
		void OnExitMenuItemSelected(wxCommandEvent& event);
		void ComboboxOptionSelected(wxCommandEvent& event);

		void OnVarTextEnterClicked(wxCommandEvent& event);
		void OnVarCheckboxChanged(wxCommandEvent& event);
		void OnVarTextCtrlFocusChanged(wxFocusEvent& event);
		void OnVarSliderValueChanged(wxCommandEvent& event);

		void OnDrawConstrainedButtonToggled(wxCommandEvent& event);
		void OnPlotHeightSliderValueChanged(wxCommandEvent& event);
		void OnPlotCtrlMouseEnter(wxMouseEvent& event);

		void OnStepLeftButtonClicked(wxCommandEvent& event);
		void OnStepRightButtonClicked(wxCommandEvent& event);
		void OnStepSliderValueChanged(wxCommandEvent& event);
		void OnStartButtonClicked(wxCommandEvent& event);
		void OnStopButtonClicked(wxCommandEvent& event);
		void OnStepTimerTriggered(wxTimerEvent& event);

	public:
		static HSParams Params;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 526,299 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

