/* MADE BY: Abubakr Nada r0767316*/ 
#pragma once
#include <sciplot/sciplot.hpp>
// Variants need to be used because of sciplot but could probably change library file to accept different types if needed
class BasePlot; 

using PlotList = std::initializer_list<BasePlot*> ; 
using PlotVectorList = std::vector<std::vector<sciplot::PlotVariant>>; 
// NOTE: Change set points to a shared ptr later;
#include "GlobalTypes.h" 
#include "SLAMTest.h"
class BasePlot {
public:

    virtual sciplot::DrawSpecs& DrawPositionsPoints() = 0;
    virtual void SetPoints(const std::vector<Pose2>& Points) = 0;
    //Different Functions for plotting we want we can add here
}; 

class Plot3D : public BasePlot{
    private: 
        sciplot::Plot3D m_Plot;  
    public: 
    Plot3D(); 
    sciplot::Plot3D& GetPlot()  { return m_Plot; };
    virtual sciplot::DrawSpecs& DrawPositionsPoints() override;
    virtual void SetPoints(const std::vector<Pose2>& Points) override; 
};

class Plot2D : public BasePlot{
    private: 
        sciplot::Plot m_Plot;  
        std::string m_Title; 
        std::vector<Pose2> m_Points;
    public: 
    Plot2D(); 
    
    Plot2D(const std::string& Title, const std::vector<Pose2>& Points) { 
        m_Points = Points; 
        m_Title = Title;
    }; 
    sciplot::Plot& GetPlot() { return m_Plot; };
    virtual sciplot::DrawSpecs& DrawPositionsPoints() override;


    // Inherited via BasePlot
    virtual void SetPoints(const std::vector<Pose2>& Points) override;

};
 
class PlotsFigure  {
private: 
    uint32_t m_Layout[2] = {1,1}; 
    uint32_t  m_Size[2] = {600,600}; 
    std::string m_Title; 
    std::string m_Palette = "dark2" ; 

    PlotVectorList m_Plots; 

    sciplot::Figure* m_Figure;
    template<typename T1,typename T2> 
    void SetLineSpace(T1 x0, T2 x1){

    }; 
public:
    ~PlotsFigure(); 
    PlotsFigure(); 
    PlotsFigure(const std::string& Title) : m_Title(Title) { m_Figure = nullptr;  };
    //PlotsFigure(const PlotList& Plots, const std::string& Title, const uint32_t* layout); 
    void Show(); 
    void SetPalette(const std::string& palette) { m_Palette = palette;};  // probably create enum to see all options
    void SetLayout(uint32_t rows, uint32_t cols) {m_Layout[0] = rows; m_Layout[1] = cols;  }; 
    void SetSize(uint32_t x_size, uint32_t y_size){m_Size[0] = x_size; m_Size[1] = y_size; }; 
    void AttatchPlots(PlotList Plots);
    // Template Figures go here
    void PlotGeneratedCarTrackWithNoise(const std::function<double(double)>& func, double lb, double ub,double landmark_distance, double car_distance, uint32_t point_count); // Generate test track with function, lower and upper bounds ,landmark distance and point count;  
    void PlotCarPositionsAndLandMarks(const std::vector<Pose2>& CarPositions, const std::vector<Point2>& LandMarkPositions); 
}; 