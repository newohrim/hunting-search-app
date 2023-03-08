#include "ScatterRegionPlotCtrl.h"

ScatterRegionPlotCtrl::ScatterRegionPlotCtrl(wxWindow* parent,
    wxWindowID id,
    const wxScatterPlotData& data,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_scatterPlot(data, size)
{
}

ScatterRegionPlotCtrl::ScatterRegionPlotCtrl(wxWindow* parent,
    wxWindowID id,
    const wxScatterPlotData& data,
    wxSharedPtr<wxScatterPlotOptions>& options,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_scatterPlot(data, options, size)
{
}

ScatterRegionPlot& ScatterRegionPlotCtrl::GetChart()
{
    return m_scatterPlot;
}