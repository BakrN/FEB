#pragma once 
#include "GlobalTypes.h"
#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 



void WritePoints(const std::string& filename, const std::vector<Point2>& points){
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
void ReadPoints(const std::string& filename, std::vector<Point2>& points ) {
    points.clear();  
    std::ifstream File(filename); 
 
    double * line_data = (double*)malloc(sizeof(double)*3); 
    if (File.is_open()){
        std::string line; 
     
        while (getline(File, line, ',') && !line.empty()){

           for (int i = 0; i < 3; i++){
               File >> line_data[i]; 
           }
           points.push_back(Point2{line_data[0],line_data[1],line_data[2]});  
        }
        File.close(); 
    }
    else{
        std::cout << "Couldn't Open File to Read\n"; 
    }
    delete line_data; 
}
