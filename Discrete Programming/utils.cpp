//
//  tokenizeLine.cpp
//  Discrete Programming
//
//  Created by Anton Pütz on 03.07.13.
//  Copyright (c) 2013 Anton Pütz. All rights reserved.
//

#include "utils.h"

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
