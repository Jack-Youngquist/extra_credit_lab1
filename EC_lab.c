#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 5
#define COLUMNS 5

bool programmer_prefers(int programmer_array[][5], int company_array[][5],int current_comp, int rival_comp, int programmer){
	for (int i=0;i<5;i++){
		if ((programmer_array[programmer-1][i])== current_comp){
			return true;//current company is prefered do nothing
		}
		if ((programmer_array[programmer-1][i]) == rival_comp){
			return false;//new company is prefered swap
		}
	}
}

int pair_assigner(int company_array[][5], int programmer_array[][5]){
	/*
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++)
		printf("%d ", company_array[i][j]);
		printf("\n");
	}
	printf("----------\nProgrammer\n");
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLUMNS; j++)
		printf("%d ", programmer_array[i][j]);
		printf("\n");
	}
	*/
	int free_count = 5;//Tracks how many companies still dont have a programmer
	int pick = 0;//tracks which pick the company is on i.e. 1st 2nd 3rd. 0 being their 1st pick
	int programmer_assignment[5]= {0,0,0,0,0};//tracks the programmers current company assignment. index 0 being programmer 1 and index 4 being programmer 5. each programmers index equals their current assigned company i.e. value of 1 meaning company 1, when the value is -1 that means they are open.
	int company_picks[5]= {0,0,0,0,0};//tracks wheather the company has a programmer yet. index 0 being company 1 and index 4 being company 5. each companies index equalls their current assigned programmer i.e. value of 1 meaning programmer 1, when the value is -1 that means they are open.
	while (free_count > 0){
		for (int company = 0;company<5;company++){//goes through every company
			int cur_comp_choice = company_picks[company];//integer value representing current companies programmer choice; 1 being programmer 1
			int cur_prog_assignment = programmer_assignment[company_array[company][pick]-1];//integer value representing the current companies prefered programmers company assignment; i.e. if the programmer they want is assigned to company 4n then it equals 4.
			if ((cur_comp_choice == (0)) && ((cur_prog_assignment) ==  0)){//if the company does not have a programmer picked yet and the programer of the current pick is available then it assigns them to eachother
				company_picks[company] = company_array[company][pick];
				programmer_assignment[company_array[company][pick]-1] = company+1;
				free_count = free_count-1;			
			} else if ((cur_comp_choice == (0)) && (cur_prog_assignment != 0)){
				if (programmer_prefers(programmer_array, company_array, cur_prog_assignment, company+1, company_array[company][pick]) == false){//runs if the programmer would prefer the current company in the for loop over his currently assigned company
					company_picks[cur_prog_assignment-1] = 0;//assigns company whose programmer left to none
					programmer_assignment[company_array[company][pick]-1] = company +1;//changes the programmers chosen company
					company_picks[company] = company_array[company][pick];//assigns current companies programmer to the newly changed one
					

				}
			}
			
		}
		pick++;
		if (pick==5){
			break;
		}
	}
	printf("Department #1 will get Programmer #%d\n", company_picks[0]);
	printf("Department #2 will get Programmer #%d\n", company_picks[1]);
	printf("Department #3 will get Programmer #%d\n", company_picks[2]);
	printf("Department #4 will get Programmer #%d\n", company_picks[3]);
	printf("Department #5 will get Programmer #%d\n", company_picks[4]);
}

int main(void)
{
	int company_array[5][5];//first index is picks the company. 0 being company 1, 4 being company 5. second index is the student pick, 0 being their first choice 5 being their last choice.
	int programmer_array[5][5];
	FILE *file;
	char file_name [100];
	printf("Enter file name: ");
	scanf("%s", &file_name);
	file = fopen(file_name, "r");
	if (file == NULL){
		printf("Error opening file.\n");
		return 1;
	}

	int row = 0;
	while (!feof(file)){//stores each departments preference into an array so that department 1 is at index 0 etc.
		if (ferror(file)){
			printf("Error reading file.\n");
			return 1;
		}
		if (ferror(file)){
			printf("Error reading file.\n");
			return 1;
		}

		for (int i = 0; i < COLUMNS; i++){
			if (fscanf(file, "%d", &company_array[i][row]) == EOF)
			break;
		}
		row++;
		if (row == ROWS) break;
	}
	row = 0;
	while (!feof(file)){//stores each departments preference into an array so that department 1 is at index 0 etc.
		if (ferror(file)){
			printf("Error reading file.\n");
			return 1;
		}

		for (int i = 0; i < COLUMNS; i++){
			if (fscanf(file, "%d", &programmer_array[i][row]) == EOF)
			break;
		}
		row++;
		if (row == ROWS) break;
	}

	// close the file as we are done working with it
	fclose(file);
	pair_assigner(company_array, programmer_array);
	printf("hit");

	return 0;
}