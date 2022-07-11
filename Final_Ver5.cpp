/*
Update Version 2 :
	Add grade function inside Student Class.
	Add reset function to delete all file as well as the data inside.
Update Version 3 :
	Fixed a few bugs.
Update Version 4 : 
	New user interface.
Update Version 5:
	Password added.
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<string>
#include<conio.h>
#include<unistd.h>
using namespace std;


class Student{
	private:
		struct subject{
			double marks;
			unsigned int credits;
		}eng,cal,alg,phy,phi;// english, calculus, algebra, physics, philosophy.
		int id;
		char name[50];
		double gpa;
		char grade[10];
	public:
		void getData(){
			cout<<"Enter student's ID : ";
			cin>>id;
			cout<<"Enter student name : ";
			cin.ignore();
			cin.getline(name,50);
			cout<<"Enter marks in scale of 10\n";
			cout<<"Enter marks in English : ";
			cin>>eng.marks;
			while(eng.marks<0||eng.marks>10){
				cout<<"All mark should be from 0 to 10\n";
				cout<<"Enter marks in English : ";
				cin>>eng.marks;
			}
			cout<<"Enter marks in Calculus : ";
			cin>>cal.marks;
			while(cal.marks<0||cal.marks>10){
				cout<<"All mark should be from 0 to 10\n";
				cout<<"Enter marks in Calculus : ";
				cin>>cal.marks;
			}
			cout<<"Enter marks in Algebra : ";
			cin>>alg.marks;
			while(alg.marks<0||alg.marks>10){
				cout<<"All mark should be from 0 to 10\n";
				cout<<"Enter marks in Algebra : ";
				cin>>alg.marks;
			}
			cout<<"Enter marks in Physics : ";
			cin>>phy.marks;
			while(phy.marks<0||phy.marks>10){
				cout<<"All mark should be from 0 to 10\n";
				cout<<"Enter marks in Physics : ";
				cin>>phy.marks;
			}
			cout<<"Enter marks in Philosophy : ";
			cin>>phi.marks;
			while(phi.marks<0||phi.marks>10){
				cout<<"All mark should be from 0 to 10\n";
				cout<<"Enter marks in Philosophy : ";
				cin>>phi.marks;
			}
			calculate();
		}
		void showData(){
			cout<<"Student's ID : "<<id;
			cout<<"\nName of student : "<<name;
			cout<<"\nEnglish : "<<eng.marks;
			cout<<"\nCalculus : "<<cal.marks;
			cout<<"\nAlgebra : "<<alg.marks;
			cout<<"\nPhysics : "<<phy.marks;
			cout<<"\nPhilosophy : "<<phi.marks;
			cout<<"\nGpa : "<<gpa<<"/4";
			cout<<"\nGrade : "<<grade;
		}
		void calculate(){
			eng.credits=2;
			cal.credits=4;
			alg.credits=4;
			phy.credits=5;
			phi.credits=1;
			int sumCredits=eng.credits+cal.credits+alg.credits+phy.credits+phi.credits;
			gpa=(eng.marks*eng.credits+cal.marks*cal.credits+alg.marks*alg.credits+phy.marks*phy.credits+phi.marks*phi.credits)/sumCredits;
			gpa=(gpa*4)/10;
			if(gpa<1){
				strcpy(grade,"Fail");
			}
			else if(gpa>=1&&gpa<=1.49){
				strcpy(grade,"Very Bad");
			}
			else if(gpa>=1.5&&gpa<=1.99){
				strcpy(grade,"Bad");
			}
			else if(gpa>=2&&gpa<=2.49){
				strcpy(grade,"Average");
			}
			else if(gpa>=2.5&&gpa<=3.19){
				strcpy(grade,"Good");
			}
			else if(gpa>=3.2&&gpa<=3.59){
				strcpy(grade,"Very Good");
			}
			else{
				strcpy(grade,"Excellent");
			}
		}
		int getID(){
			return id;
			//Since "id" is a private variable of class Student, it cannot be access in the main function, therefore this function is needed.
		}
};
void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}
bool checkID(int id){
	//Check for repeated ID num.		
}
bool checkPassword(){
	unsigned int trail=5;
	string password = "123456"; // change password here.
	begin :
	cout<<"Require admin permission."<<endl;
	cout<<"Enter password to continue : ";
	char ch;
	string input="";
	ch = _getch();
	while(ch != 13){
		if(ch==127||ch==8){
			system("cls");
			goto begin;
		}
		input.push_back(ch);
		cout<<"*";
		ch = _getch();
	}
	system("cls");
	if(input==password){
		cout<<"Password correct."<<endl;
		return 1;
	}
	else{
		trail--;
		if(trail==0){
			cout<<"0 trail left.Try again after 30 seconds.";
			sleep(30);
			return 0;
		}
		cout<<"Password incorrect."<<endl<<trail<<" trail left.";
		getch();
		system("cls");
		goto begin;
	}
}
int main(){
	//system("color %");
	//The above line of code show instruction to change the background and foreground. Not needed for the final program.
	Student objStudent;
	char choice;
	int num;
	bool flag;
	cout<<setprecision(3);
	while(1){
		system("cls");
		system("color 3f");
		cout<<"MENU";
		cout<<"\n1. Add student record";
		cout<<"\n2. Search student by ID";
		cout<<"\n3. Display all students records";
		cout<<"\n4. Delete student record";
		cout<<"\n5. Edit student record";
		cout<<"\n6. Recycle Bin";
		cout<<"\n7. Reset";
		cout<<"\n8. Exit";
		cout<<"\nWhat is your Choice ? (1/2/3/4/5/6/7/8) ";
		cin>>choice;
		system("cls");
		switch(choice){
			case '1':{
				ofstream studentFile;
				studentFile.open("Student List.dat",ios::binary|ios::app);
				objStudent.getData();
				studentFile.write(reinterpret_cast<char*>(&objStudent),sizeof(Student));
				studentFile.close();
				system("pause");
				break;
			}
			case '2':{
				cout<<"Enter ID to found : "; 
				cin>>num;
				ifstream studentFile;
				studentFile.open("Student List.dat",ios::binary);
				if(studentFile==0){
					cout<<"File could not be open."<<endl;
					system("pause");
					break;
				}
				flag=0;
				while(studentFile.read(reinterpret_cast<char*>(&objStudent),sizeof(Student))){
					if(objStudent.getID()==num){
						cout<<"====================================\n";
						objStudent.showData();
						cout<<endl;
						flag=1;
					}
				}
				studentFile.close();
				if(flag==0){
					cout<<"ID "<<num<<" does not exists\n";
				}
				system("pause");
				break;
			}
			case '3':{
				ifstream studentFile;
				studentFile.open("Student List.dat",ios::binary);
				if(studentFile==0){
					cout<<"File could not be open."<<endl;
					system("pause");
					return 0;
				}
				flag=0;
				while(studentFile.read(reinterpret_cast<char*>(&objStudent),sizeof(Student))){
					objStudent.showData();
					cout<<"\n====================================\n";
					flag=1;
				}
				if(flag==0){
					cout<<"Record file is Empty"<<endl;
				}
				studentFile.close();
				system("pause");
				break;
			}	
			case '4':{
//				if(checkPassword()==1){
//					return 0;
//				}
				cout<<"Enter ID to delete : -"; 
				cin>>num;
				ifstream studentFile;
				studentFile.open("Student List.dat",ios::binary);
				if(studentFile==0){
					cout<<"File could not be open."<<endl;
					system("pause");
					break;
				}
				ofstream tempFile;
				ofstream recycleBin;
				recycleBin.open("Recycle Bin.dat",ios::binary|ios::app);
				tempFile.open("Temp.dat",ios::out);
				studentFile.seekg(0,ios::beg);
				flag=0;
				while(studentFile.read(reinterpret_cast<char *> (&objStudent), sizeof(Student))){
					if(objStudent.getID()!=num){
						tempFile.write(reinterpret_cast<char *> (&objStudent), sizeof(Student));
					}
					else{
						flag=1;
						recycleBin.write(reinterpret_cast<char *> (&objStudent), sizeof(Student));
					}
				}
				tempFile.close();
				studentFile.close();
				recycleBin.close();
				if(flag==0){
					cout<<"ID "<<num<<" does not exists"<<endl;
					remove("Temp.dat");
					system("pause");
				}
				else{
					remove("Student List.dat");
					rename("Temp.dat","Student List.dat");
					cout<<"Record Deleted.\n";
					system("pause");
				}
				break;
			}
			case '5':{
				cout<<"Enter ID to edit : "; 
				cin>>num;
				flag=0;
				fstream studentFile;
				studentFile.open("Student List.dat",ios::binary|ios::in|ios::out);
				if(studentFile==0){
					cout<<"File could not be opened."<<endl;
					system("pause");
					break;
				}
				while(studentFile.eof()==0 && flag==0){
					studentFile.read(reinterpret_cast<char*>(&objStudent),sizeof(Student));
					if(objStudent.getID()==num){
						cout<<"====================================\n";
						cout<<"Enter student "<<num<<" new details:\n";
						objStudent.getData();
						int pos=(-1)*static_cast<int>(sizeof(objStudent));
					    studentFile.seekp(pos,ios::cur);
					    studentFile.write(reinterpret_cast<char*>(&objStudent),sizeof(Student));
					    cout<<"Record Updated\n";
					    flag=1;
					}
				}
				studentFile.close();
				if(flag==0)
					cout<<"Record Not Found"<<endl;
				system("pause");
				break;
			}
			case '6':{
				ifstream studentFile;
				studentFile.open("Recycle Bin.dat",ios::binary);
				cout<<"\tRecycle Bin";
				cout<<"\n====================================\n";
				if(studentFile==0){
					cout<<"Recycle Bin is empty"<<endl;
					system("pause");
				}
				else{
					while(studentFile.read(reinterpret_cast<char*>(&objStudent),sizeof(Student))){
						objStudent.showData();
						cout<<"\n====================================\n";
					}
					studentFile.close();
					system("pause");
				}
				break;
			}
			case '7':{
				char confirm='1';
				cout<<"All recorded data will be delete\nConfirm to reset ? (y/n) ";
				while(confirm!='n'){
					cin>>confirm;
					if(confirm=='y'){
						remove("Student List.dat");
						remove("Recycle Bin.dat");
						remove("Temp.dat");
						cout<<"Reset Successfully.";
						exit(0);					
					}
					else{
						system("cls");
						cout<<"All recorded data will be delete\nConfirm to reset ? (y/n) ";
					}
				}
				break;
			}
			case '8':{
				cout<<"Exiting, Thank you!"<<endl;
				system("pause");
				exit(0);
			}
		}
	}
	return 0;
}
