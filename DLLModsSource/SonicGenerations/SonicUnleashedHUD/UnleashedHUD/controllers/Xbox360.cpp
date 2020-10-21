#include "Controller.h"

namespace Xbox360 {
	ControllerInfo getControllerInfo(bool isFixExtended) {
		ControllerInfo toReturn;

		toReturn.controllertype = XBOX360;
		toReturn.btn = "ui_gp_btn_guide";
		toReturn.win = "ui_window";
		toReturn.pam = "ui_pam";
		toReturn.trick = "ui_gp_trick";
		toReturn.how = "ui_howto";
		toReturn.bt = "ui_btn_guide";

		toReturn.ui = isFixExtended ? "ui_gameplaa" : "ui_gameplay";

		return toReturn;
	}
}