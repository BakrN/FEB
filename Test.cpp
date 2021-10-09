#include "GlobalTypes.h"
#include "FileHandler.h"
#include "Plotter.h"
#include "SLAMTest.h"
// Random vector test 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <random>
#include <iomanip>
#include <math.h>



int main() {
  
    PlotsFigure figure1("Showing generated car and landmark positions with noise");
    figure1.SetSize(600, 600);
    figure1.PlotGeneratedCarTrackWithNoise(CurvedCornerTrackFunction, -5, 5, 1, 1, 50); //func , lb,ub,landmark_dist,dist from car
     
    PlotsFigure figure2("Showing generated car and landmark positions with noise");
    figure2.SetSize(600, 600);
    figure2.PlotGeneratedCarTrackWithNoise(ParabolicTrackFunction, -5, 5, 1, 1, 10); //func , lb,ub,landmark_dist,dist from car

    PlotsFigure figure3("Showing generated car and landmark positions with noise");
    figure3.SetSize(600, 600);
    figure3.PlotGeneratedCarTrackWithNoise(SineFunction, -5, 5, 1, 1, 30); //func , lb,ub,landmark_dist,dist from car
}
