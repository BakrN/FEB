/* MADE BY: Abubakr Nada r0767316*/ 
#pragma once
#include <sciplot/sciplot.hpp>
// Variants need to be used because of sciplot but could probably change library file to accept different types if needed
class Plot2D; 
class Plot3D; 

using PlotList = std::initializer_list<std::variant<Plot2D,Plot3D>> ; 
using PlotVectorList = std::vector<std::vector<sciplot::PlotVariant>>; 

#include "GlobalTypes.h" 
/*template <typename T> 
class BasePlot {
private: 
    friend class Plot3D; 
    friend class Plot2D; 

public: 
    virtual T& GetPlot() = 0; 
    virtual void DrawPositionsPoints() = 0; 

    template <typename F> 
    virtual void DrawPositionsFunc(const std::function<F>& f) = 0;

    //Different Functions for plotting we want we can add here
   };*/

class Plot3D {
    private: 
        sciplot::Plot3D m_Plot;  
    public: 
    Plot3D(); 
    sciplot::Plot3D& GetPlot()  { return m_Plot; };
};

class Plot2D {
    private: 
        sciplot::Plot m_Plot;  
        std::vector<Point2> m_Points;
    public: 
    Plot2D(); 
    Plot2D(const std::vector<Point2>& Points) { 
        m_Points = Points; 
    }; 
    sciplot::Plot& GetPlot() { return m_Plot; };
    void DrawPositionsPoints() ; 
    void DrawHistogram();  // Not Implemented Yet 
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
    
    void AttatchPlots(PlotList Plots) ;  
}; 