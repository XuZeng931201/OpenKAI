/*
 * FrameGPU.h
 *
 *  Created on: Aug 21, 2015
 *      Author: yankai
 */

#ifndef OpenKAI_src_Vision_FrameGPU_H_
#define OpenKAI_src_Vision_FrameGPU_H_

#include "../Base/common.h"

#ifdef USE_CUDA

namespace kai
{

class FrameGPU
{
public:
	FrameGPU();
	virtual ~FrameGPU();

	virtual void operator=(const FrameGPU& f);
	virtual void operator=(const Mat& m);

	virtual void allocate(int w, int h);
	virtual void copy(const FrameGPU& f);
	virtual void copy(const Mat& m);

	virtual FrameGPU warpAffine(Mat& mWA);
	virtual FrameGPU flip(int iOpt);
	virtual void setRemap(Mat& mX, Mat& mY);
	virtual FrameGPU remap(void);
	virtual FrameGPU crop(Rect bb);
	virtual FrameGPU resize(int w, int h);
	virtual FrameGPU resize(double scaleW, double scaleH);
	virtual FrameGPU gray(void);
	virtual FrameGPU hsv(void);
	virtual FrameGPU bgra(void);
	virtual FrameGPU rgba(void);
	virtual FrameGPU f8UC3(void);
	virtual FrameGPU f32FC4(void);

	virtual Mat* m(void);
	virtual Size size(void);
	virtual bool bEmpty(void);

	uint64_t tStamp(void);

public:
	uint64_t m_tStamp;
	Mat m_mat;

	//calibration remap
	Mat m_mapX;
	Mat m_mapY;

};

}
#endif
#endif
