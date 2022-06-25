#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ipl_schedule
{
    char days[100];
    char time[100];
    char a_final[100];
    char b_final[100];
    char venue_final[100];
};

struct ipl_schedule *ipl_match_ptr; //Globally Declaring Pointer

//Returns 0 even if a single non-zero element is present in a array
int checkArray(int *arr, int *total)
{
    int flag = 1;
    for(int i = 0; i < *total; i++)
    {
        if(arr[i] != 0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

//Returns 1 if the team has not played in the previous n matches
int compare(int *arr, int *team_A, int *team_B, int i, int j, int n)
{
    int flag;
    flag = 0;
    for(int k = 0; k < n; k++)
    {
        if((arr[j-1-k] != team_A[i]) && (arr[j-1-k] != team_B[i]))
        {
            flag = 1;
        }
    }
    return flag;
}

//Returns 1 if previous n matches has been scheduled
int compare_zero(int *arr, int i, int j, int n)
{
    int flag;
    flag = 0;
    for(int k = 0; k < n; k++)
    {
        if(arr[j-1-k] != 0)
        {
            flag = 1;
        }
    }
    return flag;
}

//Ashwin

//Right rotates the array by 1 unit starting from element 2
void rotate(int *arr, int n)
{
    int x = arr[n-1];
    for(int i = n-1; i > 1; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[1] = x;
}

//Arjun

// Updates array with Days Schedule Based on Requirement
// gap_based_choice
// 1 -> Normal case, Weekend 2 matches, 1 day gap
// 2 -> Leave one day gap between consecutive games
// 3 -> Normal Weekday, only one match on Weekends
void schedule_days(int *days, int day_one, int total, int gap_based_choice)
{
    if(gap_based_choice == 1)
    {
        int i = 0;
        while(i < total)
        {
            if (i == 0)
            {
                days[i] = day_one;
                i += 1;
            }
            else if (days[i-1] == 1)
            {
                days[i] = 2;
                i += 1;
            }
            else if (days[i-1] == 2)
            {
                days[i] = 3;
                i += 1;
            }
            else if (days[i-1] == 3)
            {
                days[i] = 4;
                i += 1;
            }
            else if (days[i-1] == 4)
            {
                days[i] = 5;
                i += 1;
            }
            else
            {
                if(i == total - 1) //Last day, Only one match on Weekends
                {
                    if(days[i-1] == 5)
                    {
                        days[i] = 6;
                        i += 1;
                    }
                    else if(days[i-1] == 6)
                    {
                        days[i] = 7;
                        i += 1;
                    }
                    else if(days[i-1] == 7)
                    {
                        days[i] = 1;
                        i += 1;
                    }
                }
                else //Normal weekend, then two matches
                {
                    if(days[i-1] == 5)
                    {
                        days[i] = 6;
                        days[i+1] = 6;
                        i += 2;
                    }
                    else if(days[i-1] == 6)
                    {
                        days[i] = 7;
                        days[i+1] = 7;
                        i += 2;
                    }
                    else if(days[i-1] == 7)
                    {
                        days[i] = 1;
                        i += 1;
                    }
                }
            }
        }
    }
    else if(gap_based_choice == 2)
    {
        int i = 0;
        while(i < total)
        {
            if(i == 0)
            {
                days[i] = day_one;
                i += 1;
            }
            else if (days[i-1] == 1)
            {
                days[i] = 3;
                i += 1;
            }
            else if (days[i-1] == 2)
            {
                days[i] = 4;
                i += 1;
            }
            else if (days[i-1] == 3)
            {
                days[i] = 5;
                i += 1;
            }
            else if (days[i-1] == 4)
            {
                days[i] = 6;
                i += 1;
            }
            else if (days[i-1] == 5)
            {
                days[i] = 7;
                i += 1;
            }
            else if (days[i-1] == 6)
            {
                days[i] = 1;
                i += 1;
            }
            else if (days[i-1] == 7)
            {
                days[i] = 2;
                i += 1;
            }
        }
    }
    else if (gap_based_choice == 3)
    {
        int i = 0;
        while(i < total)
        {
            if(i == 0)
            {
                days[i] = day_one;
                i += 1;
            }
            else if (days[i-1] == 1)
            {
                days[i] = 2;
                i += 1;
            }
            else if (days[i-1] == 2)
            {
                days[i] = 3;
                i += 1;
            }
            else if (days[i-1] == 3)
            {
                days[i] = 4;
                i += 1;
            }
            else if (days[i-1] == 4)
            {
                days[i] = 5;
                i += 1;
            }
            else if (days[i-1] == 5)
            {
                days[i] = 6;
                i += 1;
            }
            else if (days[i-1] == 6)
            {
                days[i] = 7;
                i += 1;
            }
            else if (days[i-1] == 7)
            {
                days[i] = 1;
                i += 1;
            }
        }
    }
}

//Arjun

// Updates array with Time Schedule Based on Requirement
// time_based_choice
// 1 -> A and E matches
// 2 -> Only E matches
void schedule_time(char time[][100], int total, int *days, int time_based_choice)
{
    if(time_based_choice == 1)
    {
        strcpy(time[0], "E");
        for(int i = 0; i < total; i++)
        {
            if(i == total - 1) //last match is always an evening match in IPL.
            {
                strcpy(time[i], "E");
            }
            else if(days[i] == 1 || days[i] == 2 || days[i] == 3 || days[i] == 4 || days[i] == 5)
            {
                strcpy(time[i], "E");
            }
            else if (days[i] == 6 && days[i-1] == 5) //first match is saturday or not
            {
                strcpy(time[i], "A");
            }
            else if (days[i] == 7 && days[i-1] == 6) //first match is sunday or not
            {
                strcpy(time[i], "A");
            }
            else if (strcmp(time[i-1], "A") == 0) //if previous match A, then next match is E.
            {
                strcpy(time[i], "E");
            }
        }
    }
    else if(time_based_choice == 2)
    {
        strcpy(time[0], "E");
        for(int i = 0; i < total; i++)
        {
            strcpy(time[i], "E");
        }
    }
}

char day[500][100], a_final[500][100], b_final[500][100], venue_final[500][100]; //Global Declaration

int n_stadium; //Global Declaration
int venue[100]; //Global Declaration for nStadium < nTeams.


//Maps integer days to readable string days
void map_days(char day[][100], int *days, int total)
{
    for(int i = 0; i < total; i++)
    {
        if(days[i] == 1)
        {
            strcpy(day[i], "Monday");
        }
        else if(days[i] == 2)
        {
            strcpy(day[i], "Tuesday");
        }
        else if(days[i] == 3)
        {
            strcpy(day[i], "Wednesday");
        }
        else if(days[i] == 4)
        {
            strcpy(day[i], "Thursday");
        }
        else if(days[i] == 5)
        {
            strcpy(day[i], "Friday");
        }
        else if(days[i] == 6)
        {
            strcpy(day[i], "Saturday");
        }
        else if(days[i] == 7)
        {
            strcpy(day[i], "Sunday");
        }
    }
}

//Maps keys to Readable time string.
void map_time(char time[][100], int total)
{
    for(int i = 0; i < total; i++)
    {
        if(strcmp(time[i], "A") == 0)
        {
            strcpy(time[i], "3:30 pm");
        }
        else if(strcmp(time[i], "E") == 0)
        {
            strcpy(time[i], "7:30 pm");
        }
    }
}

//Ananya

//Print Schedule Function (Planning to use Struct Here!)(Also write the schedule to an Output txt File!)
void print_schedule(int a[], int b[], int days[], char time[][100], int total, int n)
{
    int i;

    char team_data[500][100], venue_data[500][100];
    int flag = 0;

    //Giving user a chance to input
    while(flag == 0)
    {
        printf("Enter the number of stadiums.(Please note that the number of stadiums cannot be greater than number of teams): ");
        scanf("%d", &n_stadium);

        if(n_stadium > 0 && n_stadium <= n)
        {
            flag = 1;
        }
    }
    
    //Assigning Stadiums
    if(n_stadium < n)
    {
        //Limiting Case
        //Getting the names of teams
        for(int i = 0; i < n; i++)
        {
            printf("Enter the name for team number %d this year: ", i+1);
            scanf("%s", team_data[i]);
        }

        int count = 0;
        i = 0;
        int stadium[25]; //Source array for Stadiums
        for(int i = 0; i < n_stadium; i++)
        {
            stadium[i] = i + 1;
        }

        while(count < total - 1)
        {
            if(count != total - 1)
            {
                for(int i = 0; i < n_stadium; i++)
                {
                    if(count != total - 1)
                    {
                        venue[count] = stadium[i];
                        count += 1;
                    }
                }
            }
            i = 0;
        }

        for(int i = 0; i < total; i++)
        {
            if(i != total - 1)
            {
                continue;
            }
            else
            {
                for(int j = 0; j < n_stadium; j++)
                {
                    if(venue[count - 1] == stadium[j])
                    {
                        if(j != n_stadium - 1)
                        {
                            venue[count] = stadium[i+1];
                        }
                        else
                        {
                            venue[count] = stadium[0];
                        }
                    }
                }
            }
        }
    }

    else if (n == n_stadium)
    {
        //Getting names of teams and homegrounds
        for(int i = 0; i < n; i++)
        {
            printf("Enter the name for team number %d this year: ", i+1);
            scanf("%s", team_data[i]);
            printf("Enter the home city for %s: ", team_data[i]);
            scanf("%s", venue_data[i]);
        }

        for(int i = 0; i < total; i++)
        {
            if(a[i] == 0)
            {
                strcpy(venue_final[i], venue_data[5]);
            }
            else
            {
                for(int k = 1; k < n+1; k++)
                {
                    if(a[i] == k)
                    {
                        strcpy(venue_final[i], venue_data[k-1]);
                    }
                }
            }
        }
    }

    //Increasing Readability of the schedule
    for (int i = 0; i < total; i++)
    {
        if(a[i] == 0)
        {
            strcpy(a_final[i], team_data[5]);
        }
        else
        {
            for(int k = 1; k < n+1; k++)
            {
                if(a[i] == k)
                {
                    strcpy(a_final[i], team_data[k-1]);
                }
            }
        }
    }

    for (int i = 0; i < total; i++)
    {
        if(b[i] == 0)
        {
            strcpy(b_final[i], team_data[4]);
        }
        else
        {
            for(int k = 1; k < n+1; k++)
            {
                if(b[i] == k)
                {
                    strcpy(b_final[i], team_data[k-1]);
                }
            }
        }
    }

    //Days Mapping
    map_days(day, days, total);

    //Time mapping
    map_time(time, total);

    //Printing the IPL SCHEDULE

    ipl_match_ptr = (struct ipl_schedule*) malloc(total*(sizeof(struct ipl_schedule)));

    for(int i = 0; i < total; i++)
    {
        strcpy((ipl_match_ptr+i)->days, day[i]);
        strcpy((ipl_match_ptr+i)->time, time[i]);
        strcpy((ipl_match_ptr+i)->a_final, a_final[i]);
        strcpy((ipl_match_ptr+i)->b_final, b_final[i]);
        strcpy((ipl_match_ptr+i)->venue_final, venue_final[i]);
    }

    printf("\nTHE IPL SCHEDULE\n");
    for(int i = 0; i < total; i++)
    {
        if(n_stadium < n)
        {
            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: Stadium Number %d\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, venue[i]);
        }
        else
        {
            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: %s\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, (ipl_match_ptr+i)->venue_final);
        }
    }
}

//Schedules the Playoffs given the top 4 teams in the points table.
//Always only top 4 qualify to finals in IPL.
void playoff()
{
    int i;
    char winners[10][100];
    char venue[4][100];

    printf("\nPLAYOFFS");
    printf("\nEnter the stadium for Qualifier 1 Match: ");
    scanf("%s", venue[0]);
    printf("\nEnter the stadium for Eliminator Match: ");
    scanf("%s", venue[1]);
    printf("\nEnter the stadium for Qualifier 2 Match: ");
    scanf("%s", venue[2]);
    printf("\nEnter the stadium for the IPL Finals: ");
    scanf("%s", venue[3]);

    printf("\nEnter the top 4 teams in order:\n");
    i = 0;

    while(i < 4)
    {
        printf("Enter the team in %d position in the points table: ", i + 1);
        scanf("%s", winners[i]);
        i = i + 1;
    }

    /*
    0
    1
    2
    3
    4 -> Winner of 0 and 1
    5 -> Loser of 0 and 1

    0 1
    2 3
    */

    printf("Qualifier 1 is %s vs %s in %s at 7:30pm.\n", winners[0], winners[1], venue[0]);
    printf("Enter the team's name that won in this match: ");
    scanf("%s", winners[4]);

    if(strcmp(winners[0], winners[4]) == 0)
    {
        strcpy(winners[5], winners[1]);
    }

    printf("Eliminator is %s vs %s in %s at 7:30pm.\n", winners[2], winners[3], venue[1]);
    printf("Enter the team's name that won in this match: ");
    scanf("%s", winners[6]);

    if(strcmp(winners[2], winners[6]) == 0)
    {
        strcpy(winners[7], winners[3]);
    }

    printf("Qualifier 2 is %s vs %s in %s at 7:30pm.\n", winners[5], winners[6], venue[2]);
    printf("Enter the team's name that won in this match: ");
    scanf("%s", winners[8]);

    printf("The IPL Final: %s vs %s in %s at 7:30pm.\n", winners[4], winners[8], venue[3]);
    printf("Enter the team's name that won in this match: ");
    scanf("%s", winners[9]);

    if(strcmp(winners[9], "RCB") == 0)
    {
        printf("Congratulations to Kohli and Co! Finally %s have won the IPL!", winners[9]);
        return;
    }
    printf("The winner of this year's IPL is %s!", winners[9]);
}

//Main Driver Code
int main()
{
    //Arjun
    int n, total, day_one;

    //Number of teams INPUT
    printf("Welcome to the IPL SCHEDULER. \nFollow the instructions to get the schedule.\nEnter the number of teams:\n");
    scanf("%d", &n);
    printf("\n");

    //Starting Day of IPL INPUT
    printf("Enter the starting day of the tournament.\n1. Monday\n2. Tuesday\n3. Wednesday\n4. Thursday\n5. Friday\n6. Saturday\n7. Sunday\n\nEnter The Day: ");
    scanf("%d", &day_one);
    printf("\n");

    //Total of 2*(nC2) matches = n*(n-1)
    total = n*(n-1);

    //printf("Total Number of matches: %d\n", total); Unnecessary to print here!

    //LOGIC STARTS HERE
    int team_A[500], team_B[500]; //Source Arrays
    int days[500]; //Days 1,2,3,4,5,6,7
    char time[500][100]; //Time A, E
    int a[500], b[500]; //IPL Final Schedule Arrays

    int count = 0; //To maintain index of combinations

    //Something Magical can be done when n = 8.
    if(n == 8)
    {
        //Generating Possible Match Combinations
        for(int i = 1; i < n + 1; i++)
        {
            for(int j = 1; j < n + 1; j++)
            {
                // i -> Home Team (A), j -> Away Team (B)
                if(i != j)
                {
                    team_A[count] = i;
                    team_B[count] = j;
                    count++;
                }
            }
        }

        //Days Scheduling with gap_based_choice = 1
        schedule_days(days, day_one, total, 1);

        //Days Scheduling Done

        //Time Scheduling with time_based_choice = 1
        schedule_time(time, total, days, 1);

        //Time Scheduling Done

        //Sreepadh

        //IPL SCHEDULE MAIN ALGORITHM - 8 teams.
        //team_A - Source array with Possible match combinations
        //team_B - Source array with Possible match combinations
        //a - Final Match Schedule array of team A
        //b - Final Match Schedule array of team B
        //days - Monday, Tuesday -> 1,2,3,4,5,6,6,7,7
        //time - A, E

        //Initializing matches to 0 -> Not Scheduled.
        for(int i = 0; i < total; i++)
        {
            a[i] = 0;
            b[i] = 0;
        }

        //Initializing first 4 matches in such a way that our algorithm doesn't enter a deadlock or Infinte Loop
        if(day_one == 1)
        {
            a[0] = 1; b[0] = 2;
            a[1] = 3; b[1] = 4;
            a[2] = 5; b[2] = 6;
            a[3] = 7; b[3] = 8;
        }
        else if (day_one == 2)
        {
            a[0] = 1; b[0] = 2;
            a[1] = 3; b[1] = 4;
            a[2] = 1; b[2] = 5;
            a[3] = 2; b[3] = 3;
        }
        else if (day_one == 3)
        {
            a[0] = 1; b[0] = 6;
            a[1] = 2; b[1] = 4;
            a[2] = 1; b[2] = 5;
            a[3] = 2; b[3] = 3;
        }
        else if (day_one == 4)
        {
            a[0] = 1; b[0] = 2;
            a[1] = 3; b[1] = 4;
            a[2] = 1; b[2] = 5;
            a[3] = 2; b[3] = 3;
        }
        else if (day_one == 5)
        {
            a[0] = 1; b[0] = 2;
            a[1] = 8; b[1] = 7;
            a[2] = 3; b[2] = 4;
            a[3] = 2; b[3] = 1;
        }
        else if (day_one == 6)
        {
            a[0] = 1; b[0] = 7;
            a[1] = 5; b[1] = 6;
            a[2] = 8; b[2] = 3;
            a[3] = 2; b[3] = 1;
        }
        else if (day_one == 7)
        {
            a[0] = 1; b[0] = 8;
            a[1] = 2; b[1] = 4;
            a[2] = 1; b[2] = 5;
            a[3] = 3; b[3] = 4;
        }

        //Making scheduled matches in Source Array 0 to avoid repetetion of matches

        for(int i = 0; i < total; i++)
        {
            if(a[0] == team_A[i] && b[0] == team_B[i])
            {
                team_A[i] = 0;
                team_B[i] = 0;
            }
            if(a[1] == team_A[i] && b[1] == team_B[i])
            {
                team_A[i] = 0;
                team_B[i] = 0;
            }
            if(a[2] == team_A[i] && b[2] == team_B[i])
            {
                team_A[i] = 0;
                team_B[i] = 0;
            }
            if(a[3] == team_A[i] && b[3] == team_B[i])
            {
                team_A[i] = 0;
                team_B[i] = 0;
            }
        }

        //Initialized first 4 matches successfully.
        //Scheduling the REST OF IPL.

        while((checkArray(&team_A[0], &total) != 1) && a[total - 1] == 0) //While there are some more matches to be scheduled
        {
            for(int i = 0; i < total; i++) //Iterating through each pair of Source array which has the possible combinations
            {
                //If the pair is not scheduled
                if(team_A[i] != 0 && team_B[i] != 0)
                {
                    //Iterate through final schedule array.
                    for(int j = n/2; j < total; j++) //n/2 because first 4 matches already scheduled
                    {
                        //If the match is not scheduled.
                        if(a[j] == 0 && b[j] == 0)
                        {
                            if(days[j] == 1) //Monday
                            {
                                //comp(a, team_a, team_b, i, j, k) function checks whether the current pair of teams has played in the previous k matches. If that is true function will return 0, otherwise 1.
                                if(compare(a, team_A, team_B, i, j, 2) == 1 && compare(b, team_A, team_B, i, j, 2) == 1 && compare_zero(a, i, j, 2) == 1 && compare_zero(b, i, j, 2) == 1)
                                {
                                    a[j] = team_A[i]; //Schedule the match.
                                    b[j] = team_B[i];
                                    team_A[i] = 0; //Make it 0 in source array to identify that match has been scheduled.
                                    team_B[i] = 0;
                                }
                            }
                            else if (days[j] == 2 || days[j] == 3 || days[j] == 4 || days[j] == 5)
                            {
                                if(compare(a, team_A, team_B, i, j, 1) == 1 && compare(b, team_A, team_B, i, j, 1) == 1 && compare_zero(a, i, j, 1) == 1 && compare_zero(b, i, j, 1) == 1)
                                {
                                    a[j] = team_A[i];
                                    b[j] = team_B[i];
                                    team_A[i] = 0;
                                    team_B[i] = 0;
                                }
                            }
                            else if((days[j] == 6) && (strcmp(time[j], "A") == 0))
                            {
                                if(compare(a, team_A, team_B, i, j, 1) == 1 && compare(b, team_A, team_B, i, j, 1) == 1 && compare_zero(a, i, j, 1) == 1 && compare_zero(b, i, j, 1) == 1)
                                {
                                    a[j] = team_A[i];
                                    b[j] = team_B[i];
                                    team_A[i] = 0;
                                    team_B[i] = 0;
                                }
                            }
                            else if((days[j] == 6) && (strcmp(time[j], "E") == 0))
                            {
                                //basically writing the entire comparison the way comp works
                                if((a[j-1] != team_A[i] && b[j-1] != team_B[i]) && (a[j-1] != team_B[i] && b[j-1] != team_A[i]) && (a[j-2] != team_A[i] && b[j-2] != team_B[i]) && (a[j-2] != team_B[i] && b[j-2] != team_A[i]) && (a[j-1] != 0 && b[j-1] != 0) && (a[j-2] != 0 && b[j-2] != 0))
                                {
                                    a[j] = team_A[i];
                                    b[j] = team_B[i];
                                    team_A[i] = 0;
                                    team_B[i] = 0;
                                }
                            }
                            else if((days[j] == 7) && (strcmp(time[j], "A") == 0))
                            {
                                if((a[j-1] != team_A[i] && b[j-1] != team_B[i]) && (a[j-1] != team_B[i] && b[j-1] != team_A[i]) && (a[j-2] != team_A[i] && b[j-2] != team_B[i]) && (a[j-2] != team_B[i] && b[j-2] != team_A[i]) && (a[j-1] != 0 && b[j-1] != 0) && (a[j-2] != 0 && b[j-2] != 0))
                                {
                                    a[j] = team_A[i];
                                    b[j] = team_B[i];
                                    team_A[i] = 0;
                                    team_B[i] = 0;
                                }
                            }
                            else if((days[j] == 7) && (strcmp(time[j], "E") == 0))
                            {
                                if((a[j-1] != team_A[i] && b[j-1] != team_B[i]) && (a[j-1] != team_B[i] && b[j-1] != team_A[i]) && (a[j-2] != team_A[i] && b[j-2] != team_B[i]) && (a[j-2] != team_B[i] && b[j-2] != team_A[i]) && (a[j-3] != team_A[i] && b[j-3] != team_B[i]) && (a[j-3] != team_B[i] && b[j-3] != team_A[i]) && (a[j-1] != 0 && b[j-1] != 0) && (a[j-2] != 0 && b[j-2] != 0) && (a[j-3] != 0 && b[j-3] != 0))
                                {
                                    a[j] = team_A[i];
                                    b[j] = team_B[i];
                                    team_A[i] = 0;
                                    team_B[i] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        //Scheduling of 8 matches done.
        print_schedule(a, b, days, time, total, n);
        playoff();
    }

    else //n != 8.
    {
        if(n % 2 == 0) // n != 8 and EVEN
        {
            int arr[20]; //assuming a max of 20 teams

            //arr[] = {1,2,3,4,5,6,...n} - Team numbers
            //This array will be rotated to get the team combinations

            for(int i = 0; i < n; i++)
            {
                arr[i] = i + 1;
            }

            int match_count_A = 0;
            int match_count_B = 0;

            //team_A and team_B = stores the match combinations (ie the initial array and the rotated arrays)
            for(int i = 0; i < n / 2; i++)
            {
                team_A[match_count_A] = arr[i];
                match_count_A += 1;
            }
            for(int i = n-1; i > n/2-1; i--)
            {
                team_B[match_count_B] = arr[i];
                match_count_B += 1;
            }

            //Base Array Generated

            //Array Rotation
            for(int j = 0; j < n-2; j++)
            {
                rotate(arr, n);
                for(int i = 0; i < n / 2; i++)
                {
                    team_A[match_count_A] = arr[i];
                    match_count_A += 1;
                }
                for(int i = n-1; i > n/2-1; i--)
                {
                    team_B[match_count_B] = arr[i];
                    match_count_B += 1;
                }
            }

            printf("\n");
            //printf("Total Number of matches : %d\n", 2*match_count_A);

            int count = 1;
            for(int i = 0; i < n*(n-1)/2; i++)
            {
                a[i] = team_A[i];
                b[i] = team_B[i];
                //printf("Match %d, %d vs %d\n", count, a[i], b[i]);
                count += 1;
            }

            for(int i = n*(n-1)/2, j = 0; i < n*(n-1), j < n*(n-1)/2; i++, j++)
            {
                a[i] = team_B[j];
                b[i] = team_A[j];
                //printf("Match %d, %d vs %d\n", count, a[i], b[i]);
                count += 1;
            }

            if (n < 8) //If number of teams is less than 8, to avoid collisions, we leave 1 day gap between consective matches.
            {
                schedule_days(&days[0], day_one, total, 2);
                schedule_time(time, total, days, 2); //Only Evening matches
            }
            else
            {
                schedule_days(&days[0], day_one, total, 1);
                schedule_time(time, total, days, 1); //Both A and E matches
            }

            print_schedule(a, b, days, time, total, n);

            //Days Scheduled
            //Time Scheduled

            //print_schedule();

            //Reschedule if necessary, or proceed with playoffs
            int reschedule_choice; // 1 -> Reschedule, 0 -> Proceed to Playoffs
            do
            {
                printf("\nDid all matches go smoothly? (1 -> Yes. 0 -> No): ");
                scanf("%d", &reschedule_choice);

                if(reschedule_choice == 0)
                {
                    int starting_match; //Match Number from which IPL should be rescheduled
                    int new_dayOne; //New day from which IPL should start
                    printf("\nDon't worry! We've got it all covered. Enter the match number(1 -> %d) from which you want to reschedule the IPL: ", total);
                    scanf("%d", &starting_match);
                    printf("\nWhen is the IPL Starting again?\n1. Monday\n2. Tuesday\n3. Wednesday\n4. Thursday\n5. Friday\n6. Saturday\n7. Sunday\n\nEnter The Day: ");
                    scanf("%d", &new_dayOne);

                    if (n < 8) //If number of teams is less than 8, to avoid collisions, we leave 1 day gap between consective matches.
                    {
                        schedule_days(&days[starting_match - 1], new_dayOne, total, 2);
                    }
                    else
                    {
                        schedule_days(&days[starting_match - 1], new_dayOne, total, 1);
                        schedule_time(time, total, days, 1); //Both A and E matches
                    }

                    map_days(day, days, total);
                    map_time(time, total);

                    //Printing the IPL SCHEDULE

                    ipl_match_ptr = (struct ipl_schedule*) malloc(total*(sizeof(struct ipl_schedule)));

                    for(int i = 0; i < total; i++)
                    {
                        strcpy((ipl_match_ptr+i)->days, day[i]);
                        strcpy((ipl_match_ptr+i)->time, time[i]);
                        strcpy((ipl_match_ptr+i)->a_final, a_final[i]);
                        strcpy((ipl_match_ptr+i)->b_final, b_final[i]);
                        strcpy((ipl_match_ptr+i)->venue_final, venue_final[i]);
                    }

                    printf("\nTHE IPL SCHEDULE\n");
                    for(int i = 0; i < total; i++)
                    {
                        if(i == starting_match -1)
                        {
                            printf("\nMODIFIED PART OF SCHEDULE\n");
                        }
                        if(n_stadium < n)
                        {
                            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: Stadium Number %d\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, venue[i]);
                        }
                        else
                        {
                            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: %s\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, (ipl_match_ptr+i)->venue_final);
                        }
                    }
                }

            } while (reschedule_choice != 1);
            
            printf("Glad to hear that!\nLet's proceed to playoffs now\n\n");
            playoff();
        }
        
        else // n not != 8 and ODD -> Only difference being the extra dummy team.
        {
            int temp = n;
            temp += 1;

            int arr[20]; //assuming max 20 teams

            //Generating arr[] = {1,2,3,4,5,...n+1}
            for(int i = 0; i < temp; i++)
            {
                arr[i] = i + 1;
            }

            int match_count_A = 0;
            int match_count_B = 0;

            for(int i = 0; i < temp / 2; i++)
            {
                team_A[match_count_A] = arr[i];
                match_count_A += 1;
            }
            for(int i = temp-1; i > temp/2-1; i--)
            {
                team_B[match_count_B] = arr[i];
                match_count_B += 1;
            }

            //Base Array Generated

            //Array Rotation
            for(int j = 0; j < temp-2; j++)
            {
                rotate(arr, temp);
                for(int i = 0; i < temp / 2; i++)
                {
                    team_A[match_count_A] = arr[i];
                    match_count_A += 1;
                }
                for(int i = temp-1; i > temp / 2 - 1; i--)
                {
                    team_B[match_count_B] = arr[i];
                    match_count_B += 1;
                }
            }

            printf("\n");
            //printf("Total Number of matches : %d\n", 2*match_count_A);

            int count = 1;
            for(int i = 0; i < temp*(temp-1)/2; i++)
            {
                if((team_A[i] != temp) && (team_B[i] != temp)) //Remove matches that have the extra team(dummy team)
                {
                    a[i] = team_A[i];
                    b[i] = team_B[i];
                    //printf("Match %d, %d vs %d\n", count, a[i], b[i]);
                    count += 1;
                }
            }

            for(int i = temp*(temp-1)/2, j = 0; i < temp*(temp-1), j < temp*(temp-1)/2; i++, j++)
            {
                if((team_A[j] != temp) && (team_B[j] != temp)) //Remove matches that have the extra team(dummy team)
                {
                    a[i] = team_B[j];
                    b[i] = team_A[j];
                    //printf("Match %d, %d vs %d\n", count, a[i], b[i]);
                    count += 1;
                }
            }

            if (n < 8) //If number of teams is less than 8, to avoid collisions, we leave 1 day gap between consective matches.
            {
                schedule_days(&days[0], day_one, total, 2);
                schedule_time(time, total, days, 2); //Only Evening matches
            }
            else
            {
                schedule_days(&days[0], day_one, total, 3); //Weekend only 1 match
                schedule_time(time, total, days, 2); //Only Evening matches
            }

            //Days Scheduled
            //Time Scheduled

            //print_schedule();
            print_schedule(a, b, days, time, total, n);

            //Reschedule if necessary, or proceed with playoffs
            //Reschedule if necessary, or proceed with playoffs
            int reschedule_choice; // 1 -> Reschedule, 0 -> Proceed to Playoffs
            do
            {
                printf("\nDid all matches go smoothly? (1 -> Yes. 0 -> No): ");
                scanf("%d", &reschedule_choice);

                if(reschedule_choice == 0)
                {
                    int starting_match; //Match Number from which IPL should be rescheduled
                    int new_dayOne; //New day from which IPL should start
                    printf("\nDon't worry! We've got it all covered. Enter the match number(1 -> %d) from which you want to reschedule the IPL: ", total);
                    scanf("%d", &starting_match);
                    printf("\nWhen is the IPL Starting again?\n1. Monday\n2. Tuesday\n3. Wednesday\n4. Thursday\n5. Friday\n6. Saturday\n7. Sunday\n\nEnter The Day: ");
                    scanf("%d", &new_dayOne);

                    if (n < 8) //If number of teams is less than 8, to avoid collisions, we leave 1 day gap between consective matches.
                    {
                        schedule_days(&days[starting_match - 1], new_dayOne, total, 2);
                    }
                    else
                    {
                        schedule_days(&days[starting_match - 1], new_dayOne, total, 1);
                        schedule_time(time, total, days, 1); //Both A and E matches
                    }

                    map_days(day, days, total);
                    map_time(time, total);

                    //Printing the IPL SCHEDULE

                    ipl_match_ptr = (struct ipl_schedule*) malloc(total*(sizeof(struct ipl_schedule)));

                    for(int i = 0; i < total; i++)
                    {
                        strcpy((ipl_match_ptr+i)->days, day[i]);
                        strcpy((ipl_match_ptr+i)->time, time[i]);
                        strcpy((ipl_match_ptr+i)->a_final, a_final[i]);
                        strcpy((ipl_match_ptr+i)->b_final, b_final[i]);
                        strcpy((ipl_match_ptr+i)->venue_final, venue_final[i]);
                    }

                    printf("\nTHE IPL SCHEDULE\n");
                    for(int i = 0; i < total; i++)
                    {
                        if(i == starting_match -1)
                        {
                            printf("\nMODIFIED PART OF SCHEDULE\n");
                        }
                        if(n_stadium < n)
                        {
                            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: Stadium Number %d\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, venue[i]);
                        }
                        else
                        {
                            printf("Match No: %d | Day: %s | Time: %s | Match: (%s vs %s) | Venue: %s\n", i+1, (ipl_match_ptr+i)->days, (ipl_match_ptr+i)->time, (ipl_match_ptr+i)->a_final, (ipl_match_ptr+i)->b_final, (ipl_match_ptr+i)->venue_final);
                        }
                    }
                }

            } while (reschedule_choice != 1);
            
            printf("Glad to hear that!\nLet's proceed to playoffs now\n\n");
            playoff();
        }
    }
}