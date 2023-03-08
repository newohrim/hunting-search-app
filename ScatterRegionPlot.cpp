#include "ScatterRegionPlot.h"
#include "wxchartstheme.h"
#include <sstream>
#include <algorithm>
#include <limits>

ScatterRegionPlot::Point::Point(wxPoint2DDouble value,
    const wxSharedPtr<wxChartTooltipProvider> tooltipProvider,
    wxDouble x,
    wxDouble y,
    const wxChartsPointOptions& options)
    : wxChartsPoint(x, y, 5, 20, tooltipProvider, options), m_value(value)
{
}

wxPoint2DDouble ScatterRegionPlot::Point::GetTooltipPosition() const
{
    wxPoint2DDouble position = wxChartsPoint::GetTooltipPosition();
    position.m_y -= 10;
    return position;
}

wxPoint2DDouble ScatterRegionPlot::Point::GetValue() const
{
    return m_value;
}

ScatterRegionPlot::Dataset::Dataset()
{
}

const wxVector<ScatterRegionPlot::Point::ptr>& ScatterRegionPlot::Dataset::GetPoints() const
{
    return m_points;
}

void ScatterRegionPlot::Dataset::AppendPoint(Point::ptr point)
{
    m_points.push_back(point);
}

ScatterRegionPlot::ScatterRegionPlot(const wxScatterPlotData& data,
    const wxSize& size)
    : m_options(wxChartsDefaultTheme->GetScatterPlotOptions()),
    m_grid(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetRight()),
        size,
        GetMinXValue(data.GetDatasets()), GetMaxXValue(data.GetDatasets()),
        GetMinYValue(data.GetDatasets()), GetMaxYValue(data.GetDatasets()),
        m_options->GetGridOptions()
    ),
    m_Background(512, 512, true)
{
    Initialize(data);
}

ScatterRegionPlot::ScatterRegionPlot(const wxScatterPlotData& data,
    wxSharedPtr<wxScatterPlotOptions>& options,
    const wxSize& size)
    : m_options(options),
    m_grid(
        wxPoint2DDouble(m_options->GetPadding().GetLeft(), m_options->GetPadding().GetRight()),
        size,
        GetMinXValue(data.GetDatasets()), GetMaxXValue(data.GetDatasets()),
        GetMinYValue(data.GetDatasets()), GetMaxYValue(data.GetDatasets()),
        m_options->GetGridOptions()
    ),
    m_Background(512, 512, true)
{
    Initialize(data);
}

const wxChartCommonOptions& ScatterRegionPlot::GetCommonOptions() const
{
    return m_options->GetCommonOptions();
}

void ScatterRegionPlot::SetGridOptions(const wxChartsGridOptions& GridOptions)
{
    m_grid.SetOptions(GridOptions);
    DoFit();
}

void ScatterRegionPlot::SetCurrentFunc(HuntingSearchSpace* Func, const DecisionVars& VarValues, int ActiveVars[2])
{
    m_Func = Func;
    m_VarValues = VarValues;
    m_ActiveVars[0] = ActiveVars[0];
    m_ActiveVars[1] = ActiveVars[1];
    InitializeConstraints();
    SetUpBackground();
}

void ScatterRegionPlot::SetDataset(const wxScatterPlotData& data)
{
    m_datasets.clear();
    Initialize(data);
    DoFit();
}

void ScatterRegionPlot::SetDrawFuncConstrained(bool Value)
{
    if (Value != m_DrawFuncConstrained) 
    {
        m_DrawFuncConstrained = Value;

        // Redraw plot
        SetCurrentFunc(m_Func, m_VarValues, m_ActiveVars);
    }
}

double ScatterRegionPlot::CalculateFuncValue(const DecisionVars& VarValues) const
{
    if (m_DrawFuncConstrained) 
    {
        return m_Func->Calculate_ObjectiveFuncConstrained(VarValues);
    }

    return m_Func->Calculate_ObjectiveFunc(VarValues);
}

wxPoint2DDouble ScatterRegionPlot::MousePositionToFunctionCoords(wxPoint point) const
{
    const auto lerp = [](double v0, double v1, float t) -> double
    {
        return (1 - t) * v0 + t * v1;
    };
    const wxPoint2DDouble leftBottomCorner = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(0);
    const wxPoint2DDouble leftUpperCorner =
        m_grid.GetMapping().GetYAxis().GetTickMarkPosition(
            m_grid.GetMapping().GetYAxis().GetNumberOfTickMarks() - 1);
    const wxPoint2DDouble rightBottomCorner =
        m_grid.GetMapping().GetXAxis().GetTickMarkPosition(
            m_grid.GetMapping().GetXAxis().GetNumberOfTickMarks() - 1);
    //m_grid.GetMapping().GetSize().GetWidth() - 25,
    //    m_grid.GetMapping().GetSize().GetHeight() - 44
    const wxPoint2DDouble onPlotPos(point.x - leftUpperCorner.m_x, 
        m_grid.GetMapping().GetSize().GetHeight() - 20 - point.y - leftUpperCorner.m_y);
    return wxPoint2DDouble(
        lerp(
        m_Func->m_DesignSpace[m_ActiveVars[0]].first, 
        m_Func->m_DesignSpace[m_ActiveVars[0]].second, 
        onPlotPos.m_x / (rightBottomCorner.m_x - leftBottomCorner.m_x)),
        lerp(
            m_Func->m_DesignSpace[m_ActiveVars[1]].first,
            m_Func->m_DesignSpace[m_ActiveVars[1]].second,
            onPlotPos.m_y / -(leftUpperCorner.m_y - leftBottomCorner.m_y))
    );
}

void ScatterRegionPlot::SetPlotHeight(float frac)
{
    const auto lerp = [](double v0, double v1, float t) -> double
    {
        return (1 - t) * v0 + t * v1;
    };
    m_DivValue = lerp(1.0, m_DivValueCached, frac);

    // Redraw background
    SetUpBackground();
}

FRange ScatterRegionPlot::GetFuncValueRange() const
{
    return FRange(m_MinValue, m_MinValue + m_DivValue);
}

void ScatterRegionPlot::Initialize(const wxScatterPlotData& data)
{
    const wxVector<wxScatterPlotDataset::ptr>& datasets = data.GetDatasets();
    for (size_t i = 0; i < datasets.size(); ++i)
    {
        Dataset::ptr newDataset(new Dataset());

        const wxVector<wxPoint2DDouble>& datasetData = datasets[i]->GetData();
        for (size_t j = 0; j < datasetData.size(); ++j)
        {
            std::stringstream tooltip;
            tooltip << "(" << datasetData[j].m_x << "," << datasetData[j].m_y << ")";
            wxSharedPtr<wxChartTooltipProvider> tooltipProvider(
                new wxChartTooltipProviderStatic("", tooltip.str(), datasets[i]->GetFillColor())
            );

            Point::ptr point(
                new Point(datasetData[j], tooltipProvider, 20 + j * 10, 0,
                    wxChartsPointOptions(2, datasets[i]->GetStrokeColor(), datasets[i]->GetFillColor()))
            );

            newDataset->AppendPoint(point);
        }

        m_datasets.push_back(newDataset);
    }
}

wxDouble ScatterRegionPlot::GetMinXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_x;
                foundValue = true;
            }
            else if (result > values[j].m_x)
            {
                result = values[j].m_x;
            }
        }
    }

    return result;
}

wxDouble ScatterRegionPlot::GetMaxXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_x;
                foundValue = true;
            }
            else if (result < values[j].m_x)
            {
                result = values[j].m_x;
            }
        }
    }

    return result;
}

wxDouble ScatterRegionPlot::GetMinYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_y;
                foundValue = true;
            }
            else if (result > values[j].m_y)
            {
                result = values[j].m_y;
            }
        }
    }

    return result;
}

wxDouble ScatterRegionPlot::GetMaxYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets)
{
    wxDouble result = 0;
    bool foundValue = false;

    for (size_t i = 0; i < datasets.size(); ++i)
    {
        const wxVector<wxPoint2DDouble>& values = datasets[i]->GetData();
        for (size_t j = 0; j < values.size(); ++j)
        {
            if (!foundValue)
            {
                result = values[j].m_y;
                foundValue = true;
            }
            else if (result < values[j].m_y)
            {
                result = values[j].m_y;
            }
        }
    }

    return result;
}

void ScatterRegionPlot::DoSetSize(const wxSize& size)
{
    wxSize newSize(
        size.GetWidth() - m_options->GetPadding().GetTotalHorizontalPadding(),
        size.GetHeight() - m_options->GetPadding().GetTotalVerticalPadding()
    );
    m_grid.Resize(newSize);

    // Update background image scale
    //if (m_Background.IsOk()) 
    //{
        //m_Background = std::move(m_Background.Rescale(
        //    m_grid.GetMapping().GetSize().GetWidth() - m_options->GetPadding().GetTotalHorizontalPadding(),
        //    m_grid.GetMapping().GetSize().GetHeight() - m_options->GetPadding().GetTotalVerticalPadding() - 44));
    //}
}

void ScatterRegionPlot::DoFit()
{
    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            const Point::ptr& point = points[j];
            point->SetPosition(
                m_grid.GetMapping().GetWindowPosition(
                    point->GetValue().m_x, point->GetValue().m_y));
        }
    }
}

void ScatterRegionPlot::DoDraw(wxGraphicsContext& gc,
    bool suppressTooltips)
{
    m_grid.Fit(gc);

    {
        // DRAW BACKGROUND START
        wxBitmap bitmap(m_Background);
        const wxPoint2DDouble leftBottomCorner = m_grid.GetMapping().GetXAxis().GetTickMarkPosition(0);
        const wxPoint2DDouble leftUpperCorner =
            m_grid.GetMapping().GetYAxis().GetTickMarkPosition(
                m_grid.GetMapping().GetYAxis().GetNumberOfTickMarks() - 1);
        gc.DrawBitmap(bitmap, leftBottomCorner.m_x, leftUpperCorner.m_y,
            m_grid.GetMapping().GetSize().GetWidth() - 25,
            m_grid.GetMapping().GetSize().GetHeight() - 44);
        // DRAW BACKGROUND END
    }

    m_grid.Draw(gc);

    Fit();

    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            points[j]->Draw(gc);
        }
    }

    if (!suppressTooltips)
    {
        DrawTooltips(gc);
    }
}

wxSharedPtr<wxVector<const wxChartsElement*>> ScatterRegionPlot::GetActiveElements(const wxPoint& point)
{
    wxSharedPtr<wxVector<const wxChartsElement*>> activeElements(new wxVector<const wxChartsElement*>());
    for (size_t i = 0; i < m_datasets.size(); ++i)
    {
        const wxVector<Point::ptr>& points = m_datasets[i]->GetPoints();
        for (size_t j = 0; j < points.size(); ++j)
        {
            if (points[j]->HitTest(point))
            {
                activeElements->push_back(points[j].get());
            }
        }
    }
    return activeElements;
}

void ScatterRegionPlot::InitializeConstraints()
{
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::min();
    const int bgWidth = m_Background.GetWidth();
    const int bgHeight = m_Background.GetHeight();
    const double xWidth = 
        m_Func->m_DesignSpace[m_ActiveVars[0]].second - m_Func->m_DesignSpace[m_ActiveVars[0]].first;
    const double yWidth =
        m_Func->m_DesignSpace[m_ActiveVars[1]].second - m_Func->m_DesignSpace[m_ActiveVars[1]].first;
    for (int i = 0; i < bgHeight; ++i)
    {
        for (int j = 0; j < bgWidth; ++j)
        {
            const float x = (j * xWidth / bgWidth) - std::abs(m_Func->m_DesignSpace[m_ActiveVars[0]].first);
            const float y = (bgHeight - i - 1) * yWidth / bgHeight - std::abs(m_Func->m_DesignSpace[m_ActiveVars[1]].first);
            m_VarValues[m_ActiveVars[0]] = x;
            m_VarValues[m_ActiveVars[1]] = y;
            const double value = CalculateFuncValue(m_VarValues);
            if (value > maxVal)
                maxVal = value;
            if (value < minVal)
                minVal = value;
        }
    }
    m_DivValue = maxVal - minVal;
    m_DivValueCached = m_DivValue;
    m_MinValue = minVal;
}

void ScatterRegionPlot::SetUpBackground()
{
    const auto lerp = [](float v0, float v1, float t) -> float
    {
        return (1 - t) * v0 + t * v1;
    };

    uint8_t* const data = m_Background.GetData();
    const int bgWidth = m_Background.GetWidth();
    const int bgHeight = m_Background.GetHeight();
    const double xWidth =
        m_Func->m_DesignSpace[m_ActiveVars[0]].second - m_Func->m_DesignSpace[m_ActiveVars[0]].first;
    const double yWidth =
        m_Func->m_DesignSpace[m_ActiveVars[1]].second - m_Func->m_DesignSpace[m_ActiveVars[1]].first;
    for (int i = 0; i < bgHeight; ++i)
    {
        for (int j = 0; j < bgWidth; ++j)
        {
            const float x = (j * xWidth / bgWidth) - std::abs(m_Func->m_DesignSpace[m_ActiveVars[0]].first);
            const float y = (bgHeight - i - 1) * yWidth / bgHeight - std::abs(m_Func->m_DesignSpace[m_ActiveVars[1]].first);
            m_VarValues[m_ActiveVars[0]] = x;
            m_VarValues[m_ActiveVars[1]] = y;
            const double value = CalculateFuncValue(m_VarValues);
            const double temp = (value + ((m_MinValue < 0) * 2 - 1) * std::abs(m_MinValue));
            float normValue = std::min(1.0, temp / m_DivValue);
            normValue *= 10;
            normValue = std::floor(normValue) / 10.0f;
            const wxColor color(lerp(0, 255, normValue), lerp(255, 0, normValue), 0);

            const int index = i * bgWidth * 3 + j * 3;
            data[index + 0] = color.Red();
            data[index + 1] = color.Green();
            data[index + 2] = color.Blue();
            //data[index + 3] = 255;
        }
    }
}
