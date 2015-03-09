/*
 * Camera.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: cbf
 */

#include "Camera.h"
#include <CameraServer.h>
#include <stdio.h>
#include <limits.h>

uInt32 Camera::cameraCount = 0;
IMAQdxCameraInformation Camera::camInfo[6];

// i is the index of the camera we want to open
Camera::Camera(uInt32 i) {
	if (cameraCount == 0 && i>cameraCount) {
		printf("Camera: attempt to open camera out of range (zero or too big).\n");
		return;
	}
	camera = i;
	frame = 0;
	session = ULONG_MAX;
}

// static function for enumerating cameras
int Camera::EnumerateCameras() {
	uInt32 count = sizeof(camInfo)/sizeof(camInfo[0]);
	// last parameter is "connectedOnly". Why would we want to enumerate non-connected cameras?
	IMAQdxEnumerateCameras(camInfo, &count, true);
	cameraCount = count;
	printf("Cameras (%u):\n", (unsigned int)cameraCount);
	for (uInt32 i=0; i!=cameraCount; i++) printf("  %s / %s / %s\n", camInfo[i].VendorName,
											     camInfo[i].ModelName, camInfo[i].InterfaceName);
	return cameraCount;
}

IMAQdxError Camera::CameraStart() {
    // create an image
	printf("Opening camera %s\n", camInfo[camera].InterfaceName);
	imaqError = IMAQdxOpenCamera(camInfo[camera].InterfaceName, IMAQdxCameraControlModeController, &session);
	if(imaqError != IMAQdxErrorSuccess) {
		printf("IMAQdxOpenCamera error: %x\n", imaqError);
		return imaqError;
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess) {
		printf("IMAQdxOpenCamera error: %x\n", imaqError);
		return imaqError;
	}
    // start to acquire images
	IMAQdxStartAcquisition(session);
	if(imaqError != IMAQdxErrorSuccess) {
		printf("IMAQdxOpenCamera error: %x\n", imaqError);
		return imaqError;
	}

	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	printf("Camera Opened for %s #: %lu\n", camInfo[camera].InterfaceName, session);
	return imaqError;
}

IMAQdxError Camera::CameraFeed() {
	imaqError = IMAQdxErrorSuccess;
    // grab an image, draw the circle, and provide it for the camera server which will
    // in turn send it to the dashboard.
	// let's only do this every 1/10 second to avoid excess cpu & network traffic
	// Ticks+2 to avoid doing it on same cycle as SmartDashBoard updates
	if (session!=ULONG_MAX && frame!=0) {
		IMAQdxGrab(session, frame, false, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			printf("IMAQdxConfigureGrab error (%s): %x\n", camInfo[camera].InterfaceName, imaqError);
		}
		else {
			CameraServer::GetInstance()->SetImage(frame);
		}				// wait for a motor update time
	}
	return imaqError;
}

IMAQdxError Camera::CameraStop() {
    // stop image acquisition
	imaqError = IMAQdxErrorSuccess;
	if (ULONG_MAX!=session) {
		// Had trouble with imaqDrawTextOnImage
		//const DrawTextOptions options = {"Arial", 12, 0, 0, 0, 0, IMAQ_CENTER, IMAQ_INVERT};
		//int fontUsed;
		//imaqDrawTextOnImage(frame, frame, {120, 80}, "X", &options, &fontUsed);
		if (NULL!=frame) {
			// Would really like to make this semi-transparent, but not apparent how.
			imaqDrawShapeOnImage(frame, frame, { 100, 100, 160, 160 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,3.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}
		IMAQdxStopAcquisition(session);
		IMAQdxCloseCamera(session);
		printf("Camera %s closed on session %lu.\n", camInfo[camera].InterfaceName, session);
		session = ULONG_MAX;
	}
	return imaqError;
}

