///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"

#include "wxcharts.h"
#include "ScatterRegionPlotCtrl.h"
#include "HeightColorBar.h"
#include "ConfigDialog.h"
#include "wx/wx.h"
#include "wx/grid.h"
#include <wx/tglbtn.h>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////

HSParams MainFrame::Params = HSParams
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

void MainFrame::InitializeFuncs()
{
	m_FunctionsMap["(x1^2 + x2 - 11)^2 + (x1 + x2^2 -7)^2"] = 
		HuntingSearchSpace
		{ 
			2, 
			[](DecisionVars X) -> double 
			{
				const double a = X[0] * X[0] + X[1] - 11;
				const double b = X[0] + X[1] * X[1] - 7;

				return a * a + b * b;
			},
			{  
				[](DecisionVars X) -> double
				{
					const double a = X[0] - 0.05f;
					const double b = X[1] - 2.5f;

					// >= 0
					return 4.84f - a * a - b * b;
				},
				[](DecisionVars X) -> double
				{
					const double a = X[0];
					const double b = X[1] - 2.5f;

					// >= 0
					return a * a + b * b - 4.84f;
				}
			},
			{
				{0.0f, 6.0f}, // x1 space
				{0.0f, 6.0f}  // x2 space
			}
		};
	m_FunctionsMap["(x1 - 2)^2 + (x2 - 1)^2"] =
		HuntingSearchSpace
	{
		2,
		[](DecisionVars X) -> double
		{
			const double a = X[0] - 2;
			const double b = X[1] - 1;

			return a * a + b * b;
		},
		{
			[](DecisionVars X) -> double
			{
				//const double a = X[0] - 0.05f;
				//const double b = X[1] - 2.5f;

				const double val = X[0] - 2 * X[1] + 1;
				// == 0
				return val > 0 ? -val : val;
			},
			[](DecisionVars X) -> double
			{
				//const double a = X[0];
				//const double b = X[1] - 2.5f;

				// >= 0
				return -X[0] * X[0] / 4.0 - X[1] * X[1] + 1;
			}
		},
		{
			{-10.0f, 10.0f}, // x1 space
			{-10.0f, 10.0f}  // x2 space
		}
	};
	m_FunctionsMap["x1 + x2 + x3^2"] =
		HuntingSearchSpace
	{
		3,
		[](DecisionVars X) -> double
		{
			return X[0] + X[1] + X[2] * X[2];
		},
		{  },
	{
		{-10.0f, 10.0f}, // x1 space
		{-10.0f, 10.0f},  // x2 space
		{-10.0f, 10.0f},  // x3 space
	}
	};
}

void MainFrame::UpdateActiveVars(int index1, int index2)
{
	if (index1 > index2) 
	{
		std::swap(index1, index2);
	}

	m_ActiveVars[0] = index1;
	m_ActiveVars[1] = index2;

	for (VariableRow& varRow : m_VarRows) 
	{
		varRow.m_VarCheckBox->Enable(false);
		varRow.m_VarCheckBox->SetValue(false);
	}
	if (m_ActiveVars[0] >= 0) 
	{
		m_VarRows[m_ActiveVars[0]].m_VarCheckBox->Enable(true);
		m_VarRows[m_ActiveVars[0]].m_VarCheckBox->SetValue(true);
		//VarCheckBoxChanged_Handle(m_VarRows[m_ActiveVars[0]].m_VarCheckBox, m_VarRows[m_ActiveVars[0]]);
	}
	if (m_ActiveVars[1] >= 0)
	{
		m_VarRows[m_ActiveVars[1]].m_VarCheckBox->Enable(true);
		m_VarRows[m_ActiveVars[1]].m_VarCheckBox->SetValue(true);
		//VarCheckBoxChanged_Handle(m_VarRows[m_ActiveVars[1]].m_VarCheckBox, m_VarRows[m_ActiveVars[1]]);
	}
}

ScatterRegionPlotCtrl* MainFrame::CreatePlotCtrl(wxWindow* parent, const HuntingSearchSpace& func)
{
	// Create the data for the scatter plot widget
	wxScatterPlotData chartData;

	// Add the first dataset
	wxVector<wxPoint2DDouble> points1;
	points1.push_back(wxPoint2DDouble(-0.2, 3.5));
	points1.push_back(wxPoint2DDouble(0.5, 2.5));
	points1.push_back(wxPoint2DDouble(1.2, 0.1));
	points1.push_back(wxPoint2DDouble(1.5, 1.6));
	points1.push_back(wxPoint2DDouble(2, 1.8));
	points1.push_back(wxPoint2DDouble(2.2, 2.1));
	points1.push_back(wxPoint2DDouble(2.7, 2));
	wxScatterPlotDataset::ptr dataset1(
		new wxScatterPlotDataset(
			wxColor(250, 20, 20, 0x78),
			wxColor(250, 20, 20, 0xB8),
			points1)
	);
	//chartData.AddDataset(dataset1);

	// Add the second dataset
	wxVector<wxPoint2DDouble> points2;
	points2.push_back(wxPoint2DDouble(-0.3, 6.5));
	points2.push_back(wxPoint2DDouble(0.2, -1.5));
	points2.push_back(wxPoint2DDouble(1.6, 0.7));
	points2.push_back(wxPoint2DDouble(1.5, 4.1));
	points2.push_back(wxPoint2DDouble(1.8, 2.7));
	points2.push_back(wxPoint2DDouble(2.1, 2));
	points2.push_back(wxPoint2DDouble(2.3, 6));
	wxScatterPlotDataset::ptr dataset2(
		new wxScatterPlotDataset(
			wxColor(20, 20, 20, 0x78),
			wxColor(20, 20, 20, 0xB8),
			points2)
	);
	//chartData.AddDataset(dataset2);

	wxChartsAxisOptions xAxisOptions(wxCHARTSAXISPOSITION_BOTTOM);
	xAxisOptions.SetExplicitStartValue(func.m_DesignSpace[0].first);
	xAxisOptions.SetExplicitEndValue(func.m_DesignSpace[0].second);
	wxChartsAxisOptions yAxisOptions(wxCHARTSAXISPOSITION_LEFT);
	yAxisOptions.SetExplicitStartValue(func.m_DesignSpace[1].first);
	yAxisOptions.SetExplicitEndValue(func.m_DesignSpace[1].second);
	m_PlotOptions = new wxScatterPlotOptions(wxChartsGridOptions(xAxisOptions, yAxisOptions));
	wxSharedPtr<wxScatterPlotOptions> optionsPtr(m_PlotOptions);
	return new ScatterRegionPlotCtrl(parent, wxID_ANY, chartData, optionsPtr);
}

wxBoxSizer* MainFrame::CreateVarRows(
	wxWindow* parent, const HuntingSearchSpace& func, std::vector<VariableRow>& rowsOut)
{
	wxBoxSizer* bSizer8 = new wxBoxSizer(wxVERTICAL);
	const int varsCount = func.m_DecisionVarsCount;
	rowsOut = std::vector<VariableRow>(varsCount);
	for (int i = 0; i < varsCount; ++i)
	{
		rowsOut[i].m_index = i;
		wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			wxCheckBox* const VarCheckBox =
				new wxCheckBox(parent, wxID_ANY, wxT("x" + std::to_string(i + 1)));
			VarCheckBox->Bind(wxEVT_CHECKBOX, &MainFrame::OnVarCheckboxChanged, this);
			rowSizer->Add(VarCheckBox, 0, wxALL, 5);
			rowsOut[i].m_VarCheckBox = VarCheckBox;
		}
		{
			wxSlider* const VarSlider = new wxSlider(parent, wxID_ANY, 0, 0, 100);
			VarSlider->Bind(wxEVT_SCROLL_CHANGED, &MainFrame::OnVarSliderValueChanged, this);
			rowSizer->Add(VarSlider, 0, wxALL, 5);
			rowsOut[i].m_VarSlider = VarSlider;
		}
		{
			wxTextCtrl* const VarText =
				new wxTextCtrl(parent, wxID_ANY, std::to_string(func.m_DesignSpace[i].first), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
			VarText->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnVarTextEnterClicked, this);
			VarText->Bind(wxEVT_KILL_FOCUS, &MainFrame::OnVarTextCtrlFocusChanged, this);
			rowSizer->Add(VarText, 0, wxALL, 5);
			VarText->SetMinSize(wxSize(25, VarText->GetSize().y));
			rowsOut[i].m_VarText = VarText;
		}
		bSizer8->Add(rowSizer, 0, wxALL);
	}

	return bSizer8;
}

void MainFrame::OnConfigureMenuItemSelected(wxCommandEvent& event)
{
	ConfigDialog* CfgDialog = new ConfigDialog(this, wxID_ANY, wxT("Configure params"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);
	CfgDialog->ShowModal();
	event.Skip();
}

void MainFrame::OnExitMenuItemSelected(wxCommandEvent& event)
{
	Close();
    event.Skip();
}

void MainFrame::ComboboxOptionSelected(wxCommandEvent& event)
{
	wxString Option = m_comboBox1->GetStringSelection();
	if (!Option.empty()) 
	{
		m_SelectedFunc = &m_FunctionsMap[Option];
		ResetDynamicVisuals();
	}

	event.Skip();
}

HSResult MainFrame::MinimizeFunction(const HuntingSearchSpace& func) const
{
	HuntingSearchSolver solver(Params);

	return solver.Solve(func, HSLogging::HSLogToResult);
}

void MainFrame::ResetDynamicVisuals()
{
	// Recreate function's variables rows sizer for scrolled window
	if (m_scrolledWindow->GetSizer())
		m_scrolledWindow->GetSizer()->Clear(true);

	m_scrolledWindow->SetSizerAndFit(
		CreateVarRows(m_scrolledWindow, *m_SelectedFunc, m_VarRows));
	m_scrolledWindow->Layout();

	// Disable all checkboxes except indexed 0 and 1
	UpdateActiveVars(0, 1);

	// Update chart background's data
	m_Plot->GetChart().SetCurrentFunc(m_SelectedFunc, GetVarValues(), m_ActiveVars);
	UpdatePlotAxisLimits(*m_SelectedFunc);

	// Minimize function and plot result data
	{
		m_LastResult = MinimizeFunction(*m_SelectedFunc);
		m_CurrentStep = m_LastResult.m_Log.size() - 1;
		ResetScatterPlot(m_CurrentStep);
		m_StepSlider->SetRange(0, m_LastResult.m_Log.size() - 1);
		m_StepSlider->SetValue(m_StepSlider->GetMax());
	}

	m_HeightSlider->SetValue(m_HeightSlider->GetMax());
	const FRange funcValueRange = m_Plot->GetChart().GetFuncValueRange();
	colorBar->SetLeftLabelText(std::to_string((int64_t)std::floor(funcValueRange.first)));
	colorBar->SetRightLabelText(std::to_string((int64_t)std::ceil(funcValueRange.second)));
}

void MainFrame::ResetScatterPlot(size_t Step)
{
	if (m_LastResult.m_Log.empty()) 
	{
		return;
	}

	// Create the data for the scatter plot widget
	wxScatterPlotData chartData;

	wxVector<wxPoint2DDouble> hunters;
	const std::vector<DecisionVars>& Positions = m_LastResult.m_Log[Step];
	// There is a leader's position at index 0, so we skip it
	for (size_t i = 1; i < Positions.size(); ++i) 
	{
		hunters.push_back(wxPoint2DDouble(Positions[i][m_ActiveVars[0]], Positions[i][m_ActiveVars[1]]));
	}
	wxScatterPlotDataset::ptr dataset1(
		new wxScatterPlotDataset(
			wxColor(20, 20, 250, 0x78),
			wxColor(20, 20, 250, 0xB8),
			hunters)
	);

	// Plot leader's position separatly
	wxVector<wxPoint2DDouble> points;
	points.push_back(wxPoint2DDouble(Positions[0][m_ActiveVars[0]], Positions[0][m_ActiveVars[1]]));
	wxScatterPlotDataset::ptr dataset2(
		new wxScatterPlotDataset(
			wxColor(250, 250, 20, 0x78),
			wxColor(250, 250, 20, 0xB8),
			points)
	);
	chartData.AddDataset(dataset1);
	chartData.AddDataset(dataset2);

	m_Plot->GetChart().SetDataset(chartData);
	m_Plot->Refresh();
}

void MainFrame::OnVarTextEnterClicked(wxCommandEvent& event)
{
	for (const VariableRow& VarRow : m_VarRows) 
	{
		if (VarRow.m_VarText == event.GetEventObject()) 
		{
			const wxString Value = VarRow.m_VarText->GetValue();
			double NumValue;
			if (Value.ToDouble(&NumValue))
			{
				NumValue =
					m_SelectedFunc->ClampByDesignSpace(NumValue, VarRow.m_index);
				VarRow.m_VarText->SetValue(wxString::FromDouble(NumValue));
				VarRow.m_VarSlider->SetValue(DoubleToSliderValue(
						NumValue, m_SelectedFunc->m_DesignSpace[VarRow.m_index], VarRow.m_VarSlider));
				return;
			}
		}
	}

	m_Plot->GetChart().SetCurrentFunc(m_SelectedFunc, GetVarValues(), m_ActiveVars);
	
	event.Skip();
}

void MainFrame::OnVarCheckboxChanged(wxCommandEvent& event)
{
	wxCheckBox* const checkedBox = 
		static_cast<wxCheckBox*>(event.GetEventObject());
	for (const VariableRow& VarRow : m_VarRows) 
	{
		if (checkedBox == VarRow.m_VarCheckBox) 
		{
			VarCheckBoxChanged_Handle(checkedBox, VarRow);
		}
	}
}

void MainFrame::OnVarTextCtrlFocusChanged(wxFocusEvent& event)
{
	if (event.GetWindow()) 
	{
		return;
	}

	event.Skip();
}

void MainFrame::OnVarSliderValueChanged(wxCommandEvent& event)
{
	for (int i = 0; i < m_VarRows.size(); ++i)
	{
		if (m_VarRows[i].m_VarSlider == event.GetEventObject())
		{
			const double Value = SliderValueToDouble(m_SelectedFunc->m_DesignSpace[i], m_VarRows[i].m_VarSlider);
			m_VarRows[i].m_VarText->SetValue(wxString::FromDouble(Value));
			break;
		}
	}

	m_Plot->GetChart().SetCurrentFunc(m_SelectedFunc, GetVarValues(), m_ActiveVars);

	event.Skip();
}

void MainFrame::OnDrawConstrainedButtonToggled(wxCommandEvent& event)
{
	wxToggleButton* const buttonToggled = static_cast<wxToggleButton*>(event.GetEventObject());
	m_Plot->GetChart().SetDrawFuncConstrained(buttonToggled->GetValue());
	m_HeightSlider->SetValue(m_HeightSlider->GetMax());
	m_Plot->Refresh();
}

void MainFrame::OnPlotHeightSliderValueChanged(wxCommandEvent& event)
{
	wxSlider* const slider = static_cast<wxSlider*>(event.GetEventObject());
	m_Plot->GetChart().SetPlotHeight(SliderValueToDouble({0.0, 1.0}, slider));
	m_Plot->Refresh();
	event.Skip();
}

void MainFrame::OnPlotCtrlMouseEnter(wxMouseEvent& event)
{
	//m_StatusBar->SetStatusText("{" + std::to_string(event.GetPosition().x) + ", " + std::to_string(event.GetPosition().y) + "}", 0);
	const wxPoint2DDouble point = m_Plot->GetChart().MousePositionToFunctionCoords(event.GetPosition());
	m_StatusBar->SetStatusText("{" + std::to_string(point.m_x) + ", " + std::to_string(point.m_y) + "}", 0);
	DecisionVars VarValues = GetVarValues();
	VarValues[m_ActiveVars[0]] = point.m_x;
	VarValues[m_ActiveVars[1]] = point.m_y;
	const double funcValue = m_SelectedFunc->Calculate_ObjectiveFunc(VarValues);
	m_StatusBar->SetStatusText(std::to_string(funcValue), 1);
	event.Skip();
}

void MainFrame::OnStepLeftButtonClicked(wxCommandEvent& event)
{
	if (m_CurrentStep == 0) 
	{
		event.Skip();
		return;
	}
	m_CurrentStep--;
	ResetScatterPlot(m_CurrentStep);
	m_StepSlider->SetValue(m_CurrentStep);

	event.Skip();
}

void MainFrame::OnStepRightButtonClicked(wxCommandEvent& event)
{
	if (m_CurrentStep == m_LastResult.m_Log.size() - 1)
	{
		event.Skip();
		return;
	}
	m_CurrentStep++;
	ResetScatterPlot(m_CurrentStep);
	m_StepSlider->SetValue(m_CurrentStep);

	event.Skip();
}

void MainFrame::OnStepSliderValueChanged(wxCommandEvent& event)
{
	m_CurrentStep = m_StepSlider->GetValue();
	ResetScatterPlot(m_CurrentStep);
	event.Skip();
}

void MainFrame::OnStartButtonClicked(wxCommandEvent& event)
{
	m_CurrentStep = 0;
	ResetScatterPlot(m_CurrentStep);
	m_StepSlider->SetValue(m_CurrentStep);

	m_StepTimer->Start(500);
	event.Skip();
}

void MainFrame::OnStopButtonClicked(wxCommandEvent& event)
{
	m_StepTimer->Stop();
	event.Skip();
}

void MainFrame::OnStepTimerTriggered(wxTimerEvent& event)
{
	if (m_CurrentStep == m_LastResult.m_Log.size() - 1)
	{
		m_StepTimer->Stop();
		event.Skip();
		return;
	}

	m_CurrentStep++;
	ResetScatterPlot(m_CurrentStep);
	m_StepSlider->SetValue(m_CurrentStep);

	event.Skip();
}

void MainFrame::UpdatePlotAxisLimits(const HuntingSearchSpace& func)
{
	wxChartsAxisOptions xAxisOptions(wxCHARTSAXISPOSITION_BOTTOM);
	xAxisOptions.SetExplicitStartValue(func.m_DesignSpace[m_ActiveVars[0]].first);
	xAxisOptions.SetExplicitEndValue(func.m_DesignSpace[m_ActiveVars[0]].second);
	wxChartsAxisOptions yAxisOptions(wxCHARTSAXISPOSITION_LEFT);
	yAxisOptions.SetExplicitStartValue(func.m_DesignSpace[m_ActiveVars[1]].first);
	yAxisOptions.SetExplicitEndValue(func.m_DesignSpace[m_ActiveVars[1]].second);
	const wxChartsGridOptions gridOptions(xAxisOptions, yAxisOptions);
	m_Plot->GetChart().SetGridOptions(gridOptions);
}

DecisionVars MainFrame::GetVarValues() const
{
	DecisionVars result(m_SelectedFunc->m_DecisionVarsCount);
	for (int i = 0; i < m_VarRows.size(); ++i) 
	{
		if (m_VarRows[i].m_VarCheckBox->IsChecked()) 
		{
			result[i] = 0.0;
		}
		else 
		{
			result[i] = 
				SliderValueToDouble(m_SelectedFunc->m_DesignSpace[i], m_VarRows[i].m_VarSlider);
		}
	}

	return result;
}

void MainFrame::EnableVarRow(bool Value, const VariableRow& VarRow)
{
	VarRow.m_VarSlider->Enable(!Value);
	VarRow.m_VarText->Enable(!Value);
}

void MainFrame::VarCheckBoxChanged_Handle(wxCheckBox* checkBox, const VariableRow& VarRow)
{
	const bool CheckedStatus = checkBox->IsChecked();
	EnableVarRow(CheckedStatus, VarRow);
	if (!CheckedStatus) 
	{
		for (const VariableRow& Row : m_VarRows)
		{
			Row.m_VarCheckBox->Enable(true);
		}
	}
	else 
	{
		// Check if any other checkbox was checked (we need 2 to draw plot)
		for (const VariableRow& Row : m_VarRows)
		{
			if (Row.m_VarCheckBox->IsChecked() && &Row != &VarRow)
			{
				UpdateActiveVars(Row.m_index, VarRow.m_index);
				m_Plot->GetChart().SetCurrentFunc(m_SelectedFunc, GetVarValues(), m_ActiveVars);
				UpdatePlotAxisLimits(*m_SelectedFunc);
				ResetScatterPlot(m_LastResult.m_Log.size() - 1);
				m_HeightSlider->SetValue(m_HeightSlider->GetMax());
				break;
			}
		}
	}
}

double MainFrame::SliderValueToDouble(const FRange varRange, wxSlider* slider)
{
	const float SliderFrac = 
		(float)slider->GetValue() / (slider->GetMax() - slider->GetMin());
	return varRange.first + (varRange.second - varRange.first) * SliderFrac;
}

int MainFrame::DoubleToSliderValue(double Value, FRange varRange, wxSlider* slider)
{
	if (varRange.first < 0) 
	{
		Value += -varRange.first;
		varRange.second += -varRange.first;
		varRange.first = 0;
	}
	return std::floor(
		((Value - varRange.first) / varRange.second) 
		* (slider->GetMax() - slider->GetMin()));
}

MainFrame::MainFrame( 
    wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) 
    : wxFrame( parent, id, title, pos, size, style )
{
	InitializeFuncs();
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	m_StepTimer = new wxTimer(this);
	this->Bind(wxEVT_TIMER, &MainFrame::OnStepTimerTriggered, this);

	// Create a top-level panel to hold all the contents of the frame
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));

	m_MenuBar = new wxMenuBar(0);
	FileOption = new wxMenu();
	wxMenuItem* ConfigureOption = 
		new wxMenuItem(FileOption, 10009, wxString(wxT("Configure")), wxEmptyString, wxITEM_NORMAL);
	this->Bind(wxEVT_MENU, &MainFrame::OnConfigureMenuItemSelected, this, 10009);
	FileOption->Append(ConfigureOption);
	wxMenuItem* ExitOption;
	ExitOption = new wxMenuItem(FileOption, 10001, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	this->Bind(wxEVT_MENU, &MainFrame::OnExitMenuItemSelected, this, 10001);
	FileOption->Append(ExitOption);

	m_MenuBar->Append(FileOption, wxT("File"));

	AboutOption = new wxMenu();
	m_MenuBar->Append(AboutOption, wxT("About"));

	this->SetMenuBar(m_MenuBar);

	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	wxToggleButton* m_toggleBtn1 = 
		new wxToggleButton(m_ToolBar, wxID_ANY, wxT("Draw Constrained"), wxDefaultPosition, wxDefaultSize, 0);
	m_toggleBtn1->Bind(wxEVT_TOGGLEBUTTON, &MainFrame::OnDrawConstrainedButtonToggled, this);
	m_ToolBar->AddControl(m_toggleBtn1);
	m_HeightSlider = new wxSlider(m_ToolBar, wxID_ANY, 10, 0, 10);
	m_HeightSlider->Bind(wxEVT_SCROLL_CHANGED, &MainFrame::OnPlotHeightSliderValueChanged, this);
	m_ToolBar->AddControl(m_HeightSlider);
	colorBar = new HeightColorBar(m_ToolBar, wxID_ANY);
	m_ToolBar->AddControl(colorBar);
	wxButton* StepLeftButton = new wxButton(m_ToolBar, wxID_ANY, wxT("<"));
	StepLeftButton->Bind(wxEVT_BUTTON, &MainFrame::OnStepLeftButtonClicked, this);
	m_ToolBar->AddControl(StepLeftButton);
	m_StepSlider = new wxSlider(m_ToolBar, wxID_ANY, 1, 0, 1, wxDefaultPosition, wxDefaultSize, wxSL_LABELS);
	m_StepSlider->Bind(wxEVT_SCROLL_CHANGED, &MainFrame::OnStepSliderValueChanged, this);
	m_ToolBar->AddControl(m_StepSlider);
	wxButton* StepRightButton = new wxButton(m_ToolBar, wxID_ANY, wxT(">"));
	StepRightButton->Bind(wxEVT_BUTTON, &MainFrame::OnStepRightButtonClicked, this);
	m_ToolBar->AddControl(StepRightButton);
	wxButton* StartButton = new wxButton(m_ToolBar, wxID_ANY, wxT("Start"));
	StartButton->Bind(wxEVT_BUTTON, &MainFrame::OnStartButtonClicked, this);
	m_ToolBar->AddControl(StartButton);
	wxButton* StopButton = new wxButton(m_ToolBar, wxID_ANY, wxT("Stop"));
	StopButton->Bind(wxEVT_BUTTON, &MainFrame::OnStopButtonClicked, this);
	m_ToolBar->AddControl(StopButton);
	m_ToolBar->Realize();

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	m_scrolledWindow = new wxScrolledWindow(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxALWAYS_SHOW_SB);
	m_scrolledWindow->SetScrollRate(5, 5);

	const std::string DefaultFuncString = 
		"(x1^2 + x2 - 11)^2 + (x1 + x2^2 -7)^2";
	const HuntingSearchSpace& DefaultFunc = m_FunctionsMap[DefaultFuncString];

	//wxBoxSizer* bSizer8 = CreateVarRows(m_scrolledWindow, DefaultFunc, m_VarRows);
	//UpdateActiveVars(0, 1);

	//->SetSizerAndFit(bSizer8);
	//m_scrolledWindow->Layout();
	//wxSize Temp = bSizer8->Fit(m_scrolledWindow3);
	//m_scrolledWindow3->SetSize(Temp);
	bSizer7->Add(m_scrolledWindow, 0, wxEXPAND | wxALL, 5);

	std::vector<wxString> Funcs;
	for (auto KeyVal : m_FunctionsMap) 
	{
		Funcs.push_back(KeyVal.first);
	}
	m_SelectedFunc = &m_FunctionsMap["(x1^2 + x2 - 11)^2 + (x1 + x2^2 -7)^2"];
	m_Plot = CreatePlotCtrl(panel, DefaultFunc);
	m_Plot->GetChart().SetCurrentFunc(m_SelectedFunc, GetVarValues(), m_ActiveVars);
	//m_Plot->Bind(wxEVT_ENTER_WINDOW, &MainFrame::OnPlotCtrlMouseEnter, this);
	m_Plot->Bind(wxEVT_MOTION, &MainFrame::OnPlotCtrlMouseEnter, this);
	ResetDynamicVisuals();

	wxBoxSizer* bSizer9 = new wxBoxSizer(wxVERTICAL);
	m_comboBox1 = new wxComboBox(panel, 10002, wxT("Combo!"));
	m_comboBox1->Bind(wxEVT_COMBOBOX, &MainFrame::ComboboxOptionSelected, this, 10002);
	m_comboBox1->Set(Funcs);
	bSizer9->Add(m_comboBox1, 0, wxALL | wxEXPAND);
	bSizer9->Add(m_Plot, 1, wxALL | wxEXPAND);
	bSizer7->Add(bSizer9, 1, wxALL | wxEXPAND);

	panel->SetSizer(bSizer7);
	this->Layout();

	m_StatusBar = this->CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
	m_StatusBar->SetFieldsCount(2);
	this->Centre(wxBOTH);
}

MainFrame::~MainFrame()
{
	// Disconnect Events

}
