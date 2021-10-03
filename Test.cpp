#include "GlobalTypes.h"
#include "FileHandler.h"
#include "Plotter.h"

// Random vector test 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <random>
#include <iomanip>
#include <math.h>


using std::setprecision;


/**
 * Function generator a list containing nb object Point2.
 */
std::vector<Point2> randGenerator(double rand_min, double rand_max, double rand_min_theta, double rand_max_theta, int nb){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(rand_min, rand_max);

    std::random_device rd_theta;
    std::default_random_engine eng_theta(rd_theta());
    std::uniform_real_distribution<double> distr_theta(rand_min_theta, rand_max_theta);

    std::vector<Point2> vect_pts = std::vector<Point2>();

    for (int i=0; i<nb; i++){
        vect_pts.push_back(Point2{distr(eng), distr(eng), distr_theta(eng_theta)});
    }
    return vect_pts;
}


int main(){
    Point2 pt1 = Point2{0.0, 0.0, 0.0};
    std::cout << "Hello world" << std::endl;
    double rand_min = 0.0;
    double rand_max = 10.0;
    double rand_min_theta = 0.0;
    double rand_max_theta = 2.0*3.14;
    int nb = 10;
    std::vector<Point2> vect_pts = randGenerator(rand_min, rand_max, rand_min_theta, rand_max_theta, nb);
    
    for (int i=0 ; i < vect_pts.size() ; i++){
        std::cout << "(x,y,theta) = ( " << vect_pts[i].x << " , " << vect_pts[i].y << " , " << vect_pts[i].theta << " )" << std::endl;
    }
    std::string FileName = "OutputPoints.txt"; 
    //Write To File
    WritePoints(FileName, vect_pts); 
    //Read From File
    ReadPoints(FileName, vect_pts); 
    //XY Plot

}