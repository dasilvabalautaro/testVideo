
#include "pch.h"
#include <iostream>
#include "ASSVideoLibrary.h"
#include <cuda_runtime.h>
#include <helper_cuda.h>

void ShootVideo1() {
	

	ASSVideoLibrary* aSSVideoLibrary = new ASSVideoLibrary();
	aSSVideoLibrary->SetConfigurationVideo("video1.txt");
	aSSVideoLibrary->SetFileconfigurationDetect("detect1.txt");
	auto template_input
		= aSSVideoLibrary->aSSCentralProcessingVideo->observableTemplate.map([](char* m) {
		return m;
	});

	auto subscription = template_input.subscribe([](char* m) {
		
		int errorCode;
		void* faceHandler;
		errorCode = IFACE_CreateFaceHandler(&faceHandler);
		int majorVersion0, minorVersion0, majorVersion1, minorVersion1, quality0, quality1;
		errorCode = IFACE_GetTemplateInfo(faceHandler, m, &majorVersion0, &minorVersion0, &quality0);
		std::cout << "First template version: " << majorVersion0 << "." << minorVersion0 << ", quality: " << quality0
			<< endl;
	});
	auto frame_input
		= aSSVideoLibrary->aSSCentralProcessingVideo->observableFrame.map([](Mat img) {
		return img;
	});

	auto subscriptionFrame = frame_input.subscribe([](Mat img) {
		cv::imshow("video 1", img);
	});

	aSSVideoLibrary->RunProcessVideo();

}

int main()
{
	ShootVideo1();
	
}
