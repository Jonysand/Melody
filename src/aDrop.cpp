//
//  aDrop.cpp
//  SM01_YongkunLi
//
//  Created by Yongkun Li on 9/19/19.
//

#include "aDrop.hpp"

aDrop::aDrop(){};

aDrop::aDrop(int x, int y, float vX, float vY){
    this->cord_x = x;
    this->cord_y = y;
    this->velocity_x = vX;
    this->velocity_y = vY;
}

void aDrop::setVelocity(float vX, float vY){
    velocity_x = vX;
    velocity_y = vY;
}


void aDrop::updateThroughVelocity(float g, float target_vX, float target_vY){
    if(velocity_x<target_vX && target_vX>0){
        velocity_x += g;
    }
    if(velocity_x>target_vX && target_vX<0){
        velocity_x -= g;
    }
    
    if(velocity_y<target_vY && target_vY>0){
        velocity_y += g;
    }
    if(velocity_y>target_vY && target_vY<0){
        velocity_y -= g;
    }
}

void aDrop::updateThroughAcceleration(float gX, float gY){
    velocity_x += gX;
    velocity_y += gY;
}


void aDrop::updatePosition(float mag_v){
    cord_x += int(velocity_x*mag_v);
    cord_y += int(velocity_y*mag_v);
}


void aDrop::setReborn(int winWidth, int winHeight){
    if(cord_x>winWidth){
        cord_x=0;
        cord_y=rand()%winHeight;
    }else if(cord_x<0){
        cord_x=winWidth;
        cord_y=rand()%winHeight;
    }
    
    if(cord_y>winHeight){
        cord_y=0;
        cord_x=rand()%winWidth;
    }else if(cord_y<0){
        cord_y=winHeight;
        cord_x=rand()%winWidth;
    }
}

void aDrop::setRebounce(int winWidth, int winHeight){
    if(cord_x>=winWidth || cord_x<=0){
        if(!isOutX){
            velocity_x *= -1;
            isOutX=true;
        }
    }else{
        isOutX=false;
    }
    
    if(cord_y>=winHeight || cord_y<=0){
        if(!isOutY){
            velocity_y *= -1;
            isOutY=true;
        }
    }else{
        isOutY=false;
    }
}
