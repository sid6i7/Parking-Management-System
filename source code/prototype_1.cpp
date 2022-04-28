#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
#include<fstream>
#include<sstream>
using namespace std;

struct time;
class parkingSlot;

// This structure will be used to handle times at which a vehicle arrives or/and departes
struct time{
	
	int hh;
	int mm;
	
};

int setTotalCount(){
	
	int n;
	ifstream in;
	in.open("total_slots_count.txt");
	in>>n;
	in.close();
	
	return n;
}

int set2Count(){
	
	int n;
	ifstream in;
	in.open("total_2_wheeler_slots_count.txt");
	in>>n;
	in.close();
	
	return n;
}

int set4Count(){
	
	int n;
	ifstream in;
	in.open("total_4_wheeler_slots_count.txt");
	in>>n;
	in.close();
	
	return n;
}

int setPaymentCount(){
	
	int n;
	ifstream in;
	in.open("payment_count.txt");
	in>>n;
	in.close();
	
	return n;
	
}

float getEarning(){
	
	float e;
	ifstream in;
	in.open("earning.txt");
	in>>e;
	in.close();
	
	return e;
	
}

// Defining the Vehicle class
class vehicle{
	
	private:
		time vehicle_arrival;
		time vehicle_departure;
		string vehicle_number;
		int vehicle_type;		
		parkingSlot *myVehicleSlot;
	
	public:
		
		void setVehicleType(int x){
			
			vehicle_type = x;
			
		}
		
		int getVehicleType(){
			
			return vehicle_type;
			
		}
		
		string getVehicleNumber(){
			
			return vehicle_number;
			
		}
		
		void setVehicleArrival(){
			
			cout<<"Enter the arrival time of vehicle:\n";
			cout<<"hh: ";
			cin>>vehicle_arrival.hh;
			cout<<"mm: ";
			cin>>vehicle_arrival.mm;
			cout<<"---------------\n";
			cout<<"Vehicle Arrival time has been set to "<<vehicle_arrival.hh<<":"<<vehicle_arrival.mm<<endl;
		
		}
		void setVehicleDeparture(){
			
			cout<<"Enter the departure time of vehicle:\n";
			cout<<"hh: ";
			cin>>vehicle_departure.hh;
			cout<<"mm: ";
			cin>>vehicle_departure.mm;
			cout<<"---------------\n";
			cout<<"Vehicle Departure time has been set to "<<vehicle_departure.hh<<":"<<vehicle_departure.mm<<endl;
		
		}
		
		time getVehicleArrival(){
			
			return vehicle_arrival;
			
		}
		
		time getVehicleDeparture(){
			
			return vehicle_departure;
			
		}
		
		void allocateSlot(){
			
			myVehicleSlot = parkingSlot p(vehicle);
			
		}
		
		vehicle(time t){
		// This constructor is invoked when removeCustomer is called	
			vehicle_arrival = t;
			
		}
		
		vehicle(){
		// This constructor is invoked when addCustomer is called	
			cout<<"Enter the vehicle number: ";
			cin>>vehicle_number;
			cout<<"Enter the type of vehicle:\n2 for two-wheeler\n4 for four-wheeler\n"<<endl;
			cin>>vehicle_type;
			// Allocating the slot
			allocateSlot();
			// Setting the arrival time of vehicle
			setVehicleArrival();
					
		}					
};

// Defining the Parking Slot's class
class parkingSlot{
	
	private:		
		int slot_occupied;
		int parking_slot_type;
		vehicle v;
		
	public:
		static int total_slot_count;
		static int total_2_count;
		static int total_4_count;
		// This constructor will be used when add2_Slot() or add4_Slot() is invoked
		parkingSlot(int st){
			slot_occupied = 0;
			
			++total_slot_count;
			
			ofstream out;
			out.open("total_slots_count.txt");
			out<<total_slot_count;
			out.close();
			
			parking_slot_type = st;
			if(st==2){
				
				++total_2_count;
				ofstream out;
				out.open("total_2_wheeler_slots_count.txt");
				out<<total_2_count;
				out.close();
				
			}
			else if(st==4){
				
				++total_4_count;
				ofstream out;
				out.open("total_4_wheeler_slots_count.txt");
				out<<total_4_count;
				out.close();
				
			}
		}
		
		// This constructor will be used following the invocation of addCustomer()
		parkingSlot(vehicle myVehicle){
			v = myVehicle;
			slot_occupied = 1;
		}
		
		int isEmpty(){
			
			return slot_occupied;
			
		}
		
		/* 
		   This method is used to print the parking grid:
		   -> If the slot_occupied is 0 then O will be displayed
		   -> If the slot_occupied is 1 then X will be displayed
		*/ 
		void printGrid(vector<parkingSlot> &v){
			
		}
				
};

int parkingSlot::total_slot_count = setTotalCount();
int parkingSlot::total_2_count = set2Count();
int parkingSlot::total_4_count = set4Count();

// Defining the base person class
class person{
	
	public:
		string username;
		int user_type;
	
};

// Defining the Customer's class privately inherited from person class
class customer: private person{
	
	private:
		
		int usertype = 1;
		vehicle myVehicle;
		
	public:
		
		customer(string n){
			username = n;
		}
		
		customer(){
			
			cout<<"Enter name of the customer: ";
			cin>>username;
						
		}
		
		void setVehicle(vehicle newVehicle){
					
			myVehicle = newVehicle;		
				
		}
		
		vehicle getVehicle(){
					
			return myVehicle;
						
		}
		
		string getName(){
			
			return username;
			
		}
									
};

// Defining the Parking Operator's class privately inherited from person class
class parkingOperator: private person{
	
	private:
		
		int user_type = 2;
		string password;
			
	public:
		
		// This constructor is invoked when someone tries to login as an operator
		parkingOperator(string user, string pass){
			
			username = user;
			password = pass;
			
		}
		
		// This constructor is invoked when an admin adds a new parking operator
		parkingOperator(){
			
			cout<<"Enter username: ";
			cin>>username;
			cout<<"Enter password: ";
			cin>>password;
			
			ofstream out;
			out.open("operators.txt",ios::app);
			out<<username<<" "<<password;
			out.close();
						
		}
		
		// Function to add a new customer and their respective vehicle
		
		void addCustomer(){
			
			// creating the customer object			
			customer newCustomer;
			// creating the vehicle object
			vehicle newVehicle;
			// allocating the slot to the vehicle
			newVehicle.allocateSlot();
			// setting the arrival time of vehicle
			newVehicle.setVehicleArrival();
			// passing the vehicle object to the setVehicle function of our customer class
			newCustomer.setVehicle(newVehicle);
			
			// Writing to the customer_info file:
			ofstream out;
			out.open("customer_info.txt",ios::app);
			time arrival = newCustomer.getVehicle().getVehicleArrival();
			out<<newCustomer.getName()<<" "<<newVehicle.getVehicleNumber()<<" "<<newVehicle.getVehicleType()<<" "<<arrival.hh<<" : "<<arrival.mm<<"\n";
			out.close();
			
			out;
			out.open("vehicle_info.txt",ios::app);
			time arrival = newCustomer.getVehicle().getVehicleArrival();
			out<<newVehicle.getVehicleNumber()<<newVehicle.getVehicleType()<<" "<<arrival.hh<<" : "<<arrival.mm<<"\n";
			out.close();
		}
		
		void removeCustomer(){
			
			string customer_name;
			string vehicle_number;
			int vehicle_type;
			string temp;
			time arrival;
			time departure;			
			
			cout<<"Enter the customer name: ";
			cin>>customer_name;
			
			ifstream in;
			in.open("customer_info.txt");
			
			while(in.eof()!=0){
				in>>temp;
				// for reading vehicle number and vehicle arrival time from file
				if(strcmp(temp,customer_name)==0){
					in>>vehicle_number;
					in>>temp;
					stringstream geek(temp);
					geek>>vehicle_type;
					in>>temp;
					geek(temp);
					geek>>arrival.hh;
					
					in>>temp;
					in>>temp;
					geek(temp);
					geek>>arrival.mm;
				}
			}
			
			vehicle v(arrival);
			customer c(customer_name);
			v.setVehicleDeparture();
			v.setVehicleType(vehicle_type);
			
			c.setVehicle(v);		
					
			payment p(c);
			cout<<"Here is your bill: "<<endl;
			cout<<"=================="<<endl;
			p.printBill();
			 					
		}
				
		// this function is used to check whether login credentials of a parking operator
		// are correct or not
		
		int verify(string u, string p){
			
			// pull username and password data from the files and check
			// return 0 if not-correct and return 1 if correct
			
			ifstream in;
			in.open("operator.txt");
			string user,pass;
			
			while(in.eof()!=1){
				in>>u>>p;
				if(strcmp(user,u)==0 && strcmp(pass,p)==0){
					cout<<"successfully logged in!!"<<endl;
					return 1;
				}
			}
			cout<<"wrong username or password.."<<endl;
			return 0;			
		}	
};

// Defining the bill class used to handle bills
class bill{
	
	public:	
	
		static int count;
		customer c;
		vehicle v;		
		float duration;
		float amount;
		int bill_id;
				
		// Defining the constructor for bill classs
		bill(customer cust){
			
			c = cust;
			//v = cust.getVehicle();
			//duration = (v.getVehicleDeparture().hh + (((float)v.getVehicleDeparture().mm)/60)) - (v.getVehicleArrival().hh + (((float)v.getVehicleArrival().mm)/60));
			++count;
			bill_id = count;
											
		}
		
		void printBill(){
			
			cout<<"customer name: "<<c.username<<endl;
			cout<<"vehicle number: "<<c.getVehicle().setVehicleArrival()<<endl;
			cout<<"duration of parking: "<<duration<<endl;
			cout<<"==================="<<endl;
			cout<<"total amount: "<<amount<<endl;
			
		}
					
};

int bill::count = setPaymentCount();// Read from file and put here9

// Defining the payment class privately inherited from bill, this is used to calculate amount to be payed..
class payment: public bill{
	
	private:
		
				
		float rate_2 = 20;
		float rate_4 = 40;
	
	public:
				
		static float total_earned;
		
		payment(customer c) : bill(c){
			
			if(v.getVehicleType()==2){
				amount = rate_2 * duration;
			}
			else if(v.getVehicleType()==4){
				amount = rate_4 * duration;
			}
			else{
				cout<<"error.. please check the vehicle type.. it might not be supported";
				amount = -1;
			}
			
			ofstream out;
			out.open("payments.txt",ios::app);
			out<<"customer name: "c.getName()<<", vehicle number: "<<v.getVehicleNumber()<<", arrival: "<<v.getVehicleArrival()<<", departure: "<<v.getVehicleDeparture()<<", duration: "<<duration<<"hrs "<<", payment: "<<amount<<"rs\n";
			out.close();
			
			total_earned = total_earned + amount;
			
			out;
			out.open("earning.txt");
			out<<total_earned;
			out.close();
			
		}
	
};

float payment::total_earned = getEarning();

// Defining the admin's class privately inherited from person class
class admin: private person{
	
	private:
		user_type = 3;
		string password;
	
	public:
		
		admin(string n, string p){
			
			username = n;
			password = p;
			
		}
		
		// Function used to add a new parking operator
		void addOperator(vector<parkingOperator> &p){
			
			parkingOperator op;
			p.push_back(op);
			
		}
		
		//Function used to remove an existing parking operator
		void removeOperator(){
			
			
			
		}
		// This function is used to add 2-wheeler parking slots
		void add2_slot(vector<parkingSlot> &v_2){
			int n, i;
			
			cout<<"How many 2-wheeler slots would you like to add?"<<endl;
			for(i=1;i<=n;i++){
				parkingSlot newSlot(2);
				v_2.push_back(newSlot);
			}			
		}
		
		// This function is used to remove 2-wheeler parking slot/s
		void remove2_slot(vector<parkingSlot> &v_2){
			
		}
				
		//This function is used to add 4-wheeler parking slots
		void add4_slot(vector<parkingSlot> &v_4){
			int n, i;
			
			cout<<"How many 4-wheeler slots would you like to add?"<<endl;
			for(i=1;i<=n;i++){
				parkingSlot newSlot(4);
				v_4.push_back(newSlot);
			}
		}
		
		// This function is used to remove 4-wheeler parking slot/s
		void remove4_slot(vector<parkingSlot> &v_4){
			
		}
				
		int verify(){
			
			// pull username and password data from the files and check
			// return 0 if not-correct and return 1 if correct
			
			ifstream in;
			in.open("admin.txt");
			string user, pass;
			
			in>>user>>pass;
			
			in.close();
			
			if(strcmp(user,username)==0 && strcmp(pass,password)==0){
				cout<<"successfully logged in!!"<<endl;
				return 1;
			}
			else{
				cout<<"wrong username or password.."<<endl;
				return 0;
			}
			
		}
			
};


// Main function:
int main(){
	
	
	vector<parkingSlot> slots_2;
	vector<parkingSlot> slots_4;
	
	// Store this in file and only allow it to exist once
	// admin p("siddhant","123");
		
	cout<<"======================"<<endl;
	cout<<"1 to login as admin"<<endl;
	cout<<"2 to login as an operator "<<endl;
	cout<<"3 to exit the program..."<<endl;
	cout<<"======================"<<endl;
			
		int c1;
		cin>>c1;
		
		int proceed = 0;
		string username;
		string password;
		
		switch(c1){
		
		case 1:
								
		cout<<"Enter your registered username: ";
		cin>>username;
		cout<<"Enter your registered password: ";
		cin>>password;
		
		admin a(username, password);
		
		proceed = a.verify();
		if(proceed==0){
			break;
		}
				
		if(proceed==1){
			int z=1;					
			while(z){
				
				cout<<"1 to manage parking slots"<<endl;
				cout<<"2 to check earnings"<<endl;
				cout<<"3 to logout.."<<endl;
				int c2;
				cin>>c2;
				if(c2==3){
					break;
					z = 0;
				}
				switch(c2){
				case 1:
					cout<<"Which type of parking slots would you like to manage?\n2 for 2-wheelers\n4 for 4-wheelers"<<endl;
					int c3;
					cin>>c3;
					
					switch(c3){
						case 2:
							
							cout<<"1 to add parking slot/s"<<endl;
							cout<<"2 to remove parking slot/s"<<endl;
							cout<<"3 to list the number of 2-wheeler parking slot\s"<<endl;
							
							int c4;
							cin>>c4;
							if(c4==1){
								a.add2_slot(slots_2);
							}
							else if(c4==2){
								a.remove2_slot(slots_2);
							}
							else if(c4==3){
								ifstream in;
								in.open("total_2_wheeler_slots_count.txt");
								int temp;
								in>>temp;
								in.close();
								cout<<"number of 2-wheeler slots: "<<temp<<endl;
							}
							else{
								cout<<"invalid choice..."<<endl;
							}
							break;
							
						case 4:
							
							cout<<"1 to add parking slot/s"<<endl;
							cout<<"2 to remove parking slot/s"<<endl;
							cout<<"3 to list the number of 4-wheeler parking slot\s"<<endl;
							int c4;
							cin>>c4;
							if(c4==1){
								a.add4_slot(slots_4);
							}
							else if(c4==2){
								a.remove4_slot(slots_4);
							}
							else if(c4==3){
								ifstream in;
								in.open("total_2_wheeler_slots_count.txt");
								int temp;
								in>>temp;
								in.close();
								cout<<"number of 4-wheeler slots: "<<temp<<endl;
							}
							else{
								cout<<"invalid choice..."<<endl;
							}
							break;
							
						default:							
							cout<<"invalid selection..."<<endl;							
						}
					break;
											
				case 2:
					
					float x;
					ifstream in;
					in.open("earning.txt");
						in>>x;
					in.close();
					cout<<"total money earned: "<<x<<"rs"<<endl;
					
				case 3:
					z = 0;		
					break;
					
				default:
					
					cout<<"invalid choice..."<<endl;
										
				}
				
			}
									
		}
		
		break;
		
		case 2:
			
			cout<<"Enter your registered username: ";
			cin>>username;
			cout<<"Enter your registered password: ";
			cin>>password;
			
			parkingOperator p(username, password);
			proceed = p.verify();
			
			if(proceed==0){
				break;
			}
			if(proceed==1){
				int o = 1;
				while(o){
					cout<<"1 to add a customer(vehicle arrival)"<<endl;
					cout<<"2 to remove a customer(vehicle departure)"<<endl;
					cout<<"3 to view current vehicles on the parking"<<endl;
					cout<<"4 to logout..."<<endl;
				
					int c5;
					cin>>c5;
				
					switch(c5){
					
						case 1:
							p.addCustomer();
							break;	
							
						case 2:
							p.removeCustomer();	
							break;
							
						case 3:
							
						case 4:
							o = 0;
							break;
						
						default:
							cout<<"invalid choice..."<<endl;			
					}
				}
								
			}
			
			break;
			
		default:
			cout<<"invalid choice.."<<endl;
		
	}
	
	cout<<"exiting the program.."<<endl;
	
	return 0;
		
}
