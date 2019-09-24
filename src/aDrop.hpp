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

#endif /* aDrop_hpp */
class aDrop{
public:
    //-----------
    // properties
    //-----------
    int cord_x;
    int cord_y;
    float velocity_x;
    float velocity_y;
    
    
    //----------
    // functions
    //----------
    aDrop();
    aDrop(int x, int y, float vX, float vY);
    void setVelocity(float vX, float vY);
    
    void updateThroughVelocity(float g, float target_vX, float target_vY);
    void updateThroughAcceleration(float gX, float gY);
    
    void updatePosition(float mag_v);
    void setReborn(int winWidth, int winHeight);
    void setRebounce(int winWidth, int winHeight);
    
private:
    bool isOutX = false;
    bool isOutY = false;
};
