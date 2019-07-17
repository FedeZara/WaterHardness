#include "Point.h"

class LinearRegression
{
  public:
    LinearRegression(){}
    LinearRegression(int numSamples, Point* points){
        this->points = points;
        this->numSamples = numSamples;

        double sumX = 0;
        double sumY = 0;
        double sumXSquared = 0;
        double sumXy = 0;
        for(int i=0; i<numSamples; i++){
            sumX += points[i].x;
            sumY += points[i].y;
            sumXSquared += points[i].x * points[i].x;
            sumXy += points[i].x * points[i].y;
        }

        double numSamplesDouble = double(numSamples);

        m = (numSamplesDouble*sumXy - sumX*sumY) / (numSamplesDouble*sumXSquared - sumX*sumX);
        b = (sumY - m*sumX) / numSamplesDouble;

        double ess = 0, tss = 0, avgY = sumY/numSamplesDouble;

        for(int i=0; i<numSamples; i++){
            double diff = calculateY(points[i].x) - avgY;
            ess += diff*diff;

            diff = points[i].y - avgY;
            tss += diff*diff;
        }

        rSquared = ess / tss;
    }
    

    double calculateY(double x){
        return m*x + b;
    }

    double calculateX(double y){
        return (y - b)/m;
    }

    double getSlope(){
        return m;
    }

    double getIntercept(){
        return b;
    }

    double getDetermination(){
        return rSquared;
    }

  private:
    Point* points;
    int numSamples;
    double m = 0;
    double b = 0;
    double rSquared = 0; 
};
