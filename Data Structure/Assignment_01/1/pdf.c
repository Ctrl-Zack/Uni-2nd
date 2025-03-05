/*
# Task
    Buatlah program menu yang berisi data-data KTP penduduk yang
    disimpan dalam array struct 1 dimensi dan dapat dilakukan
    penambahan data, pencarian data, penampilan data dan
    penghapusan data.

    Create a menu program that contains resident ID card data that
    is stored in a 1-dimensional struct array and can be used
    to add data, search for data, display data and delete data.
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_FILENAME "database_ktp.txt"
#define MAX_DATA 256
#define NIK_LEN 16
#define NAME_LEN 60
#define ADMINISTRATIVE_LEN 64
#define RELIGION_LEN 18
#define JOB_LEN 32

typedef struct {
    unsigned short day;
    unsigned short month;
    unsigned short year;
} Date;

typedef struct {
    char Addr[128];
    int RT;
    int RW;
    char village[ADMINISTRATIVE_LEN];
    char district[ADMINISTRATIVE_LEN];
} Address;

typedef struct {
    char NIK[NIK_LEN + 1];
    char full_name[NAME_LEN + 1];
    char place_of_birth[ADMINISTRATIVE_LEN];
    Date date_of_birth;
    char gender;
    char religion[RELIGION_LEN];
    _Bool marital_status;
    char blood_type[4];
    Address address;
    char job[JOB_LEN];
} KTP;


void load_data();

int main() {
    KTP citizen_data[MAX_DATA];
    return 0;
}

void load_data(KTP data[], short *record_count) {
    *record_count = 0;

    FILE *db = fopen(DATABASE_FILENAME, "r+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    char buffer[1024];
    const char tok[2] = ",";
    char *token;
    char *endPtr;

    while(fgets(buffer, 1024, db) != NULL) {
        // NIK
        token = strtok(buffer, tok);
        strcpy(data[*record_count].NIK, token);
        
        // full_name
        token = strtok(NULL, tok);
        strncpy(data[*record_count].full_name, token, NAME_LEN);
        
        // place_of_birth
        token = strtok(NULL, tok);
        strncpy(data[*record_count].place_of_birth, token, ADMINISTRATIVE_LEN);
        
        // date_of_birth
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.day = (unsigned short)strtold(token, &endPtr);
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.month = (unsigned short)strtold(token, &endPtr);
        token = strtok(NULL, tok);
        data[*record_count].date_of_birth.year = (unsigned short)strtold(token, &endPtr);
        
        // gender
        token = strtok(NULL, tok);
        data[*record_count].gender = *token;
        
        // religion
        token = strtok(NULL, tok);
        strncpy(data[*record_count].religion, token, RELIGION_LEN);
        
        // marital status
        token = strtok(NULL, tok);
        data[*record_count].marital_status = (_Bool)strtold(token, &endPtr);
        
        // blood type
        token = strtok(NULL, tok);
        strncpy(data[*record_count].blood_type, token, 4);
        
        (*record_count)++;
    }

    fclose(db);
}

/*
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHT 200
#define MAX_CITY_LEN 20
#define FLIGHT_CODE_LEN 6
#define STR_DATE_LEN 10
#define STR_TIME_LEN 8
#define DATABASE_FILE "databases.txt"

typedef struct {
    char date[STR_DATE_LEN + 1]; // YYYY-MM-DD
    char time[STR_TIME_LEN + 1]; // HH:MM:SS
} DateTime;

typedef struct {
    char flight_number[FLIGHT_CODE_LEN + 1];
    char departure_city[MAX_CITY_LEN + 1];
    char destination_city[MAX_CITY_LEN + 1];
    DateTime date_time_departure;
    DateTime date_time_arrival;
    short f_c_seats_available;
    short f_c_seats_sold;
    short c_seats_available;
    short c_seats_sold;
} Flight;

void prompt(Flight records[], short *record_count);
void load_flight(Flight records[], short *record_count);
void save_database(const Flight records[], const short *record_count);
void display(const Flight records[], const short record_count);
void display_specific_record(const Flight records[], const short record_line);
void create(short *record_count);
void delete(Flight records[], short *record_count);
void update(Flight records[], const short *record_count);
short find_flight_line(const char* flight_number);
void make_reservation(Flight records[], const short *record_count);
void cancel_reservation(Flight records[], const short *record_count);

int main() {
    Flight records[MAX_FLIGHT];
    short record_count;
    load_flight(records, &record_count);
    prompt(records, &record_count);
    return 0;
}

void prompt(Flight records[], short *record_count) {
    char prt;
    
    do {
        printf("\033[H\033[J");
        puts("+----------------------------+");
        puts("| Airline Reservation System |");
        puts("+----------------------------+");
        puts("| 1. Create Flight           |");
        puts("| 2. Update Flight           |");
        puts("| 3. Delete Flight           |");
        puts("| 4. Make Reservation        |");
        puts("| 5. Cancel Reservation      |");
        puts("| 6. Display All Records     |");
        puts("| 7. Exit                    |");
        puts("+----------------------------+");
        
        scanf("%c", &prt);
        switch(prt) {
        case '1':
            create(record_count);
            load_flight(records, record_count); // re-load database
            break;
        case '2':
            update(records, record_count);
            load_flight(records, record_count); // re-load database
            break;
        case '3':
            delete(records, record_count);
            load_flight(records, record_count); // re-load database
            break;
        case '4':
            make_reservation(records, record_count);
            load_flight(records, record_count); // re-load database
            break;
        case '5':
            cancel_reservation(records, record_count);
            load_flight(records, record_count); // re-load database
            break;
        case '6':
            display(records, *record_count);
            break;
        default:
            break;
        }
    } while(prt != '7');
}

void load_flight(Flight records[], short *record_count) {
    *record_count = 0;

    FILE *db = fopen(DATABASE_FILE, "r+");
    if(db == NULL) {
        save_database(records, record_count); // create new database on fail
        return;
    }
    
    char buffer[1024];
    const char tok[2] = ",";
    char *token;
    char *endPtr;

    while(fgets(buffer, 1024, db) != NULL) {
        // flight number
        token = strtok(buffer, tok);
        strcpy(records[*record_count].flight_number, token);
        
        // departure city
        token = strtok(NULL, tok);
        strncpy(records[*record_count].departure_city, token, MAX_CITY_LEN);
        
        // destination city
        token = strtok(NULL, tok);
        strncpy(records[*record_count].destination_city, token, MAX_CITY_LEN);
        
        // departure dateTime
        token = strtok(NULL, tok);
        strncpy(records[*record_count].date_time_departure.date, token, STR_DATE_LEN);
        strncpy(records[*record_count].date_time_departure.time, token + STR_DATE_LEN + 1, STR_TIME_LEN);
        
        // arrival dateTime
        token = strtok(NULL, tok);
        strncpy(records[*record_count].date_time_arrival.date, token, STR_DATE_LEN);
        strncpy(records[*record_count].date_time_arrival.time, token + STR_DATE_LEN + 1, STR_TIME_LEN);
        
        // first class seats available
        token = strtok(NULL, tok);
        records[*record_count].f_c_seats_available = (short)strtold(token, &endPtr);
        
        // first class seats sold
        token = strtok(NULL, tok);
        records[*record_count].f_c_seats_sold = (short)strtold(token, &endPtr);
        
        // coach seats available
        token = strtok(NULL, tok);
        records[*record_count].c_seats_available = (short)strtold(token, &endPtr);
        
        // coach seats sold
        token = strtok(NULL, tok);
        records[*record_count].c_seats_sold = (short)strtold(token, &endPtr);

        (*record_count)++;
    }

    fclose(db);
}

void save_database(const Flight records[], const short *record_count) {
    FILE *db = fopen(DATABASE_FILE, "w+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }

    // print updated data to the database
    for(short i = 0; i < *record_count; i++) {
        fprintf(db, "%s,%s,%s,%s %s,%s %s,%hi,%hi,%hi,%hi\n",
        records[i].flight_number,
        records[i].departure_city,
        records[i].destination_city,
        records[i].date_time_departure.date,
        records[i].date_time_departure.time,
        records[i].date_time_arrival.date,
        records[i].date_time_arrival.time,
        records[i].f_c_seats_available,
        records[i].f_c_seats_sold,
        records[i].c_seats_available,
        records[i].c_seats_sold
        );
    }
    
    fclose(db);
}

void display(const Flight records[], const short record_count) {
    printf("\033[H\033[J");
    puts("+========+======================+======================+=====================+=====================+===============+===============+=========+=========+");
    puts("| fl_num |    departure_city    |   destination_city   |   departure__time   |    arrival__time    | first_class_a | first_class_s | coach_a | coach_s |");
    puts("+========+======================+======================+=====================+=====================+===============+===============+=========+=========+");
    for(short i = 0; i < record_count; i++) {
        printf("| %-6s | %-20s | %-20s | %s %s | %s %s | %-13hi | %-13hi | %-7hi | %-7hi |\n",
            records[i].flight_number,
            records[i].departure_city,
            records[i].destination_city,
            records[i].date_time_departure.date,
            records[i].date_time_departure.time,
            records[i].date_time_arrival.date,
            records[i].date_time_arrival.time,
            records[i].f_c_seats_available,
            records[i].f_c_seats_sold,
            records[i].c_seats_available,
            records[i].c_seats_sold
        );
        puts("+--------+----------------------+----------------------+---------------------+---------------------+---------------+---------------+---------+---------+");
    }
    printf("Total : %hi records\n", record_count);
    puts("Press any key to go back to the main menu...");
    getch();
}

void display_specific_record(const Flight records[], const short record_line) {
    puts("+========+======================+======================+=====================+=====================+===============+===============+=========+=========+");
    puts("| fl_num |    departure_city    |   destination_city   |   departure__time   |    arrival__time    | first_class_a | first_class_s | coach_a | coach_s |");
    puts("+========+======================+======================+=====================+=====================+===============+===============+=========+=========+");
    printf("| %-6s | %-20s | %-20s | %s %s | %s %s | %-13hi | %-13hi | %-7hi | %-7hi |\n",
        records[record_line].flight_number,
        records[record_line].departure_city,
        records[record_line].destination_city,
        records[record_line].date_time_departure.date,
        records[record_line].date_time_departure.time,
        records[record_line].date_time_arrival.date,
        records[record_line].date_time_arrival.time,
        records[record_line].f_c_seats_available,
        records[record_line].f_c_seats_sold,
        records[record_line].c_seats_available,
        records[record_line].c_seats_sold
    );
    puts("+--------+----------------------+----------------------+---------------------+---------------------+---------------+---------------+---------+---------+");
}

void create(short *record_count) {
    printf("\033[H\033[J");
    
    (*record_count)++;
    if(*record_count >= MAX_FLIGHT) {
        (*record_count)--;
        puts("Flight Limit Reached.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    Flight newRecord;

    puts("Create new flight record.");
    
    // flight number
    printf("Flight Number: ");
    scanf(" %s", newRecord.flight_number);
    if(find_flight_line(newRecord.flight_number) != -1) {
        puts("Flight number already exist.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    // departure city
    printf("Departure city: ");
    scanf(" %[^\n]s", newRecord.departure_city);
    
    // destination city
    printf("Destination city: ");
    scanf(" %[^\n]s", newRecord.destination_city);
    
    // departure dateTime
    printf("Departure time: ");
    scanf(" %s %s", newRecord.date_time_departure.date, newRecord.date_time_departure.time);
    
    // arrival dateTime
    printf("Arrival time: ");
    scanf(" %s %s", newRecord.date_time_arrival.date, newRecord.date_time_arrival.time);
    
    // first class seats
    printf("First Class seats: ");
    scanf("%hi", &newRecord.f_c_seats_available);
    newRecord.f_c_seats_sold = 0;
    
    // coach seats
    printf("Coach seats: ");
    scanf("%hi", &newRecord.c_seats_available);
    newRecord.c_seats_sold = 0;

    FILE *db = fopen(DATABASE_FILE, "a+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }

    // append new record to the database
    fprintf(db, "%s,%s,%s,%s %s,%s %s,%hi,%hi,%hi,%hi\n",
        newRecord.flight_number,
        newRecord.departure_city,
        newRecord.destination_city,
        newRecord.date_time_departure.date,
        newRecord.date_time_departure.time,
        newRecord.date_time_arrival.date,
        newRecord.date_time_arrival.time,
        newRecord.f_c_seats_available,
        newRecord.f_c_seats_sold,
        newRecord.c_seats_available,
        newRecord.c_seats_sold
    );

    fclose(db);
}

void delete(Flight records[], short *record_count) {
    char fl_num[FLIGHT_CODE_LEN + 1];
    
    printf("\033[H\033[J");
    puts("Delete flight record.");
    printf("Please enter the flight number that you would like to delete: ");
    scanf("%s", fl_num);

    short record_line = find_flight_line(fl_num);

    if(record_line == -1) {
        puts("Flight number doesn't exist.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    display_specific_record(records, record_line);

    // update all records index
    for (int i = record_line; i < *record_count - 1; i++) {
        records[i] = records[i + 1];
    }
    
    (*record_count)--;
    save_database(records, record_count);

    puts("record deleted successfully.");
    puts("Press any key to go back to the main menu...");
    getch();
}

void update(Flight records[], const short *record_count) {
    char fl_num[FLIGHT_CODE_LEN + 1];
    
    printf("\033[H\033[J");
    puts("Update flight record.");
    printf("Please enter the flight number that you would like to update: ");
    scanf("%s", fl_num);

    short record_line = find_flight_line(fl_num);

    if(record_line == -1) {
        puts("Flight number doesn't exist.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    display_specific_record(records, record_line);
    
    printf("update data on flight number [%s]:\n", records[record_line].flight_number);

    // departure city
    printf("Departure city: ");
    scanf(" %[^\n]s", records[record_line].departure_city);
    
    // destination city
    printf("Destination city: ");
    scanf(" %[^\n]s", records[record_line].destination_city);
    
    // departure dateTime
    printf("Departure time: ");
    scanf(" %s %s", records[record_line].date_time_departure.date, records[record_line].date_time_departure.time);
    
    // arrival dateTime
    printf("Arrival time: ");
    scanf(" %s %s", records[record_line].date_time_arrival.date, records[record_line].date_time_arrival.time);
    
    // first class seats available
    printf("First Class seats available: ");
    scanf("%hi", &records[record_line].f_c_seats_available);
    
    // first class seats sold
    printf("First Class seats sold: ");
    scanf("%hi", &records[record_line].f_c_seats_sold);
    
    // coach seats available
    printf("Coach seats available: ");
    scanf("%hi", &records[record_line].c_seats_available);

    // coach seats sold
    printf("Coach seats sold: ");
    scanf("%hi", &records[record_line].c_seats_sold);

    // save change to the database
    save_database(records, record_count);

    display_specific_record(records, record_line);

    puts("record updated successfully.");
    puts("Press any key to go back to the main menu...");
    getch();
}

short find_flight_line(const char* flight_number) {
    short record_line = 0;
    
    FILE *db = fopen(DATABASE_FILE, "r+");
    if(db == NULL) {
        perror("Error Opening Database");
        exit(-1);
    }
    
    char buffer[1024];
    const char tok[2] = ",";
    char *token;

    while(fgets(buffer, 1024, db) != NULL) {
        token = strtok(buffer, tok);
        if(strcmp(token, flight_number) == 0) {
            fclose(db);
            return record_line;
        }
        record_line++;
    }

    fclose(db);
    return -1;
}

void make_reservation(Flight records[], const short *record_count) {
    char fl_num[FLIGHT_CODE_LEN + 1];
    char seats_class;
    unsigned short seats_to_reserve;
    
    printf("\033[H\033[J");
    puts("Make reservation.");
    printf("Please enter your flight number to proceed with your reservation: ");
    scanf("%s", fl_num);

    short record_line = find_flight_line(fl_num);

    if(record_line == -1) {
        puts("Flight number doesn't exist.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    puts("Make reservation on this flight.");

    while(1) {
        display_specific_record(records, record_line);
        puts("Please select your preferred seat type:");
        puts("1. First Class");
        puts("2. Coach");
        puts("3. Back to the main menu");

        scanf(" %c", &seats_class);
        if(seats_class == '1') {
            if(records[record_line].f_c_seats_available != 0) {
                
                // first class seats available
                printf("First Class seats available: %hi\n", records[record_line].f_c_seats_available);
                puts("How many seat(s) would you like to reserve:");

                while(1) {
                    scanf("%hu", &seats_to_reserve);
                    if(seats_to_reserve > records[record_line].f_c_seats_available) {
                        printf("Sorry, we only have %hi seats available. Please enter a number equal to or less than the available seats\n", records[record_line].f_c_seats_available);
                    } else {
                        records[record_line].f_c_seats_available -= seats_to_reserve;
                        records[record_line].f_c_seats_sold += seats_to_reserve;

                        // save change to the database
                        save_database(records, record_count);
                        printf("%hi First class seat(s) successfully reserved.\n", seats_to_reserve);
                        break; // break the loop for seats to reserve input
                    }
                }
                break; // break the loop for seats class
            } else {
                puts("Sorry, there are no seats available.");
            }
        } else if(seats_class == '2') {
            if(records[record_line].c_seats_available != 0) {
                
                // first class seats available
                printf("Coach seats available: %hi\n", records[record_line].c_seats_available);
                puts("How many seat(s) would you like to reserve:");

                while(1) {
                    scanf("%hu", &seats_to_reserve);
                    if(seats_to_reserve > records[record_line].c_seats_available) {
                        printf("Sorry, we only have %hi seats available. Please enter a number equal to or less than the available seats\n", records[record_line].c_seats_available);
                    } else {
                        records[record_line].c_seats_available -= seats_to_reserve;
                        records[record_line].c_seats_sold += seats_to_reserve;

                        // save change to the database
                        save_database(records, record_count);
                        printf("%hi First class seat(s) successfully reserved.\n", seats_to_reserve);
                        break; // break the loop for seats to reserve input
                    }
                }
                break; // break the loop for seats class
            } else {
                puts("Sorry, there are no seats available.");
            }
        } else if(seats_class == '3') {
            return; // go back to the main menu
        } else {
            printf("\033[H\033[J");
        }
    }

    puts("Press any key to go back to the main menu...");
    getch();
}

void cancel_reservation(Flight records[], const short *record_count) {
    char fl_num[FLIGHT_CODE_LEN + 1];
    char seats_class;
    unsigned short seats_to_cancel;
    
    printf("\033[H\033[J");
    puts("Cancel reservation.");
    printf("Please enter your flight number to proceed with your reservation: ");
    scanf("%s", fl_num);

    short record_line = find_flight_line(fl_num);

    if(record_line == -1) {
        puts("Flight number doesn't exist.");
        puts("Press any key to go back to the main menu...");
        getch();
        return;
    }

    puts("Cancel reservation on this flight.");

    while(1) {
        display_specific_record(records, record_line);
        puts("Please select your seat class:");
        puts("1. First Class");
        puts("2. Coach");
        puts("3. Back to the main menu");

        scanf(" %c", &seats_class);
        if(seats_class == '1') {
            if(records[record_line].f_c_seats_sold != 0) {
                
                // first class seats sold
                printf("First Class seats sold: %hi\n", records[record_line].f_c_seats_sold);
                puts("How many seat(s) would you like to cancel:");

                while(1) {
                    scanf("%hu", &seats_to_cancel);
                    if(seats_to_cancel > records[record_line].f_c_seats_sold) {
                        printf("Sorry, we only have %hi seats sold. Please enter a number equal to or less than the sold seats\n", records[record_line].f_c_seats_sold);
                    } else {
                        records[record_line].f_c_seats_sold -= seats_to_cancel;
                        records[record_line].f_c_seats_available += seats_to_cancel;

                        // save change to the database
                        save_database(records, record_count);
                        printf("%hi First class seat(s) reservation successfully canceled.\n", seats_to_cancel);
                        break; // break the loop for seats to reserve input
                    }
                }
                break; // break the loop for seats class
            } else {
                puts("Sorry, there are no seats sold.");
            }
        } else if(seats_class == '2') {
             if(records[record_line].c_seats_sold != 0) {
                
                // first class seats sold
                printf("First Class seats sold: %hi\n", records[record_line].c_seats_sold);
                puts("How many seat(s) would you like to cancel:");

                while(1) {
                    scanf("%hu", &seats_to_cancel);
                    if(seats_to_cancel > records[record_line].c_seats_sold) {
                        printf("Sorry, we only have %hi seats sold. Please enter a number equal to or less than the sold seats\n", records[record_line].c_seats_sold);
                    } else {
                        records[record_line].c_seats_sold -= seats_to_cancel;
                        records[record_line].c_seats_available += seats_to_cancel;

                        // save change to the database
                        save_database(records, record_count);
                        printf("%hi First class seat(s) reservation successfully canceled.\n", seats_to_cancel);
                        break; // break the loop for seats to reserve input
                    }
                }
                break; // break the loop for seats class
            } else {
                puts("Sorry, there are no seats sold.");
            }
        } else if(seats_class == '3') {
            return; // go back to the main menu
        } else {
            printf("\033[H\033[J");
        }
    }

    puts("Press any key to go back to the main menu...");
    getch();
}
*/


/*
Develop a small airline reservation system. The database of flight information should be kept in a file of structures with the following components:
    a. Flight number (including airline code)
    b. City of departure
    c. Destination
    d. Date and time of departure
    e. Date and time of arrival
    f. Number of first-class seats still available
    g. Number of first-class seats sold
    h. Number of coach seats still available
    i. Number of coach seats sold
Include in your program separate functions for creation, deletion, and update of flight records. Also, implement make_reservation and cancel_reservation functions.
*/