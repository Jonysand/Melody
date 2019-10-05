//
//  kinectBgsDetector.cpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 10/5/19.
//

#include "kinectBgsDetector.hpp"

kinectBgsDetector::kinectBgsDetector(){}

kinectBgsDetector::kinectBgsDetector(int winWidth, int winHeight, int winDepth, int width, int height, int depth){
    this->width = width;
    this->height = height;
    this->depth = depth;
    thresholded.allocate(width, height, OF_IMAGE_GRAYSCALE);
    thresholdedDepth.allocate(width, height, OF_IMAGE_GRAYSCALE);
    
    nearThreshold = 230;
    farThreshold = 70;
    
    centerX = width/2;
    centerY = height/2;
    centerD = 0;
    centerX_old = width/2;
    centerY_old = height/2;
    centerD_old = 0;
    
    guiPanel.setup("Magic Drop");
    thresholdValue.set("Threshold Value of BGsub", 70, 0, 255);
    
    background.setLearningTime(0);
    backgroundDepth.setLearningTime(0);
    background.setThresholdValue(thresholdValue);
    backgroundDepth.setThresholdValue(thresholdValue);
    
    guiPanel.add(thresholdValue);
}

tuple<float, float, float> kinectBgsDetector::getDetectMove(const ofxKinect & kinect){
    float obj_X = 0;
    float obj_Y = 0;
    float obj_D = 0;
    
    background.update(kinect.getPixels(), thresholded);
    thresholded.mirror(false, true);
    int sumX = 0;
    int sumY = 0;
    int sumD = 0;
    int count = 0;
    
    // find center of the difference in 2D
    thre_pix = thresholded.getPixels();
    for(int i=0; i<(width*height); i++){
        if(thre_pix.getColor(i)==ofColor(255)){
            sumX += i%width;
            sumY += i/height;
            count ++;
        }
    }
    if(count!=0){
        // update offset center, using 1/2 filter
        centerX = (sumX/count+centerX_old)/2;
        centerY = (sumY/count+centerY_old)/2;
        obj_X = centerX-centerX_old;
        obj_Y = centerY-centerY_old;
        // update target X&Y
        centerX_old = centerX;
        centerY_old = centerY;
    }
    
    // find difference in depth
    thre_pixDepth = kinect.getDepthPixels();
    for(int i=0; i<(width*height); i++){
        sumD += thre_pixDepth.getColor(i).getLightness();
    }
    centerD = (sumD/(width*height)+centerD_old)/2;
    obj_D = centerD-centerD_old;
    centerD_old = centerD;
    
    return make_tuple(obj_X, obj_Y, obj_D);
}
