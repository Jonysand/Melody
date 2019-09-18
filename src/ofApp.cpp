#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(width*2, height);
    guiPanel.setup("Magic Rain");
    
    //-------------
    // falling rain
    //-------------
    srand((unsigned)time(NULL));
    for(int i=0; i<rain_amount; i++){
        int cord_x = rand() % width;
        int cord_y = rand() % height;
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
    guiPanel.add(thresholdValue.set("Threshold Value", 10, 0, 255));
    
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
            obj_Xv = (float(centerX)-float(centerX_old));
            obj_Yv = (float(centerY)-float(centerY_old));
            centerX_old = centerX;
            centerY_old = centerY;
        }
    }
    
    
    
    //-------------
    // falling rain
    //-------------
    for(int i=0; i<rain_amount; i++){
        //----------------
        // velocity update
        //----------------
        if(rains[i][2]<obj_Xv && obj_Xv>0){
            rains[i][2] += g*mag_g;
        }
        if(rains[i][2]>obj_Xv && obj_Xv<0){
            rains[i][2] -= g*mag_g;
        }
        rains[i][0] += int(rains[i][2]*mag_v);
        
        if(rains[i][3]<obj_Yv && obj_Yv>0){
            rains[i][3] += g*mag_g;
        }
        if(rains[i][3]>obj_Yv && obj_Yv<0){
            rains[i][3] -= g*mag_g;
        }
        rains[i][1] += int(rains[i][3]*mag_v);
        
        
        
        if(rains[i][0]>width){
            rains[i][0]=0;
            rains[i][1]=rand()%height;
        }else if(rains[i][0]<0){
            rains[i][0]=width;
            rains[i][1]=rand()%height;
        }
        
        if(rains[i][1]>height){
            rains[i][1]=0;
            rains[i][0]=rand()%width;
        }else if(rains[i][1]<0){
            rains[i][1]=height;
            rains[i][0]=rand()%width;
        }
    }
}








//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0);
    //-------
    // camera
    //-------
    thresholded.draw(width, 0);
    guiPanel.draw();
    
    
    //-------------
    // falling rain
    //-------------
    ofSetColor(255);
    for(int i=0; i<rain_amount; i++){
        ofDrawCircle(int(rains[i][0]), int(rains[i][1]), r);
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
