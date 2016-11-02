// -*- C++ -*-
/*!
 * @file  SoundDirection.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "SoundDirection.h"

//--------------------------add----------------------------
CComPtr<IKinectSensor> kinect = nullptr;
CComPtr<IAudioBeamFrameReader> audioFrame = nullptr;

float angle;
float angleconf;
double fangle;
double angle_p;
double fangle_p;
double angle_deg;


//-----------------------end add---------------------------

// Module specification
// <rtc-template block="module_spec">
static const char* sounddirection_spec[] =
  {
    "implementation_id", "SoundDirection",
    "type_name",         "SoundDirection",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "sako",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.angle_conf", "0.9",
    "conf.default.mode", "rad",

    // Widget
    "conf.__widget__.angle_conf", "text",
    "conf.__widget__.mode", "radio",
    // Constraints
    "conf.__constraints__.mode", "(rad, deg)",

    "conf.__type__.angle_conf", "double",
    "conf.__type__.mode", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SoundDirection::SoundDirection(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_angleOut("angle", m_angle)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SoundDirection::~SoundDirection()
{
}



RTC::ReturnCode_t SoundDirection::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("angle", m_angleOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("angle_conf", m_angle_conf, "0.9");
  bindParameter("mode", m_mode, "rad");
  // </rtc-template>


  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection::onActivated(RTC::UniqueId ec_id)
{
	//------------------------add---------------------------
	//---Initialization
	angle = 0.0;
	angleconf = 0.0;
	fangle = 0.0;
	angle_p = 0.0;
	fangle_p = 0.0;

	//----------------------end add-------------------------

	//-------------------------add---------------------
	//---Open Kinect v2
	std::cout << "Start the preparation of Kinect" << std::endl;

	if (FAILED(GetDefaultKinectSensor(&kinect))){
		std::cout << "Failed to get Kinect" << std::endl;
		return RTC::RTC_OK;
	}

	if (FAILED(kinect->Open())){
		std::cout << "Failed to open Kinect" << std::endl;
		return RTC::RTC_OK;
	}


	//---Open Kinect Audio
	CComPtr<IAudioSource> audioSource;

	if (FAILED(kinect->get_AudioSource(&audioSource))){
		std::cout << "Failed to get AudioSource" << std::endl;
		return RTC::RTC_OK;
	}

	if (FAILED(audioSource->OpenReader(&audioFrame))){
		std::cout << "Failed to Open audioFrame" << std::endl;
		return RTC::RTC_OK;
	}

	std::cout << "Ready" << std::endl;

	//-----------------------end add-----------------


  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection::onDeactivated(RTC::UniqueId ec_id)
{
	if (kinect != nullptr){
		kinect->Close();
	}


  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection::onExecute(RTC::UniqueId ec_id)
{
	//--------------------add-------------------------------
	//---Get BeamFrameList
	CComPtr<IAudioBeamFrameList> audioFrameList;

	if (FAILED(audioFrame->AcquireLatestBeamFrames(&audioFrameList))){
		std::cout << "Failed to acquire LatestBeamFrames" << std::endl;
		return RTC::RTC_OK;
	}

	//--Get BeamFrame
	UINT beamCount = 0;
	if (FAILED(audioFrameList->get_BeamCount(&beamCount))){
		std::cout << "Failed to get BeamCount" << std::endl;
		return RTC::RTC_OK;
	}

	for (int i = 0; i < beamCount; i++){
		CComPtr<IAudioBeamFrame> audioBeamFrame;
		if (FAILED(audioFrameList->OpenAudioBeamFrame(i, &audioBeamFrame))){
			std::cout << "Failed to open AudioFrame" << std::endl;
			return RTC::RTC_OK;
		}

		//--Get subFrame
		UINT subFrameCout = 0;
		if (FAILED(audioBeamFrame->get_SubFrameCount(&subFrameCout))){
			std::cout << "Failed to get SubFrameCount" << std::endl;
			return RTC::RTC_OK;
		}

		for (int j = 0; j < subFrameCout; ++j){
			CComPtr<IAudioBeamSubFrame> audioBeamSubFrame;

			if (FAILED(audioBeamFrame->GetSubFrame(j, &audioBeamSubFrame))){
				std::cout << "Failed to get SubFrame" << std::endl;
				return RTC::RTC_OK;
			}

			if (FAILED(audioBeamSubFrame->get_BeamAngle(&angle))){
				std::cout << "Failed to get angle" << std::endl;
				return RTC::RTC_OK;
			}

			if (FAILED(audioBeamSubFrame->get_BeamAngleConfidence(&angleconf))){
				std::cout << "Failed to get angleconf" << std::endl;
				return RTC::RTC_OK;
			}	
		}
	}

	//---angle out 
	if (angleconf >= m_angle_conf){
		
		angle_deg = angle * (180 / 3.14);
		fangle = fabs(angle);

		if (angle * angle_p > 0){
			//---case of same sign

			if (fangle > fangle_p){
				m_angle.data = angle;
			}
			else
			{
				m_angle.data = 0;
			}

		}
		else if (angle * angle_p < 0){
			//---case of opposite sign

			m_angle.data = angle;


		}
		else if (angle * angle_p == 0){
			
			if (angle == 0){
				m_angle.data = 0;
			}
			else if (angle_p == 0){
				m_angle.data = angle;
			}

		}
			

		m_angleOut.write();








	
		/*
		fangle = fabs(angle);

		if (angle * angle_p >= 0){
			//---case of same sign

			if (fangle > fangle_p){
				//---case of it greater than the size of the past
				if (m_mode == "rad"){
					m_angle.data = angle - angle_p;
				}
				else if (m_mode == "deg"){
					m_angle.data = (angle - angle_p) * 180 / 3.1428;
				}

				m_angleOut.write();
			}

		}


		if (angle * angle_p < 0){
			//---case of opposite sign

			if (fangle > fangle_p){
				//---case of it greater than the size of the past
				if (m_mode == "rad"){
					m_angle.data = angle;
				}
				else if (m_mode == "deg"){
					m_angle.data = angle * 180 / 3.1428;
				}

				m_angleOut.write();
			}

			//---koushin
			angle_p = angle;
			fangle_p = fangle;


		}
		*/


	}

	std::cout << "-----------------------------------------------------------" << std::endl;

	std::cout << "anlge = " << m_angle.data << std::endl;
	std::cout << "conf = " << angleconf << std::endl;

	//----------------------------end add--------------------------

  return RTC::RTC_OK;
}


extern "C"
{
 
  void SoundDirectionInit(RTC::Manager* manager)
  {
    coil::Properties profile(sounddirection_spec);
    manager->registerFactory(profile,
                             RTC::Create<SoundDirection>,
                             RTC::Delete<SoundDirection>);
  }
  
};


