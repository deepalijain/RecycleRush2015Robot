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
	static uInt32 cameraCount;
	Image *frame;
	IMAQdxSession session;
	IMAQdxError imaqError;
	uInt32 camera;

public:
	Camera(uInt32 i);
	static int EnumerateCameras();

	IMAQdxError CameraStart();
	IMAQdxError CameraFeed();
	IMAQdxError CameraStop();

};
