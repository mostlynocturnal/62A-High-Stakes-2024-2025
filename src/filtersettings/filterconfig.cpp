#include "main.h"
#include "subsystems/classes.hpp"
#include "config.h"
#include "api.h"
#include "filtersettings/filterconfig.hpp"

float redlowCheck;
float redhighCheck;
float bluelowCheck;
float bluehighCheck;

void writeSettings() {
    FILE* file = fopen("filtersettings.txt", "w");
    if (file == NULL) {
        printf("error opening file for writing.\n");
        return;
    }

    fprintf(file, "%f\n%f\n%f\n%f\n", redlow, redhigh, bluelow, bluehigh);
    fclose(file);
    printf("filter settings saved succesfully\n");
}

enum saveState{
    COMPLETE,
    RUNNING
};
saveState runState;

void readSettings() {
    runState = RUNNING;
    FILE* file = fopen("filtersettings.txt", "r");
    if (file == NULL) {
        printf("settings file not found, using manual values.");
        runState = COMPLETE;
        return;
    }

    if (fscanf(file, "%f\n%f\n%f\n%f\n", &redlow, &redhigh, &bluelow, &bluehigh) != 4) {
        printf("error reading filter config, using manual values.\n");
    }
    else {
        printf("settings read succesfully");
    }

    fclose(file);
    runState = COMPLETE;
}

enum filterSettings{
    UPDATED,
    OLD
};
filterSettings updateState;

void checkSettings() {
    FILE* file = fopen("filtersettings.txt", "r");
    if (file == NULL) {
        printf("settings file not found, unable to check.");
        return;
    }
    if (fscanf(file, "%f\n%f\n%f\n%f\n", &redlowCheck, &redhighCheck, &bluelowCheck, &bluehighCheck) != 4) {
        printf("error reading filter config, unable to check.");
    }
    else {
        if (redlow != redlowCheck && redhigh != redhighCheck && bluelow != bluelowCheck && bluehigh != bluehighCheck) {
            printf("filter config not updated.");
            updateState = OLD;
        }
        else {
            printf("filter config updated.");
            updateState = UPDATED;
        }
    }

    fclose(file);
}