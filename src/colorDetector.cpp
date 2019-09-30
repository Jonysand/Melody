//
//  colorDetector.cpp
//  SM01_YongkunLI
//
//  Created by Yongkun Li on 9/25/19.
//

#include "colorDetector.hpp"

colorDetector::colorDetector(){};

colorDetector::colorDetector(int width, int height){
    this->width = width;
    this->height = height;
    // Setup my parameters
    processedImage.allocate(width, height, OF_IMAGE_COLOR);
    colorThreshold.set("Color Threshold", 10, 0, 255);
    targetColor.set("Target Color", ofColor(0, 255, 0));
    minAreaContour.set("Min Area", 0.01, 0, 0.25);
    maxAreaContour.set("Max Area", 0.2, 0, 0.25);
    blurAmount.set("Blur Size", 20, 0, 100);
    DrawBlur.set("Draw Blur", true);
    erodeIterations.set("Erode Image", 1, 0, 20);
    maxTrackDistance.set("Max Track Distance", 50, 0, 200);
    persistance.set("Persistance", 10, 0, 600);
    
    // Setup the gui.
    guiPanel.setup("Object Tracker", "settings.json");
    guiPanel.add(targetColor);
    guiPanel.add(colorThreshold);
    guiPanel.add(minAreaContour);
    guiPanel.add(maxAreaContour);
    guiPanel.add(blurAmount);
    guiPanel.add(erodeIterations);
    guiPanel.add(maxTrackDistance);
    guiPanel.add(persistance);
    guiPanel.add(DrawBlur);
}

void colorDetector::pickColor(int x, int y, ofVideoGrabber grabber){
    mouseColor = grabber.getPixels().getColor(x, y);
    targetColor = mouseColor;
}

tuple<float, float> colorDetector::detectMove(ofVideoGrabber grabber){
    float obj_X = 0;
    float obj_Y = 0;
    
    // config contourFinder
    contourFinder.setTargetColor(targetColor, ofxCv::TRACK_COLOR_HSV);
    contourFinder.setThreshold(colorThreshold);
    contourFinder.setMinAreaNorm(minAreaContour);
    contourFinder.setMaxAreaNorm(maxAreaContour);
    
    // process the image
    ofPixels imagePix = grabber.getPixels();
    
    imagePix.mirror(false, true);
    
    ofxCv::GaussianBlur(imagePix, processedImage, blurAmount);
    ofxCv::erode(processedImage, processedImage, erodeIterations);
    
    contourFinder.getTracker().setMaximumDistance(maxTrackDistance);
    contourFinder.getTracker().setPersistence(persistance);
    
    contourFinder.findContours(processedImage);
    
    //get target information
    if(startDetect){
        cv::Vec2f result = contourFinder.getTracker().getVelocity(0);
        obj_X = result[0];
        obj_Y = result[1];
    }
    
    return make_tuple(obj_X, obj_Y);
}

void colorDetector::draw(ofVideoGrabber grabber, int winWidth, int winHeight){
    ofSetColor(255);
    
    // Draw the grabber image.
    if(DrawBlur){
        processedImage.update();
        processedImage.draw(0,0);
    }
    else{
        grabber.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

    contourFinder.draw();
    for(int i=0;i<contourFinder.size();i++){
        int label = contourFinder.getLabel(i);
        ofVec2f center = ofxCv::toOf(contourFinder.getCenter(i));
        //cv::Point2f center =  contourFinder.getCenter(i);
        ofDrawBitmapString(label, center.x, center.y);
    }
    
    // Draw the gui.
//    guiPanel.draw();
}

void colorDetector::autoCorrectThreshold(ofVideoGrabber grabber){
    int Min;
    int Max;
    grabber.update();
    
    // find Min
    for(int i=0;i<255;i++){
        contourFinder.setThreshold(i);
        ofPixels imagePix = grabber.getPixels();
        ofxCv::GaussianBlur(imagePix, processedImage, blurAmount);
        ofxCv::erode(processedImage, processedImage, erodeIterations);
        contourFinder.findContours(processedImage);
        if(contourFinder.size()>=1){
            Min = i;
            cout<<contourFinder.size()<<endl;
            break;
        }
    }
    
    //find Max
    for(int i=Min;i<255;i++){
        contourFinder.setThreshold(i);
        ofPixels imagePix = grabber.getPixels();
        ofxCv::GaussianBlur(imagePix, processedImage, blurAmount);
        ofxCv::erode(processedImage, processedImage, erodeIterations);
        contourFinder.findContours(processedImage);
        if(contourFinder.size()>=2){
            Max = i;
            cout<<contourFinder.size()<<endl;
            break;
        }
    }
    
    colorThreshold = (Max+Min)/2;
    startDetect = true;
}
