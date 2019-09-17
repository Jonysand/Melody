#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(width, height);
    guiPanel.setup("Hand Detection");
    
    // hand detecting
//    grabber.setup(width, hright);
//    finder.setup("haarcascade_eye_tree_eyeglasses.xml");
    
    // falling rain
    srand((unsigned)time(NULL));
    for(int i=0; i<rain_amount; i++){
        int cord_x = rand() % width;
        int cord_y = rand() % height;
        vector<int> drop;
        drop.push_back(cord_x);
        drop.push_back(cord_y);
        drop.push_back(init_v);
        rains[i] = drop;
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // hand detecting
//    grabber.update();
//    img.setFromPixels(grabber.getPixels());
//    finder.findHaarObjects(img);
//    img.update();
    
    // falling rain
    for(int i=0; i<rain_amount; i++){
        rains[i][2]+=g;
        rains[i][1]+=rains[i][2];
        if(rains[i][1]>=height){
            rains[i][1]=0;
            rains[i][0]=rand() % width;
            rains[i][2]=init_v;
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColor(0);
//    img.draw(0, 0);
//    ofNoFill();
//    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
//        ofRectangle cur = finder.blobs[i].boundingRect;
//        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);
//    }
    
    // falling rain
    ofSetColor(255);
    for(int i=0; i<rain_amount; i++){
        ofDrawCircle(rains[i][0], rains[i][1], r);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
