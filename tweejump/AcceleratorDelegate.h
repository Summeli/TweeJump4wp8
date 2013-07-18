#pragma once

class GameScene;
ref class AcceleratorDelegate sealed
{
public:
	AcceleratorDelegate(void);
//	~AcceleratorDelegate(void);

public:
	 void ReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e);
private:

	  Windows::Devices::Sensors::Accelerometer^ m_accelerometer;
	  Windows::Foundation::EventRegistrationToken m_readingToken;
	  uint32 m_desiredReportInterval;
};

