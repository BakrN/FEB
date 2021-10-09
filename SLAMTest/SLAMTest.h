#pragma once

#include <functional> 
#include <GlobalTypes.h>
#include <vector> 
#include <forward_list>

double CurvedCornerTrackFunction(double x);
double ParabolicTrackFunction(double x); 
double SineFunction(double x); 

std::vector<Pose2> GenerateCarPositions(const std::function<double(double x)>& func,double lb,double ub, uint32_t point_count);

std::vector<Point2> GenerateLandmarkPositions(std::vector<Pose2>& car_positions,double distance_between_landmarks,double distance_from_car);

void AddNoiseCarPositions(std::vector<Pose2>&  car_positions, double amplitude);
void AddNoiseLandmarkPositions(std::vector<Point2>& landmark_points,double amplitude);
void DetectCones(const std::vector<Pose2>& car_positions, const std::vector<Point2>& landmark_points , double triangle_theta, double triangle_h);
void DeleteFromPos(std::forward_list<uint32_t>& list, std::forward_list<uint32_t>::iterator pos);
bool IsPointInsideTriangle(const Point2& check_point, const Point2& p0,const Point2& p1, const Point2& p2); 

