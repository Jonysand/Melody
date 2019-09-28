#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(winWidth, winHeight);
    //-------------
    // generating drops
    //-------------
    srand((unsigned)time(NULL));
    for(int i=0; i<drops_amount; i++){
        aDrop drop(rand()%winWidth, rand()%winHeight, init_v, init_v);
        drops[i] = drop;
    }
    
    cam.setup(width, height);
    
    // background subtracktion
//    BGSdetector = bgsDetector(winWidth, winHeight, width, height);
    // color object detection
    COLORdetector = colorDetector(width, height);
}


//--------------------------------------------------------------
void ofApp::update(){
    //----------------
    // offset tracking
    //----------------
    cam.update();
    if(cam.isFrameNew()) {
        // background subtracktion
//        auto obj_result = BGSdetector.detectMove(cam);
        auto obj_result = COLORdetector.detectMove(cam);
        obj_X = get<0>(obj_result);
        obj_Y = get<1>(obj_result);
    }
    
    
    //-------------
    // falling rain
    //-------------
    for(int i=0; i<drops_amount; i++){
        //----------------
        // movement control
        //----------------
        
        // update velocity
        drops[i].updateThroughVelocity(g*mag_g, obj_X, obj_Y);
        
        // update position
        drops[i].updatePosition(mag_v);
        

        //---------------
        // touch window border
        //---------------
        
        // go outside and reborn
//        drops[i].setReborn(winWidth, winHeight);
        
        // rebounce
        drops[i].setRebounce(winWidth, winHeight);
    }
}






//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0);
    //-------
    // camera
    //-------
//    BGSdetector.draw(winWidth, winHeight);
    COLORdetector.draw(cam, winWidth, winHeight);
//    guiPanel = COLORdetector.guiPanel;
//    guiPanel.draw();
    
    
    //-------------
    // falling drops
    //-------------
    ofSetColor(255);
    for(int i=0; i<drops_amount; i++){
        ofDrawEllipse(drops[i].cord_x, drops[i].cord_y, r, r);
    }
}

void ofApp::mousePressed(int x, int y, int button){
    COLORdetector.pickColor(x, y, cam);
    COLORdetector.autoCorrectThreshold(cam);
}
