/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DriveSubsystem.h"
#include "Commands/DriveFromInput.h"
#include "../RobotMap.h"
#include <WPILib.h>

DriveSubsystem::DriveSubsystem() : Subsystem("ExampleSubsystem")
{
	color_sensor = new I2C(frc::I2C::Port::kOnboard, 0x39);
}

void DriveSubsystem::InitDefaultCommand()
{
	SetDefaultCommand(new DriveFromInput());
}

void DriveSubsystem::OutputRed()
{
	uint8_t data;
	color_sensor->Read(0x16, 2, &data);
	std::cout << (int)data << std::endl;
}
