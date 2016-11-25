// -*- C++ -*-
/*!
 * @file  SoundDirection2.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "SoundDirection2.h"

//--------------------------add----------------------------
CComPtr<IKinectSensor> kinect = nullptr;
CComPtr<IAudioBeamFrameReader> audioFrame = nullptr;

float angle;
float angleconf;
//-----------------------end add---------------------------

// Module specification
// <rtc-template block="module_spec">
static const char* sounddirection2_spec[] =
  {
    "implementation_id", "SoundDirection2",
    "type_name",         "SoundDirection2",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "sako",
    "category",          "kinect",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.mode", "rad",
    "conf.default.angle_conf", "0.9",

    // Widget
    "conf.__widget__.mode", "radio",
    "conf.__widget__.angle_conf", "text",
    // Constraints
    "conf.__constraints__.mode", "(rad, deg)",
    "conf.__constraints__.angle_conf", "0<, 1>",

    "conf.__type__.mode", "string",
    "conf.__type__.angle_conf", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SoundDirection2::SoundDirection2(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_angleOut("angle", m_angle)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SoundDirection2::~SoundDirection2()
{
}



RTC::ReturnCode_t SoundDirection2::onInitialize()
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
  bindParameter("mode", m_mode, "rad");
  bindParameter("angle_conf", m_angle_conf, "0.9");
  // </rtc-template>
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection2::onActivated(RTC::UniqueId ec_id)
{
	//------------------------add---------------------------
	//---Initialization
	angle = 0.0;
	angleconf = 0.0;

	kinect = nullptr;
	audioFrame = nullptr;
	//----------------------end add-------------------------

	//-------------------------add---------------------
	//---Open Kinect v2
	std::cout << "Start the preparation of Kinect" << std::endl;

	if (FAILED(GetDefaultKinectSensor(&kinect))){
		std::cout << "Failed to get Kinect" << std::endl;
		return RTC::RTC_ERROR;
	}

	if (FAILED(kinect->Open())){
		std::cout << "Failed to open Kinect" << std::endl;
		return RTC::RTC_ERROR;
	}

	//---Open Kinect Audio
	CComPtr<IAudioSource> audioSource;

	if (FAILED(kinect->get_AudioSource(&audioSource))){
		std::cout << "Failed to get AudioSource" << std::endl;
		return RTC::RTC_ERROR;
	}

	if (FAILED(audioSource->OpenReader(&audioFrame))){
		std::cout << "Failed to Open audioFrame" << std::endl;
		return RTC::RTC_ERROR;
	}

	std::cout << "Ready" << std::endl;

	//-----------------------end add-----------------

  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection2::onDeactivated(RTC::UniqueId ec_id)
{
	if (kinect != nullptr){
		kinect->Close();
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t SoundDirection2::onExecute(RTC::UniqueId ec_id)
{	//--------------------add-------------------------------
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

		if (m_mode == "rad"){						//mode rad
			m_angle.data = angle;
		}
		else if (m_mode == "deg"){
			m_angle.data = angle * 180 / M_PI;		//mode deg
		}
		
		m_angleOut.write();

		std::cout << "--------------------------------------------------------------" << std::endl;
		std::cout << "angle = " << angle << std::endl;
		std::cout << "conf = " << angleconf << std::endl;

	}




	//----------------------------end add--------------------------


  return RTC::RTC_OK;
}


extern "C"
{
 
  void SoundDirection2Init(RTC::Manager* manager)
  {
    coil::Properties profile(sounddirection2_spec);
    manager->registerFactory(profile,
                             RTC::Create<SoundDirection2>,
                             RTC::Delete<SoundDirection2>);
  }
  
};


