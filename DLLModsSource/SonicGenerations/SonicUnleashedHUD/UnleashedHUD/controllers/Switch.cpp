#include "Controller.h"

namespace Switch {
	ControllerInfo getControllerInfo(bool isFixExtended) {
		ControllerInfo toReturn;

		toReturn.controllertype = SWITCH;
		toReturn.btn = "ui_gp_btn_nswit";
		toReturn.win = "ui_nswdow";
		toReturn.pam = "ui_nsm";
		toReturn.trick = "ui_gp_nswit";
		toReturn.how = "ui_howns";
		toReturn.bt = "ui_btn_nside";

		toReturn.ui = isFixExtended ? "ui_gamensaa" : "ui_gamensay";

		return toReturn;
	}
}