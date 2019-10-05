//
//  kinectBgsDetector.hpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 10/5/19.
//

#ifndef kinectBgsDetector_hpp
#define kinectBgsDetector_hpp

#include <stdio.h>

#endif /* kinectBgsDetector_hpp */

#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "bgsDetector.hpp"

class kinectBgsDetector: public bgsDetector{
public:
    int depth;
    float centerD;
    float centerD_old;
    
    ofxCv::RunningBackground backgroundDepth;
    ofImage thresholdedDepth;
    ofPixels thre_pixDepth;
    
    int nearThreshold;
    int farThreshold;
    
    kinectBgsDetector();
    kinectBgsDetector(int winWidth, int winHeight, int winDepth, int width, int height, int depth);
    tuple<float, float, float> getDetectMove(const ofxKinect & kinect);
};
