//
//  aDrop.cpp
//  SM01_YongkunLi
//
//  Created by Yongkun Li on 9/19/19.
//

#include "aDrop.hpp"

aDrop::aDrop(){};

aDrop::aDrop(int x, int y, float d, float vX, float vY, float vD){
    this->cord_x = x;
    this->cord_y = y;
    this->cord_d = d;
    this->velocity_x = vX;
    this->velocity_y = vY;
    this->velocity_d = vD;
}

void aDrop::setVelocity(float vX, float vY, float vD){
    velocity_x = vX;
    velocity_y = vY;
    velocity_d = vD;
}


void aDrop::updateThroughVelocity(float g, float target_vX, float target_vY, float target_vD){
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
    
    if(velocity_d<target_vD && target_vD>0){
        velocity_d += g;
    }
    if(velocity_d>target_vD && target_vD<0){
        velocity_d -= g;
    }
}


void aDrop::updateThroughAcceleration(float gX, float gY, float gD){
    velocity_x += gX;
    velocity_y += gY;
    velocity_d += gD;
}


void aDrop::updatePosition(float mag_v){
    cord_x += int(velocity_x*mag_v);
    cord_y += int(velocity_y*mag_v);
    cord_d += int(velocity_d*mag_v);
}


void aDrop::setReborn(int winWidth, int winHeight){
    int rand_depth = rand()%winHeight * pow((-1), rand()%2);
    if(cord_x>winWidth){
        cord_x=0;
        cord_y=rand()%winHeight;
        cord_d=rand_depth;
    }else if(cord_x<0){
        cord_x=winWidth;
        cord_y=rand()%winHeight;
        cord_d=rand_depth;
    }
    
    if(cord_y>winHeight){
        cord_y=0;
        cord_x=rand()%winWidth;
        cord_d=rand_depth;
    }else if(cord_y<0){
        cord_y=winHeight;
        cord_x=rand()%winWidth;
        cord_d=rand_depth;
    }
    
    if(cord_d>winHeight){
        cord_d=-winHeight;
        cord_x=rand()%winWidth;
        cord_y=rand()%winHeight;
    }else if(cord_y<0){
        cord_d=winHeight;
        cord_x=rand()%winWidth;
        cord_y=rand()%winHeight;
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
    
    if(cord_d>=winHeight || cord_d<=0){
        if(!isOutD){
            velocity_d *= -1;
            isOutD=true;
        }
    }else{
        isOutD=false;
    }
}
