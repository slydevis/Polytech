/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 6 du TD1
 */
 
 #include<stdio.h>
 
 #define NBMONTH 12
 int dayMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 int main() {
    int day;
    int month;
    int year;
    
    printf("Entrer une date (d/m/y) : ");
    scanf("%d/%d/%d", &day, &month, &year);
    
    day++;
    
    if(day > dayMonth[month - 1]) {
        
        if(month != 2){ 
            day = 1;
            month++;
        }
        else {
            if(((year%4 == 0) && (year%100 != 0)) || year%400 == 0)
                day = 29;
            else{
                day = 1;
                month++;       
            }
        }

        if(month > 12) {
            month = 1;
            year++;
        }
    }
    printf("Demain on est le %d/%d/%d\n", day, month, year);
    return 0;
}
