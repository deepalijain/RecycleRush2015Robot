/*
 * CANTalonOur.h
 *
 *  Created on: Jan 15, 2015
 *      Author: cbf
 */

#pragma once
#include <WPILib.h>
#define MAX_TALONS 12


#if TalonRUs
// Attempt to created a derived class for managing CANTalon's which gets bizarre
// compiler errors for some reason ...
// ..\src\Subsystems\CANTalonOur.h: In constructor 'CANTalonOur::CANTalonOur(int)':
// ..\src\Subsystems\CANTalonOur.h:24:35: error: array used as initializer
class CANTalonOur: public CANTalon {
	private:
	int m_deviceNumber;
	float m_voltage=0;
	float m_current=0;
	char *m_description = nullptr;
	char m_lasterror[120] = "";
	bool m_status = false;

public:
	CANTalonOur(int dN) : CANTalon(dN)
	{
		m_deviceNumber = dN;
	}
	CANTalonOur(int dN,  int controlPeriodMs) : CANTalon(dN, controlPeriodMs)
	{
		m_deviceNumber = dN;
	}

	float getVoltage();
	float getCurrent();
	bool getStat();
	char *getDescr();
	char *getLastError();
};

#endif
class CANTalons {
private:
	int maxTalon = 0;
	struct Talon {
			CANTalon *talon;
			int deviceNumber = 0;
			bool status = false;
			float voltage = 0.0;
			float current = 0.0;
			char *description;
			const char *lasterror = NULL;
			char stat_label[32];
			char volt_label[32];
			char amp_label[32];
		};
public:
		Talon m_talons[MAX_TALONS];
		CANTalon* Init(int device_number, char *description);
		bool Status(int i);
		void UpdateDashboard();
};


