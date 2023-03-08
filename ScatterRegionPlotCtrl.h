#pragma once

#include <wxchartctrl.h>
#include "ScatterRegionPlot.h"

class ScatterRegionPlotCtrl : public wxChartCtrl
{
public:
    ScatterRegionPlotCtrl(wxWindow* parent, wxWindowID id, const wxScatterPlotData& data,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = 0);
    ScatterRegionPlotCtrl(wxWindow* parent, wxWindowID id, const wxScatterPlotData& data,
        wxSharedPtr<wxScatterPlotOptions>& options, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0);

    virtual ScatterRegionPlot& GetChart();

private:
    ScatterRegionPlot m_scatterPlot;
};

