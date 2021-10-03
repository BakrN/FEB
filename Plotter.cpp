#include "Plotter.h"

void Plot2D::DrawXYPlot() {
    std::vector<double> xCoords,yCoords; 
    xCoords.reserve(m_Points.size()); 
    yCoords.reserve(m_Points.size()); 
    for(auto& p : m_Points){
        xCoords.push_back(p.x); 
        yCoords.push_back(p.y); 
    }
    this->xlabel("x"); 
    this->ylabel("y");
    this->drawPoints(sciplot::Vec(xCoords.data(),xCoords.size()), sciplot::Vec(yCoords.data(),yCoords.size())).pointType(0); // could replace all casting by creating a private sciplot member in Plot2/3D classes and create iterator functions; 
 
}

void Plot2D::DrawHistogram() {
    
}

PlotsFigure::~PlotsFigure() {
    delete m_Figure; 
}

void PlotsFigure::AttatchPlots(PlotList plots){
    uint32_t size = plots.size(); 
    // for now we will have them in same row ; 
    for(auto& plot : plots){ 
        std::variant<sciplot::Plot, sciplot::Plot3D> var ; 
        try {
           // m_Plots.emplace_back(std::variant<sciplot::Plot, sciplot::Plot3D>(static_cast<sciplot::Plot>(std::get<Plot2D>(plot)))); 
          }
        catch (...) {
            
          //  m_Plots.emplace_back(std::variant<sciplot::Plot, sciplot::Plot3D>(static_cast<sciplot::Plot3D>(std::get<Plot3D>(plot)))); 
        }
    } 

    
    //for (int i = 0; i < m_Layout[0]; i++){
    //    plots.emplace_back(); 
    //} 
}

void PlotsFigure::Show() {
    
    m_Figure = new sciplot::Figure{m_Plots}; 
    m_Figure->title(m_Title); 
    m_Figure->palette(m_Palette); 
    m_Figure->size(m_Size[0],m_Size[1]); 
    m_Figure->show(); 
}
