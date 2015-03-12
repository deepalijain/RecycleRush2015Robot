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
	static Image *frame;
	IMAQdxSession session;
	IMAQdxError imaqError;
	uInt32 camera;

public:
	Camera(uInt32 i);
	static int EnumerateCameras();
	static uInt32 SwitchCamera();
	static void Feed();

	IMAQdxError Start();
	IMAQdxError GetFrame();
	IMAQdxError Stop();

};
