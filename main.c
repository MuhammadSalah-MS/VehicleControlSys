//============================================================================
// Name        : Vehcile_Control_System - First Mini Project
// Author      : Muhammad Salah Ahmed
// 
// Description : This projects aims to simulate the vehcile inside control system
//		 adjusting the car speed, room tempuratre , engine temperature and changing the states of actuators,
//	         depending on the sensors reading .
//============================================================================

// include the standard input/output library
#include <stdio.h>
typedef enum
{
	FALSE,TRUE
}bool;
#define TRUE 1
#define FALSE 0
#define OFF 0
#define ON 1
int first_time=1;

// making vehicle structure
struct vechile
{
	char engine_state;
	char ac_state;
	char speed;
	char room_temp;
	char engine_temp_controller;
	unsigned char engine_temp;

}v1;

// Functions Declaration

bool system_main();
void turn_off_vechile_engine();
void print_vechile_status();
void turn_on_vechile_engine();
bool sensor_menu_display();
void set_traffic_light();
void set_room_temp();
void set_engine_temp();
void vechicle_control_speed();

// The Core Function Definition which contains the first screen
// the function returns TRUE as long as the user didn't choose to close the program
bool system_main()
{
	// making a variable to read the user option
	char option;
	// check if this is the first run of the program to show the welcome message
	if (first_time)
		printf("---- Welcome to VCS ----\n");
	first_time=0;
	// Priniting the options
	printf("Choose Your Option\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	// reading the user option
	scanf(" %c",&option);
	// checking the user option and calling the function he wants
	if (option=='a')
		turn_on_vechile_engine();
	else if (option=='b')
		turn_off_vechile_engine();
	else if (option=='c')  // if the user chose to close the program , function return false
	{	printf("---- VCS CLOSED -----\n");
	return FALSE;
	}
	return TRUE;
}

// turn off vehicle engine , just as the name says .

void turn_off_vechile_engine()
{
	printf("Engine is turned off\n");
	v1.engine_state=OFF;
}

// this function is responsible to turn the engine of the motor , and calling the second men
// the function should be active as long as the engine is turned on , ending if the user chose to turn it off

void turn_on_vechile_engine()
{
	printf("Engine is turned on\n");
	v1.engine_state=ON;
	char menu_state=1;
	// the condition role is to end function when user choose to turn off the engine
	while (TRUE)
	{
		menu_state=sensor_menu_display();
		if (menu_state==FALSE)
			break;
		vechicle_control_speed();
		print_vechile_status();
	}
}
// This function is the responsible to adjust the vehicle interiors after turning the engine on depending on the user input
bool sensor_menu_display()
{

	char option;
	printf("---- Menu ----\nchoose your option\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	printf("d. Set the engine temperature\n\n");
	scanf(" %c",&option);
	if (option=='a')
	{
		turn_off_vechile_engine();
		return FALSE;
	}
	else if (option=='b')
		set_traffic_light();
	else if (option=='c')
		set_room_temp();
	else if (option=='d')
		set_engine_temp();
	return TRUE;
}
// this function updates the vehcile speed
void set_traffic_light()
{
	char color;
	printf("please enter the color\n");
	scanf(" %c",&color);
	if (color=='G'||color=='g')
		v1.speed=100;
	else if (color=='O'||color=='o')
		v1.speed=30;
	else if (color=='R'||color=='r')
		v1.speed=0;

}
// This function updated vehicle room temperature
void set_room_temp()
{
	printf("Enter Room Temp\n");
	scanf("%d",&v1.room_temp);
	if (v1.room_temp<10)
	{
		v1.ac_state=ON;
		v1.room_temp=20;
	}
	else if (v1.room_temp>30)
	{
		v1.ac_state=ON;
		v1.room_temp=20;
	}
	else
	{
		v1.ac_state=OFF;
	}
}
// this function updates the engine temperature
void set_engine_temp()
{
	printf("Enter Engine Temp\n");
	scanf("%d",&v1.engine_temp);
	if (v1.engine_temp<100)
	{
		v1.engine_temp_controller=ON;
		v1.engine_temp=125;

	}
	else if (v1.engine_temp>150)
	{
		v1.engine_temp_controller=ON;
		v1.engine_temp=125;

	}
	else
	{
		v1.engine_temp_controller=OFF;
	}
}

// in the case the  vehicle speed is 30 km/hr the tempurature should be modified
void vechicle_control_speed()
{
	if (v1.speed==30)
	{
		if (v1.ac_state==OFF)
			v1.ac_state=ON;
		v1.room_temp=v1.room_temp*(5.0/4.0)+1;
		if (v1.engine_temp_controller==OFF)
			v1.engine_temp_controller=ON;
		v1.engine_temp=v1.engine_temp*(5.0/4.0)+1;
	}
}
// this function acts as the dashboard which keeps the user updated with his vechile info
void print_vechile_status()
{
	printf("----- Updated Vechile Status -----\n");
	if (v1.engine_state==OFF)
		printf("Engine State : OFF\n");
	else printf("Engine State : ON\n");

	if (v1.ac_state==OFF)
		printf("AC State : OFF\n");
	else printf("AC State : ON\n");

	printf("Vechile Speed = %d\n",v1.speed);
	printf("Room Temp = %d\n",v1.room_temp);

	if (v1.engine_temp_controller==OFF)
		printf("Engine Temp Controller State : OFF\n");
	else printf("Engine Temp Controller  State : ON\n");
	printf("Engine Temp : %d\n",v1.engine_temp);

}

// THE MAIN FUNCTION
// it's role is to keep the system running all the time unless the user close it

int main() {
	// disabling the input/output buffering
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	// the infinte loop ends only when user choose to call the turn off eninge function which returns 0
	int status=1;
	while (TRUE)
	{
		if (status==0) return 0;
		status=system_main();

	}
	return 0;

}
