/* MADE BY: Abubakr Nada r0767316*/ 
#pragma once
#include <sciplot/sciplot.hpp>
// Variants need to be used because of sciplot but could probably change library file to accept different types if needed
class Plot2D; 
class Plot3D; 
using PlotList = std::initializer_list<std::variant<Plot2D,Plot3D>> ; 
using PlotVectorList = std::vector<std::vector<sciplot::PlotVariant>>; 

#include "GlobalTypes.h" 

class Plot3D : public sciplot::Plot3D{
    private: 
    public: 

}; 

class Plot2D :public sciplot::Plot{
    private: 
        std::vector<Point2> m_Points; 
        
    public: 
    Plot2D() : sciplot::Plot() {}; 
    Plot2D(const std::vector<Point2>& Points) : sciplot::Plot(){ 
        m_Points = Points; 
    }; 
    template <typename T>  
    void DrawLineGraph(std::function<T> function) { // could also take func pointer
        // Definition will go here

    }; 
    void DrawXYPlot(); // With Points 
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
    void SetLineSpace(T1 x0, T2 x1); 
public:
    ~PlotsFigure(); 
    PlotsFigure(const std::string& Title) : m_Title(Title) { };
    //PlotsFigure(const PlotList& Plots, const std::string& Title, const uint32_t* layout); 
    void Show(); 
    void SetPalette(const std::string& palette) { m_Palette = palette;};  // probably create enum to see all options
    void SetLayout(uint32_t rows, uint32_t cols) {m_Layout[0] = rows; m_Layout[1] = cols;  }; 
    void SetSize(uint32_t x_size, uint32_t y_size){m_Size[0] = x_size; m_Size[1] = y_size; }; 
    void AttatchPlots(PlotList Plots) ; // Note: will have to change cpy ctr move data so that not every element is copied with passed 
}; 
