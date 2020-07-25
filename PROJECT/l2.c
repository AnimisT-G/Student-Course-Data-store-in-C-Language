#include<stdio.h>
#include<string.h>

#ifndef OKAY
	#define STUDENT_DETAILS main
	
	struct STUDENT{
		int student_id, d, m, y;
		char student_name[20], student_father_name[20];
	} data_s,copy_s;

	short int size_s = sizeof(data_s);
	
	FILE *fp, *ft;
	
	go_back(){
		printf("\n\nPress any key to go back to Main menu");
		getch();
	}
	
	heading(int x){
		system("cls");
		printf("Student Database:-\n\n");
	}
	
	print_data_heading(int x){
		printf("\n\n%-15s%-20s%-20s%s\n","Student ID","Student Name","Father Name","Date of Birth");
	}

	print_data(int x){
		printf("\n%-15d%-20s%-20s%2d %2d %d",data_s.student_id,data_s.student_name,data_s.student_father_name,data_s.d,data_s.m,data_s.y);
	}
	
	file_close(char *str){
		fclose(ft);
		fclose(fp);
		remove(str);
		rename("temp.txt","enroll.txt");
		fp = fopen(str,"rb+");
	}
#endif

add_s(){
	short int flag;
	heading(2);
	
	if(fread(&data_s,size_s,1,fp) != 1){
		data_s.student_id = 1001;
	}
	else{
		fseek(fp,-size_s,SEEK_END);
		fread(&data_s,size_s,1,fp);
		data_s.student_id += 1;
	}
	printf("Add new Student info:\n\nNOTE: All Alphabets in Names will be converted to UPPER case.\n");
	
	printf("\nStudent ID: %d\n\nEnter the Student's Name: ",data_s.student_id); 
	fflush(stdin);
	gets(data_s.student_name);
	strupr(data_s.student_name);
	printf("Enter the Father's Name : ");
	fflush(stdin);
	gets(data_s.student_father_name);
	strupr(data_s.student_father_name);
	printf("Enter the Date of birth : dd mm yyyy\b\b\b\b\b\b\b\b\b\b");
	scanf("%d %d %d",&data_s.d, &data_s.m, &data_s.y);
	
	fseek(fp,0,SEEK_END);
	fwrite(&data_s,size_s,1,fp);
	
	printf("\n\nData Successfully stored:");
	print_data_heading(2);
	print_data(2);
	
	go_back();
}

int search_s(){
	char opt;
	char flag = 0;
	heading(2);
	printf("Search by:\n1. ID\n2. Name\n3. DOB\n4. Go Back\nEnter the option: ");
	do{
		opt = getche();
		switch(opt){
			case '1':
				printf("\n\nEnter the ID: ");
				scanf("%d",&copy_s.student_id);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.student_id == copy_s.student_id){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
						break;
					}
				}
				break;
			
			case '2':
				printf("\n\nEnter the Student or Father Name: ");
				fflush(stdin);
				gets(copy_s.student_name);
				strupr(copy_s.student_name);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(strstr(data_s.student_father_name,copy_s.student_name) || strstr(data_s.student_name,copy_s.student_name)){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				break;
			
			case '3':
year:		printf("\n\nEnter the year: ");
				scanf("%d",&copy_s.y);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
month:	rewind(fp);
				printf("\n\nEnter the month: ");
				scanf("%d",&copy_s.m);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m == copy_s.m){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m != copy_s.m){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y != copy_s.y && data_s.m == copy_s.m){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
date:		rewind(fp);
				printf("\n\nEnter the date: ");
				scanf("%d",&copy_s.d);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m == copy_s.m && data_s.d == copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m == copy_s.m && data_s.d != copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m != copy_s.m && data_s.d == copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y == copy_s.y && data_s.m != copy_s.m && data_s.d != copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y != copy_s.y && data_s.m == copy_s.m && data_s.d == copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y != copy_s.y && data_s.m == copy_s.m && data_s.d != copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				rewind(fp);
				while(fread(&data_s,size_s,1,fp) == 1){
					if(data_s.y != copy_s.y && data_s.m != copy_s.m && data_s.d == copy_s.d){
						if(flag == 0){
							print_data_heading(2);
							flag = 1;
						}
						print_data(2);
					}
				}
				
				break;
			case '4':
				return 0;
				
			default:
				printf("\nInvalid input!\nPlease enter again.. ");
		}
	}while(opt < '1' || opt > '4');
	
	if(flag == 0)
		printf("\n\nNo data found!");
	go_back();
}

view_all_s(){
	char flag = 0;
	heading(2);
	printf("All Student Details:");
	
	while(fread(&data_s,size_s,1,fp) == 1){
		if(flag == 0){
			print_data_heading(2);
			flag = 1;
		}
		print_data(2);
	}
	
	if(flag == 0)
		printf("\n\nNo data found!");
	go_back();
}

delete_s(){
	char opt, check = 1, change = 0;
	ft = fopen("temp.txt","wb");
	
	heading(2);
	
	printf("Delete:\n\nWhich data to be entered to check if the student details are present in database or not: ");
	printf("\n1. ID\n2. Student or Father Name\n3. Go Back\nEnter the choice: ");
	do{
		opt = getche();
		switch(opt){
			case '1':
				printf("\n\nEnter the Student ID: ");
				scanf("%d",&copy_s.student_id);
				break;
				
			case '2':
				printf("\n\nEnter the Student or Father Name: ");
				fflush(stdin);
				gets(copy_s.student_name);
				strupr(copy_s.student_name);
				break;
				
			case '3':
				return 0;
				
			default:
				printf("\nInvalid input!\nPlease enter again.. ");
		}
	}while(opt < '1' || opt > '3');
	
	while(fread(&data_s,size_s,1,fp) == 1){
		switch(opt){
			case '1':
				if(copy_s.student_id == data_s.student_id)
					change = 1;
				break;
				
			case '2':
				if(check == 1 && (strstr(data_s.student_father_name,copy_s.student_name) || strstr(data_s.student_name,copy_s.student_name)))
					change = 1;
		}
		if(change == 1){
			change = 0;
			printf("\n\nIs this the data to be deleted.");
			print_data_heading(2);
			print_data(2);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			if(check == 'Y' || check == 'y'){
				printf("\n\nDeletion Successful.");
				continue;
			}
			else{
				check = 1;
			}
		}
		fwrite(&data_s,size_s,1,ft);
	}
	
	file_close("student.txt");
	
	if(check == 1)
		printf("\n\nNo data found!");
	go_back();
}

int update_s(){
	char opt, check = 1, change = 0;
	ft = fopen("temp.txt","wb");
	
	heading(2);
	
	printf("Update:\n\nWhich data to be entered to check if the student details are present in database or not: ");
	printf("\n1. ID\n2. Student or Father Name\n3. Go Back\nEnter the choice: ");
	do{
		opt = getche();
		switch(opt){
			case '1':
				printf("\n\nEnter the Student ID: ");
				scanf("%d",&copy_s.student_id);
				break;
				
			case '2':
				printf("\n\nEnter the Student or Father Name: ");
				fflush(stdin);
				gets(copy_s.student_name);
				strupr(copy_s.student_name);
				break;
				
			case '3':
				return 0;
				
			default:
				printf("\nInvalid input!\nPlease enter again.. ");
		}
	}while(opt < '1' || opt > '3');
	
	while(fread(&data_s,size_s,1,fp) == 1){
		switch(opt){
			case '1':
				if(copy_s.student_id == data_s.student_id)
					change = 1;
				break;
				
			case '2':
				if(check == 1 && (strstr(data_s.student_father_name,copy_s.student_name) || strstr(data_s.student_name,copy_s.student_name)))
					change = 1;
		}
		if(change == 1){
			change = 0;
			printf("\nIs this the data to be updated.");
			print_data_heading(2);
			print_data(2);
			printf("\n\nIf YES then press 'Y'...");
			fflush(stdin);
			check = getch();
			
			if(check == 'Y' || check == 'y'){
				
				printf("\nEnter the Student's Name: ");
				fflush(stdin);
				gets(data_s.student_name);
				strupr(data_s.student_name);
				printf("Enter the Father's Name : ");
				fflush(stdin);
				gets(data_s.student_father_name);
				strupr(data_s.student_father_name);
				printf("Enter the Date of birth : dd mm yyyy\b\b\b\b\b\b\b\b\b\b");
				scanf("%d%d%d",&data_s.d,&data_s.m,&data_s.y);
				
				printf("\n\nUpdation Successfull.\n\nNew Data stored is:");
				print_data_heading(2);
				print_data(2);
			}
			else{
				check = 1;
			}
		}
		fwrite(&data_s,size_s,1,ft);
	}
	
	file_close("student.txt");
	
	if(check == 1)
		printf("\n\nNo data found!");
	go_back();
}

int STUDENT_DETAILS(){
	char menu_option;
	
	fp = fopen("student.txt","rb+");
	if(fp == NULL)
		fp = fopen("student.txt","wb+");
	
	while(1){
		rewind(fp);
		heading(2);
		printf("Menu:\n\n1. Add\n2. Search\n3. View All\n4. Delete\n5. Update\n0. Exit\nEnter the Choice: ");
		fflush(stdin);
		menu_option = getche();
		
		switch(menu_option){
			case '1':
				add_s();
				break;
				
			case '2':
				search_s();
				break;
				
			case '3':
				view_all_s();
				break;
			
			case '4':
				delete_s();
				break;
			
			case '5':
				update_s();
				break;
			
			case '0':
				fclose(fp);
				return 0;
			
			default:
				printf("\nInavalid Option!\nPlease Try Again");
		}
	}
}