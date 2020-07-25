#include<stdio.h>
#include<string.h>

#ifndef OKAY
	#define ENROLL_DETAILS main
	
	struct COURSE{
		int course_fee;
		char course_id[20], course_name[28];
	} data_c;
	
	struct STUDENT{
		int student_id, d, m, y;
		char student_name[20], student_father_name[20];
	} data_s;
	
	struct ENROLLMENT{
		int student_id;
		char course_id[20];
	}data, copy;

	short int size = sizeof(data), size_c = sizeof(data_c), size_s = sizeof(data_s);
	
	FILE *fp, *ft, *fs;
	
	go_back(){
		printf("\n\nPress any key to go back to Main menu");
		getch();
	}
	
	heading(int x){
		system("cls");
		printf("Enrollment Database:-\n\n");
	}
	
	print_data_heading(int x){
		printf("%-15s%-20s\n","Student ID","Course ID");
	}
	
	print_data(int x){
		printf("%-15d%-20s", data.student_id, data.course_id);
	}
	
	file_close(char *str){
		fclose(ft);
		fclose(fp);
		remove(str);
		rename("temp.txt","enroll.txt");
		fp = fopen(str,"rb+");
	}
#endif

int add(){
	char flag;
	heading(3);
	
	printf("New Enrollment:\n");
	
	do{
		flag = 0;
		printf("\nEnter the Student ID: ");
		scanf("%d",&data.student_id);
		
		rewind(fp);
		while(fread(&copy,size,1,fp) == 1){
			if(copy.student_id == data.student_id){
				printf("\nThis ID is already enrolled.\n\nDo you want to type another ID (Y) ");
				flag = getche();
				if(!(flag == 'y' || flag == 'Y'))
					return 0;
				else
					break;
			}
		}
		
		if(flag == 'y' || flag == 'Y')
			continue;
		
		ft = fopen("student.txt","rb");
		while(fread(&data_s,size_s,1,ft) == 1){
			if(data_s.student_id == data.student_id){
				printf("\n\n%-15s%-20s%-20s%s\n","Student ID","Student Name","Father Name","Date of Birth");
				printf("\n%-15d%-20s%-20s%2d %2d %d",data_s.student_id,data_s.student_name,data_s.student_father_name,data_s.d,data_s.m,data_s.y);
				flag = 'n';
				break;
			}
		}
		fclose(ft);
		
		if(flag != 'n'){
			printf("\nThis ID is not found in the students database.\n\nDo you want to type another ID (Y) ");
			flag = getch();
			if(!(flag == 'y' || flag == 'Y'))
				return 0;
		}
			
	}while(flag == 'y' || flag == 'Y');
	
	do{
		flag = 0;
		
		printf("\n\nEnter the Course ID : ");
		fflush(stdin);
		gets(data.course_id);
		strupr(data.course_id);
		ft = fopen("course.txt","rb");
		while(fread(&data_c,size_c,1,ft) == 1){
			if(strstr(data_c.course_id,data.course_id)){
				printf("\n\n%-20s%-28s%s\n","Course ID","Course Name","Total Fees(INR)");
				printf("\n%-20s%-28s%10d",data_c.course_id,data_c.course_name,data_c.course_fee);
				
				printf("\n\nIs this the course to be enrolled (Y) ");
				flag = getche();
				if(flag == 'y' || flag == 'Y'){
					strcpy(data.course_id,data_c.course_id);
					flag = 1;
					break;
				}
			}
		}
		fclose(ft);
		
		if(flag != 1){
			printf("\nThis ID is not found in the students database.\n\nDo you want to type another ID (Y) ");
			flag = getche();
			if(!(flag == 'y' || flag == 'Y'))
				return 0;
		}
	}while(flag == 'y' || flag == 'Y');
	
	fseek(fp,0,SEEK_END);
	fwrite(&data,size,1,fp);
	
	printf("\n\nData Successfully stored:\n\n");
	print_data_heading(3);
	print_data(3);
	
	go_back();
}

int search(){
	char opt, flag = 0;
	short int sr = 1;
	heading(3);
	printf("Search by:\n1. Student ID\n2. Course ID\n3. Go Back\nEnter the option: ");
	
	do{
		opt = getche();
		switch(opt){
			case '1':
				printf("\n\nEnter the Student ID: ");
				scanf("%d",&copy.student_id);
				while(fread(&data,size,1,fp) == 1){
					if(data.student_id == copy.student_id){
						printf("\n\n");
						print_data_heading(3);
						printf("\n");
						print_data(3);
						flag = 1;
						break;
					}
				}
				break;
				
			case '2':
				printf("\n\nEnter Course ID: ");
				fflush(stdin);
				gets(copy.course_id);
				strupr(copy.course_id);
				while(fread(&data,size,1,fp) == 1){
					if(strstr(data.course_id,copy.course_id)){
						if(flag == 0){
							printf("\n\n%-10s","Sr. No.");
							print_data_heading(3);
							flag = 1;
						}
						printf("\n%8d  ",sr++);
						print_data(3);
					}
				}
				break;
				
			case '3':
				return 0;
				
			default:
				printf("\nInvalid input!\nPlease enter again.. ");
		}
	}while(opt < '1' || opt > '3');
	
	if(flag != 1){
		printf("\n\nNO DATA FOUND");
	}
	go_back();
}

view_all(){
	char flag = 0;
	short int sr = 1;
	heading(3);
	printf("All Student Details:");
	
	while(fread(&data,size,1,fp) == 1){
		if(flag == 0){
			printf("\n\n%-10s","Sr. No.");
			print_data_heading(3);
			flag = 1;
		}
		printf("\n%8d  ",sr++);
		print_data(3);
	}
	
	if(flag == 0)
		printf("\n\nNo data found!");
	
	go_back();
}

delete(){
	char check = 1;
	ft = fopen("temp.txt","wb");
	
	heading(3);
	printf("Delete:\n\nEnter the Student ID, to check if the student details are present in database or not: ");
	scanf("%d",&copy.student_id);
	
	while(fread(&data,size,1,fp) == 1){
		if(data.student_id == copy.student_id){
			printf("\n\nIs this the data to be deleted.");
			printf("\n\n");
			print_data_heading(3);
			printf("\n");
			print_data(3);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			if(check == 'Y' || check == 'y'){
				printf("\n\nDeletion Successful.");
				continue;
			}
		}
		fwrite(&data,size,1,ft);
	}
	
	file_close("enroll.txt");
	
	if(check == 1)
		printf("\n\nNo data found!");
	go_back();
}

int update(){
	char check = 1, flag;
	ft = fopen("temp.txt","wb");
	
	heading(3);
	printf("Update:\n\nEnter the Student ID, to check if the student details are present in database or not: ");
	scanf("%d",&copy.student_id);
	
	while(fread(&data,size,1,fp) == 1){
		if(data.student_id == copy.student_id){
			printf("\n\nIs this the data to be updated.");
			printf("\n\n");
			print_data_heading(3);
			printf("\n");
			print_data(3);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			if(check == 'Y' || check == 'y'){
s1:				
				do{
					flag = 0;
					
					printf("\n\nEnter the Course ID : ");
					fflush(stdin);
					gets(data.course_id);
					strupr(data.course_id);
					fs = fopen("course.txt","rb");
					while(fread(&data_c,size_c,1,fs) == 1){
						if(strstr(data_c.course_id,data.course_id)){
							printf("\n\n%-20s%-28s%s\n","Course ID","Course Name","Total Fees(INR)");
							printf("\n%-20s%-28s%10d",data_c.course_id,data_c.course_name,data_c.course_fee);
							
							printf("\n\nIs this the course to be enrolled (Y) ");
							flag = getche();
							if(flag == 'y' || flag == 'Y'){
								strcpy(data.course_id,data_c.course_id);
								flag = 1;
								break;
							}
						}
					}
					fclose(fs);
					
					if(flag != 1){
						printf("\nThis ID is not found in the students database.\n\nDo you want to type another ID (Y) ");
						flag = getche();
						if(!(flag == 'y' || flag == 'Y'))
							return 0;
					}
				}while(flag == 'y' || flag == 'Y');
s2:				
				printf("\n\nUpdation Successfull.\n\nNew Data stored is:");
				printf("\n\n");
				print_data_heading(3);
				printf("\n");
				print_data(3);
			}
		}
		fwrite(&data,size,1,ft);
	}
	
	file_close("enroll.txt");
	
	if(check == 1)
		printf("\n\nNo data found!");
	go_back();
}

int ENROLL_DETAILS(){
	char menu_opt;
	
	fp = fopen("enroll.txt","rb+");
	if(fp == NULL)
		fp = fopen("enroll.txt","wb+");
	
	while(1){
		rewind(fp);
		heading(3);
		printf("Menu:\n1. Add\n2. Search\n3. View All\n4. Delete\n5. Update\n0. Exit\nEnter the option: ");
		menu_opt = getche();
		
		switch(menu_opt){
			case '1':
				add();
				break;
				
			case '2':
				search();
				break;
				
			case '3':
				view_all();
				break;
				
			case '4':
				delete();
				break;
				
			case '5':
				update();
				break;
				
			case '0':
				fclose(fp);
				return 0;
				
			default:
				printf("\nInavalid Option!\nPlease Try Again");
		}
	}
}