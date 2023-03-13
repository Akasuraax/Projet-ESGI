#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
    short menu = 1;

    long long number = -1 ;

    unsigned long long reverse_binary_number = 0; //on obtient le nombre converti en binaire, mais à l'envers
    unsigned long long reverse_binary_number2 = 0; //si le nombre de chiffre > 18, je le stock dans cette variable pour ne pas faire de dépassement de valeur
    unsigned long long binary_number = 0; //correspond au nombre converti à l'endroit
    unsigned long long binary_number2 = 0;
    unsigned long long left_or_right = -1;

    unsigned long long temporary_number = 0; //variables temporaires utilisées pour ne pas altérer les variables de base
    unsigned long long temporary_number2 = 0;
    unsigned long long temporary_binary_number = 0;
    unsigned long long temporary_binary_number2 = 0;
    unsigned long long temporary_reverse_binary_number =0;

    unsigned long long divider = 10;
    unsigned long long power;
    unsigned long long bin_pow; //correspond au rajout de nombre de 0 à la fin (car elle peut être retirée avant le 1er 1)

    unsigned long long digits_counter = 0; //compte le nombre de chiffres
    unsigned long long digits_counter2 = 0; //compte le nombre de chiffres si on à plus de 20 chiffres
    unsigned long long number_of_0 = 0; //compte le nombre de 0
    unsigned long long number_of_0_2 = 0;
    unsigned long long before_1; //nombre de 0 avant le 1er bit à 1
    unsigned long long before_last_1 ; //nombre de 0 avant le dernier bit à 1
    unsigned long long number_of_1 = 0; //compte le nombre de 1

    do {
        divider = 10; //j'initialise à nouveau mes valeurs lorsque je recommence la boucle

        number_of_0 = 0;
        number_of_0_2 = 0;

        reverse_binary_number = 0;
        reverse_binary_number2 = 0;

        binary_number = 0;
        binary_number2 = 0;

        digits_counter = 0;
        digits_counter2 = 0;

        before_1 = 0;
        number_of_1 = 0;

        do { //recommence tant que ce n'est pas une valeur valide (char, <0)
            printf("Veuillez saisir votre nombre :");
            scanf("%lld", &number);
            fflush(stdin);
        } while (number < 0);

        do { //recommence tant que ce n'est pas une valeur valide (char, <0)
            printf("Souhaitez-vous compter les 0 a gauche (1), ou droite ? (2) :");
            scanf("%lld", &left_or_right);
            fflush(stdin);
        } while (left_or_right < 0 || left_or_right != 1 && left_or_right !=2);

        temporary_number = number; //je stock le nombre dans une valeur temporaire pour ne pas le changer

        while (temporary_number % 2 != 1) { //je compte le nombre de 0 avant le 1er 1
            number_of_0++;
            temporary_number = temporary_number / 2;
        }

        temporary_number = number; //je re attribut number à temporary_number pour faire la conversion

        //conversion en binaire
        while (temporary_number != 0) {
            if (temporary_number % 2 == 1)
                reverse_binary_number = reverse_binary_number * 10 + 1; //je rajoute 1 à reverse_num*10 pour ne pas bouger les chiffres de gauche avant

            if (temporary_number % 2 == 0)
                reverse_binary_number = reverse_binary_number * 10 + 0;

            temporary_number = temporary_number / 2;
            digits_counter++;

            if (digits_counter > 18) {
                //lorsque j'atteint 18 chiffre dans la variable, je la stock dans une nouvelle pour éviter le dépassement (>20 long long)
                temporary_number2 = temporary_number;
                break;  //j'arrête le code car je dois convertir temporary_number2
            }
        }

        if (temporary_number2 != 0){
            temporary_reverse_binary_number = reverse_binary_number;

            //si j'utilise la deuxième variable de stock, je garde les 0 pour ne pas qu'ils soient retirés (ex var_1 = 1000, si je le met a l'envers je perdrai les 0, donc je les garde)
            while (temporary_reverse_binary_number % 2 != 1) {
                number_of_0_2++;
                temporary_reverse_binary_number = temporary_reverse_binary_number / 2;
            }
        }

        //si la variable temporary_number2 est utilisée, je converti le restant en binaire
        if (temporary_number2 != 0) {
            while (temporary_number2 % 2 != 1) {
                number_of_0_2++;
                temporary_number2 = temporary_number2 / 2; //compte le nombre de 0 aussi pour le rajouter plus tard
            }

            temporary_number2 = temporary_number;

            while (temporary_number2 > 0) { //même fonctionnement que pour temporary, je converti
                if (temporary_number2 % 2 == 1)
                    reverse_binary_number2 = reverse_binary_number2 * 10 + 1;

                if (temporary_number2 % 2 == 0)
                    reverse_binary_number2 = reverse_binary_number2 * 10 + 0;
                temporary_number2 = temporary_number2 / 2;
            }
        }


        power = pow(10,digits_counter);


        //compte le nombre de 1
        while (power != 0){
            if ((reverse_binary_number/power)%10 == 1)
                number_of_1++;
            power = power/10;
        }

        //remet le nombre binaire dans le bon sens (soit je met le résultat à l'envers)
        while(reverse_binary_number > 0){
            binary_number = binary_number*10 + reverse_binary_number%10; //je fais le *10 pour ne pas altérer les chiffres de gauche
            reverse_binary_number = reverse_binary_number/10;
        }

        if (reverse_binary_number2 != 0) {
            while (reverse_binary_number2 > 0) {
                binary_number2 = binary_number2 * 10 + reverse_binary_number2 % 10;
                reverse_binary_number2 = reverse_binary_number2 / 10;
            }
        }


        //permet de rajouter les 0 manquants à la fin qui ont été rétirés (ex: bin = 0011011, à l'endroit -> 1101100
        bin_pow = pow(10, number_of_0); //je fais une puissance pour obtenir le nombre de 0 manquants
        if (number_of_0 > 0){
            binary_number = binary_number*bin_pow;
        }

        if (binary_number2 != 0) {
            bin_pow = pow(10, number_of_0_2);
            if (number_of_0_2 > 0) {
                binary_number2 = binary_number2 * bin_pow;
            }
        }

        temporary_binary_number = binary_number;
        digits_counter = 0;

        //permet d'obtenir le nombre de chiffres présents
        while(temporary_binary_number > 0){
            digits_counter++;
            temporary_binary_number = temporary_binary_number - temporary_binary_number%divider;
            divider = divider*10;
        }

        if (binary_number2 != 0){
            //permet d'obtenir le nombre de chiffres présents si on utilise binary_number2
            temporary_binary_number2 = binary_number2;
            divider = 10;
            while(temporary_binary_number2 > 0){
                digits_counter2++;
                temporary_binary_number2 = temporary_binary_number2 - temporary_binary_number2%divider;
                divider = divider*10;
            }
        }

        temporary_binary_number = binary_number;

        power = pow(10,digits_counter-1);

        //compte le nombre de 1
        while (power > 0){
            if ((temporary_binary_number/power)%10 == 1)
                number_of_1++;
            power = power/10;
        }

        if (binary_number2 != 0){
            power = pow(10,digits_counter2-1);
            temporary_binary_number2 = binary_number2;
            while (power > 0){
                if ((temporary_binary_number2/power)%10 == 1)
                    number_of_1++;
                power = power/10;
            }
        }

        digits_counter = digits_counter+digits_counter2;

        if (left_or_right == 1) {
            //compare le nombre de chiffre pour le ranger dans 1,2,3,4 octets
            //cela permet d'obtenir le nombre de 0 avant le 1er bit à 1
            if (digits_counter <= 8)
                before_1 = 8 - digits_counter;
            if (digits_counter > 8 && digits_counter <= 16)
                before_1 = 16 - digits_counter;
            if (digits_counter > 16 && digits_counter <= 24)
                before_1 = 24 - digits_counter;
            if (digits_counter > 24 && digits_counter <= 32)
                before_1 = 32 - digits_counter;

            before_last_1 = before_1;

            //permet d'obtenir le nombre de 0 avant le dernier bit à 1
            if (number_of_1 > 1) {
                while (temporary_binary_number % 10 != 1) {
                    temporary_binary_number = temporary_binary_number / 10;
                }

                while (temporary_binary_number > 0) {
                    if (temporary_binary_number % 10 == 0)
                        before_last_1++;
                    temporary_binary_number = temporary_binary_number / 10;
                }

                if (binary_number2 != 0) {
                    //teste aussi dans binary number 2 si elle est utilisée
                    while (temporary_binary_number2 > 0) {
                        if (temporary_binary_number2 % 10 == 0)
                            before_last_1++;
                        temporary_binary_number2 = temporary_binary_number2 / 10;


                    }
                }
            }
        }

        if (left_or_right == 2) {
            while (temporary_binary_number % 10 != 1) { //je compte le nombre de 0 avant le 1er 1
                before_1++;
                temporary_binary_number = temporary_binary_number / 10;

                if (temporary_binary_number2 != 0 && temporary_binary_number == 0) {
                    while (temporary_binary_number2 % 10 != 1) { //je compte le nombre de 0 avant le 1er 1
                        before_1++;
                        temporary_binary_number2 = temporary_binary_number2 / 10;

                    }
                }
            }

            before_last_1 = before_1;

            while (temporary_binary_number > 0) {
                if (temporary_binary_number % 10 == 0)
                    before_last_1++;
                temporary_binary_number = temporary_binary_number / 10;
            }

            if (binary_number2 != 0) {
                //teste aussi dans binary number 2 si elle est utilisée
                while (temporary_binary_number2 > 0) {
                    if (temporary_binary_number2 % 10 == 0)
                        before_last_1++;
                    temporary_binary_number2 = temporary_binary_number2 / 10;
                }
            }
        }



        if (binary_number2 !=0){
            printf("%lld est le nombre que vous avez tape, converti en binaire il donne : %llu%llu.\nIl y a %llu zero avant le premier bit à 1.\nIl y a %llu zero avant le dernier bit a 1.", number, binary_number2, binary_number, before_1, before_last_1);
        }else
            printf("%lld est le nombre que vous avez tape, converti en binaire il donne : %llu.\nIl y a %llu zero avant le premier bit à 1.\nIl y a %llu zero avant le dernier bit a 1.", number, binary_number, before_1, before_last_1);

        fflush(stdin);
        printf("\nQuitter ? Taper 0\nContinuer ? Taper n importe quelle valeur\n");
        scanf("%hd", &menu);
        fflush(stdin);

    }while(menu != 0);
    printf("Vous avez arrete le code.");


}
