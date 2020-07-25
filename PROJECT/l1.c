#include<stdio.h>										//Standard Input Output functions header file included
#include<string.h>										//String functions header file included

#ifndef OKAY										//If the program is not runned by the integration with other c files
	#define COURSE_DETAILS main										//main function is named as COURSE_DETAILS
	
	struct COURSE{										//Structure of the details to be stored in file
		int course_fee;										//Variable to store Fees of the courses
		char course_id[20], course_name[28];										//Strings to store ID and Name of the courses
	} data_c,copy_c,temp_c;

	short int size_c = sizeof(data_c);										//Variable assigned to the size of the structure

	FILE *fp, *ft, *fs;										//File pointers used at different places...   fp is used as the pointer to main file  and others are the helper file pointers
	
	go_back(){										//Used for printing the message to go back from a feature of the program and receive any key input
		printf("\n\nPress any key to go back to Main menu");
		getch();
	}
	
	heading(int x){										//Used for clearing the screen and giving the heading to the program
		system("cls");
		printf("Course Database:-\n\n");
	}
	
	print_data_heading(int x){										//Used to give the heading to the Data printed on the screen from the file
		printf("\n\n%-20s%-28s%s\n","Course ID","Course Name","Total Fees(INR)");
	}

	print_data(int x){										//Used to print the data on the screen from the file
		printf("\n%-20s%-28s%10d",data_c.course_id,data_c.course_name,data_c.course_fee);
	}

	file_close(char *str){
		fclose(ft);
		fclose(fp);
		remove(str);
		rename("temp.txt","enroll.txt");
		fp = fopen(str,"rb+");
	}
#endif

add_c(){										//Used to ADD the structured data in the file
	short int flag;
	heading(1);
	printf("Add new Course:\n\nNOTE: All Alphabets in ID and Name will be converted to UPPER case.\n");
	
	do{										//Receives the Course ID, checks if already stored and if present then again asks ID input
		flag = 0;
		rewind(fp);
		printf("\nEnter the course ID  : ");
		fflush(stdin);
		gets(data_c.course_id);
		strupr(data_c.course_id);
		while(fread(&copy_c,size_c,1,fp) == 1){
			if(!strcmp(copy_c.course_id,data_c.course_id)){
				flag = 1;
				printf("\nCourse ID already present in database.\n");
				break;
			}
		}
	}while(flag == 1);	
	
	do{										//Receives the Course Name, checks if already present and if present then again asks the Name input
		flag = 0;
		rewind(fp);
		printf("\nEnter the Course Name: ");
		fflush(stdin);
		gets(data_c.course_name);
		strupr(data_c.course_name);
		while(fread(&copy_c,size_c,1,fp) == 1){
			if(!strcmp(copy_c.course_name,data_c.course_name)){
				flag = 1;
				printf("\nCourse Name already present in database.\n");
				break;
			}
		}
	}while(flag == 1);	
	
	do{										//Receives the Course FEES, Fee can't be less than or equal to 0 , so asks input again and again if it is so
		flag = 0;
		printf("\nEnter the Course Fee : ");
		fflush(stdin);
		scanf("%d",&data_c.course_fee);
		if(data_c.course_fee < 0){
			flag = 1;
			printf("\nFees can't be negative.\n");
		}
	}while(flag == 1);
	
	fseek(fp,0,SEEK_END);
	fwrite(&data_c,size_c,1,fp);										//Writes the Course DATA in the file
	
	printf("\n\nData Successfully stored:");										//Shows the data which is stored in the file
	print_data_heading(1);
	print_data(1);
	
	go_back();										//Asks any key input to go back to the main menu
}

search_c(){
	char flag = 0;
	heading(1);
	printf("Search:\n\nEnter Course ID or Name: ");
	fflush(stdin);
	gets(copy_c.course_id);
	strupr(copy_c.course_id);
	while(fread(&data_c,size_c,1,fp) == 1){
		if(strstr(data_c.course_id,copy_c.course_id) || strstr(data_c.course_name,copy_c.course_id)){
			if(flag == 0){
				print_data_heading(1);
				flag = 1;
			}
			print_data(1);
		}
	}
	if(flag == 0)
		printf("\n\nNo data found!");
	go_back();
}

view_all_c(){
	char flag = 0;
	heading(1);
	printf("All Course Details:");
	
	while(fread(&data_c,size_c,1,fp) == 1){
		if(flag == 0){
			print_data_heading(1);
			flag = 1;
		}
		print_data(1);
	}
	
	if(flag == 0)
		printf("\n\nNo data found!");
	go_back();
}

delete_c(){
	char check = 1;
	ft = fopen("temp.txt","wb");
	
	heading(1);
	printf("Delete:\n\nEnter the course ID or Name, to check if the course details are present in database or not: ");
	fflush(stdin);
	gets(copy_c.course_id);
	strupr(copy_c.course_id);
	
	while(fread(&data_c,size_c,1,fp) == 1){
		if(strstr(data_c.course_id,copy_c.course_id) || strstr(data_c.course_name,copy_c.course_id)){
			printf("\n\nIs this the data to be deleted.");
			print_data_heading(1);
			print_data(1);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			if(check == 'Y' || check == 'y'){
				printf("\n\nDeletion Successfull.");
				continue;
			}
		}
		fwrite(&data_c,size_c,1,ft);
	}
	
	file_close("course.txt");
	
	if(check == 1)
		printf("\n\nNo data found!");
	go_back();
}

update_c(){
	char check = 1;
	short int flag = 1;
	ft = fopen("temp.txt","wb");
	fs = fopen("copy.txt","wb+");
	
	while((check = fgetc(fp)) != EOF)
		fputc(check,fs);
	
	rewind(fp);
	
	heading(1);
	printf("Update:\n\nEnter the course ID or Name, to check if the course details are present in database or not: ");
	fflush(stdin);
	gets(copy_c.course_id);
	strupr(copy_c.course_id);
	
	while(fread(&data_c,size_c,1,fp) == 1){
		if(strstr(data_c.course_id,copy_c.course_id) || strstr(data_c.course_name,copy_c.course_id)){
			printf("\nIs this the data to be updated.");
			print_data_heading(1);
			print_data(1);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			
			if(check == 'Y' || check == 'y'){
				do{
					flag = 0;
					rewind(fs);
					printf("\n\nEnter the course ID  : ");
					fflush(stdin);
					gets(data_c.course_id);
					strupr(data_c.course_id);
					while(fread(&temp_c,size_c,1,fs) == 1){
						if(!strcmp(temp_c.course_id,data_c.course_id)){
							flag = 1;
							if(strcmp(data_c.course_id,copy_c.course_id) == 0)
								printf("\nIt's the same ID.");
							else
								printf("\nCourse ID already present in database.");
							
							printf("\n\nDo you want to still keep this ID. (Y)");
							check = getch();
							if(check == 'y' || check == 'Y'){
								flag = 0;
							}
							break;
						}
					}
				}while(flag == 1);	
				
				do{
					flag = 0;
					rewind(fs);
					printf("\nEnter the Course Name: ");
					fflush(stdin);
					gets(data_c.course_name);
					strupr(data_c.course_name);
					while(fread(&temp_c,size_c,1,fs) == 1){
						if(!strcmp(temp_c.course_name,data_c.course_name)){
							flag = 1;
							if(strcmp(data_c.course_name,copy_c.course_name) == 0)
								printf("\nIt's the same Name.");
							else
								printf("\nCourse Name already present in database.");
							printf("\n\nDo you want to still keep this Name. (Y)");
							check = getch();
							if(check == 'y' || check == 'Y'){
								flag = 0;
							}
							break;
						}
					}
				}while(flag == 1);	
				
				do{
					flag = 0;
					printf("\nEnter the Course Fee : ");
					fflush(stdin);
					scanf("%d",&data_c.course_fee);
					if(data_c.course_fee < 0){
						flag = 1;
						printf("\nFees can't be negative.\n");
					}
				}while(flag == 1);
				
				printf("\n\nUpdation Successfull.\n\nNew Data stored is:");
				print_data_heading(1);
				print_data(1);
			}
		}
		fwrite(&data_c,size_c,1,ft);
	}
	
	fclose(fs);
	remove("copy.txt");
	file_close("course.txt");
	
	if(flag == 1)
		printf("\n\nNo data found!");
	go_back();
}

int filter_c(){
	char opt, flag = 0;
	
	do{
		heading(1);
		printf("Fee Filter:\n\n1. Above the limit\n2. Below the limit\n3. Between the limits\n4. Go Back\nEnter the option: ");
		fflush(stdin);
		opt = getche();
		
		switch(opt){
			case '1':
				printf("\n\nEnter the limit: ");
				scanf("%d",&copy_c.course_fee);
				while(fread(&data_c,size_c,1,fp) == 1){
					if(data_c.course_fee > copy_c.course_fee){
						if(flag == 0){
							print_data_heading(1);
							flag = 1;
						}
						print_data(1);
					}
				}
				break;
				
			case '2':
				printf("\n\nEnter the limit: ");
				scanf("%d",&copy_c.course_fee);
				while(fread(&data_c,size_c,1,fp) == 1){
					if(data_c.course_fee < copy_c.course_fee){
						if(flag == 0){
							print_data_heading(1);
							flag = 1;
						}
						print_data(1);
					}
				}
				break;
				
			case '3':
				printf("\n\nEnter the lower and upper limits: ");
				scanf("%d%d", &copy_c.course_fee, &temp_c.course_fee);
				while(fread(&data_c,size_c,1,fp) == 1){
					if(data_c.course_fee > copy_c.course_fee && data_c.course_fee < temp_c.course_fee){
						if(flag == 0){
							print_data_heading(1);
							flag = 1;
						}
						print_data(1);
					}
				}
				break;
			
			case '4':
				return 0;
				
			default:
				printf("\nInvalid Option! Try again...");
		}
	}while(opt < '1' || opt > '3');
	
	if(flag == 0)
		printf("\n\nNo data found!");
	go_back();
}

int COURSE_DETAILS(){
	char menu_option;
	
	fp = fopen("course.txt","rb+");
	if(fp == NULL){
		fp = fopen("course.txt","wb+");
	}
	
	while(1){
		rewind(fp);
		heading(1);
		printf("Menu:\n\n1. Add\n2. Search\n3. View All\n4. Delete\n5. Update\n6. Fee Filter\n0. Exit\nEnter the Choice: ");
		fflush(stdin);
		menu_option = getche();
		
		switch(menu_option){
			case '1':
				add_c();
				break;
				
			case '2':
				search_c();
				break;
				
			case '3':
				view_all_c();
				break;
			
			case '4':
				delete_c();
				break;
			
			case '5':
				update_c();
				break;
			
			case '6':
				filter_c();
				break;
			
			case '0':
				fclose(fp);
				return 0;
			
			default:
				printf("\nInavalid Option!\nPlease Try Again");
		}
	}
}