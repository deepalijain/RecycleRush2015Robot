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
		m_talons[dN].status = true;
		m_talons[dN].talon = t;
		m_talons[dN].voltage = t->GetOutputVoltage();
		Error& error = t->GetError();
		//printf("Talon GetOutputVoltage error: %d\n", error.GetCode());
		if (0==error.GetCode())
		{
			sprintf(m_talons[dN].stat_label, "%s-Status", description);
			sprintf(m_talons[dN].volt_label, "%s-Volts", description);
			sprintf(m_talons[dN].amp_label, "%s-Amps", description);
			sprintf(m_talons[dN].watt_label, "%s-Watts", description);
			printf("Talon %d, %s initialized, Error: %d, Bus Voltage: %f, Output Voltage %f\n",
					dN, description, error.GetCode(),
					busvoltage,  m_talons[dN].voltage);
		}
		else {
			m_talons[dN].status = false;
			printf("Talon %d, %s NOT PRESENT! (error %d)\n", dN, description, error.GetCode());
		}
		m_talons[dN].current = t->GetOutputCurrent();
	}
	else printf("Talon %d, %s failed initialization, new returned NULL.\n", dN, description);
	return t;
}

// tells us if a Talon is present
bool CANTalons::Status(int i) {
	return m_talons[i].status;
}

void CANTalons::UpdateDashboard() {
	for (int i=0; i!=MAX_TALONS; i++) {
		Talon &t = m_talons[i];
		if (NULL != t.talon) {
			if (t.status) {
				t.voltage = t.talon->GetOutputVoltage();
				t.current = t.talon->GetOutputCurrent();
				SmartDashboard::PutBoolean(t.stat_label,t.status);
				//SmartDashboard::PutNumber(t.volt_label, (double)t.voltage);
				//SmartDashboard::PutNumber(t.amp_label, (double)t.current);
				SmartDashboard::PutNumber(t.watt_label, (double)(t.voltage * t.current));
			}
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
