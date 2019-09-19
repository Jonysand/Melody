#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "aDrop.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
    
        int winWidth = 1440;
        int winHeight = 900;
        int width = 640;
        int height = 480;
        ofxPanel guiPanel;
    
        // offset tracking
        ofVideoGrabber cam;
        ofxCv::RunningBackground background;
        ofImage thresholded;
        ofParameter<bool> resetBackground;
        ofParameter<float> learningTime, thresholdValue;
        ofPixels thre_pix;
        float centerX;
        float centerY;
        float centerX_old;
        float centerY_old;
    
        // animation
        ofImage resultImg;
        const static int drops_amount=40;
        aDrop drops [drops_amount];
        // radius of the rain drop
        float r = 6;
        // initial velocity
        float init_v = 0;
        float obj_X = 0;
        float obj_Y = 0;
        // magnification of velocity&acceleration
        float mag_v = 1;
        float mag_g = 1;
        // initial acceleration
        float g = 0.5;
};
