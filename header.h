//Joe Leland
//This program contains 5 classes: Time, weather, mileMarker, highway, and journey. mileMarker is derived from weather so that the temperature on the asscent can be represented dynamicaly.
//highways are derived from time so that this can be used to find out which one is the fastest option. The journey class is in charge of managing the best route and is the only object created from main. 
//When it is initiliazied it sets off a chain reaction where the other objects are created as well. The mileMarker constructor this program uses populates all of the road conditions based off of the
//intitial conditions and decreasing temperature with altitude. Journey uses the highway class to determine the best route and then copies that route into its own LLL. Highway uses the mileMarkers to report back to journey which
//route is fastest, after it has anazlyed them. 
#ifndef __HEADER__
#define __HEADER__
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>

const int SIZE = 50;//const global used for temp variables
const int ROADS = 2;//Amount of highways to represent, in this case 2 that lead to Mt. Hood.

//Time class used to manage the time of the highway objects
class Time{
	public:
		Time();
		Time(int, int);//takes an hour and a min 
		void add_time(int time);//function to increment hours and minutes
		void displayTime();//function to display time
	protected:
		int hr;
		int min;
};


class weather{
	public:
		weather();
		weather(int, int);//constructor takes temp and conditions as args
	protected:
		int temp;
		int conditions;
};


class mileMarker:public weather{//derived from weather so each milemarker has it's own weather
	public:
		mileMarker();
		mileMarker(int &temp, int condition, int i); //1. Sunny, 2. Snowy, 3. Rainy
		mileMarker(int mile);//for default highway constructor
		~mileMarker();
		void display();//displays all milemarker conditions, including temp
		void connect_next(mileMarker*);//connects nodes by getting private data
		int analyzeMarker();//analyzes the marker and adds trip time based on the conditions
		mileMarker*& go_next();//returns the next pointer
	private:
		int mile;//mile marker of the road
		int conditions;//road conitionds
		bool accident;//if there is an accident at the mile marker
		int volume;//traffic volume
		mileMarker * next;
};


class highway:public Time{
	public:
		highway();
		highway(int&, int, int, int);//highway constructor that takes args for the milemarker constructor to be called with
		~highway();
		int addMarker();//populates the highway with milemarkers
		void calculateTrips(mileMarker*);//traverses the list and incremements the time given the conditions along the way
		int display(mileMarker*);//displays a highway route
		int fastest();//returns the total amount of minutes of the highway time to see which will be faster
		mileMarker* get_head();
	private:
		mileMarker * head;
		mileMarker * tail;
};


class journey:public weather{
	public:
		journey();
		journey(int, int);
		journey(int&, int, int, int);//constructor that takes temp, condition, hour, and minute, to populate all the subsequent constructors
		~journey();
		void makeBestRoute(int i);//copies over the best route into a LLL that belongs to my journey, this is a wrapper that calls a recursive copy
		void makeBestRoute(mileMarker *&, mileMarker *);//recurive copy function
		int bestRoute();//returns which highways is the fastest by calling highways functions
		void display(int);
		void displayTime(int);//displays best routes arrival time
		void displayHome();//wrapper function that displays the list in reverse order to details journey home, using recursion
		void displayHome(mileMarker *);//recursive display
	private:
		highway * roads;//an array of highway objects that points to mileMarkers that makeup a Array of Linear Linked Lists. Dynamically allocated at run time
		mileMarker * head;//Head pointer for a LLL that manages the best route
};


#endif
