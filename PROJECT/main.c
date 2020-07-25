#include<stdio.h>
#define OKAY 1

struct COURSE{										//Structure of the details to be stored in file
	int course_fee;										//Variable to store Fees of the courses
	char course_id[20], course_name[28];										//Strings to store ID and Name of the courses
} data_c,copy_c,temp_c;
	
struct STUDENT{
	int student_id, d, m, y;
	char student_name[20], student_father_name[20];
} data_s,copy_s;

struct ENROLLMENT{
	int student_id;
	char course_id[20];
}data, copy;

short int size = sizeof(data), size_c = sizeof(data_c), size_s = sizeof(data_s);

FILE *fp, *ft, *fs;

#include"l1.c"
#include"l2.c"
#include"l3.c"

go_back(){
	printf("\n\nPress any key to go back to Main menu");
	getch();
}

heading(int x){
	system("cls");
	switch(x){
		case 1:
			printf("Course Database:-\n\n");
			break;
			
		case 2:
			printf("Student Database:-\n\n");
			break;
			
		case 3:
			printf("Enrollment Database:-\n\n");
	}
}

print_data_heading(int x){
	switch(x){
		case 1:
			printf("\n\n%-20s%-28s%s\n","Course ID","Course Name","Total Fees(INR)");
			break;
			
		case 2:
			printf("\n\n%-15s%-20s%-20s%s\n","Student ID","Student Name","Father Name","Date of Birth");
			break;
			
		case 3:
			printf("%-15s%-20s\n","Student ID","Course ID");
	}
	
}

print_data(int x){
	switch(x){
		case 1:
			printf("\n%-20s%-28s%10d",data_c.course_id,data_c.course_name,data_c.course_fee);
			break;
			
		case 2:
			printf("\n%-15d%-20s%-20s%2d %2d %d",data_s.student_id,data_s.student_name,data_s.student_father_name,data_s.d,data_s.m,data_s.y);
			break;
			
		case 3:
			printf("%-15d%-20s", data.student_id, data.course_id);
	}
	
}

file_close(char *str){
	fclose(ft);
	fclose(fp);
	remove(str);
	rename("temp.txt","enroll.txt");
	fp = fopen(str,"rb+");
}
int main(){
	char opt;
	while(1){
		system("cls");
		printf("Project:-\n\nMain Menu:\n\n1. Course\n2. Student\n3. Enrollment\n0. Exit\nEnter the choice: ");
		opt = getche();
		switch(opt){
			case '1':
				COURSE_DETAILS();
				break;
				
			case '2':
				STUDENT_DETAILS();
				break;
				
			case '3':
				ENROLL_DETAILS();
				break;
				
			case '0':
				return 0;
				
			default:
				printf("\nInavalid Option!\nPlease Try Again");
		}
	}
}