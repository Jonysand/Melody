//
//  aDrop.hpp
//  SM01_YongkunLi
//
//  Created by Yongkun Li on 9/19/19.
//

#ifndef aDrop_hpp
#define aDrop_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#endif /* aDrop_hpp */
class aDrop{
public:
    //-----------
    // properties
    //-----------
    int cord_x;
    int cord_y;
    float cord_d;
    float velocity_x;
    float velocity_y;
    float velocity_d;
    
    
    //----------
    // functions
    //----------
    aDrop();
    aDrop(int x, int y, float d, float vX, float vY, float vD);
    void setVelocity(float vX, float vY, float vD);
    
    void updateThroughVelocity(float g, float target_vX, float target_vY, float target_vD);
    void updateThroughAcceleration(float gX, float gY, float gD);
    
    void updatePosition(float mag_v);
    void setReborn(int winWidth, int winHeight);
    void setRebounce(int winWidth, int winHeight);
    
private:
    bool isOutX = false;
    bool isOutY = false;
    bool isOutD = false;
};
