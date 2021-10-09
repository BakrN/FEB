#include "SLAMTest.h"
#include "math.h"
#include <random>

double CurvedCornerTrackFunction(double x) {
    return (0.02 * (x + 5) * (x - 1) * (x - 2) * (x - 5));
}

double ParabolicTrackFunction(double x)
{
    return -0.1 * (x-5) * (x+5); 
}

double SineFunction(double x)
{
    return (double)sin(x); 
}

std::vector<Pose2> GenerateCarPositions(const std::function<double(double x)>& func, double lb, double ub, uint32_t point_count) {
        std::vector<Pose2> car_positions; 
        double jump = (ub-lb)/point_count; 
         double orientation = 0; 
        for(int i = 0 ; i < point_count; i++){
            
            if(i <point_count-2){
                orientation = atan2((func(lb+(i+1)*(jump)) - func(lb + jump*i)),jump); 
            }
            car_positions.emplace_back(lb+jump*i,func(lb+jump*i),orientation); 
        }

        return car_positions; 
}

std::vector<Point2> GenerateLandmarkPositions( std::vector<Pose2>& car_positions,double distance_between_landmarks, double distance_from_car) {
    std::vector<Point2> landmark_points; 
       
    landmark_points.emplace_back(car_positions[0].x +sqrt(distance_from_car)*cos(car_positions[0].theta + M_PI/2),car_positions[0].y+ sqrt(distance_from_car)*sin(car_positions[0].theta + M_PI/2),0); 
    landmark_points.emplace_back(car_positions[0].x -sqrt(distance_from_car)*cos(car_positions[0].theta + M_PI/2),car_positions[0].y- sqrt(distance_from_car)*sin(car_positions[0].theta + M_PI/2),0); 
    uint32_t lastindex_right = 0; 
    uint32_t lastindex_left = 1;

    for (int i = 1; i < car_positions.size(); i++) {
        if (landmark_points[lastindex_right].Dist(Point2{ car_positions[i].x + sqrt(distance_from_car) * cos(car_positions[i].theta + M_PI / 2), car_positions[i].y + sqrt(distance_from_car) * sin(car_positions[i].theta + M_PI / 2), 0 }, distance_between_landmarks)) {
            landmark_points.emplace_back(Point2 { car_positions[i].x + sqrt(distance_from_car) * cos(car_positions[i].theta + M_PI / 2), car_positions[i].y + sqrt(distance_from_car) * sin(car_positions[i].theta + M_PI / 2), 0 }); 
            lastindex_right = landmark_points.size()-1; 
        }
        if(landmark_points[lastindex_left].Dist(Point2{ car_positions[i].x - sqrt(distance_from_car) * cos(car_positions[i].theta + M_PI / 2), car_positions[i].y - sqrt(distance_from_car) * sin(car_positions[i].theta + M_PI / 2), 0 }, distance_between_landmarks)) {
            landmark_points.emplace_back(Point2{ car_positions[i].x - sqrt(distance_from_car) * cos(car_positions[i].theta + M_PI / 2), car_positions[i].y - sqrt(distance_from_car) * sin(car_positions[i].theta + M_PI / 2), 0 });
            lastindex_left = landmark_points.size()-1;
        }
    }
    return landmark_points; 
}

void AddNoiseCarPositions(std::vector<Pose2>&  car_positions, double amplitude) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-amplitude, amplitude); 
    for(int i = 0; i < car_positions.size(); i++){
        car_positions[i].x += distr(eng); 
        car_positions[i].y += distr(eng); 
    }

}

void AddNoiseLandmarkPositions(std::vector<Point2>& landmark_points, double amplitude) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(-amplitude, amplitude); 
    for(int i = 0; i < landmark_points.size(); i++){
        landmark_points[i].x += distr(eng); 
        landmark_points[i].y += distr(eng); 
    }
}

void DetectCones(const std::vector<Pose2>& car_positions,  std::vector<Point2>& landmark_points, double triangle_theta, double triangle_h) {
    //variables needed to calculate if landmark can be detected by car
    
    Point2 p0,p1,p2; 
    std::forward_list<uint32_t> indices; 
    for(int i = landmark_points.size(); i >-1; --i){
        indices.push_front(i); 
    }
   

    


    std::forward_list<uint32_t>::iterator current = indices.begin(); 

    uint8_t count = 6; 

    for(auto car_position : car_positions){
        current=indices.begin();
        p0.x = car_position.x; 
        p0.y = car_position.y; 
        p1.x = p0.x + triangle_h* cos(car_position.theta - triangle_theta/2)/cos(triangle_theta/2); 
        p1.y = p0.y + triangle_h* sin(car_position.theta - triangle_theta/2)/cos(triangle_theta/2);
        p2.x = p0.x + triangle_h* cos(car_position.theta + triangle_theta/2)/cos(triangle_theta/2); 
        p2.y = p0.y + triangle_h* sin(car_position.theta + triangle_theta/2)/cos(triangle_theta/2);
        for(int i = 0; i < count; i++){
            if(IsPointInsideTriangle(landmark_points[*current],p0,p1,p2)){
                DeleteFromPos(indices, current); 
            }
            else{current++;} 
        }
    }
    // remove undetected cones
    uint32_t removed_count = 0; 
    for(auto it = indices.begin(); it!=indices.end(); it++){
        landmark_points.erase(landmark_points.begin() + (*it - removed_count)); 
        removed_count++; 
    }
}
void DeleteFromPos(std::forward_list<uint32_t>& list, std::forward_list<uint32_t>::iterator pos){
    std::forward_list<uint32_t>::iterator prev = list.begin(); 
    for(auto it = list.begin(); it != list.end(); it++){
        prev = it; 
        if(++it == pos){
            break; 
        }
    }
    list.erase_after(prev); 
}
bool IsPointInsideTriangle(const Point2& check_point, const Point2& p0,const Point2& p1, const Point2& p2){
    double Area = 0.5 *(-p1.y*p2.x + p0.y*(-p1.x + p2.x) + p0.x*(p1.y - p2.y) + p1.x*p2.y);
    double s = 1/(2*Area)*(p0.y*p2.x - p0.x*p2.y + (p2.y - p0.y)*check_point.x + (p0.x - p2.x)*check_point.y);
    double t = 1/(2*Area)*(p0.x*p1.y - p0.y*p1.x + (p0.y - p1.y)*check_point.x + (p1.x - p0.x)*check_point.y);
    if(s>0 && t>0 && 1-s-t>0){
        return true; 
    }
    return false; 
}
