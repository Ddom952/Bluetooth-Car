
#include "fsl_ftm.h"
#include "fsl_gpio.h"
#include "drive.h"

#define WHEEL_LEFT_CHNL					(kFTM_Chnl_1)
#define WHEEL_RIGHT_CHNL				(kFTM_Chnl_7)
#define GPIO_DIR_LEFT					((GPIO_Type *) PTC)
#define PIN_DIR_LEFT					(3U)
#define GPIO_DIR_RIGHT					((GPIO_Type *) PTB)
#define PIN_DIR_RIGHT					(23U)

struct wheel_data {
	uint8_t speed;
	e_wheel_direction wheel_direction;
};

typedef struct wheel_data t_wheel_data;

struct struct_drive_data {
	t_wheel_data left;
	t_wheel_data right;
};

typedef struct struct_drive_data t_drive_data;

static t_drive_data drive_data;

void DriveInit(void)
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParam[2];

/* Configures pins */
	/* PWM output */
	gpio_pin_config_t dir_pin_config =
	{
		kGPIO_DigitalOutput,
		1
	};

	GPIO_PinInit( GPIO_DIR_LEFT, PIN_DIR_LEFT, &dir_pin_config );

	GPIO_PinInit( GPIO_DIR_RIGHT, PIN_DIR_RIGHT, &dir_pin_config );

	GPIO_ClearPinsOutput(GPIO_DIR_LEFT, 1U << PIN_DIR_LEFT);

/* Configures the FTM parameters with frequency 4 kHZ */
	ftmParam[0].chnlNumber = WHEEL_LEFT_CHNL;
	ftmParam[0].level = kFTM_HighTrue;
	ftmParam[0].dutyCyclePercent = 0U;
	ftmParam[0].firstEdgeDelayPercent = 0U;

	ftmParam[1].chnlNumber = WHEEL_RIGHT_CHNL;
	ftmParam[1].level = kFTM_HighTrue;
	ftmParam[1].dutyCyclePercent = 0U;
	ftmParam[1].firstEdgeDelayPercent = 0U;

	FTM_GetDefaultConfig(&ftmInfo);

/* Initializes the FTM module. */
	FTM_Init( (FTM_Type *) FTM0, &ftmInfo);

	FTM_SetupPwm( (FTM_Type *) FTM0, ftmParam, 2U,
		kFTM_EdgeAlignedPwm, 500U, CLOCK_GetFreq(kCLOCK_BusClk));
	FTM_StartTimer( (FTM_Type *) FTM0, kFTM_SystemClock);

	FTM_SetSoftwareTrigger( (FTM_Type *) FTM0_BASE, true);

	drive_data.left.speed = 0U;
	drive_data.left.wheel_direction = FORWARD;
	drive_data.right.speed = 0U;
	drive_data.right.wheel_direction = FORWARD;
}

void DriveChangeWheelDirection( e_wheel wheel, e_wheel_direction direction)
{
	switch(wheel)
	{
	case WHEEL_RIGHT:
		switch(direction)
		{
		case FORWARD:
			GPIO_SetPinsOutput(GPIO_DIR_RIGHT, 1U << PIN_DIR_RIGHT);
			break;
		case BACK:
			GPIO_ClearPinsOutput(GPIO_DIR_RIGHT, 1U << PIN_DIR_RIGHT);
			break;
		}
		drive_data.right.wheel_direction = direction;
		break;
	case WHEEL_LEFT:
		switch(direction)
		{
		case FORWARD:
			GPIO_SetPinsOutput(GPIO_DIR_LEFT, 1U << PIN_DIR_LEFT);
			break;
		case BACK:
			GPIO_ClearPinsOutput(GPIO_DIR_LEFT, 1U << PIN_DIR_LEFT);
			break;
		}
		drive_data.left.wheel_direction = direction;
		break;
	}
};

void DriveChangeWheelSpeed( e_wheel wheel, uint8_t speed)
{
	if (speed < 15U)
		speed = 0U;
	else if (speed > 80U)
		speed = 80U;

	switch(wheel)
	{
	case WHEEL_RIGHT:
		FTM_UpdatePwmDutycycle( (FTM_Type *) FTM0_BASE, WHEEL_RIGHT_CHNL,
			kFTM_EdgeAlignedPwm, speed);
		drive_data.right.speed = speed;
		break;
	case WHEEL_LEFT:
		FTM_UpdatePwmDutycycle( (FTM_Type *) FTM0_BASE, WHEEL_LEFT_CHNL,
			kFTM_EdgeAlignedPwm, speed);
		drive_data.left.speed = speed;
		break;
	}

	FTM_SetSoftwareTrigger( (FTM_Type *) FTM0_BASE, true);
};




