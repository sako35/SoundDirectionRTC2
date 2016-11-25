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
	//-----変数の初期化
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
	//-----データの入力
	if (m_angleIn.isNew()){				//---データが新しかったら更新
		m_angleIn.read();				//データの更新

		angle = m_angle.data;			//現在の角度
		fangle = fabs(angle);			//現在の角度の絶対値

		if (angle * angle_p > 0){		//---現在の角度と過去の角度が同符号の場合

			if (fangle > fangle_p){		//現在の角度の絶対値のほうが、過去の角度の絶対値より大きい場合
				m_angle_c.data = angle;		//現在の角度を出力
			}
			else {						//小さい場合は
				m_angle_c.data = 0;			//0を出力
			}
		}
		else if (angle * angle_p < 0){	//---現在の角度と過去の角度が異符号の場合

			m_angle_c.data = angle;		//現在の角度を出力

		}
		else if (angle * angle_p == 0){	//---現在の角度か過去の角度が0のとき

			if (angle == 0){				//現在の角度が0の場合
				m_angle_c.data = 0;			//0を出力する
			}
			else if (angle_p == 0){
				m_angle_c.data = angle;
			}

		}

		m_angle_cOut.write();		//出力


		std::cout << "-----------------------------------------------------------" << std::endl;
		std::cout << "angle = " << angle << std::endl;
		std::cout << "angle_p = " << angle_p << std::endl;
		std::cout << "***** data = " << m_angle_c.data << "*****" << std::endl;


		angle_p = angle;			//過去の角度に現在の角度を入れる
		fangle_p = fangle;			//絶対値

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


