#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

#include "DataPoint.h"
#include "DistanceFunction.h"
#include "Algorithm.h"

void studentMain()
{
    Algorithm *a1 = new Algorithm("textfile_55555.txt");
    float **centroids = new float *[2];
    centroids[0] = new float[3];
    centroids[0][0] = 0.5f;
    centroids[0][1] = 4.5f;
    centroids[0][2] = 0;
    centroids[1] = new float[3];
    centroids[1][0] = 5;
    centroids[1][1] = 0.4f;
    centroids[1][2] = 1.5f;
    a1->setCentroids(centroids, 2, 3);
    DataPoint ***results = a1->fullRun(1, 20);
    if (results == NULL)
    {
        std::cout << "results == NULL" << std::endl;
    }
    else
    {
        for (int i = 0; i < 20; i++)
        {
            std::cout << "Generation: " << i << std::endl;
            if (results[i] == NULL)
            {
                std::cout << "results[" << i << "] == NULL" << std::endl;
            }
            else
            {
                for(int j=0; j < 2; j++){
                    std::cout << "Centroid: " << j << std::endl;
                    if(results[i][j] == NULL){
                        std::cout << "results[" << i << "][" << j << "] == NULL" << std::endl;
                    } else {
                        results[i][j]->printOut();
                        delete results[i][j];
                        results[i][j] = NULL;
                    }
                }
                delete[] results[i];
                results[i] = NULL;
            }
        }
        delete[] results;
        results = NULL;
    }
    for(int i=0; i < 2; i++){
        delete[] centroids[i];
        centroids[i] = NULL;
    }
    delete[] centroids;
    centroids = NULL;
    delete a1;
    a1 = NULL;

}
int main(int argc, char const *argv[])
{
    studentMain();
    // testSingleRun();
}


/*
Expected output can be found in studentExampleOutput.txt
*/