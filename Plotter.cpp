#include "Plotter.h"
#define NOISE_AMPLITUDE 0.15
void Plot3D::SetPoints(const std::vector<Pose2>& Points){

}

sciplot::DrawSpecs& Plot3D::DrawPositionsPoints() {
}
sciplot::DrawSpecs& Plot2D::DrawPositionsPoints() {
    std::vector<double> xCoords,yCoords; 
    xCoords.reserve(m_Points.size()); 
    yCoords.reserve(m_Points.size()); 
    for(auto& p : m_Points){
        xCoords.push_back(p.x); 
        yCoords.push_back(p.y); 
    }
    m_Plot.xlabel("x"); 
    m_Plot.ylabel("y");
    return m_Plot.drawPoints(sciplot::Vec(xCoords.data(),xCoords.size()), sciplot::Vec(yCoords.data(),yCoords.size())).pointSize(2).label(m_Title); // could replace all casting by creating a private sciplot member in Plot2/3D classes and create iterator functions; 
}

void Plot2D::SetPoints(const std::vector<Pose2>& Points)
{
    this->m_Points = Points; 
}


PlotsFigure::~PlotsFigure() {
    delete m_Figure; 
}

void PlotsFigure::AttatchPlots(PlotList Plots){
    for(auto p: Plots){
        if (dynamic_cast<Plot2D*>(p)) {
            auto p_cast = dynamic_cast<Plot2D*>(p); 
            m_Plots.push_back(std::vector<sciplot::PlotVariant>{p_cast->GetPlot()});
        }
        else {
            auto p_cast = dynamic_cast<Plot3D*>(p);
            m_Plots.push_back(std::vector<sciplot::PlotVariant>{p_cast->GetPlot()});
        }                 
    }
}

void PlotsFigure::PlotGeneratedCarTrackWithNoise(const std::function<double(double)>& func, double lb, double ub,double landmark_distance,double car_distance, uint32_t point_count)
{
    std::vector<Pose2> car_positions = GenerateCarPositions(func, lb, ub, point_count);
    std::vector<Point2> landmarks = GenerateLandmarkPositions(car_positions,landmark_distance, car_distance);
    AddNoiseLandmarkPositions(landmarks, NOISE_AMPLITUDE);
    AddNoiseCarPositions(car_positions, NOISE_AMPLITUDE); 
    std::vector<Pose2> landmark_positions;
    for (int i = 0; i < landmarks.size(); i++) {
        landmark_positions.push_back(Pose2{ landmarks[i].x,landmarks[i].y,0 });
    }
    BasePlot* plot = new Plot2D("", car_positions); 
    plot->DrawPositionsPoints(); 
    plot->SetPoints(landmark_positions); 
    plot->DrawPositionsPoints();
    this->AttatchPlots({ plot }); 
    this->Show();
    delete plot; 
}

void PlotsFigure::PlotCarPositionsAndLandMarks(const std::vector<Pose2>& CarPositions, const std::vector<Point2>& LandMarkPositions)
{
        BasePlot* plot = new Plot2D("Car/landmark positions", CarPositions); 
        plot->DrawPositionsPoints(); 
        std::vector<Pose2> landmark_positions;
    for (int i = 0; i < LandMarkPositions.size(); i++) {
        landmark_positions.push_back(Pose2{ LandMarkPositions[i].x,LandMarkPositions[i].y,0 });
    }

        plot->SetPoints(landmark_positions); 
        plot->DrawPositionsPoints();
        this->AttatchPlots({ plot }); 
        this->Show();
        delete plot;  
    
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





