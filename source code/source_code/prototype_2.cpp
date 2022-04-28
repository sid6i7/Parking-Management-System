#include<bits/stdc++.h>
#include<cstring>
#include<fstream>
#include<sstream>
using namespace std;

struct t{
// used for storing times of vehicle-arrvial and vehicle-departure	
	int hh;
	int mm;
	
};

class person{
// Defining the base person class	
	public:
		string username;
		int user_type;
	
};

class owner: private person{
// Defining the vehicle owner class privately derived from person			
	public:
		void setName(string n){
			username = n;
		}
		
		string getOwnerName(){
			return username;
		}
		
		owner(){}
		
		owner(string n){
			user_type = 1;
			username = n;
		}
			
};

class slot{
// Defining the slot class	
	private:
		static int total_slot_count;
		static int total_occupied_count;
		static int total_2_slot;
		static int total_2_occupied;
		static int total_4_slot;
		static int total_4_occupied;
		int slot_id;
		int slot_type;
		int slot_occupied;
		 
	public:
		void getSlotStatus(){
			cout<<"=============="<<endl;
			cout<<"available slots"<<endl;
			cout<<"=============="<<endl;
			cout<<"\n"<<endl;
			cout<<"total slots: "<<total_slot_count<<endl;
			cout<<"two-wheeler-slots: "<<total_2_slot<<endl;
			cout<<"four-wheeler-slots: "<<total_4_slot<<endl;
			cout<<"\n";
			cout<<"==============="<<endl;
			cout<<"occupied status"<<endl;
			cout<<"==============="<<endl;
			cout<<"two-wheeler-slots occupied: "<<total_2_occupied<<endl;
			cout<<"four-wheeler-slots occupied: "<<total_4_occupied<<endl;
			cout<<"\n";
		}		
		int getOccupiedCount(int x){
			if(x==2){
				return total_2_occupied;
			}
			else if(x==4){
				return total_4_occupied;
			}
			else if(x==6){
				return total_occupied_count;
			}
			else{
				return -1;
			}
		}
};

int getSlotCount(int x){
	// USED TO GET COUNT OF PARKING SLOTS AT THE TIME OF COMPILATION
	ifstream in;
	int count;
	in.open("slots_count.txt");
	string temp;
	if(x==2){
		in>>temp;
		in>>temp;
		stringstream geek(temp);
		geek>>count;
		
		return count;
	}
	else if(x==4){
		in>>temp;
		in>>temp;
		in>>temp;
		in>>temp;
		stringstream geek(temp);
		geek>>count;
		
		return count;
	}
	else{
		return -1;
	}
	in.close();
		
}

int getVehicleCount(int x){
// This function returns current vehicle count	
	ifstream in;
	in.open("vehicles_count.txt");
	string temp;
	int n;
	
	if(x==2){
		in>>temp;
		in>>temp;
		stringstream geek(temp);
		geek>>n;
		
		in.close();
		return n;
	}
	else if(x==4){
		in>>temp;
		in>>temp;
		in>>temp;
		in>>temp;
		stringstream geek(temp);
		geek>>n;
		
		in.close();
		return n;
	}
	
	in.close();
	
}

int slot::total_2_slot = getSlotCount(2);
int slot::total_4_slot = getSlotCount(4);
int slot::total_slot_count = slot::total_2_slot + slot::total_4_slot;
int slot::total_2_occupied = getVehicleCount(2);
int slot::total_4_occupied = getVehicleCount(4);
int slot::total_occupied_count = slot::total_2_occupied + slot::total_4_occupied;

class vehicle{
// defining the vehicle class	
	private:				
		int vehicle_type; // 2 for two-wheelers and 4 for four-wheelers
		string vehicle_number;	
		int slot_number;
		owner c;			
		
	public:
		static int total_vehicle_count;
		static int two_wheeler_count;
		static int four_wheeler_count;
		// t is a structure defined at line: 170
		t vehicle_arrival; 
		t vehicle_departure;
		
		vehicle(string vn, int type, int slot){
		// constructor-1			
			vehicle_number = vn;
			vehicle_type = type;
			slot_number = slot;
			
			ifstream in;
			in.open("vehicle_data.txt");
			string temp, temp2;
			while(in.eof()!=1){
				in>>temp;
				if(temp==vn){
					in>>temp;
					in>>temp;
					in>>temp;
					stringstream geek(temp);
					geek>>vehicle_arrival.hh;
					in>>temp2;
					in>>temp2;
					stringstream geek2(temp2);
					geek2>>vehicle_arrival.mm;
				}
			}
			in.close();
		}
		
		owner getOwner(){
			return c;
		}
		
		void setDeparture(){
			
			cout<<"enter the current time"<<endl;
			cout<<"hh: ";
			cin>>vehicle_departure.hh;
			cout<<"mm: ";
			cin>>vehicle_departure.mm;
				
		}
		
		void allocateSlot(){
			ifstream in;
			ofstream out;
			string temp;
			int x;
			if(vehicle_type==2){
				in.open("two_wheeler_slots.txt");
				out.open("temp.txt",ios::app);
				int count = 0;
				int go = 1;
				
				while(in.eof()!=1){
					getline(in,temp);
					if(temp.empty()!=1){
						++count;
					}
					// updating the two-wheeler-slots record
					if(temp.find("empty")!=string::npos && go==1){
						out<<count<<" : "<<"filled:"<<" "<<vehicle_number<<"\n";
						slot_number = count;
						go = 0;
						getline(in,temp);
					}
					out<<temp<<"\n";
				}
				out.close();
				in.close();
				remove("two_wheeler_slots.txt");
				rename("temp.txt","two_wheeler_slots.txt");		
			}
			else if(vehicle_type==4){
				in.open("four_wheeler_slots.txt");
				out.open("temp.txt",ios::app);
				int count = 0;
				int go = 1;
							
				while(in.eof()!=1){					
					getline(in,temp);
					if(temp.empty()!=1){
						++count;
					}
					// updating the four-wheeler-slots record
					if(temp.find("empty")!=string::npos && go){
						out<<count<<" : "<<"filled:"<<" "<<vehicle_number<<"\n";
						slot_number = count;
						go = 0;
						getline(in,temp);
					}
					out<<temp<<"\n";
				}
				out.close();
				in.close();
				remove("four_wheeler_slots.txt");
				rename("temp.txt","four_wheeler_slots.txt");		
			}
		}
		
		int getSlotNumber(){
			return slot_number;
		}
		
		string getOwnerName(){
			return c.getOwnerName();
		}
		
		string getVehicleNumber(){
			return vehicle_number;
		}
		
		int getVehicleType(){
			return vehicle_type;
		}
		
		vehicle(){
			// constructor-2
			cout<<"enter the owner's name: "<<endl;
			string name;
			cout<<"name: ";
			cin>>name;
			c.setName(name);
			
			cout<<"enter vehicle's type, 2 for two-wheelers and 4 for four-wheelers"<<endl;
			cout<<"type: ";
			cin>>vehicle_type;
			slot s;
			
			if(vehicle_type==2 && getSlotCount(2)==0){
				cout<<"---------------------------------------------------------------------"<<endl;
				cout<<"cannot add vehicle because no two-wheeler slots present in the system"<<endl;
				return;
			}
			else if(vehicle_type==4 && getSlotCount(4)==0){				
				cout<<"---------------------------------------------------------------------"<<endl;
				cout<<"cannot add vehicle because no four-wheeler slots present in the system"<<endl;
				return;
			}
			
			if(vehicle_type==2 && getSlotCount(2)==getVehicleCount(2)){
				cout<<"--------------------------------------------------"<<endl;
				cout<<"cannot add vehicle..all two-wheeler slots are full"<<endl;
				return;
			}
			else if(vehicle_type==4 && getSlotCount(4)==getVehicleCount(4)){
				cout<<"---------------------------------------------------"<<endl;
				cout<<"cannot add vehicle..all four-wheeler slots are full"<<endl;
				return;
			}
						
			cout<<"enter vehicle's number"<<endl;
			cout<<"number: ";
			cin>>vehicle_number;
			
			cout<<"enter the current time"<<endl;
			cout<<"hh: ";
			cin>>vehicle_arrival.hh;
			cout<<"mm: ";
			cin>>vehicle_arrival.mm;
			
			allocateSlot();			
		}	
};

// initializing static values using functions
int vehicle::two_wheeler_count = getVehicleCount(2);
int vehicle::four_wheeler_count = getVehicleCount(4);
int vehicle::total_vehicle_count = vehicle::two_wheeler_count + vehicle::four_wheeler_count;

int getOperatorCount(){
	ifstream in;
	string n;
	int x;
	in.open("operator_count.txt");
	in>>n;
	stringstream geek(n);
	geek>>x;
	in.close();
	
	return x;	
}
float getTotalEarned(){
// This function returns total money earned
	float x;
	ifstream in;
	in.open("total_earning.txt");
	in>>x;
	in.close();
	
	return x;
	
}

int getBillCount(){
// This function returns total transactions done till now	
	int x;
	ifstream in;
	in.open("bill_count.txt");
	in>>x;
	in.close();
	
	return x;
	
}

void writeVehicleCount(int t, int n){
	// USED TO WRITE NEW VEHICLES COUNT FILE
	// EVERYTIME A CHANGE IS DONE TO THE VEHICLES COUNT
	ofstream out;
	out.open("temp.txt",ios::app);
	if(t==2){
		out<<"two-wheelers: "<<n<<"\n";
		out<<"four-wheelers: "<<vehicle::four_wheeler_count<<"\n";
		out<<"total-vehicles: "<<n+vehicle::four_wheeler_count<<"\n";	
	}
	else if(t==4){
		out<<"two-wheelers: "<<vehicle::two_wheeler_count<<"\n";
		out<<"four-wheelers: "<<n<<"\n";
		out<<"total-vehicles: "<<n+vehicle::two_wheeler_count<<"\n";
	}
	out.close();
	remove("vehicles_count.txt");
	rename("temp.txt","vehicles_count.txt");
}

void writeSlotCount(int t, int n){
	// USED TO WRITE NEW SLOT COUNT FILE
	// EVERYTIME A CHANGE IS DONE TO THE SLOTS COUNT
	ofstream out;
	out.open("temp.txt",ios::app);
	if(t==2){
		out<<"two-wheeler-slots: "<<n<<"\n";
		out<<"four-wheeler-slots: "<<getSlotCount(2)<<"\n";
		out<<"total-slots: "<<n+getSlotCount(4)<<"\n";	
	}
	else if(t==4){
		out<<"two-wheeler-slots: "<<getSlotCount(2)<<"\n";
		out<<"four-wheeler-slots: "<<n<<"\n";
		out<<"total-slots: "<<n+getSlotCount(2)<<"\n";
	}
	out.close();
	remove("slots_count.txt");
	rename("temp.txt","slots_count.txt");
	
}

class bill{
// defining the bill class			
	public:
		
		static int bill_count;
		static float total_earned;
		float duration;	
		float amount;			
		int bill_id;
		
		bill(vehicle v){
			// constructor	
					
			duration = (v.vehicle_departure.hh - v.vehicle_arrival.hh) + ((float)(v.vehicle_departure.mm - v.vehicle_arrival.mm)/60);
			++bill_count;
			bill_id = bill_count;												
		}
		
		void printBill(vehicle v,string oname){
			// used to print out customer's bill
			
			cout<<" "<<endl;
			cout<<"thank you for your stay!!"<<endl;
			cout<<"------------------------------------"<<endl;
			cout<<"name: "<<oname<<endl;
			cout<<"vehicle number: "<<v.getVehicleNumber()<<endl;
			cout<<"duration of parking: "<<duration<<" hrs"<<endl;
			cout<<"amount to be payed: "<<amount<<" rs"<<endl;
			cout<<"------------------------------------"<<endl;			
		}						
};
// initializing static values using functions
int bill::bill_count = getBillCount(); // function at line: 21
float bill::total_earned = getTotalEarned(); // function at line: 9

class payment : private bill{
// defining the payment class privately inherited from bill	
	private:
		float rate_2 = 30; // rate of two-wheelers per hour
		float rate_4 = 60; // rate of four-wheelers per hour
	public:
		payment(vehicle v,string oname):bill(v){			
			//constructor
			if(v.getVehicleType()==2){
				amount = duration*rate_2;
			}
			else if(v.getVehicleType()==4){
				amount = duration*rate_4;
			}
			
			total_earned = total_earned + amount;
						
			ofstream out;
			// updating the payment records
			out.open("payments.txt",ios::app);
			out<<"owner: "<<oname<<" vehicle_number: "<<v.getVehicleNumber()<<" duration: "<<duration<<" amount: "<<amount<<"rs\n";
			out.close();
			
			// updating the total earning record
			out.open("total_earning.txt",ios::app);
			out<<total_earned;
			out.close();
			
			// updating the bill count record
			out.open("bill_count.txt",ios::app);
			out<<bill_count;
			out.close();
			
			// printing the bill
			printBill(v,oname);
		}	
};

class admin: private person{
// defining the admin's class privately inherited from person class	
	private:
		string password;
	
	public:
		
		admin(string n, string p){	
		// constructor		
			user_type = 3;
			username = n;
			password = p;			
		}
		
		void changeAdminPassword(){
			string new_password;
			cout<<"======================="<<endl;
			cout<<"changing admin password"<<endl;
			cout<<"======================="<<endl;
			cout<<"\n";
			cout<<"new password: ";
			cin>>new_password;
			ofstream out;
			out.open("admin.txt");
			out<<"admin"<<" "<<new_password<<"\n";
			out.close();
			cout<<"-----------------------------"<<endl;
			cout<<"password succesfully changed!"<<endl;
			cout<<"-----------------------------"<<endl;
		}
		
		void changeOperatorPassword(){
			// used to change a current operator's password
			cout<<"=========================="<<endl;
			cout<<"changing operator password"<<endl;
			cout<<"=========================="<<endl;
			cout<<"\n";
			string username, new_password, temp;
			int found = 0;
			cout<<"operator's username: ";
			cin>>username;
			
			ifstream in;
			ofstream out;
			in.open("operator.txt");
			out.open("temp.txt",ios::app);
			
			while(in.eof()!=1){
				in>>temp;
				if(temp==username){
					cout<<"new password: ";
					cin>>new_password;
					
					out<<username<<" "<<new_password<<"\n";
					found = 1;
					in>>temp;
				}
				else{
					out<<temp<<" ";
					in>>temp;
					out<<temp<<"\n";
				}
			}
			in.close();
			out.close();
			remove("operator.txt");
			rename("temp.txt","operator.txt");
			
			if(found==1){
				cout<<"----------------------------"<<endl;
				cout<<"password succesfully changed"<<endl;
				cout<<"----------------------------"<<endl;
			}
			else{
				cout<<"---------------------------"<<endl;
				cout<<"operator could not be found"<<endl;
				cout<<"---------------------------"<<endl;
			}
		}
		
		void listSlots(){
			// used to print out the number of slots currently in the parking space
			system("cls");
			ifstream in;
			in.open("slots_count.txt");
			string temp;
			while(in.eof()!=1){
				getline(in,temp);
				cout<<temp<<endl;
			}	
		}
		
		void removeSlot(int t){
			// used to remove slot or slots
			int n,end,i;
			cout<<"how many slots would you like to remove?"<<endl;
			cout<<"ans: ";
			cin>>n;
			
			ifstream in;
			ofstream out;
			string temp;
			
			if(t==2){
				// for two-wheelers
				in.open("two_wheeler_slots.txt");
				out.open("temp.txt",ios::app);
				end = getSlotCount(2) - n;
				if(end<0){
					cout<<"error.. cannot remove given number of slots\nonly "<<getSlotCount(2)<<" slots are present in the system"<<endl;
					in.close();
					out.close();
					return;
				}
				for(i=1;i<=end;i++){
					getline(in,temp);
					out<<temp<<"\n";
				}
				in.close();
				out.close();
				remove("two_wheeler_slots.txt");
				rename("temp.txt","two_wheeler_slots.txt");
				writeSlotCount(2,end);
				
				cout<<"================================================="<<endl;
				cout<<n<<" two-wheeler slots successfully removed!"<<endl;
				cout<<"================================================="<<endl;
			}
			else if(t==4){
				// for four-wheelers
				in.open("four_wheeler_slots.txt");
				out.open("temp.txt",ios::app);
				end = getSlotCount(4) - n;
				if(end<0){
					cout<<"error.. cannot remove given number of slots\nonly "<<getSlotCount(4)<<" slots are present in the system"<<endl;
					in.close();
					out.close();
					return;
				}
				for(i=1;i<=end;i++){
					getline(in,temp);
					out<<temp<<"\n";
				}
				in.close();
				out.close();
				remove("four_wheeler_slots.txt");
				rename("temp.txt","four_wheeler_slots.txt");
				writeSlotCount(4,end);
				
				cout<<"================================================="<<endl;
				cout<<n<<" four-wheeler slots successfully removed!"<<endl;
				cout<<"================================================="<<endl;
			}
		}
		
		void addSlot(int t){
			// used to add one or more slots
			int n,i;
			if(t==2){
				cout<<"how many 2-wheeler slots should be added?"<<endl;
				cout<<"slot/s: ";
				cin>>n;
				if(n==0){
					// checking if the value input is 0
					cout<<"please enter a value greater than 0"<<endl;
					return;
				}
				ofstream out;
				out.open("two_wheeler_slots.txt",ios::app);
				
				for(i=1;i<=n;i++){
					out<<i+getSlotCount(2)<<" : "<<"empty\n";
				}	
				out.close();
				// updating the slot count
				writeSlotCount(2,n+getSlotCount(2));
				cout<<"================================================="<<endl;
				cout<<n<<" two-wheeler slots successfully added!"<<endl;
				cout<<"================================================="<<endl;
			}
			else if(t==4){
				cout<<"how many 4-wheeler slots should be added?"<<endl;
				cout<<"slot/s: ";
				cin>>n;
				if(n==0){
					// checking if the value input is 0
					cout<<"please enter a value greater than 0"<<endl;
					return;
				}
				ofstream out;
				out.open("four_wheeler_slots.txt",ios::app);
				// getting the current value of four wheeler slots count
				for(i=1;i<=n;i++){
					out<<i+getSlotCount(4)<<" : "<<"empty\n";
				}
				out.close();
				// updating the slot count
				writeSlotCount(4,n+getSlotCount(4));
				cout<<"================================================="<<endl;
				cout<<n<<" four-wheeler slots successfully added!"<<endl;
				cout<<"================================================="<<endl;		
			}
			else{
				cout<<"an error has occurred.."<<endl;
			}		
		}
		
		void listOperators(){
			// used to list current operators					
			
			ifstream in;
			in.open("operator.txt");
					
			cout<<"======================================"<<endl;
			cout<<"operators currently in the system are:"<<endl;
			cout<<"--------------------------------------"<<endl;
			int i = 1;
			string name;
			while(in.eof()!=1){
				in>>name;
				if(in.eof()!=1){
					cout<<i<<") name: "<<name<<endl;
					++i;
				}		
				in>>name;
			}
			if(i==1){
				cout<<"system doesn't have any operators yet..\nplease add some first"<<endl;
				in.close();
				return;
			}
			in.close();
			cout<<"======================================"<<endl;			
		}
		
		void removeOperator(){
			// used to remove a parking operator
			cout<<"==========================="<<endl;
			cout<<"removing a current operator"<<endl;
			cout<<"==========================="<<endl;
			cout<<"\n";
			ifstream in;
			in.open("operator.txt");
			string temp;
	
			ofstream out;
			out.open("temp.txt",ios::app);
			
			cout<<"enter operator's name whom to delete"<<endl;
			cout<<"name: ";
			string name;
			cin>>name;
			int checker = 1;	
			while(in.eof()!=1){
				in>>temp;
				//cout<<temp;		
				if (temp==name) {
					checker = 0;
					in>>temp;
					continue;
				}
				out<<temp<<" ";
				in>>temp;
				out<<temp<<"\n"; 
			}
			if(checker==1){
				cout<<"\n----------------"<<endl;
				cout<<"operator not found"<<endl;
				cout<<"\n----------------"<<endl;
				in.close();
				out.close();
				return;
			}
			
			in.close();
			out.close();
			remove("operator.txt");
			rename("temp.txt","operator.txt"); 
			
			cout<<"============================="<<endl;
			cout<<"operator successfully removed"<<endl;
			cout<<"============================="<<endl;
			
		}
		
		void addOperator(){
			// used to add a parking operator
			string u,p;
			cout<<"====================="<<endl;
			cout<<"adding a new operator"<<endl;
			cout<<"====================="<<endl;
			cout<<"\nenter new operator's username: ";
			cin>>u;
			cout<<"enter new operator's password: ";
			cin>>p;
						
			ofstream out;
			out.open("operator.txt",ios::app);
			out<<u<<" "<<p<<"\n";
			out.close();
			ifstream in;
			in.open("operator_count.txt");
			string temp;
			int n;
			in>>temp;
			stringstream geek(temp);
			geek>>n;
			in.close();
			++n;
			out.open("operator_count.txt");
			out<<n;
			out.close();
			cout<<"==========================="<<endl;
			cout<<"operator successfully added"<<endl;
			cout<<"==========================="<<endl;
			
		}
				
		int verify(){
			// used to verify admin credentials during login
			ifstream in;
			in.open("admin.txt");
			string user, pass;
			
			in>>user>>pass;
			
			in.close();
			
			if(user==username && pass==password){
				cout<<"========================"<<endl;
				cout<<"successfully logged in!!"<<endl;
				cout<<"========================"<<endl;
				return 1;
			}
			else{
				cout<<"============================"<<endl;
				cout<<"wrong username or password.."<<endl;
				cout<<"============================"<<endl;
				return 0;
			}			
		}			
};

class parkingOperator: private person{
// Defining the Parking Operator's class privately inherited from person class	
	private:
		string password;
	
	public:
	static int operator_count;		
		parkingOperator(string u, string p){
			user_type = 2;
			username = u;
			password = p;
		}
		
		void listCustomers(){
			
			ifstream in,in2;
			in.open("vehicle_data.txt");
			in2.open("vehicle_data.txt");
			string temp,temp2;
			while(in.eof()!=1){
				getline(in,temp);
				//cout<<temp<<endl;
				if(temp.empty()){
					continue;
				}
				if(temp.find(":departed:")==string::npos){
					cout<<"------------------"<<endl;
					in2>>temp2;
					cout<<"name: "<<temp2<<endl;
					in2>>temp2;
					cout<<"vehicle "<<temp2<<endl;
					in2>>temp2;
					cout<<"vehicle type: "<<temp2<<endl;
					in2>>temp2;
					cout<<"slot number: "<<temp2<<endl;
					cout<<"------------------"<<endl;
										
				}
				else{
					in2.seekg(in.tellg()-1,ios::beg);
				}
			}
			in.close();					
		}
		
		void updateVehicleRecord(string cname, vehicle v){
			
			string temp;
			
			ifstream in;
			ofstream out;
						
			in.open("vehicle_data.txt");
			out.open("temp1.txt",ios::app);
			
			while(in.eof()!=1){
				getline(in,temp);
				
				if(temp.find(cname)!=string::npos){
					out<<temp<<" :departed: "<<v.vehicle_departure.hh<<" : "<<v.vehicle_departure.mm<<"\n";	
					getline(in,temp);								
				}
				out<<temp<<"\n";
			}
			
			in.close();
			out.close();
			
			remove("vehicle_data.txt");
			rename("temp1.txt","vehicle_data.txt");
		}
		
		void removeVehicle(){
			string name, vn, temp,temp2;;
			int type, slot_number;
			cout<<"enter the customer's name: "<<endl;
			cout<<"name: ";
			cin>>name;
			ifstream in;
			ofstream out;
			in.open("vehicle_data.txt");
			
			// checking if the person has already departed
			while(in.eof()!=1){
				getline(in,temp);
				if(temp.find(":departed")!=string::npos){
					cout<<"this customer has already departed.."<<endl;
					return;								
				}
			}					
			in.close();
			
			in.open("vehicle_data.txt");
			// getting the vehicle data from file using customer name..						
			while(in.eof()!=1){
				in>>temp;
				if(temp==name){
					in>>temp;
					vn = temp;
					in>>temp;
					stringstream geek(temp);
					// getting the vehicle type
					geek>>type;
					in>>temp2;
					// getting the slot number
					stringstream geek2(temp2);
					geek2>>slot_number;	
					break;									
				}
			}
					
			in.close();			
						
			// updating record of slots to change it back to empty
			if(type==2){
				out.open("temp.txt",ios::app);
				in.open("two_wheeler_slots.txt");
				while(in.eof()!=1){
					getline(in,temp);
					if(temp.find(vn)!=string::npos){
						out<<slot_number<<" : "<<"empty\n";
						getline(in,temp);
					}
					out<<temp<<"\n";
				}
				out.close();
				in.close();
				remove("two_wheeler_slots.txt");
				rename("temp.txt","two_wheeler_slots.txt");
			}
			else if(type==4){
				in.open("four_wheeler_slots.txt");
				out.open("temp.txt",ios::app);
				while(in.eof()!=1){
					getline(in,temp);			
					if(temp.find(vn)!=string::npos){
						out<<slot_number<<" : "<<"empty\n";
						getline(in,temp);
					}
					out<<temp<<"\n";
				}
				out.close();
				in.close();
				remove("four_wheeler_slots.txt");
				rename("temp.txt","four_wheeler_slots.txt");				
			}
						
			vehicle v(vn, type, slot_number);			
			v.setDeparture();
						
			payment p(v,name);
			
			// updating the records
			updateVehicleRecord(name,v);
			// updating the vehicle count
			int z = getVehicleCount(type);			
			writeVehicleCount(type,z-1);			
		}
		
		void addVehicle(){
			
			vehicle v;
			
			if(getVehicleCount(v.getVehicleType())==getSlotCount(v.getVehicleType())){
				return;
			}
			else if(getSlotCount(v.getVehicleType())==0){
				return;
			}	

			int x = 1 + getVehicleCount(v.getVehicleType());
			writeVehicleCount(v.getVehicleType(), x);
			ofstream out;
			out.open("vehicle_data.txt",ios::app);
			out<<v.getOwnerName()<<" "<<v.getVehicleNumber()<<" "<<v.getVehicleType()<<" "<<v.getSlotNumber()<<" "<<v.vehicle_arrival.hh<<" : "<<v.vehicle_arrival.mm<<"\n";
			out.close();
			
			cout<<"==============="<<endl;
			cout<<"vehicle added!"<<endl;
			cout<<"==============="<<endl;
		}
			
		int verify(){
			// used to verify operator credentials during login
			ifstream in;
			in.open("operator_count.txt");
			string temp;
			int n;
			in>>temp;
			stringstream geek(temp);
			geek>>n;
			in.close();
			if(n==0){
				cout<<"no operators present in the system"<<endl;
				return 0;
			}
			in.open("operator.txt");				
			string u,p;
			int checker = 1;
			while(in.eof()!=1){
				in>>u>>p;
				if(username==u && password==p){
					cout<<"========================"<<endl;
					cout<<"successfully logged in!!"<<endl;
					cout<<"========================"<<endl;
					++checker;
					return 1;
				}				
			}
			cout<<"=============================="<<endl;
			cout<<"invalid username or password.."<<endl;
			cout<<"=============================="<<endl;
			return 0;
			
		}
		
};
int parkingOperator::operator_count = getOperatorCount(); 
int main(){
	
	int infLoop_main = 1;
	while(infLoop_main){
	system("Color F");
	cout<<"================================="<<endl;
	cout<<"VEHICLE PARKING MANAGEMENT SYSTEM"<<endl;
	cout<<"================================="<<endl;		
	cout<<"\n1 to login as operator"<<endl;
	cout<<"2 to login as admin"<<endl;
	cout<<"3 to exit..."<<endl;	
	cout<<"\n================================"<<endl;
	
	int c1;
	cout<<"choice: ";
	cin>>c1;
	system("cls");
	string username, password;
	int proceed = 0;
	
	switch(c1){
		
		case 1:
			cout<<"=============="<<endl;
			cout<<"operator login"<<endl;
			cout<<"=============="<<endl;
			cout<<"\n";
			cout<<"username: ";
			cin>>username;
			cout<<"password: ";
			cin>>password;
			system("cls");
			{
				parkingOperator p(username,password);
				proceed = p.verify();
				system("pause");
				system("cls");
			}
			
			if(proceed==1){
				parkingOperator p(username,password);
				int infLoop_operator = 1;
				while(infLoop_operator){
					system("cls");
					cout<<"==========================="<<endl;
					cout<<"1 for vehicle arrival"<<endl;
					cout<<"2 for vehicle departure"<<endl;
					cout<<"3 to list current customers"<<endl;
					cout<<"4 to view the slots status"<<endl;
					cout<<"5 to log-out.."<<endl;
					cout<<"==========================="<<endl;
					
					int c7;
					cout<<"choice: ";
					cin>>c7;
					
					switch(c7){
						case 1:
							system("cls");
							cout<<"==============="<<endl;
							cout<<"vehicle arrival"<<endl;
							cout<<"==============="<<endl;
							p.addVehicle();
							system("pause");
							break;
							
						case 2:
							system("cls");
							cout<<"================="<<endl;
							cout<<"vehicle departure"<<endl;
							cout<<"================="<<endl;
							p.removeVehicle();
							system("pause");
							break;
							
						case 3:
							system("cls");
							cout<<"============="<<endl;
							cout<<"customer list"<<endl;
							cout<<"============="<<endl;
							p.listCustomers();
							system("pause");
							break;
							
						case 4:
							system("cls");
							slot s;
							s.getSlotStatus();	
							system("pause");
							break;
							
						case 5:
							system("pause");
							system("cls");
							infLoop_operator = 0;
							break;
							
						default:
							cout<<"invalid choice..."<<endl;
							system("pause");
					}
				}
			}
					
			break;
			
				
		case 2:
			cout<<"====================="<<endl;
			cout<<"     admin login     "<<endl;
			cout<<"====================="<<endl;
			cout<<"\n";
			cout<<"     username: ";
			cin>>username;
			cout<<"     password: ";
			cin>>password; 
			
			system("cls");
			{
				admin a(username,password);
				proceed = a.verify();
				system("pause");
				system("cls");
			}	
								
			if(proceed==1){
				admin a(username,password);
				int infLoop_admin = 1;
				while(infLoop_admin){
					system("cls");
					cout<<"============================="<<endl;
					cout<<"1 to manage parking operators"<<endl;
					cout<<"2 to manage parking slots"<<endl;
					cout<<"3 to check earnings"<<endl;
					cout<<"4 to change admin password"<<endl;
					cout<<"5 to logout.."<<endl;
					cout<<"============================="<<endl;
																			
						int c2;
						cout<<"choice: ";
						cin>>c2;
						int infLoop_admin_1 = 1;
						int infLoop_admin_2 = 1;
						int infLoop_admin_3 = 1;
						int infLoop_admin_4 = 1;
						
						switch(c2){							
							case 1:
								infLoop_admin_1 = 1;
								while(infLoop_admin_1){
								system("cls");
								cout<<"======================================="<<endl;
								cout<<"1 to add an operator"<<endl;
								cout<<"2 to remove an operator"<<endl;
								cout<<"2 to list all the current operators"<<endl;
								cout<<"3 to change operator's password"<<endl;
								cout<<"4 to go back"<<endl;
								cout<<"======================================="<<endl;
							
								int c3;
								cout<<"choice: ";
								cin>>c3;
								
								switch(c3){
									
									case 1:
										system("cls");
										a.addOperator();
										system("pause");
										break;
//									case 2:
//										system("cls");
//										//a.removeOperator();
//										system("pause");
//										break;
									case 2:
										system("cls");
										a.listOperators();
										system("pause");
										break;
									case 3:
										system("cls");
										a.changeOperatorPassword();
										system("pause");
										break;
									case 4:
										infLoop_admin_1 = 0;
										break;	
									default:
										cout<<"invalid choice.."<<endl;	
										system("pause");					
								}
							}
							break;
							
							case 2:
								infLoop_admin_2 = 1;
								while(infLoop_admin_2){
									system("cls");
									cout<<"================================"<<endl;
									cout<<"1 to add parking slot/s"<<endl;
									cout<<"2 to remove parking slot/s"<<endl;
									cout<<"3 to list count of parking slot/s"<<endl;
									cout<<"4 to go back"<<endl;
									cout<<"================================"<<endl;
								
									int c4;
									cout<<"choice: ";
									cin>>c4;
								
									switch(c4){
										case 1:
											infLoop_admin_3 = 1;
											while(infLoop_admin_3){
												system("cls");
												cout<<"================================="<<endl;
												cout<<"1 to add 2-wheeler parking slot/s"<<endl;
												cout<<"2 to add 4-wheeler parking slot/s"<<endl;
												cout<<"3 to go back"<<endl;
												cout<<"================================="<<endl;
												
												int c5;
												cout<<"choice: ";
												cin>>c5;
												
												switch(c5){
													case 1:
														a.addSlot(2);
														system("pause");
														break;
														
													case 2:
														a.addSlot(4);
														system("pause");
														break;
														
													case 3:
														infLoop_admin_3 = 0;
														break;
															
													default:
														cout<<"invalid choice.."<<endl;
														system("pause");
												}
											}
											break;
										
										case 2:
											infLoop_admin_4 = 1;
											while(infLoop_admin_4){
												system("cls");
												cout<<"===================================="<<endl;
												cout<<"1 to remove 2-wheeler parking slot/s"<<endl;
												cout<<"2 to remove 4-wheeler parking slot/s"<<endl;
												cout<<"3 to go back"<<endl;
												cout<<"===================================="<<endl;
												
												int c6;
												cout<<"choice: ";
												cin>>c6;
												cout<<" "<<endl;
												switch(c6){
													case 1:
														a.removeSlot(2);
														system("pause");
														break;
														
													case 2:	
														a.removeSlot(4);
														system("pause");
														break;
														
													case 3:
														infLoop_admin_4 = 0;
														break;
														
													default:
														cout<<"invalid choice.."<<endl;
														system("pause");
												}
											}
											break;
											
										case 3:	
											a.listSlots();
											system("pause");
											break;
										
										case 4:
											infLoop_admin_2 = 0;
											break;
											
										default:
											 cout<<"invalid choice.."<<endl;
											 system("pause");											
									}
								}
								
								break;
							
							case 3:
								system("cls");
								cout<<"============="<<endl;
								cout<<"Total Earned"<<endl;
								cout<<"============="<<endl;
								cout<<"amount: "<<getTotalEarned()<<" rs"<<endl;
								system("pause");
								break;
								
							case 4:
								system("cls");
								a.changeAdminPassword();
								system("pause");
								break;
																					
							case 5:
								infLoop_admin = 0;
								cout<<"============="<<endl;
								cout<<"loggin out..."<<endl;
								cout<<"============="<<endl;
								system("pause");
								break;						
						}					
				}																	
			}
			
		break;	
				
		case 3:
			infLoop_main = 0;
			cout<<"================================="<<endl;
			cout<<"VEHICLE PARKING MANAGEMENT SYSTEM"<<endl;
			cout<<"================================="<<endl;			
			cout<<"\nexiting the program..."<<endl;
			cout<<"\n";
			system("pause");
			system("cls");	
			break;
			
		default:
			cout<<"invalid choice.."<<endl;
			system("pause");
			system("cls");		
		}
	
	}
	return 0;			
}
