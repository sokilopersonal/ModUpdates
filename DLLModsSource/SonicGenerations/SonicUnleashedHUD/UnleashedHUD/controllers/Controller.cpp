#include <memory>
#include "Controller.h"

ControllerInfo GetXncpNames(int buttonType, bool isFixExtended)
{
	switch (buttonType) {
		case PS3:
			return Dualshock3::getControllerInfo(isFixExtended);
		case SWITCH:
			return Switch::getControllerInfo(isFixExtended);
		case XBOX360:
			return Xbox360::getControllerInfo(isFixExtended);
		case XBOXSERIES:
			return XboxSeries::getControllerInfo(isFixExtended);
		default:
			return { };
	}
}