#include "Controller.h"
#include "XError.h"

Controller::Controller(ThickWrapper thick, int argc, char* argv[]) : optionView(thick, fileModel), fileModel(argc, argv), fileView(thick), statusView(thick, fileModel)
{
	fileModel.Attach(&fileView);
	fileModel.Attach(&optionView);
	fileModel.Attach(&statusView);
	fileModel.ScanFile();
	
}

Controller::~Controller()
{

}

