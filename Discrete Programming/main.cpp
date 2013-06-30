//
//  main.cpp
//  Discrete Programming
//
//  Created by Anton Pütz on 29.06.13.
//  Copyright (c) 2013 Anton Pütz. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


int itemAmount;
int capacity;
std::vector<int> values;
std::vector<int> weights;
bool error =false;


std::vector<std::string> tokenizeLine(std::string input){
    
    std::stringstream liness(input);
    std::string segment;
    
    std::vector<std::string> segment_list;
    while (getline(liness, segment,' ')) {
        if(segment!=""){
            segment_list.push_back(segment);
        }
    }
    
    return segment_list;
    
}

void readInputFile(std::string pathToFile){
    
    std::ifstream myfile;
    myfile.open(pathToFile.c_str(), std::ifstream::in);
    
    int lineNumber =0;
    std::string line;
    
    
    
    if(myfile.is_open())
    {
        while (myfile.good()) {
            
            
            
            getline(myfile,line);
            std::vector<std::string> segment_list = tokenizeLine(line);
            
            if(lineNumber==0){
                //read number of items and knapsack capacity
                itemAmount = atoi(segment_list[0].c_str());
                capacity = atoi(segment_list[1].c_str());
                
            }else{
                
                //read items
                if(lineNumber<itemAmount+1){
                    weights.push_back(atoi(segment_list[1].c_str()));
                    values.push_back(atoi(segment_list[0].c_str()));
                }
                }
            
    //        std::cout << line <<std::endl;
            lineNumber++;
        
            
        }
        
        myfile.close();
    }
    else{
     std::cout << "Unable to open file"<<std::endl;
        error=true;
    }
    
}

void processInputFile(){
    //do the calculation
    
    std::vector<std::vector<int>> computeTable(itemAmount+1,std::vector<int>(capacity+1));
    
    
    for (int i=0; i<=capacity; i++) {
        computeTable[0][i]=0; //Initialize 0 column
    }
    
    //Calculate Values-Table
    
    for (int i=1; i<=itemAmount; i++) {
        for (int j=0; j<=capacity; j++) {
            if(j>= weights[i-1]){
                computeTable[i][j]= std::max(computeTable[i-1][j], computeTable[i-1][j-weights[i-1]]+values[i-1]);
            }
            else{
                computeTable[i][j] = computeTable[i-1][j];
            }
        }
    }
    
    
    
    //Calculate Result (traceback)
    std::vector<int> taken(itemAmount);
    
  /*
    //print table contents
    for (int i=0; i<=capacity; i++) {
        
        std::cout << i<<"| ";
        
        for (int j=0; j<=itemAmount; j++) {
            std::cout << computeTable[j][i]<<' ';
        }
        std::cout << std::endl;
    }
    */
    
    int capacityUsed=capacity;
    int currentItem = itemAmount-1;
    
    while(capacityUsed>0){
        
        if(computeTable[itemAmount][capacity]>computeTable[currentItem][capacity]){
            taken[currentItem]=1;
            capacityUsed=capacityUsed-weights[currentItem];
        }
        
        currentItem--;
        
    }
    
    std::cout<< computeTable[itemAmount][capacity]<<' '<<0<<std::endl;
    
    for (int i=0; i<itemAmount; i++) {
        std::cout << taken[i]<<' ';
    }
    
    std::cout << std::endl;

}


int main(int argc, const char * argv[])
{
    // insert code here...
    if(argc<2){
        std::cout << "Please provide a filename to process!!"<<std::endl;
        return 1;
    }
    
    readInputFile(argv[1]);
    if(!error){
        processInputFile();
        return 0;
    }
    else{
        return 1;
    }
    
    
}