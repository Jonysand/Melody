#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "aDrop.hpp"

// method of tracking
#include "bgsDetector.hpp"
#include "colorDetector.hpp"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void mousePressed(int x, int y, int button);
        void keyPressed(int key);
    
        int winWidth = 1440;
        int winHeight = 900;
        int width = 640;
        int height = 480;
    
        // offset tracking
        ofVideoGrabber cam;
    
        bgsDetector BGSdetector;
        colorDetector COLORdetector;
    
        // animation
        const static int drops_amount=40;
        aDrop drops [drops_amount];
        // radius of the rain drop
        float r = 6;
        // initial velocity
        float init_v = 0;
        // threshold distance for drawing a line
        int line_thresh = 300;
        // objective velocity
        float obj_X = 0;
        float obj_Y = 0;
        float obj_D = -1;
        // magnification of velocity&acceleration
        float mag_v = 1;
        float mag_g = 1;
        // initial acceleration
        float g = 0.5;
};
