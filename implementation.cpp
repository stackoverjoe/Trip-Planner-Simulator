//Joe Leland
//CS202
//Assignment #1
//This file contains all of the functions defined in header.h
#include "header.h"


Time::Time():hr(0), min(0){};//default Time constructor


Time::Time(int h, int m):hr(h), min(m){};//Time constructor to set hours and minutes


mileMarker::mileMarker():conditions(0), accident(false), volume(0), next(NULL){};//default mileMarker constructor


mileMarker::mileMarker(int m):weather(), mile(m), conditions(0), accident(false), volume(0), next(NULL){};//mileMarker constructor that can create mileMarkers with no conditions preset 


mileMarker::mileMarker(int &t, int c, int i):weather(t, c), mile(i), next(NULL){//mileMarker road conditions: 1: DRY 2: SNOWY 3:WET 4: ICY
	int chance = 0;						    //This constructor uses the temperature, and weather conditions, from portland to estimate
								    //what the conditions at each mileMarker are.

	//this if-else block determines the road conditions by looking at the temp and weather, then
	//generating a random number. Logic allows for greater chance of snowy, or icy, roads depending
	//on if it was snowing earlier, and if it is cold enough, etc.
	if(t <= 32 && c == 2){
		conditions = 2;//snow
	}
	else if(t > 32 && c == 2){
		chance = rand()%30;
		if(chance > 15){
			conditions = 2;//snow
		}
		else{
			conditions = 1;//dry
		}

	}
	else if(t <= 32 &&  c == 1){
		i += 1;
		chance = rand()%i;//chance for snow increases with altitude 
		if(chance > 20){
			conditions = 2;//snow
		}
		else{
			conditions = 1;//dry
		}
	}
	else if(t > 32 && c == 1){
		this->conditions = 1;//dry				
	}
	
	else if(t <= 32 && c == 3){
		conditions = 4;//icy
	}
	else if(t > 32 && c == 3){
		conditions = 3;//wet
	}
	//accident decision
	//If an accident has occured depends on the road conditions, the chance of an accident goes up
	//as the roads get worse.
	if(conditions == 1){
		chance = rand()%100;
		if(chance <= 10){
			accident = true;
		}
		else{
			accident = false;
		}
	}
	else if(conditions == 2){
		chance = rand()%100;
		if(chance > 70){
			accident = true;
		}
		else{
			accident = false;
		}
	}
	else if(conditions == 3){
		chance = rand()%100;
		if(chance < 20){
			accident = true;
		}
		else{
			accident = false;
		}
	}
	else if(conditions == 4){
		chance = rand()%100;
		if(chance < 35){
			accident = true;
		}
		else{
			accident = false;
		}
	}
	//Traffic volume adjuster
	//Finally to decide the traffic volume, the road conditions and accidents are looked at. e.g. Accident + Ice = more traffic
	//then Sun + no accident. 
	if(conditions == 1 && accident == false){
		volume = 1;
	}
	else if(conditions == 1 && accident == true){
		volume = 2;
	}
	else if(conditions == 2 && accident == false){
		volume = 1;
	}
	else if(conditions == 2 && accident == true){
		volume = 3;
	}
	else if(conditions == 3 && accident == false){
		volume = 1;
	}
	else if(conditions == 3 && accident == true){
		volume = 2;
	}
	else if(conditions == 4 && accident == false){
		volume = 2;
	}
	else if(conditions == 4 && accident == true){
		volume = 3;
	}
			
};


//this destructor acts in a recursive fashion by automatically calling the next delete in a linear linked list
mileMarker::~mileMarker(){
	if(next){
		delete next;
		next = NULL;
	}
}


//this default highway is not used in the program, but would set up the milemarkers with no conditions if called
highway::highway():Time(), head(NULL), tail(NULL){

	for(int i = 20; i < 140; i += 20){
		if(!head){
			mileMarker *temp = new mileMarker(i);
			head = tail = temp;
		}
		else{
			mileMarker *temp = new mileMarker(i);
			tail->connect_next(temp);
			tail = temp;
		}
	}

};


//this highway constructor takes in the arguments from journey to populate the milemarker constructors args.
//the weather decreases anywhere from 0-5 degrees as you ascend the mountain, this allows for more interesting
//randomized results in the prediction algorithims, it also reflects a dynamic weather system.
highway::highway(int& t, int c, int h, int m):Time(h+2, m+11), head(NULL), tail(NULL){
	int local = t;
	for(int i = 20; i < 160; i += 20){
		if(!head){
			mileMarker *temp = new mileMarker(t, c, i);//milemarker is called with temp, conditions, and i(for the mile marker position)
			head = tail = temp;
			t -= rand()%6;
		}
		else{
			mileMarker *temp = new mileMarker(t, c, i);//subsequent mile markers are added at the tail to avoid traversal
			tail->connect_next(temp);
			tail = temp;
			t -= rand()%6;
		}
	}
	t = local;//resets temp for second highway object

};


//this destructor calls the mile marker destructor which will deallocate the entire linked list
highway::~highway(){
	if(head){
		delete head;
		head = NULL;
	}
}


//default weather constructor
weather::weather():temp(0), conditions(0){};


//weather constructor that takes temp and conditions as arguments
weather::weather(int t, int c): temp(t), conditions(c){};


//default journey constructor sets the array of roads to however many highways you are comparing (in this case 2 for hwy 26 and 84)
journey::journey():weather(), head(NULL){

	roads = new highway[ROADS];

};


//Constructor that can create the highways with their default NULL values
journey::journey(int t, int c): weather(t, c), head(NULL){

	roads = new highway[ROADS];

};


//this constructor is the one called from main. It allocates the array of LLL and calls those highway element constructors
//and provides all the data they need to call their respective mileMarker constructors and calculate the conditions given
//all the data passed as args.
journey::journey(int &t, int c, int h, int m): weather(t, c), head(NULL){

	roads = new highway[ROADS]{highway(t, c, h, m), highway(t, c, h, m)};//allocates an array of highways

};


//this destructor deallocates the array of LLL by first calling delete on the array, which
//calls the highways to delete their lists, and finally deletes its own LLL used to store
//the optimal route results
journey::~journey(){
	delete[] roads;
	roads = NULL;
	delete head;
	head = NULL;
}


//funstion used to connect mileMarkers, given their data is private
void mileMarker::connect_next(mileMarker* to_connect){
	this->next = to_connect;
};


//returns the nodes next
mileMarker*& mileMarker::go_next(){
	return this->next;
};


//returns the a particular highway head element
mileMarker* highway::get_head(){
	return this->head;
};


//recursive function to display a highways elements from the array of LLL
int highway::display(mileMarker *start){
	if(!start){
		return 0;
	}
	start->display();//calls mileMarker display
	return display(start->go_next());

};


//mileMarker display function that checks the roads conditions and outputs the appropriate message 
void mileMarker::display(){
	using namespace std;
	cout << "Mile: " << mile << '\n'
	     << "Conditions: "; 
	     if(conditions == 1){
		     cout << "The roads are dry." << '\n';
	     }
	     else if(conditions == 2){
		    cout << "The roads are snowy." << '\n';
	     }
	     else if(conditions == 3){
		     cout << "The roads are wet." << '\n';
	     }
	     else{
		     cout << "The roads are icy." << '\n';
	     }
	     if(accident){
		     cout << "There has been an accident at this mile marker." << '\n';  
	     }
	     else{
		     cout << "No accidents reported." << '\n';
	     }
	     if(volume == 1){
		     cout << "Traffic volume is light." << '\n';
	     }
	     else if(volume == 2){
		     cout << "Traffic volume is moderate." << '\n';
	     }
	     else{
		     cout << "Traffic volume is heavy." << endl;
	     }
	     cout << "Temperature: " << temp << endl << endl;
};


//display function recursivly calls highway display function with desired hwy, represented as an int, 0 or 1
void journey::display(int hwynum){
	mileMarker*head = roads[hwynum].get_head();
	roads[hwynum].display(head);
	//mileMarker *temp = head;
	/*
	while(temp){
		temp->display();
		temp = temp->go_next();
	}*/


};


//wrapper for recursive return home details
void journey::displayHome(){
	mileMarker *temp = head;
	displayHome(temp);

}


//This will print the trip details in reverse order using head recursion
void journey::displayHome(mileMarker *head){
	if(!head){
		return;
	}
	displayHome(head->go_next());
	head->display();

}


//add time function which is used to increment a highways final arrival time
void Time::add_time(int to_add){
	if(min + to_add < 60){
		min = min + (to_add);
	}
	else{
		hr += 1;
		min = (min + to_add) - 60;
		if(hr > 12){
			hr = 1;
		}
	}
};


//this highways function recursivly traverses the list, by calling the analyzemarker function (which returns an int) and
//supplying that number back to the add_time function, which will increment the highways time
void highway::calculateTrips(mileMarker* head){
	if(!head){
		return;
	}
	add_time(head->analyzeMarker());
	calculateTrips(head->go_next());	

}


//function that looks at all the conditions of a mile marker, and adds trip time accordingly, returning the value to add in minutes
int mileMarker::analyzeMarker(){
	int time_to_add = 0;
	if(conditions == 2){
		time_to_add += 10;
	}
	else if(conditions == 3){
		time_to_add += 5;
	}
	else if(conditions == 4){
		time_to_add += 15;
	}
	if(accident){
		time_to_add += 15;
	}
	return time_to_add;

}


//bestRoute increments each highways arrival time by calling the calculateTrips function, it then converts those times
//into minutes using the fastest() function, finally those are compared and the faster highway is returned to the caller
int journey::bestRoute(){
	int x = 0;
	int y = 0;
	mileMarker *temp = roads[0].get_head();
	roads[0].calculateTrips(temp);
	temp = roads[1].get_head();
	roads[1].calculateTrips(temp);
	x = roads[0].fastest();
	y = roads[1].fastest();
	if(x < y){
		return 1;
	}
	else{
		return 0;
	}
}


int highway::fastest(){
	int total = 0;
	return total = (hr*60) + min;//converts time into minutes for easy comparison
}


void journey::displayTime(int i){
	roads[i].Time::displayTime();//calls the times display function to output the arrival time

}


//display function for time
void Time::displayTime(){
	using namespace std;
	if(min >= 10){
		cout << hr << ":" << min << endl;
	}
	else{
		cout << hr << ":" << '0' << min << endl;
	}
}


//wrapper function calls a recursive LLL copy for journey's class. This list represents the idea route
void journey::makeBestRoute(int i){
	mileMarker *temp = roads[i].get_head();
	makeBestRoute(head, temp);

}


//recursive LLL copy
void journey::makeBestRoute(mileMarker*& dest, mileMarker *source){
	if(!source){
		return;
	}
	dest = new mileMarker(*source);//calls implicit copy constructor
	return makeBestRoute(dest->go_next(), source->go_next());

}











