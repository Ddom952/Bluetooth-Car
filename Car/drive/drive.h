#ifndef _DRIVE_H_
#define _DRIVE_H_

typedef enum enum_wheel_direction { FORWARD, BACK } e_wheel_direction;

typedef enum enum_wheel { WHEEL_RIGHT, WHEEL_LEFT } e_wheel;

void DriveInit(void);
void DriveChangeWheelDirection( e_wheel wheel, e_wheel_direction direction);
void DriveChangeWheelSpeed( e_wheel wheel, uint8_t speed);

#endif /* _DRIVE_H_ */
