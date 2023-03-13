#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    short menu = 1;
    short users_choice = 0;

    long long number = -1;

    long long min_number = -1; //première valeur de la borne
    long long max_number = -1; //dernière valeur de la borne

    long long used_number = 0; //prendra la valeur, ou la première valeur pour la borne
    long long temporary_used_number = 0; //permet de stocker la valeur used_number pour ne pas la modifier
    long long temporary_used_number2 = 0; //stock temporary_used_number pour ne pas la modifier

    int digit_counter = 0; //permet de compter le nombre de chiffre
    short digits = 0; //permettra d'avoir les chiffres de 0 à 9 (comparateur)
    int temporary_digit_counter = 0; //comparateur

    long long divider = 10; //me permettra de faire un modulo afin de retirer les chiffres de mon nombre
    long long temporary_divider = 0;

    long long ordered_result = 0; //vaudra les chiffres mis dans l'ordre croissant
    long long result = 0;
    long long final_result = 0;//sera le résultat de la somme de ses chiffres élevés à des puissances consécutives
    long long i;

    do {

        do{ //recommence tant que la valeur n'est pas valide (si c'est un char, <0..)
            printf("Souhaitez-vous tester pour une seule valeur (taper 1) ?\nPour une plage de valeurs (taper 2) ?\n");
            scanf("%hd", &users_choice);
            fflush(stdin);
        }while (users_choice != 1 && users_choice != 2);


        // ------- Cas si l'utilisateur souhaite taper qu'une seule valeur ------- //
        if (users_choice == 1) {
            number = -1; //re-initialise quand je reviens dans la boucle
            digit_counter = 0;
            divider = 10;
            digits = 0;
            ordered_result = 0;
            result = 0;
            final_result = 0;
            temporary_digit_counter = 0;

            while (number < 0) { //recommence tant que la valeur n'est pas valide (si c'est un char, <0..)
                printf("Veuillez rentrer votre valeur numerique : ");
                scanf("%lld", &number);
                fflush(stdin);
            }

            used_number = number;
            temporary_used_number = used_number;

            do {
                digit_counter = digit_counter + 1; //permet de compter le nombre de chiffres
                temporary_used_number = temporary_used_number - temporary_used_number % divider; //je retire petit a petit tout les chiffres pour finir la boucle
                divider = divider * 10;
            } while (temporary_used_number != 0);

            divider = pow(10, digit_counter - 1); //je retire 1 pour éviter d'avoir un 0 en trop

            while (temporary_digit_counter < digit_counter && digits < 10) {
                // tant que le compteur temporaire n'atteint pas le compteur principal, il fait une boucle
                // par ex digit_counter = 5, il va parcourir la boucle 5 fois pour pouvoir parcourir tout les chiffres
                // digits < 10 car on compare 0 au chiffre, 1 au chiffre...

                temporary_used_number2 = used_number; //deuxième valeur temporaire, permet d'initialiser en enlevant le chiffre le plus à gauche
                temporary_divider = divider; //diviseur temporaire pour ne pas altérer le diviseur

                while (temporary_used_number2 > 0) {
                    temporary_used_number = temporary_used_number2 / temporary_divider; //on prend le chiffre le plus à gauche

                    if (temporary_used_number == digits) { //comparera notre chiffre actuel à 0 puis 1, 2, 3...
                        temporary_digit_counter = temporary_digit_counter + 1;
                        ordered_result = (ordered_result * 10) + digits; //le *10 permet d'avoir la dizaine,centaine lorsqu'on ajoute un chiffre
                    }

                    temporary_used_number2 = temporary_used_number2 % temporary_divider; //on enleve un chiffre de gauche pour comparer avec le reste
                    temporary_divider = temporary_divider / 10; //je réduit mon diviseur pour se placer au bon endroit

                }
                digits = digits + 1; //j'incrémente de 1 pour comparer 1 au second chiffre de mon nombre choisi (ex: chiffre = 123, je comparerais 1 a 2)
            }

            for (i = 1; divider != 0; i++) { //fait le calcul de la somme des chiffres (rangés dans l'ordre croissant élevés à des puissances consécutives
                result = (ordered_result / divider) % 10;
                final_result += pow(result, i);
                divider = divider / 10;
            }

            if (final_result == number) //test si le résultat de la somme est égal au nombre initial
                printf("Ce nombre est egal à la somme de ses chiffres eleves à des puissances consecutives");
            else
                printf("Ce nombre n'est pas egal à la somme de ses chiffres eleves à des puissances consecutives");


        }

        // ------- Cas si l'utilisateur rentre une plage de valeur ------- //
        if (users_choice == 2) {

            while (min_number > max_number || min_number < 0 || max_number < 0) { //recommence tant que les valeurs ne sont pas valides
                printf("Veuillez rentrer votre plage de valeur numérique ");
                printf("\nminimum : ");
                scanf("%lld", &min_number);
                fflush(stdin);
                printf("maximum : ");
                scanf(" %lld", &max_number);
                fflush(stdin);
            }

            do {
                used_number = min_number; //je re-initialise pour enlever les valeurs des précédents calculs
                temporary_used_number = used_number;
                digit_counter = 0;
                divider = 10;
                digits = 0;
                ordered_result = 0;
                result = 0;
                final_result = 0;
                temporary_digit_counter = 0;


                //meme fonctionnement que pour le cas avec 1 seule valeur
                while (temporary_used_number != 0) {
                    digit_counter = digit_counter + 1;
                    temporary_used_number = temporary_used_number - temporary_used_number % divider;
                    divider = divider * 10;
                }

                divider = pow(10, digit_counter - 1);

                while (temporary_digit_counter < digit_counter && digits < 10) {

                    temporary_used_number2 = used_number;
                    temporary_divider = divider;

                    while (temporary_used_number2 > 0) {
                        temporary_used_number = temporary_used_number2 / temporary_divider;

                        if (temporary_used_number == digits) {
                            temporary_digit_counter = temporary_digit_counter + 1;
                            ordered_result = (ordered_result * 10) + digits;
                        }

                        temporary_used_number2 = temporary_used_number2 % temporary_divider;
                        temporary_divider = temporary_divider / 10;

                    }
                    digits = digits + 1;
                }

                for (i = 1; divider != 0; i++) {
                    result = (ordered_result / divider) % 10;
                    final_result += pow(result, i);
                    divider = divider / 10;
                }


                if (final_result == used_number) {
                    printf("%lld ", final_result);
                }

                min_number = min_number + 1;

            } while (min_number <= max_number);
            printf("voici la/les valeur(s) dont le nombre est egal à la somme de ses chiffres elevés à des puissances consecutives entre %lld et %lld\n", min_number-max_number, max_number);
        }

        fflush(stdin);
        printf("\nQuitter ? Taper 0\nContinuer ? Taper n importe quelle valeur\n");
        scanf("%hd", &menu);
        fflush(stdin);

    } while (menu != 0);

    printf("\nVous avez arrete le code.");
    return EXIT_SUCCESS;
}
