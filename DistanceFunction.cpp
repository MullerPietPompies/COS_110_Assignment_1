#include "DistanceFunction.h"
#include "DataPoint.h"

#include <cmath>

float DistanceFunction :: ManhattanDistance(DataPoint* dpA, DataPoint* dpB){
    
    if ((dpA==NULL) || (dpB==NULL)){
        return INFINITY;
    }else if (dpA->getNumberOfAttributes()!=dpB->getNumberOfAttributes()){
        return INFINITY;
    }else{
        const float* Attrs_A = dpA -> getAttributes();
        const float* Attrs_B = dpB -> getAttributes();

        int numAttrs = dpA -> getNumberOfAttributes();

        float distance = 0.0;

        for (int i=0 ; i< numAttrs; i++){
            distance+= std::abs(Attrs_A[i]-Attrs_B[i]);
        }
        return distance;
        }
    

};
float DistanceFunction::EuclideanDistance(DataPoint* dpA, DataPoint* dpB){
    if ((dpA==NULL) || (dpB==NULL)){
        return INFINITY;
    }else if (dpA->getNumberOfAttributes()!=dpB->getNumberOfAttributes()){
        return INFINITY;
    }else{
        const float* Attrs_A = dpA -> getAttributes();
        const float* Attrs_B = dpB -> getAttributes();

        int numAttrs = dpA ->getNumberOfAttributes();

        float distance=0.0;
        float sum = 0.0;

        for (int i=0;i<numAttrs;i++){
            sum +=std::pow((Attrs_A[i]+Attrs_B[i]),2);
        }
        distance = std::sqrt(sum);
        return distance;
    }
};

float DistanceFunction::ChebyshevDistance(DataPoint* dpA, DataPoint* dpB){
    if ((dpA==NULL) || (dpB==NULL)){
        return INFINITY;
    }else if (dpA->getNumberOfAttributes()!=dpB->getNumberOfAttributes()){
        return INFINITY;
    }else{
        const float* AttrA = dpA->getAttributes();
        const float* AttrB = dpB -> getAttributes();
        float temp = 0.0;
        float largest = 0.0;

        int numAttrs = dpA->getNumberOfAttributes();

        for (int i=0; i<numAttrs;i++){
            temp = (std::abs(AttrA[i]-AttrB[i]));
            if (temp>largest)
            {
                largest = temp;
            }   
        }
        return largest;
    }
};