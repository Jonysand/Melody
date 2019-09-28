//
//  bgsDetector.hpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 9/24/19.
//

#ifndef bgsDetector_hpp
#define bgsDetector_hpp

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

#ifndef aDrop_hpp
#include "aDrop.hpp"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#endif /* bgsDetector_hpp */

class bgsDetector{
public:
    //----------
    //properties
    //----------
    int width, height;
    ofxPanel guiPanel;
    ofxCv::RunningBackground background;
    ofImage thresholded;
    ofParameter<float> thresholdValue;
    ofPixels thre_pix;
    float centerX;
    float centerY;
    float centerX_old;
    float centerY_old;
    
    //--------
    //funtions
    //--------
    bgsDetector();
    bgsDetector(int winWidth, int winHeight, int width, int height);
    
    tuple<float, float> detectMove(ofVideoGrabber cam);
    
    void draw(int winWidth, int winHeight);
};
