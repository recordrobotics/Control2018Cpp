
void Grabber::succ(double speed){
	left_motor.Set(speed);
	right_motor.Set(-speed);
}

void Grabber::adjust(double speed, bool direction){
	if (direction)
	{
		left_motor.Set(speed);
		right_motor.Set(speed);
	}
	else
	{
		left_motor.Set(-speed);
		right_motor.Set(-speed);
	}
}
