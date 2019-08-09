//Joe Leland
//CS202
//Assignment #1
//This file takes input from the user in the form of temperature, initial weather condition, and departure time. It then creates the journey object with those args
#include "header.h"
using namespace std;


int main(){
	int tempp = 0;//variable for portland temperature
	int tcondition = 0;//variable for portland weather
	int hr = 0;//variable for hour
	int min = 0;//variable for minute
	int best = 0;//used to store fastest highway
	int rand();//random int
	srand(time(NULL));//seeds time to use for random number generation 
	
	cout << "Hello, welcome to the Mt. Hood Trip Predictor!\nPlease enter the current temperature in Portland: " << endl;
	cin >> tempp;//gets portland temp
	cin.clear();
	cin.ignore(SIZE, '\n');
	cout << "What is the weather in Portland like:\n1.Sunny\n2.Snowy\n3.Rainy" << endl;
	cin >> tcondition;//gets portland weather condition
	cin.clear();
	cout << "what time are you departing? (Please enter hr min, seperated by a space (ex. 2 30)\n";
	cin >> hr;//gets the time of departure
	cin >> min;
	cin.clear();
	cin.ignore(SIZE, '\n');
	cout << endl;
	journey my_journey(tempp, tcondition, hr, min);//journey created with temp, condition, hours, and minutes
	best = my_journey.bestRoute();//returns 1 if HWY 26 is fastest, 0 if hwy 84
	my_journey.makeBestRoute(best);//copies best route into journey object
	//best route is displayed to the screen
	if(best){
		cout << "Highway 26 is the fastest route to Mt. Hood. The arrival time is: ";  my_journey.displayTime(0); cout << endl;//displays arrival time
		cout << "Please make sure to equip chains on icy or snowy roads.\n\n";
		cout << "The travel conditions are: " << endl;
		my_journey.display(1);
		cout << "Return trip details: " << endl
		     << "________________________________" << endl << endl;
		my_journey.displayHome();//displays return home details
	}
	else{
		cout << "Highway 84 is the fastest route to Mt. Hood. The arrival time is: ";  my_journey.displayTime(1); cout << endl;
		cout << "Please make sure to equip chains on icy or snowy roads.\n\n";
		cout << "The travel conditions are: " << endl;
		my_journey.display(0);
		cout << "Return trip details: " << endl
		     << "________________________________" << endl << endl;
		my_journey.displayHome();

	}
	
	return 0;

}
