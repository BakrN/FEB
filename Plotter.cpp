#include "Plotter.h"

void Plot2D::DrawPositionsPoints() {
    std::vector<double> xCoords,yCoords; 
    xCoords.reserve(m_Points.size()); 
    yCoords.reserve(m_Points.size()); 
    for(auto& p : m_Points){
        xCoords.push_back(p.x); 
        yCoords.push_back(p.y); 
    }
    m_Plot.xlabel("x"); 
    m_Plot.ylabel("y");
    m_Plot.drawPoints(sciplot::Vec(xCoords.data(),xCoords.size()), sciplot::Vec(yCoords.data(),yCoords.size())).pointType(0); // could replace all casting by creating a private sciplot member in Plot2/3D classes and create iterator functions; 
}

void Plot2D::DrawHistogram() {
    
}

PlotsFigure::~PlotsFigure() {
    delete m_Figure; 
}

void PlotsFigure::AttatchPlots(PlotList Plots){
    for(auto p: Plots){
        try{
            m_Plots.push_back(std::vector<sciplot::PlotVariant>{std::get<Plot2D>(p).GetPlot()});
        }
        catch(...){
            m_Plots.push_back(std::vector<sciplot::PlotVariant>{std::get<Plot3D>(p).GetPlot()});
        }
        
    }
}

void PlotsFigure::Show() {
    
    m_Figure = new sciplot::Figure{m_Plots}; 
    m_Figure->title(m_Title); 
    m_Figure->palette(m_Palette); 
    m_Figure->size(m_Size[0],m_Size[1]); 
    m_Figure->show(); 
}


Plot2D::Plot2D() {
    
}





