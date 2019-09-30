//
//  bgsDetector.cpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 9/24/19.
//

#include "bgsDetector.hpp"

bgsDetector::bgsDetector(){};

bgsDetector::bgsDetector(int winWidth, int winHeight, int width, int height){
    this->width = width;
    this->height = height;
    thresholded.allocate(width, height, OF_IMAGE_GRAYSCALE);
    centerX = width/2;
    centerY = height/2;
    centerX_old = width/2;
    centerY_old = height/2;
    
    guiPanel.setup("Magic Drop");
    background.setLearningTime(0);
    thresholdValue.set("Threshold Value of BGsub", 70, 0, 255);
    guiPanel.add(thresholdValue);
}

tuple<float, float> bgsDetector::detectMove(ofVideoGrabber cam){
    float obj_X = 0;
    float obj_Y = 0;
    
    background.setThresholdValue(thresholdValue);
    background.update(cam, thresholded);
    thresholded.mirror(false, true);
    
    int sumX = 0;
    int sumY = 0;
    int count = 0;
    // find center of the difference
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
    
    return make_tuple(obj_X, obj_Y);
}

void bgsDetector::draw(int winWidth, int winHeight){
    thresholded.update();
    thresholded.draw(winWidth-width, winHeight-height);
//    guiPanel.draw();
}
