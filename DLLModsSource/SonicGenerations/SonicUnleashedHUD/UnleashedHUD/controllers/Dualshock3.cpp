#include "Controller.h"

namespace Dualshock3 {
	ControllerInfo getControllerInfo(bool isFixExtended) {
		ControllerInfo toReturn;

		toReturn.controllertype = PS3;
		toReturn.btn = "ui_gp_btn_pside";
		toReturn.win = "ui_psndow";
		toReturn.pam = "ui_psm";
		toReturn.trick = "ui_gp_psick";
		toReturn.how = "ui_howps";
		toReturn.bt = "ui_btn_pside";

		toReturn.ui = isFixExtended ? "ui_gamepsaa" : "ui_gamepsay";

		return toReturn;
	}
}