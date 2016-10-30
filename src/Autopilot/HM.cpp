#include "HM.h"

namespace kai
{

HM::HM()
{
	ActionBase();

	m_pROITracker = NULL;
	m_pCtrl = NULL;
}

HM::~HM()
{
}

bool HM::init(Config* pConfig, AUTOPILOT_CONTROL* pAC)
{
	CHECK_F(this->ActionBase::init(pConfig, pAC) == false)

	m_pCtrl = pAC;

//	F_ERROR_F(pConfig->v("targetX", &m_roll.m_targetPos));
//	F_ERROR_F(pConfig->v("targetY", &m_pitch.m_targetPos));

//link ROI tracker
//	string roiName = "";
//	F_ERROR_F(pConfig->v("ROItracker", &roiName));
//	m_pROITracker = (_ROITracker*) (pConfig->root()->getChildInstByName(&roiName));

//setup UI
//	Config* pC;
//	pC = pConfig->o("assist");
//	if (!pC->empty())
//	{
//		m_pUIassist = new UI();
//		F_FATAL_F(m_pUIassist->init(pC));
//	}

	pConfig->m_pInst = this;

	return true;
}

void HM::update(void)
{
	this->ActionBase::update();

	NULL_(m_pCtrl);
	NULL_(m_pCtrl->m_pCAN);
//	NULL_(m_pROITracker);

//	if (m_pROITracker->m_bTracking == false)
//	{
//		return;
//	}

//RC output
//	m_pCtrl->m_pRC->rc_overide(m_pCtrl->m_nRC, m_pCtrl->m_pRC);

	unsigned long addr = 0x113;
	unsigned char cmd[8];

	uint8_t b0 = 0;
	uint8_t b1 = 0; // = B11000011;
	b1 |= 1;
	b1 |= (1 << 1);
	//   b1 |= (1<<5);
	b1 |= (1 << 6);
	b1 |= (1 << 7);

	cmd[0] = b0;
	cmd[1] = b1;
	cmd[2] = 0x40;
	cmd[3] = 0x1f;
	cmd[4] = 0x40;
	cmd[5] = 0x1f;
	cmd[6] = 0xc4;
	cmd[7] = 0x09; //pwmM;

	// send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
//	CAN.sendMsgBuf(0x113, 0, 8, cmd);

	m_pCtrl->m_pCAN->send(addr, 8, cmd);
	return;

}

bool HM::draw(Frame* pFrame, iVec4* pTextPos)
{
	NULL_F(pFrame);
//	NULL_F(m_pROITracker);
	Mat* pMat = pFrame->getCMat();

	putText(*pMat, "HM", cv::Point(pTextPos->m_x, pTextPos->m_y),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);

	pTextPos->m_y += pTextPos->m_w;

	return true;
}

}