#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(winWidth, winHeight);
    guiPanel.setup("Magic Rain");
    
    //-------------
    // falling drops
    //-------------
    srand((unsigned)time(NULL));
    for(int i=0; i<drops_amount; i++){
        aDrop drop(rand()%winWidth, rand()%winHeight, init_v, init_v);
        drops[i] = drop;
    }
    
    
    //----------------
    // offset tracking
    //----------------
    cam.setup(width, height);
    thresholded.allocate(width, height, OF_IMAGE_GRAYSCALE);
    centerX = width/2;
    centerY = height/2;
    centerX_old = width/2;
    centerY_old = height/2;
    guiPanel.add(resetBackground.set("Reset Background", false));
    guiPanel.add(learningTime.set("Learning Time", 0, 0, 30));
    guiPanel.add(thresholdValue.set("Threshold Value of BGsub", 70, 0, 255));
}





//--------------------------------------------------------------
void ofApp::update(){
    //----------------
    // offset tracking
    //----------------
    cam.update();
    if(resetBackground) {
        background.reset();
        resetBackground = false;
    }
    if(cam.isFrameNew()) {
        background.setLearningTime(learningTime);
        background.setThresholdValue(thresholdValue);
        background.update(cam, thresholded);
        thresholded.mirror(false, true);
        thresholded.update();

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
            // update target X&Y
            obj_X = centerX-centerX_old;
            obj_Y = centerY-centerY_old;
            centerX_old = centerX;
            centerY_old = centerY;
        }
    }
    
    
    
    //-------------
    // falling rain
    //-------------
    for(int i=0; i<drops_amount; i++){
        //----------------
        // movement control
        //----------------
        
        // 1. update velocity
        drops[i].updateThroughVelocity(g*mag_g, obj_X, obj_Y);
    
        // 2. update acceleration
//        drops[i].updateThroughAcceleration(obj_X, obj_Y);
        
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
    thresholded.draw(winWidth-width, winHeight-height);
    guiPanel.draw();
    
    
    //-------------
    // falling drops
    //-------------
    ofSetColor(255);
    for(int i=0; i<drops_amount; i++){
        ofDrawEllipse(drops[i].cord_x, drops[i].cord_y, r, r);
    }
}









//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g'){
        if(mag_v<=2){
            mag_v += 0.1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    mag_v = 1;
}
