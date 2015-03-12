/*
 * Camaera.h
 *
 *  Created on: Mar 9, 2015
 *      Author: cbf
 */

#pragma once
#include <NIIMAQdx.h>
#include <nivision.h>

class Camera {
private:
	static IMAQdxCameraInformation camInfo[6];
	static Camera *cameras[6];	// array of ourselves
	static uInt32 cameraCount;
	static uInt32 currentCamera;
	Image *frame;
	IMAQdxSession session;
	IMAQdxError imaqError;
	uInt32 camera;
	bool firstTime;

public:
	Camera(uInt32 i);
	void DumpAttrs();
	void DumpModes();
	static int EnumerateCameras();
	static uInt32 SwitchCamera();
	static void StartCameras();
	static void StopCameras();
	static void Feed();
	static char *GetName();
	static char *GetModel();

	IMAQdxError Start();
	IMAQdxError GetFrame();
	IMAQdxError Stop();

};
