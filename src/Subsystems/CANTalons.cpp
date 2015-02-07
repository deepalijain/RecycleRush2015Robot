#include "CANTalons.h"
#include <stdio.h>

CANTalon* CANTalons::Init(int dN, char* description) {
	if (dN > MAX_TALONS) {
		printf("Failed to initialize CANTalon #%d, max allowed is %d.\n", dN, MAX_TALONS);
		return NULL;
	}
	if (strlen(description) > 20)
	{
		printf("Failed to initialize CANTalon #%d, your description '%s' exceeds 20 characters.\n", dN, description);
		return NULL;
	}
	m_talons[dN].deviceNumber = dN;
	m_talons[dN].description = description;
	CANTalon *t = new CANTalon(dN);
	float busvoltage = 0.0;
	if (NULL != t) {
		m_talons[dN].talon = t;
		if (t->GetBusVoltage() > 8.0) {
			m_talons[dN].status = true;
		}
		m_talons[dN].voltage = t->GetOutputVoltage();
		m_talons[dN].current = t->GetOutputCurrent();
		sprintf(m_talons[dN].stat_label, "%s-Status", description);
		sprintf(m_talons[dN].volt_label, "%s-Volts", description);
		sprintf(m_talons[dN].amp_label, "%s-Amps", description);
		printf("Talon %d, %s initialized, Bus Voltage: %f, Output Voltage %f\n", dN, description,
				busvoltage,  m_talons[dN].voltage);
	}
	else printf("Talon %d, %s failed initialization, new returned NULL.\n", dN, description);
	return t;
}

void CANTalons::UpdateDashboard() {
	for (int i=0; i!=MAX_TALONS; i++) {
		Talon &t = m_talons[i];
		if (NULL != t.talon) {
			Error& e = ((ErrorBase *)t.talon)->GetError();
			if (e.GetCode() > 0) {
				t.status = false;
				t.lasterror = e.GetMessage();
			}
			t.voltage = t.talon->GetOutputVoltage();
			t.current = t.talon->GetOutputCurrent();
			SmartDashboard::PutBoolean(t.stat_label,t.status);
			SmartDashboard::PutNumber(t.volt_label, (double)t.voltage);
			SmartDashboard::PutNumber(t.amp_label, (double)t.current);
		}
	}
}


#if TalonRUs
float CANTalonOur::getVoltage() {
	m_voltage = this->GetOutputVoltage();
	return m_voltage;
}

float CANTalonOur::getCurrent() {
	m_current = this->GetOutputVoltage();
	return m_current;
}

char *CANTalonOur::getDescr() {
	return(m_description);
}

char *CANTalonOur::getLastError() {
	return(m_lasterror);
}

bool CANTalonOur::getStat() {
	return(m_status);
}
#endif
