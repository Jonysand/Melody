# Motion controled Animation - SensingMachine assignment 1
## Demo Videos
<iframe width="560" height="315" src="https://www.youtube.com/embed/0nyqud0FAMk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
>Using color detection

<iframe width="560" height="315" src="https://www.youtube.com/embed/3jMAW00ypwk" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
>Using background subtraction

## Basic Idea
- Use motion to control the pattern on screen.

## Tech detail
### Drops animation
- Randomly generated dots on the screen, using class to create object. Make movements according to the motion.
- Pre-generated strings, plucked by detected fingers.

### Motion tracking
- Background subtraction, set learing time to 0 as to find difference between each frame. Change threshold to 
- Object detection:
	- Color object detection: chose a color interval to detect. (similar to SensingMachine class content)
	- Cascade feature detection: select a proper cascade file for detection. Refer to OpenCV documentation to find more methods, and convert format space between OF and CV.

## Tasks
- train/find hand recognizing models
	- Use background subtraction, to get difference of the current frame and last frame. Then use the center of the difference as the offset. 
		- Average the coordinate of bright/different pixels after BGsubtraction and threshold to get the center. 
- send signal/information to parameters
	- flip the picture
- bouncing animation
	- use hand movements to alter the acceleration
- decrease pixels of the camera, increase pixels of the animation.
- put animation on the left/center, and camera scene on the righ corner.

## notes
- other cascade files that might be useful:<br>
https://github.com/Aravindlivewire/Opencv/tree/master/haarcascade 
- alternative control method: background subtraction with learning
- auto correction algorithm with color object tracking
	- increase the threshold value gradually, then recorde the value when there's one blob, as Min.
	- increase the threshold value gradually, then recorde the value when there's two blob, as Max.
	- use the average of Min and Max as the threshold value

## logs
- /Users/yongkunli/Desktop/OpenFramework/apps/myApps/myBGsub
	- frame offset tracking, works and committed
- /Users/yongkunli/Desktop/OpenFramework/apps/SensingMachines/SM01_YongkunLI
	- regular rain drops, works and committed.

### done:
- simple control works
- flip the camera
- resize the animation & camera
- rebounce effect
- auto correction
	- make an app to generate colors
	- try autocorrection algrithm
### to do:
- generating the drops by a certain gesture.
