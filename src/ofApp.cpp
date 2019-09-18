#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(winWidth, winHeight);
    guiPanel.setup("Magic Rain");
    
    //-------------
    // falling rain
    //-------------
    srand((unsigned)time(NULL));
    for(int i=0; i<rain_amount; i++){
        int cord_x = rand() % winWidth;
        int cord_y = rand() % winHeight;
        vector<float> drop;
        // drop -> {cord_x, cord_y, velovcity_x, velocity_y}
        drop.push_back(cord_x);
        drop.push_back(cord_y);
        drop.push_back(init_v);
        drop.push_back(init_v);
        rains[i] = drop;
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
    guiPanel.add(thresholdValue.set("Threshold Value of BGsub", 80, 0, 255));
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
            // update objective velocity
            obj_Xv = float(centerX)-float(centerX_old);
            obj_Yv = float(centerY)-float(centerY_old);
            centerX_old = centerX;
            centerY_old = centerY;
        }
    }
    
    
    
    //-------------
    // falling rain
    //-------------
    for(int i=0; i<rain_amount; i++){
        //----------------
        // movement control
        //----------------
        // 1. update velocity
        if(rains[i][2]<obj_Xv && obj_Xv>0){
            rains[i][2] += g*mag_g;
        }
        if(rains[i][2]>obj_Xv && obj_Xv<0){
            rains[i][2] -= g*mag_g;
        }

        if(rains[i][3]<obj_Yv && obj_Yv>0){
            rains[i][3] += g*mag_g;
        }
        if(rains[i][3]>obj_Yv && obj_Yv<0){
            rains[i][3] -= g*mag_g;
        }
    
        // 2. update acceleration
//        rains[i][2] += 10*obj_Xv/width;
//        rains[i][3] += 10*obj_Yv/height;
        
        rains[i][0] += int(rains[i][2]*mag_v);
        rains[i][1] += int(rains[i][3]*mag_v);
        
        
        // outside window
        if(rains[i][0]>winWidth){
            rains[i][0]=0;
            rains[i][1]=rand()%winHeight;
        }else if(rains[i][0]<0){
            rains[i][0]=winWidth;
            rains[i][1]=rand()%winHeight;
        }
        
        if(rains[i][1]>winHeight){
            rains[i][1]=0;
            rains[i][0]=rand()%winWidth;
        }else if(rains[i][1]<0){
            rains[i][1]=winHeight;
            rains[i][0]=rand()%winWidth;
        }
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
    // falling rain
    //-------------
    ofSetColor(255);
    for(int i=0; i<rain_amount; i++){
        ofDrawEllipse(int(rains[i][0]), int(rains[i][1]), r, r);
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
