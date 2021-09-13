/** A wrapper for the Joyshock library for Game Maker Studio 2 to allow for more elaborate controller inputs such as gyro*/

#include "JoyShockLibrary.h"
#include <string>

#if _MSC_VER // this is defined when compiling with Visual Studio
#define func extern "C" __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define func // XCode does not need annotating exported functions, so define is empty
#endif

func double JslImplConnectDevices() {
	return JslConnectDevices();
}
/* TODO: Not sure of the best way to handle this in GM
func double JslImplGetConnectedDeviceHandles(int* deviceHandleArray, int size) {
	return JslGetConnectedDeviceHandles(deviceHandleArray, size);
}
*/
func double JslImplDisconnectAndDisposeAll() {
	JslDisconnectAndDisposeAll();
	return true;
}

// get thumbsticks
func double JslImplGetLeftX(double deviceId) {
	return JslGetLeftX(deviceId);
}

func double JslImplGetLeftY(double deviceId) {
	return JslGetLeftY(deviceId);
}

func double JslImplGetRightX(double deviceId) {
	return JslGetRightX(deviceId);
}

func double JslImplGetRightY(double deviceId) {
	return JslGetRightY(deviceId);
}

// analog parameters have different resolutions depending on device
func double JslImplGetStickStep(double deviceId) {
	return JslGetStickStep(deviceId);
}
func double JslImplGetTriggerStep(double deviceId) {
	return JslGetTriggerStep(deviceId);
}
func double JslImplGetPollRate(double deviceId) {
	return JslGetPollRate(deviceId);
}

// calibration
func double JslImplResetContinuousCalibration(double deviceId) {
	JslResetContinuousCalibration(deviceId);
	return true;
}
func double JslImplStartContinuousCalibration(double deviceId) {
	JslStartContinuousCalibration(deviceId);
	return true;
}
func double JslImplPauseContinuousCalibration(double deviceId) {
	JslPauseContinuousCalibration(deviceId);
	return true;
}
func double JslImplGetCalibrationOffset(double deviceId, double xOffset, double yOffset, double zOffset) {
	JslGetCalibrationOffset(deviceId, (float&)xOffset, (float&)yOffset, (float&)zOffset);
	return true;
}
func double JslImplSetCalibrationOffset(double deviceId, double xOffset, double yOffset, double zOffset) {
	JslSetCalibrationOffset(deviceId, xOffset, yOffset, zOffset);
	return true;
}

/*
// this function will get called for each input event from each controller
func std::string JslImplSetCallback(void(*callback)(int, JOY_SHOCK_STATE, JOY_SHOCK_STATE, IMU_STATE, IMU_STATE, float));
// this function will get called for each input event, even if touch data didn't update
func std::string JslImplSetTouchCallback(void(*callback)(int, TOUCH_STATE, TOUCH_STATE, float));
*/
// what kind of controller is this?
func double JslImplGetControllerType(double deviceId) {
	return JslGetControllerType(deviceId);
}
// is this a left, right, or full controller?
func double JslImplGetControllerSplitType(double deviceId) {
	return JslGetControllerSplitType(deviceId);
}
// what colour is the controller (not all controllers support this; those that don't will report white)
func double JslImplGetControllerColour(double deviceId) {
	return JslGetControllerColour(deviceId);
}
// set controller light colour (not all controllers have a light whose colour can be set, but that just means nothing will be done when this is called -- no harm)
func double JslImplSetLightColour(double deviceId, double colour) {
	JslSetLightColour(deviceId, colour);
	return true;
}
// set controller rumble
func double JslImplSetRumble(double deviceId, double smallRumble, double bigRumble) {
	JslSetRumble(deviceId, smallRumble, bigRumble);
	return true;
}
// set controller player number indicator (not all controllers have a number indicator which can be set, but that just means nothing will be done when this is called -- no harm)
func double JslImplSetPlayerNumber(double deviceId, double number) {
	JslSetPlayerNumber(deviceId, number);
	return true;
}

// get buttons as bits in the following order, using North South East West to name face buttons to avoid ambiguity between Xbox and Nintendo layouts:
// 0x00001: up
// 0x00002: down
// 0x00004: left
// 0x00008: right
// 0x00010: plus
// 0x00020: minus
// 0x00040: left stick click
// 0x00080: right stick click
// 0x00100: L
// 0x00200: R
// ZL and ZR are reported as analogue inputs (GetLeftTrigger, GetRightTrigger), because DS4 and XBox controllers use analogue triggers, but we also have them as raw buttons
// 0x00400: ZL
// 0x00800: ZR
// 0x01000: S
// 0x02000: E
// 0x04000: W
// 0x08000: N
// 0x10000: home / PS
// 0x20000: capture / touchpad-click
// 0x40000: SL
// 0x80000: SR
// These are the best way to get all the buttons/triggers/sticks, gyro/accelerometer (IMU), orientation/acceleration/gravity (Motion), or touchpad
enum FaceButtons {
	jsl_padU,
	jsl_padD,
	jsl_padL,
	jsl_padR,
	jsl_faceMenuR,
	jsl_faceMenuL,
	jsl_stickL,
	jsl_stickR,
	jsl_shoulderL,
	jsl_shoulderR,
	jsl_shoulderBackL,
	jsl_shoulderBackR,
	jsl_faceD,
	jsl_faceR,
	jsl_faceL,
	jsl_faceU,
	jsl_faceMenuHome,
	jsl_faceMenuCapture,
	jsl_smallShoulderL,
	jsl_smallShoulderR
};

// Used for `*_isPressed` functions
static bool isPressed[FaceButtons::jsl_smallShoulderR];
static bool isPressedTriggered[FaceButtons::jsl_smallShoulderR];

// Used for `*_isReleased` functions
static bool isReleased[FaceButtons::jsl_smallShoulderR];
static bool isReleasedTriggered[FaceButtons::jsl_smallShoulderR];

func double JslImplGetButtonBitField(double deviceId) {
	return JslGetButtons(deviceId);
}

// Get each button individually for ease of use and so GM can avoid doing the repetative calculation that compiled C generally can handle faster
// Shifts bitfield and masks with 1 to effectively return a boolean of whether or not the button is being pressed
// TODO: Doesn't work? Probably issues casting a double to int then using it for bit shifting
func double JslImplGetButton(double deviceId, double buttonShift) {
	return (JslGetButtons(deviceId) >> (int)buttonShift) & 1;
}

func double JslImplGetButtonPressed(double deviceId, double buttonShift) {
	FaceButtons button = static_cast<FaceButtons>(buttonShift);
	bool rawInput = JslImplGetButton(deviceId, buttonShift);

	// Check if button is pressed, if so perform oneshot check
	if (rawInput) {
		// If nothing has happened, check for input
		if (!isPressedTriggered[button]) {
			// First tick, returns true
			isPressed[button] = true;
			isPressedTriggered[button] = true;
		} else {
			// Second tick onwards returns false until released
			isPressed[button] = false;
		}
	} else { // If not pressed, reset logic
		isPressedTriggered[button] = false;
		isPressed[button] = false;
	}

	return isPressed[button];
}

func double JslImplGetButtonReleased(double deviceId, double buttonShift) {
	FaceButtons button = static_cast<FaceButtons>(buttonShift);
	bool rawInput = JslImplGetButton(deviceId, buttonShift);

	// Check if button is not pressed, if so perform oneshot check
	if (!rawInput) {
		// If nothing has happened, check for input
		if (!isReleasedTriggered[button]) {
			// First tick, returns true
			isReleased[button] = true;
			isReleasedTriggered[button] = true;
		} else {
			// Second tick onwards returns false until pressed
			isReleased[button] = false;
		}
	} else { // If pressed, reset logic
		isReleasedTriggered[button] = false;
		isReleased[button] = false;
	}

	return isReleased[button];
}

// get triggers. Switch controllers don't have analogue triggers, but will report 0.0 or 1.0 so they can be used in the same way as others
func double JslImplGetLeftTrigger(double deviceId) {
	return JslGetLeftTrigger(deviceId);
}
func double JslImplGetRightTrigger(double deviceId) {
	return JslGetRightTrigger(deviceId);
}

// get gyro
func double JslImplGetGyroX(double deviceId) {
	return JslGetGyroX(deviceId);
}
func double JslImplGetGyroY(double deviceId) {
	return JslGetGyroY(deviceId);
}
func double JslImplGetGyroZ(double deviceId) {
	return JslGetGyroZ(deviceId);
}

// get accelerometor
func double JslImplGetAccelX(double deviceId) {
	return JslGetAccelX(deviceId);
}
func double JslImplGetAccelY(double deviceId) {
	return JslGetAccelY(deviceId);
}
func double JslImplGetAccelZ(double deviceId) {
	return JslGetAccelZ(deviceId);
}

// get touchpad
func double JslImplGetTouchId(double deviceId, double secondTouch = false) {
	return JslGetTouchId(deviceId, secondTouch);
}


func double JslImplGetTouchDown(double deviceId, double secondTouch = false) {
	return JslGetTouchDown(deviceId, secondTouch);
}

func double JslImplGetTouchX(double deviceId, double secondTouch = false) {
	return JslGetTouchX(deviceId, secondTouch);
}
func double JslImplGetTouchY(double deviceId, double secondTouch = false) {
	return JslGetTouchY(deviceId, secondTouch);
}
