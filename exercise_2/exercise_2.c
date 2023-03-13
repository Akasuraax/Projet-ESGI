#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    long long number_n = -1;
    long long number_m = -1;

    long long divider_number_n = 10; //diviseur du nombre n
    long long divider_number_m = 10; //diviseur du nombre m
    long long divider_number_nm; //diviseur nm : correspond à la différence n-m

    long long temporary_number_n; //prendra la valeur de n pour de pas modifier la variable de base
    long long temporary_number_m; //prendra la valeur de m pour de pas modifier la variable de base

    long long partitioned_number = 0; //permettra de donner les nombres décomposés afin de comparer

    long long final_number_n =0; //donnera le chiffre avec le ou les m retirés de n

    short menu = 1;

    //compteurs de chiffres
    long long counter_number_n = 0;
    long long counter_number_m = 0;
    long long counter_number_nm;


    do{

        //re-initialisation des variables lorsque je recommence le traitement
        number_n = -1;
        number_m = -1;

        divider_number_n = 10;
        divider_number_m = 10;

        counter_number_m = 0;
        counter_number_n = 0;

        temporary_number_n = 0;

        partitioned_number = 0;
        final_number_n = 0;


        while(number_n < 0 || number_m < 0) //recommence la saisie tant que la valeur n'est pas valide (non-valide : char, <0)
        {
            printf("Veuillez taper votre nombre n :");
            scanf("%lld", &number_n);
            fflush(stdin);

            printf("Veuillez taper votre nombre m :");
            scanf("%lld", &number_m);
            fflush(stdin);
        }

        temporary_number_n = number_n;
        temporary_number_m = number_m;

        //compteur de chiffres du nombre n
        do{
            counter_number_n++;
            temporary_number_n = temporary_number_n - temporary_number_n % divider_number_n;
            divider_number_n = divider_number_n * 10;
        }while(temporary_number_n > 0);

        //compteur de chiffres du nombre m
        do{
            counter_number_m++;
            temporary_number_m = temporary_number_m - temporary_number_m % divider_number_m;
            divider_number_m = divider_number_m * 10;
        }while(temporary_number_m > 0);

        counter_number_nm = counter_number_n - counter_number_m;

        divider_number_nm = pow(10, counter_number_nm);
        divider_number_n = pow(10, counter_number_n-1);
        divider_number_m = pow(10, counter_number_m);

        temporary_number_n = number_n;
        temporary_number_m = number_m*divider_number_nm;
        //permet d'avoir le meme nombre de 0 dans m que n (ex, n = 12345, m = 23, temp_m = 23000) pour faire les soustractions

        while(divider_number_nm > 0) {
            partitioned_number = (temporary_number_n / divider_number_nm) % (divider_number_m);
            //si je marque n = 12345, m = 12, cela retourna 12 23 34 45, avec m = 3 chiffres, les 3 premières valeurs de n etc...

            if (partitioned_number == number_m) {
                temporary_number_n = temporary_number_n - temporary_number_m;
                //si je retrouve m dans n, je le retire de n, (n = 1234, m = 23, temp_n = 1004)
            }

            //permettra de passer au chiffre suivant (gauche à droite)
            divider_number_nm = divider_number_nm / 10;
            temporary_number_m = temporary_number_m / 10;
            divider_number_n = divider_number_n/10;
        }

        divider_number_n = pow(10, counter_number_n-1);

        //compare les chiffres du nombre n initial, au nombre n lorsqu'on retire les m, (ex, n = 1234, n_final = 1004, cela comparera 1 à 1 puis 2 à 0 etc..)
        while(divider_number_n > 0){
            if((((temporary_number_n/divider_number_n)%10)) == ((number_n/divider_number_n)%10)){
                //si les 2 chiffres correspondent, je le garde, sinon je passe au chiffre suivant
                final_number_n = final_number_n*10 + (temporary_number_n/divider_number_n)%10;
            }
            divider_number_n = divider_number_n/10;
        }
        printf("Vous avez decide de retirer %lld ! Voici donc la valeur restante : %lld", number_m, final_number_n);

        printf("\nQuitter ? Taper 0\nContinuer ? Taper n importe quelle valeur\n");
        scanf("%hd", &menu);
        fflush(stdin);


    }while(menu != 0);
    printf("Vous avez arrete le code.");

    return EXIT_SUCCESS;
}
