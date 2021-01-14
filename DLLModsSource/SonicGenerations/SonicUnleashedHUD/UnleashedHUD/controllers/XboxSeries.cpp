#include "Controller.h"

namespace XboxSeries {
	ControllerInfo getControllerInfo(bool isFixExtended) {
		ControllerInfo toReturn;

		toReturn.controllertype = XBOXSERIES;
		toReturn.btn = "ui_gp_btn_xboxs";
		toReturn.win = "ui_xbxdow";
		toReturn.pam = "ui_xbm";
		toReturn.trick = "ui_gp_xboxs";
		toReturn.how = "ui_howxb";
		toReturn.bt = "ui_btn_xbide";

		toReturn.ui = isFixExtended ? "ui_gamexbaa" : "ui_gamexbay";

		return toReturn;
	}
}