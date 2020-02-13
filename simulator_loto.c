/*
*Regulile jocului Loto 5/40 : Sursa : http://www.lotoinfo.org/loto-5-40/reguli/

*În Loto 5/40 trebuie sa alegeti 5 numere cuprinse între 1 si 40. 
*Tragerea la sorti a numerelor câstigatoare se face prin extragere din urna 
*a 6 numere, oferindu-va 3 categorii de câstiguri, dupa cum urmeaza:

*categoria I – ati ghicit primele 5 numere extrase

*categoria II – ati ghicit 5 numere din toate cele 6 numere extrase

*categoria III – ati ghicit 4 numere din toate cele 6 extrase

*/

#include <stdio.h>
#include <stdlib.h>


/*
 * Functie ce genereaza un nr random intre min si max - in cazul nostru 
 * min va fi 1 si max va fi 40
 */
int random_between(int min, int max) 
{
	return rand() % (max - min + 1) + min;
}

/*
 * Functie care returneaza valoarea 1 daca elementul elem se afla in vectorul v si
 * returneaaza valoarea 0 daca acel element nu se afla . nr_elem reprezinta numarul 
 * de elemente introduse pana la momentul respectiv in vectorul v.
 */
int is_in_vector(int elem, int *v, int nr_elem)
{
	int i;
	
	for (i = 0; i < nr_elem; ++i)
		if (v[i] == elem)
			return 1;

	return 0;
}

/*
 * Functia care genereaza cele 6 nr random de la loto
 */
void generate_numbers(int *loto)
{
	int i, generated_number, nr_elem = 0;
	time_t t;

	
	srand((unsigned) time(&t));

	for (i = 0; i < 6; ++i) {
		generated_number = random_between(1, 40); // generez un numar

		// cat tip el se afla deja in vectorul loto, atunci generez in continuare
		while (is_in_vector(generated_number, loto, nr_elem)) {
			generated_number = random_between(1, 40);
		}

		// odata generat, il pun pe pozitia corespunzatoare in vector
		loto[nr_elem] = generated_number;

		// cresc nr de elemente generate.
		++nr_elem;
	}
}

int main()
{	
	//my_numbers[5] este vectorul cu nr citite de la tastatura
	int i, my_numbers[5] = {0}, elem, loto[6], nr_introduse = 0;
	int nr_ghicite = 0;
	printf("Introduceti numerele dumneavoastra:\n");
	for (i = 0; i < 5; ++i) {
		scanf("%d", &elem);

		// cat timp citesc un nr care e deja citit, il oblig pe utilizator sa reincerce
		while (is_in_vector(elem, my_numbers, nr_introduse)) {
			printf("REINCERCATI: ATI MAI INTRODUS ACEST NR\n");
			scanf("%d", &elem);
		}

		// la fel si daca introduce un nr gresit
		while (elem < 1 || elem > 40) {
			printf("REINCERCATI: VALOARE GRESITA\n");
			scanf("%d", &elem);
		}

		// odata ce am citit un nr corect, il pun pe pozitia corespunzatoare in vector
		my_numbers[nr_introduse] = elem;

		// cresc nr de elemente introduse
		++nr_introduse;
	}

	//apelez functia de generare a nr loto
	generate_numbers(loto);

	printf("LOTO:\n");
	for (i = 0; i < 6; ++i) {
		printf("%d\n", loto[i]);
	}
	printf("-----------------\n");

	int cat1 = 1;

	// iterez prin primele 5 nr de loto si verific daca fiecare e in my_numbers. Daca 
	// gasesc un element care nu e in my_numbers atunci inseamna ca nu am reusit sa castig 
	// la categoria 1 si fac variabila cat1 = 0
	for (i = 0; i < 5; ++i) {
		if (!is_in_vector(loto[i], my_numbers, 5)) {
			cat1 = 0;
			break;
		}
	}

	if (cat1 == 0)
		printf("NU ATI CASTIGAT PREMIUL PENTRU CATEGORIA 1\n");
	else {
		printf("ATI CASTIGAT PREMIUL PENTRU CATEGORIA 1\n");
		return 0;
	}

	// iterez prin toate cele 6 nr de la loto si verific daca apare in my_numbers . Totodata contorizez
	// numerele gasite in my_numbers. Daca am ghicit 5 -> am castiga la categoria 2, 
	// daca am ghicit 4-> am castigat la categoria 3, altfel nu am castigat nimic.
	for (i = 0; i < 6; ++i) {
		if (is_in_vector(loto[i], my_numbers, 5))
			nr_ghicite++;
	}

	if (nr_ghicite == 5)
		printf("ATI CASTIGAT PREMIUL PENTRU CATEGORIA 2\n");
	else if (nr_ghicite == 4) 
		printf("ATI CASTIGAT PREMIUL PENTRU CATEGORIA 3\n");
	else 
		printf("NU ATI CASTIGAT NICI PENTRU CATEGORIA 2 NICI PENTRU CATEGORIA 3\n");

	return 0;
}
