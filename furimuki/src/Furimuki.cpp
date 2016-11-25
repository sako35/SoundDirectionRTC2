// -*- C++ -*-
/*!
 * @file  Furimuki.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "Furimuki.h"

//*****add*********************************************
double angle;
double fangle;
double angle_p;
double fangle_p;
//*****end add*****************************************



// Module specification
// <rtc-template block="module_spec">
static const char* furimuki_spec[] =
  {
    "implementation_id", "Furimuki",
    "type_name",         "Furimuki",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "sako  ",
    "category",          "kinect v",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Furimuki::Furimuki(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_angleIn("angle", m_angle),
    m_angle_cOut("angle_c", m_angle_c)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Furimuki::~Furimuki()
{
}



RTC::ReturnCode_t Furimuki::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("angle", m_angleIn);
  
  // Set OutPort buffer
  addOutPort("angle_c", m_angle_cOut);
  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Furimuki::onActivated(RTC::UniqueId ec_id)
{
	//*****add*******************************************************
	//-----�ϐ��̏�����
	angle = 0;
	fangle = 0;
	angle_p = 0;
	fangle_p = 0;
	//*****End add***************************************************

  return RTC::RTC_OK;
}


RTC::ReturnCode_t Furimuki::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Furimuki::onExecute(RTC::UniqueId ec_id)
{
	//*****add*******************************************************
	//-----�f�[�^�̓���
	if (m_angleIn.isNew()){				//---�f�[�^���V����������X�V
		m_angleIn.read();				//�f�[�^�̍X�V

		angle = m_angle.data;			//���݂̊p�x
		fangle = fabs(angle);			//���݂̊p�x�̐�Βl

		if (angle * angle_p > 0){		//---���݂̊p�x�Ɖߋ��̊p�x���������̏ꍇ

			if (fangle > fangle_p){		//���݂̊p�x�̐�Βl�̂ق����A�ߋ��̊p�x�̐�Βl���傫���ꍇ
				m_angle_c.data = angle;		//���݂̊p�x���o��
			}
			else {						//�������ꍇ��
				m_angle_c.data = 0;			//0���o��
			}
		}
		else if (angle * angle_p < 0){	//---���݂̊p�x�Ɖߋ��̊p�x���ٕ����̏ꍇ

			m_angle_c.data = angle;		//���݂̊p�x���o��

		}
		else if (angle * angle_p == 0){	//---���݂̊p�x���ߋ��̊p�x��0�̂Ƃ�

			if (angle == 0){				//���݂̊p�x��0�̏ꍇ
				m_angle_c.data = 0;			//0���o�͂���
			}
			else if (angle_p == 0){
				m_angle_c.data = angle;
			}

		}

		m_angle_cOut.write();		//�o��


		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "angle = " << angle << std::endl;
		std::cout << "angle_p = " << angle_p << std::endl;
		std::cout << "***** data = " << m_angle_c.data << "*****" << std::endl;


		angle_p = angle;			//�ߋ��̊p�x�Ɍ��݂̊p�x������
		fangle_p = fangle;			//��Βl

	}

  return RTC::RTC_OK;
}



extern "C"
{
 
  void FurimukiInit(RTC::Manager* manager)
  {
    coil::Properties profile(furimuki_spec);
    manager->registerFactory(profile,
                             RTC::Create<Furimuki>,
                             RTC::Delete<Furimuki>);
  }
  
};


