#include "pch.h"
#include "AcceleratorDelegate.h"

using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Platform;

#include "Classes/GameScene.h"


AcceleratorDelegate::AcceleratorDelegate(void)
{
	   m_accelerometer = Accelerometer::GetDefault();
	   if (m_accelerometer != nullptr)
	   {
			// Select a report interval that is both suitable for the purposes of the app and supported by the sensor.
			// This value will be used later to activate the sensor.
			uint32 minReportInterval = m_accelerometer->MinimumReportInterval;
			m_desiredReportInterval = minReportInterval > 16 ? minReportInterval : 16;
			m_readingToken = m_accelerometer->ReadingChanged::add(ref new TypedEventHandler<Accelerometer^, AccelerometerReadingChangedEventArgs^>(this, &AcceleratorDelegate::ReadingChanged));
		
	   }
}

void AcceleratorDelegate::ReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e)
{
	AccelerometerReading^ reading = e->Reading;
	GameScene::accelerated(reading->AccelerationX, reading->AccelerationY, reading->AccelerationZ );
}

