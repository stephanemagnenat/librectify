/*
 * (c) 2017
 * Stéphane Magnenat (stephane.magnenat@inf.ethz.ch)
 * ETH Game Technology Center
 */

#if _MSC_VER                              // This is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport)  // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API                        // XCode does not need annotating exported functions, so define is empty
#endif

#include <opencv2/opencv.hpp>

extern "C"
{
	//! The four corners of the AR target on the camera image
	struct TargetCameraCoordinates
	{
		float x[4];
		float y[4];
	};
	
	void rectifyMats(const cv::Mat& inMat, struct TargetCameraCoordinates* targetCoordinates, cv::Mat& outMat)
	{
		// setup corresponding points
		const auto inHeight(inMat.size().height);
		cv::Point2f srcPoints[4];
		for (size_t i = 0; i < 4; ++i)
			srcPoints[i] = { targetCoordinates->x[i], inHeight - targetCoordinates->y[i] - 1};
		const float outHeightF(outMat.size().height);
		const float outWidthF(outMat.size().width);
		const cv::Point2f dstPoints[4] = { {0, 0}, {0, outHeightF}, {outWidthF, outHeightF}, {outWidthF, 0} };
		
		// get the perspective transform
		const auto perspectiveTransform = cv::getPerspectiveTransform(srcPoints, dstPoints);
		
		// correct image
		cv::warpPerspective(inMat, outMat, perspectiveTransform, outMat.size());
	}
	
	void EXPORT_API rectifyBGRA(unsigned char* inPixels, int inWidth, int inHeight, int inStride, struct TargetCameraCoordinates* targetCoordinates, unsigned char* outPixels, int outWidth, int outHeight)
	{
		// map inputs as OpenCV matrices
		cv::Mat cameraImage(inHeight, inWidth, CV_8UC4, inPixels, inStride);
		cv::Mat warpedImage(outHeight, outWidth, CV_8UC4, outPixels);
		
		rectifyMats(cameraImage, targetCoordinates, warpedImage);
	}
	
	void EXPORT_API rectifyBGR(unsigned char* inPixels, int inWidth, int inHeight, int inStride, struct TargetCameraCoordinates* targetCoordinates, unsigned char* outPixels, int outWidth, int outHeight)
	{
		// map inputs as OpenCV matrices
		cv::Mat cameraImage(inHeight, inWidth, CV_8UC3, inPixels, inStride);
		cv::Mat cameraImageBGRA;
		cv::cvtColor(cameraImage, cameraImageBGRA, cv::COLOR_BGR2BGRA);
		cv::Mat warpedImage(outHeight, outWidth, CV_8UC4, outPixels);
		
		rectifyMats(cameraImageBGRA, targetCoordinates, warpedImage);
	}
	
	void EXPORT_API rectifyBGR565(unsigned char* inPixels, int inWidth, int inHeight, int inStride, struct TargetCameraCoordinates* targetCoordinates, unsigned char* outPixels, int outWidth, int outHeight)
	{
		// map inputs as OpenCV matrices
		cv::Mat cameraImage(inHeight, inWidth, CV_8UC2, inPixels, inStride);
		cv::Mat cameraImageBGRA;
		cv::cvtColor(cameraImage, cameraImageBGRA, cv::COLOR_BGR5652BGRA);
		cv::Mat warpedImage(outHeight, outWidth, CV_8UC4, outPixels);
		
		rectifyMats(cameraImageBGRA, targetCoordinates, warpedImage);
	}
	
	void EXPORT_API rectifyYUV_NV21(unsigned char* inPixels, int inWidth, int inHeight, int inStride, struct TargetCameraCoordinates* targetCoordinates, unsigned char* outPixels, int outWidth, int outHeight)
	{
		cv::Mat cameraImage(inHeight+inHeight/2, inWidth, CV_8UC1, inPixels, inStride);
		cv::Mat cameraImageBGRA;
		cv::cvtColor(cameraImage, cameraImageBGRA, cv::COLOR_YUV2BGRA_NV21);
		cv::Mat warpedImage(outHeight, outWidth, CV_8UC4, outPixels);
		
		rectifyMats(cameraImageBGRA, targetCoordinates, warpedImage);
	}
	
	void EXPORT_API rectifyGrayscale(unsigned char* inPixels, int inWidth, int inHeight, int inStride, struct TargetCameraCoordinates* targetCoordinates, unsigned char* outPixels, int outWidth, int outHeight)
	{
		// map inputs as OpenCV matrices
		cv::Mat cameraImage(inHeight, inWidth, CV_8UC1, inPixels, inStride);
		cv::Mat cameraImageBGRA;
		cv::cvtColor(cameraImage, cameraImageBGRA, cv::COLOR_GRAY2BGRA);
		cv::Mat warpedImage(outHeight, outWidth, CV_8UC4, outPixels);
		
		rectifyMats(cameraImageBGRA, targetCoordinates, warpedImage);
	}
	
	int EXPORT_API testLib()
	{
		return 42;
	}
}

