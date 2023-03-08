#pragma once

#include <wxscatterplot.h>
#include "HuntingSearchSpace.h"

class ScatterRegionPlot : public wxChart
{
public:
    ScatterRegionPlot(const wxScatterPlotData& data, const wxSize& size);
    ScatterRegionPlot(const wxScatterPlotData& data, wxSharedPtr<wxScatterPlotOptions>& options,
        const wxSize& size);

    virtual const wxChartCommonOptions& GetCommonOptions() const;
    void SetGridOptions(const wxChartsGridOptions& GridOptions);

    void SetCurrentFunc(HuntingSearchSpace* Func, const DecisionVars& VarValues, int ActiveVars[2]);
    void SetDataset(const wxScatterPlotData& data);
    void SetDrawFuncConstrained(bool Value);
    double CalculateFuncValue(const DecisionVars& VarValues) const;
    wxPoint2DDouble MousePositionToFunctionCoords(wxPoint point) const;
    void SetPlotHeight(float frac);
    FRange GetFuncValueRange() const;

private:
    double m_DivValue = 1.0;
    double m_DivValueCached = 1.0;
    double m_MinValue = 0.0;
    DecisionVars m_VarValues;
    int m_ActiveVars[2] = { 0, 1 };
    bool m_DrawFuncConstrained = false;

    void Initialize(const wxScatterPlotData& data);
    static wxDouble GetMinXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMaxXValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMinYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);
    static wxDouble GetMaxYValue(const wxVector<wxScatterPlotDataset::ptr>& datasets);

    virtual void DoSetSize(const wxSize& size);
    virtual void DoFit();
    virtual void DoDraw(wxGraphicsContext& gc, bool suppressTooltips);
    virtual wxSharedPtr<wxVector<const wxChartsElement*>> GetActiveElements(const wxPoint& point);

    void InitializeConstraints();
    void SetUpBackground();

private:
    class Point : public wxChartsPoint
    {
    public:
        typedef wxSharedPtr<Point> ptr;

        Point(wxPoint2DDouble value,
            const wxSharedPtr<wxChartTooltipProvider> tooltipProvider,
            wxDouble x, wxDouble y,
            const wxChartsPointOptions& options);

        virtual wxPoint2DDouble GetTooltipPosition() const;

        wxPoint2DDouble GetValue() const;

    private:
        wxPoint2DDouble m_value;
    };

    class Dataset
    {
    public:
        typedef wxSharedPtr<Dataset> ptr;

        Dataset();

        const wxVector<Point::ptr>& GetPoints() const;
        void AppendPoint(Point::ptr point);

    private:
        wxVector<Point::ptr> m_points;
    };

private:
    wxSharedPtr<wxScatterPlotOptions> m_options;
    wxChartsGrid m_grid;
    wxVector<Dataset::ptr> m_datasets;

    wxImage m_Background;
    HuntingSearchSpace* m_Func = nullptr;
};
