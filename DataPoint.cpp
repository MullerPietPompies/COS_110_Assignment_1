#include "DataPoint.h"
#include <iostream>
#include <sstream>

DataPoint::DataPoint(std::string line){
    numberOfAttributes =0;
        int count = 0;

        for (std::string::size_type i =0; i < line.size();i++){
            char c = line[i];
            if (c == ','){
                numberOfAttributes++;
            }
            count++;
            if (c ==')'){
                break;
            }
        }

        attributes = new float[numberOfAttributes];

        std::istringstream ss(line);
        char c_2;

        for (int i=0 ; i< numberOfAttributes;i++){
            ss>>c_2;
            ss>>attributes[i];

        }
}
DataPoint::DataPoint(DataPoint *other){
    if (other == NULL){
        attributes = NULL;
        numberOfAttributes = 0;
    } else{
        numberOfAttributes = other -> numberOfAttributes;
        if (numberOfAttributes > 0){
            attributes = new float[numberOfAttributes];
            for (int i=0; i<numberOfAttributes; i++){
                attributes[i] = other -> attributes[i];
            }
        }else{
            attributes = NULL;
        }
    }
 
}
DataPoint::DataPoint(float *attrs, int numAttrs){
        if (attrs==NULL || numAttrs <= 0){
            attributes = NULL;
            numberOfAttributes =0;
        }else{
            numberOfAttributes = numAttrs;
            attributes = new float[numberOfAttributes];
            for (int i = 0; i < numberOfAttributes; i++)
            {
                attributes[i] = attrs[i];
            }
            
        }
    }

DataPoint::~DataPoint(){
    delete[] attributes;
}

float* DataPoint::getAttributes(){
    return attributes;
}
int DataPoint::getNumberOfAttributes(){
    return numberOfAttributes;
}