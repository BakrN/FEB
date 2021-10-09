#pragma once 
#include "GlobalTypes.h"
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 



void WritePoints(const std::string& filename, const std::vector<Pose2>& points){
    std::ofstream File(filename); 
    if(File.is_open()){
        for(auto& p: points){
           File << p.x << "," << p.y << "," << p.theta << "\n"; 
        }
        File.close();  
    }
    else{
        std::cout <<  "Error writing to file\n "; 
    }
}
void ReadPoints(const std::string& filename, std::vector<Pose2>& points ) {
    points.clear();  
    std::ifstream File(filename); 
    double line_data[3] = { 0 }; 
     if (File.is_open()){
        std::string line; 
     
        while (getline(File, line) && !line.empty()){
           int offset = 0; 
           for (int i = 0; i < 3; i++){
               line_data[i] = std::stod(line.substr(offset, line.find(',', offset + 1) - offset)); 
               offset = line.find(',', offset+1)+1; 
           }
           points.push_back(Pose2{line_data[0],line_data[1],line_data[2]});  
        }
        File.close(); 
    }
    else{
        std::cout << "Couldn't Open File to Read\n"; 
    }
  }

void WritePoints(const std::string& filename, const std::vector<Point2>& points){
    std::ofstream File(filename); 
    if(File.is_open()){
        for(auto& p: points){
           File << p.x << "," << p.y << "," << p.index << "\n"; 
        }
        File.close();  
    }
    else{
        std::cout <<  "Error writing to file\n "; 
    }
}
void ReadPoints(const std::string& filename, std::vector<Point2>& points ) {
    points.clear();  
    std::ifstream File(filename); 
    double line_data[2] = { 0 }; 
    uint32_t index =  0; 
     if (File.is_open()){
        std::string line; 
     
        while (getline(File, line) && !line.empty()){
           int offset = 0; 
           for (int i = 0; i < 2; i++){
               line_data[i] = std::stod(line.substr(offset, line.find(',', offset + 1) - offset)); 
               offset = line.find(',', offset+1)+1; 
           }
            index = std::stoi(line.substr(offset, line.find(',', offset + 1) - offset)); 
            points.push_back(Point2{line_data[0],line_data[1],index});  
        }
        File.close(); 
    }
    else{
        std::cout << "Couldn't Open File to Read\n"; 
    }
  }