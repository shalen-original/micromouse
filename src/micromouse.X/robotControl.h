// guard condition  
#ifndef ROBOT_H
#define	ROBOT_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef enum // movement state of robot
{
    IDLE=0,
    MOVE,
    TURNL,
    TURNR
} movementState;

typedef enum // environement state of robot (where are walls)
{
    LRWALL=0,
    LWALL,
    RWALL,
    NWALL
} envState;


// setups the initial robot configuration
void initRobot(void);

// is called whenever the sensors are read
void onSensorUpdate(float timeInterval, unsigned int sensorFront, unsigned int sensorLeft, unsigned int sensorRight);
// sets the rotation value of the robot (in a 8-axis system) and all corresponding changes
void setRotation(dir direction);
// sets the movement state and all corresponding changes
void setMovState(movementState state);
// checks whether the robot has proceeded in a cell position, if yes: updates maze map and robot position
void checkCellChange(void);

#endif	/* ROBOT_H */

