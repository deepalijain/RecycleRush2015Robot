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
uInt32 Camera::currentCamera = 0;
IMAQdxCameraInformation Camera::camInfo[6];
Camera *Camera::cameras[6];

// i is the index of the camera we want to open
Camera::Camera(uInt32 i) {
	if (cameraCount == 0 && i>cameraCount) {
		printf("Camera: attempt to open camera out of range (zero or too big).\n");
		return;
	}
	camera = i;
	firstTime = true;
	frame = NULL;
	session = ULONG_MAX;
}

char *Camera::GetName() {
	return camInfo[currentCamera].InterfaceName;
}

char *Camera::GetModel() {
	return camInfo[currentCamera].ModelName;
}


void Camera::StartCameras() {
	for (uInt32 i=0; i!=cameraCount; i++) cameras[i]->Start();
}

void Camera::StopCameras() {
	for (uInt32 i=0; i!=cameraCount; i++) cameras[i]->Stop();
}


// static function for enumerating cameras
int Camera::EnumerateCameras() {
	uInt32 count = sizeof(camInfo)/sizeof(camInfo[0]);
	// last parameter is "connectedOnly". Why would we want to enumerate non-connected cameras?
	IMAQdxEnumerateCameras(camInfo, &count, true);
	cameraCount = count;
	printf("Cameras (%u):\n", (unsigned int)cameraCount);
	for (uInt32 i=0; i!=cameraCount; i++) {
		cameras[i] = new Camera(i);
		printf("  %s / %s / %s\n", camInfo[i].VendorName,
											     camInfo[i].ModelName, camInfo[i].InterfaceName);
	}
	return cameraCount;
}

uInt32 Camera::SwitchCamera() {
	if (++currentCamera >= cameraCount) currentCamera = 0;
	return currentCamera;
}


// Feed video frams from the currently selected camera.
// Should be called once per tick, or however often you want frames.
void Camera::Feed()
{
	if (cameraCount > 0) {
		IMAQdxError imaqError = cameras[currentCamera]->GetFrame();
		if (cameras[currentCamera]->frame!=NULL) {
			if (IMAQdxErrorSuccess==imaqError) {
				CameraServer::GetInstance()->SetImage(cameras[currentCamera]->frame);
			}
		}
	}
}

void Camera::DumpModes() {
	IMAQdxVideoMode videoModes[120];
	uInt32 count;
	uInt32 mode;
	IMAQdxEnumerateVideoModes(session, videoModes, &count, &mode);
	printf("There are %lu video modes, and the current mode is %lu\n", count, mode);
	for (uInt32 i=0; i!=count; i++) {
		printf("Video mode[%lu] is %s = %lu\n", i, videoModes[i].Name, videoModes[i].Value);
	}
}

IMAQdxError Camera::SetMode() {
	IMAQdxVideoMode videoModes[120];
	uInt32 count;
	uInt32 mode;
	IMAQdxEnumerateVideoModes(session, videoModes, &count, &mode);
	printf("There are %lu video modes, and the current mode is %lu\n", count, mode);
	for (uInt32 i=0; i!=count; i++) {
		printf("Video mode[%lu] is %s = %lu\n", i, videoModes[i].Name, videoModes[i].Value);
		if (i==95) {
			imaqError = IMAQdxSetAttribute(session, IMAQdxAttributeVideoMode, IMAQdxValueTypeU32, videoModes[i].Value);
			if(imaqError != IMAQdxErrorSuccess) {
				printf("IMAQdxOpenCamera attempt to set video mode to %lu failed: %x\n", videoModes[i].Value, imaqError);
			}
			return imaqError;
		}
	}
	return IMAQdxErrorInternal;
}

void Camera::DumpAttrs() {
		//IMAQdxEnumerateAttributes(IMAQdxSession id, IMAQdxAttributeInformation attributeInformationArray[], uInt32* count, const char* root);
		IMAQdxAttributeInformation attributeInformationArray[300];
		uInt32 count;
		IMAQdxEnumerateAttributes(session, NULL, &count, "");
		union {
			uInt32 a;
			uInt64 b;
			double c;
			char *d;
			unsigned int e;
			bool f;
			char y[256];	// just in case
		} x;
		printf("IMAQdxEnumerateAttributes - there are %lu attributes", count);
		if (count > sizeof(attributeInformationArray)/sizeof(attributeInformationArray[0])) {
			printf(" -- that's too many to enumerate\n");
		}
		else printf("\n");
		IMAQdxEnumerateAttributes(session, attributeInformationArray, &count, "");
		for (uInt32 i=0; i!=count; i++) {
			printf("  attr[%lu] is %s, type %u, writeable %lu, value=", i, attributeInformationArray[i].Name, attributeInformationArray[i].Type, attributeInformationArray[i].Writable);
 			IMAQdxGetAttribute(session, attributeInformationArray[i].Name, (IMAQdxValueType)attributeInformationArray[i].Type, &x);
 			switch (attributeInformationArray[i].Type) {
				case IMAQdxValueTypeU32:
					printf("%lu\n", x.a);
					break;
				case IMAQdxValueTypeI64:
					printf("%llu\n", x.b);
					break;
				case IMAQdxValueTypeF64:
					printf("%f\n", x.c);
					break;
				case IMAQdxValueTypeString:
					//printf("%s\n", x.d);
					printf("%s\n", x.y);
					break;
				case IMAQdxValueTypeEnumItem:
					printf("%u\n", x.e);
					break;
				case IMAQdxValueTypeBool:
					printf("%d\n", x.f);
					break;
				default:
					printf("%x\n", x.e);
					break;

			}
		}
}

IMAQdxError Camera::Start() {
    // create an image
	printf("Opening camera %s\n", camInfo[camera].InterfaceName);
	imaqError = IMAQdxOpenCamera(camInfo[camera].InterfaceName, IMAQdxCameraControlModeController, &session);
	if(imaqError != IMAQdxErrorSuccess) {
		printf("IMAQdxOpenCamera error: %x\n", imaqError);
		return imaqError;
	}
	imaqError = Camera::SetMode();
	if(imaqError != IMAQdxErrorSuccess) {
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
	printf("Camera Opened for %s #: %lu, frame=%x\n", camInfo[camera].InterfaceName, session, (unsigned int)frame);
	return imaqError;
}

IMAQdxError Camera::GetFrame() {
	imaqError = IMAQdxErrorSuccess;
    // grab an image,
	if (session!=ULONG_MAX && frame!=NULL) {
		if (false && firstTime) {
			DumpModes();
			DumpAttrs();
		}
		IMAQdxGrab(session, frame, false, NULL);
		if(imaqError != IMAQdxErrorSuccess) {
			printf("IMAQdxConfigureGrab error (%s): %x\n", camInfo[camera].InterfaceName, imaqError);
		}
		else if (firstTime) {
			int xRes, yRes;
			imaqGetImageSize(frame, &xRes, &yRes);
			printf("Camera: first image grab is %d x %d frame=%x\n", xRes, yRes, (unsigned int)frame);
		}
		firstTime = false;
	}
	return imaqError;
}

IMAQdxError Camera::Stop() {
    // stop image acquisition
	imaqError = IMAQdxErrorSuccess;
	if (ULONG_MAX!=session) {
		// Had trouble with imaqDrawTextOnImage
		//const DrawTextOptions options = {"Arial", 12, 0, 0, 0, 0, IMAQ_CENTER, IMAQ_INVERT};
		//int fontUsed;
		//imaqDrawTextOnImage(frame, frame, {120, 80}, "X", &options, &fontUsed);
		if (NULL!=frame && camera==currentCamera) {
			// Would really like to make this semi-transparent, but not apparent how.
			imaqDrawShapeOnImage(frame, frame, { 80, 80, 160, 160 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL,3.0f);
			CameraServer::GetInstance()->SetImage(frame);
		}
		IMAQdxStopAcquisition(session);
		IMAQdxCloseCamera(session);
		printf("Camera %s closed on session %lu.\n", camInfo[camera].InterfaceName, session);
		session = ULONG_MAX;
	}
	return imaqError;
}

