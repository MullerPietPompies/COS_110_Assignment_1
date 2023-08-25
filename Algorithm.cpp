#include "Algorithm.h"
#include "DistanceFunction.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>

Algorithm::Algorithm(std::string textfile) : dataPoints(NULL), numberOfDataPoints(0),k(-1),centroids(NULL){
    std::ifstream inputFile(textfile.c_str());

    if (!inputFile){
        std::cout << "Error opening file: " << textfile<< std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile,line))
    {
        if(!line.empty()){
            std::istringstream ss(line);

            DataPoint* newPoint = new DataPoint(line);
            DataPoint** temp = new DataPoint*[numberOfDataPoints+1];
            for (int i=0; i<numberOfDataPoints;i++){
                temp[i] = dataPoints[i];
            }
            temp[numberOfDataPoints] = newPoint;
            delete[] dataPoints;
            dataPoints = temp;
            numberOfDataPoints++;
        }
    }
    inputFile.close();
};

Algorithm::Algorithm(DataPoint** dps, int numberOfDatapoints):
k(-1), centroids(NULL){
    if (dps == NULL||numberOfDataPoints<=0)
    {
        return;
    }
    this->numberOfDataPoints = numberOfDataPoints;
    dataPoints = new DataPoint*[numberOfDataPoints];
    for (int i = 0; i < numberOfDataPoints; i++)
    {
        dataPoints[i] = new DataPoint(*(dps[i]));
    }
};
Algorithm::Algorithm(Algorithm* other): dataPoints(NULL), numberOfDataPoints(0), k(-1),centroids(NULL){
    if (other == NULL){
        return;
    }
    if (other->dataPoints != NULL && other->numberOfDataPoints>0){
        dataPoints = new DataPoint*[other->numberOfDataPoints];
        for (int i=0; i<other->numberOfDataPoints;i++){
            dataPoints[i] = new DataPoint(*(other->dataPoints[i]));
        }
        numberOfDataPoints = other->numberOfDataPoints;
    }
};

DataPoint** Algorithm::setCentroids(float** rawCentroidPositions,int newk,int numAttributes){
    if (rawCentroidPositions == NULL||newk<0){
        return NULL;
    }
    for (int i=0; i<k;i++){
        if (centroids[i]==NULL){
            delete centroids[i];
            centroids[i] = NULL;
        }
    }
    delete[] centroids;
    centroids = NULL;
    k = newk;
    centroids = new DataPoint*[k];
    for (int i=0;i<k;i++){
        centroids[i] = new DataPoint(rawCentroidPositions[i], numAttributes);
    }
    return centroids;
};

DataPoint** Algorithm::getCentroids() const{
    return centroids;
};
GroupInfo* Algorithm::formGroup(int distanceMetric){
    if(distanceMetric<0 || distanceMetric>2){
        distanceMetric = -1;
    }
    GroupInfo* groupsInfo = new GroupInfo;
    groupsInfo->groups = new DataPoint**[k];
    groupsInfo->sizes = new int[k];

    

    for (int i = 0;i<k;i++){
        groupsInfo->groups[i] = new DataPoint*[numberOfDataPoints];
        groupsInfo->sizes[i] = 0;
    }
    for (int i = 0; i < numberOfDataPoints;i++){
        DataPoint* dataPoint = dataPoints[i];

        int closestCentroiIndex = 0;
        float minDistance = (distanceMetric==0)?INFINITY :HUGE_VAL;
        
        for (int j=0; j<k;j++){
            float distance=0.0;
            if (distanceMetric==0){
                distance = DistanceFunction::ManhattanDistance(dataPoint,centroids[j]);
            }else if (distanceMetric==1){
                distance = DistanceFunction :: EuclideanDistance(dataPoint,centroids[j]);
            }
            else if (distanceMetric==2){
                distance = DistanceFunction :: ChebyshevDistance(dataPoint, centroids[j]);
            }else{
                distance = INFINITY;
            }


            if (distance < minDistance){
                minDistance = distance;
                closestCentroiIndex = j;
            };
        }

        int groupSize = groupsInfo-> sizes[closestCentroiIndex];
        groupsInfo -> groups[closestCentroiIndex][groupSize]= dataPoint;
        groupsInfo -> sizes[closestCentroiIndex]++;
    }
    return groupsInfo;

};

DataPoint* Algorithm::averagePositionOfGroup(DataPoint** group, int size) const{
    if (group == NULL || size <= 0) {
        return NULL;
    }

    int numAttributes = group[0]->getNumberOfAttributes();
    float* averageAttrs = new float[numAttributes];

    for (int i = 0; i < numAttributes; i++) {
        averageAttrs[i] = 0.0;
        for (int j = 0; j < size; j++) {
            const float* attrs = group[j]->getAttributes();
            averageAttrs[i] += attrs[i];
        }
        averageAttrs[i] /= size;
    }

    DataPoint* averagePoint = new DataPoint(averageAttrs, numAttributes);
    delete[] averageAttrs;
    return averagePoint;
};

DataPoint** Algorithm::singleRun(int distanceMetric){
    if (centroids == NULL || k <= 0) {
        return NULL;
    }

    DataPoint** newCentroids = new DataPoint*[k];
    
    for (int i = 0; i < k; i++) {
        newCentroids[i] = NULL;
    }
    
    GroupInfo* groupsInfo = formGroup(distanceMetric);

    for (int i = 0; i < k; i++) {
        if (groupsInfo->sizes[i] > 0) {
            DataPoint* average = averagePositionOfGroup(groupsInfo->groups[i], groupsInfo->sizes[i]);
            newCentroids[i] = average;
        }
    }
    

    for (int i = 0; i < k; i++) {
        delete[] groupsInfo->groups[i];
    }
    delete[] groupsInfo->groups;
    delete[] groupsInfo->sizes;
    delete groupsInfo;

    return newCentroids;
};

DataPoint*** Algorithm::fullRun(int distanceMetric, int numberOfIterations){
    if (centroids==NULL||numberOfIterations<0){
        return NULL;
    }

    DataPoint*** centroidHistory = new DataPoint**[numberOfIterations+1];
    centroidHistory[0] = centroids;

    for (int iteration=0;iteration<numberOfIterations;iteration++){

        DataPoint** newCentroids= singleRun(distanceMetric);
        delete[] centroids;
        centroids = newCentroids;

        centroidHistory[iteration +1] =centroids;
    }

    return centroidHistory;
};

int Algorithm::getNumDataPoints() const{
    return numberOfDataPoints;
};
 DataPoint** Algorithm::getDataPoints() const{
    return dataPoints;
};



Algorithm::~Algorithm(){

    for (int i=0; i<numberOfDataPoints; i++){
        delete dataPoints[i];
        dataPoints[i] = NULL; 
    }
    delete[] dataPoints;
    dataPoints = NULL;
    delete[] centroids;
    centroids = NULL;
};

