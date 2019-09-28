//
//  colorDetector.hpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 9/25/19.
//

#ifndef colorDetector_hpp
#define colorDetector_hpp

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

#include <stdio.h>

#endif /* colorDetector_hpp */

class colorDetector{
public:
    //----------
    //properties
    //----------
    int width, height;
    bool startDetect = false;
    
    ofxCv::ContourFinder contourFinder;
    
    ofColor mouseColor;
    ofImage processedImage;
    
    ofParameter<ofColor> targetColor;
    ofParameter<int> colorThreshold;
    ofParameter<float> minAreaContour;
    ofParameter<float> maxAreaContour;
    ofParameter<int> blurAmount;
    ofParameter<bool> DrawBlur;
    ofParameter<int> erodeIterations;
    ofParameter<int> maxTrackDistance;
    ofParameter<int> persistance;
    
    ofxPanel guiPanel;
    
    
    
    //----------
    //functions
    //----------
    colorDetector();
    colorDetector(int width, int height);
    
    // pick color under the mouse when clicked
    void pickColor(int x, int y, ofVideoGrabber grabber);
    
    // detect and track the object
    tuple<float, float> detectMove(ofVideoGrabber grabber);
    
    //draw the (processed)image
    void draw(ofVideoGrabber grabber, int winWidth, int winHeight);
    
    //auto correction threshold value
    void autoCorrectThreshold(ofVideoGrabber grabber);
};
