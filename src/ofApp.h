#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "ofxGui.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        int width = 640;
        int height = 480;
    
        // hand tracking
		ofImage img;
        ofVideoGrabber grabber;
    
        // animation
        ofImage resultImg;
        const static int rain_amount=20;
        vector<int> rains [rain_amount];
        float r = 3;
        float init_v = 3;
        float g = 0.2;
    
        ofxPanel guiPanel;
		ofxCvHaarFinder finder;
};
