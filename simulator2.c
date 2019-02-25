#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define ONE_MINUTE 60




typedef struct{
    int hour;
    int minute;

}Time;

typedef struct{
    char *plateNumber;
    char permit;
    Time enteringTime;
    Time leavingTime;
    int lotParkedIn;

}Car;

typedef struct{
    int lotNumber;
    double hourlyRate;
    double maxCharge;
    int capacity;
    int currentCarCount;
    double revenue;

}ParkingLot;
// Sets the hours and minutes amount for the given time t based
// on the specified hours h.  (e.g., 1.25 hours would be 1 hour
// and 15 minutes)

void setHours(Time *t, double h) {
    t->hour = (int)h;
    // gets hour from h
    int num = (int)(h * ONE_MINUTE);
    //variable num takes in h and converts to minutes
    while(num > ONE_MINUTE){
        num = num - ONE_MINUTE;
    }
    //while num is greater than 60, reduce num to get the minute
    t->minute = num;
    //gets minutes from num
}
// Takes two Time objects (not pointers) and computes the difference
// in time from t1 to t2 and then stores that difference in the diff
// Time (which must be a pointer)

void difference(Time t1, Time t2, Time *diff) {
    int hourDifference = t1.hour - t2.hour;
    //t2 hour subtracted from t1 hour
    int minuteDifference = t1.minute - t2.minute;
    //t2 minute subtracted from t1 minute
    diff->hour = hourDifference;
    diff->minute = minuteDifference;
    //diff pointer takes in the (difference) for hour and minute
}

char* randomPlate(){

    int randomNumber = 0;
    char *string[7];
    char *word;
    char str[7] = "";
    word = malloc(7 * sizeof(char));

    for(int i = 0; i < 3; i++){
        randomNumber = (rand() % (90 - 65 + 1)) + 65;
        word[i] = randomNumber;}

    word[3] = 32;

    for(int i = 4; i < 7; i++){
        randomNumber = (rand() % (57 - 48 + 1)) + 48;
        word[i] = randomNumber;}

    for(int i = 0; i <  7; i++){
        str[i] = ((char)word[i]);
    }
    return word;
}

// Initialize the car pointed to by c to have the given plate and
// hasPermit status.  The car should have it’s lotParkedIn set to
// 0 and enteringTime to be -1 hours and -1 minutes.

void initializeCar(Car *c, char *plate, char hasPermit) {
    c->plateNumber = plate;     //PlateNumber
    c->permit = hasPermit;      // Permit
    c->lotParkedIn = 0;         //lotParkedIn set to 0
    c->enteringTime.hour = -1;  //car entering time (Hour) set to -1
    c->enteringTime.minute = -1;//car entering time (minute) set to -1
}
// Initialize the lot pointed to by p to have the given number,
// capacity, hourly rate and max charge values.  The currentCarCount
// and revenue should be at 0.

void initializeLot(ParkingLot *p, int num, int cap, double rate, double max) {
    p->lotNumber  = num;  //p given the lotNumber
    p->capacity   = cap;  //p given the capacity
    p->hourlyRate = rate; //p given the hourly rate
    p->maxCharge  = max;  //p given the max charge
    p->currentCarCount  = 0; //current Car count initialized to 0
    p->revenue          = 0; // the revenue initialized to 0
}

Car* randomCar(){

    int randomPermit = 0;
    randomPermit = (rand() % (1 - 0 + 1)) + 0;

    Car* iniCar = (Car*)malloc(sizeof(Car));

    if(iniCar == NULL){
        printf("Memory Allocation Error\n");
    }

    initializeCar(iniCar,randomPlate(), randomPermit);

    printf("Car %s ",iniCar->plateNumber);
    printf("with permit %d \n",iniCar->permit);

    return iniCar;
}






// Print out the parking lot parameters so that is displays as
// follows:   Parking Lot #2 - rate = $3.00, capacity 6, current cars 5

void printLotInfo(ParkingLot p) {
    printf("Parking Lot #%d - rate = %.2f, capacity %d, current cars %d\n", p.lotNumber, p.hourlyRate, p.capacity, p.currentCarCount);
}
// Simulate a car entering the parking lot
// ...

// Simulate a car leaving the parking lot
// ...

void carEnters(ParkingLot* p,Car* c, int hour,int minute){

    if(p->currentCarCount < p->capacity){
        p->currentCarCount += 1;       //increases the lot car count
        c->enteringTime.hour   = hour; //gets entering hour of car
        c->enteringTime.minute = minute; //gets entering minute of car

        printf("Car %s enters Lot %d at %d:%d.\n", c->plateNumber,p->lotNumber,c->enteringTime.hour, c->enteringTime.minute);
    }else{

        c->enteringTime.hour   = hour; //gets entering hour of car
        c->enteringTime.minute = minute; //gets entering minute of car

        printf("Car %s arrives at Lot %d at %d:%d, but the lot is full.\n", c->plateNumber, p->lotNumber, hour, minute);
        printf("Car %s cannot get in.\n", c->plateNumber);
    }
}

void carLeaves(ParkingLot* p,Car* c, int hour,int minute){
    p->currentCarCount-=1;
    c->leavingTime.hour = hour;
    c->leavingTime.minute = minute;


    if(c->permit){
        printf("Car %s leaves Lot %d at %d:%d\n", c->plateNumber, p->lotNumber, hour, minute);
    }else {
        int time = c->leavingTime.hour - c->enteringTime.hour;
        double charge = (p->hourlyRate * time);
        if(charge > p->maxCharge || charge > 15){
            charge = p->maxCharge;
        }
        p->revenue += charge;


        printf("Car %s leaves Lot %d at %d:%d, paid $%.2f\n", c->plateNumber, p->lotNumber, hour, minute, charge);
    }

}

int main() {
    srand(time(NULL));

    int hour = 6;
    int minute = 0;

    int    num        = 1;
    int    capacity   = 5;
    double hourlyRate = 4.0;
    double maxCharge  = 12.0;

    ParkingLot* lotArr = (ParkingLot*) malloc(5 * sizeof(ParkingLot));
    Car* car = (Car*)malloc(sizeof(Car) *50);
    ParkingLot* lot = (ParkingLot*) malloc (sizeof(ParkingLot));

    if(car == NULL){
        printf("Malloc of size failed\n");
    }

    for(int i = 0; i < 50; i++){

        car[i] = *randomCar();
        
    }



    printf("\n");
    for(int i = 0; i < 5; i++){
        initializeLot(lot, num, capacity, hourlyRate, maxCharge);

        num = num  +  1;;
        capacity   = capacity + 5;
        hourlyRate = hourlyRate + 1;
        maxCharge  =  maxCharge + 2;

        printLotInfo(*lot);
        lotArr[i]  = *lot;
        // lot++;


    }
    printf("\n");





    for(int i = 0; i < 50; i++){



        int randomLot = 0;
        randomLot = (rand() % (4 - 0 + 1)) + 0;

        carEnters(&lotArr[randomLot], car, hour, minute);

        minute = minute + 5;

        if(minute == 60){
            minute = 0;
            hour = hour + 1;
        }

        if(hour == 24){
            hour = 0;
        }
        car++;
    }

    printf("\n");
    for(int i = 0; i < 5; i++){
        printLotInfo(lotArr[i]);
    }

    for(int i = 0; i < 50; i++) {
        carLeaves(&lotArr[i], car, hour, minute);



             minute = minute + 5;

              if(minute == 60){
                  minute = 0;
                  hour = hour + 1;
              }

              if(hour == 24){
                  hour = 0;
              }





//        lotArr++;
//        car++;
    }
//    carLeaves(&lotArr[1], car, hour, minute);


}


