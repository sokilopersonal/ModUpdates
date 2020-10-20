#pragma once

/**
	Changes general XNCP references to ones that use custom buttons buttons
**/
void WriteButtons(int buttonType);

/**
	Writes UI XNCP references, which are also responsible for fixing the extended boost bar, if needed
**/
void WriteUi(int buttonType, bool fixExtended);