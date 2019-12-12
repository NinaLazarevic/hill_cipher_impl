#include "stdio.h"
#include "math.h"
#include "string.h"

int DeterminantaMatrice(int M[3][3])
{
	//da li je det != 0

	int det;

	det = M[0][0] * ((M[1][1] * M[2][2]) - (M[2][1] * M[1][2])) - M[0][1] * (M[1][0]
		* M[2][2] - M[2][0] * M[1][2]) + M[0][2] * (M[1][0] * M[2][1] - M[2][0] * M[1][1]);

	return det;
}

int InvDeterminanta(int det, int mod)
{
	int i;
	int detinverse = -1;

	det = det % mod;
	if (det < 0) det += mod;

	for (i = 1; i < mod; i++)
		if ((det * i) % mod == 1)
			detinverse = i;

	return detinverse;
}

void UnosMatrice(int M[3][3])
{
	int i, j;

	printf("Unesite kljuc (matricu 3x3): \n");

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			scanf("%d", &M[i][j]);

	printf("\nUneti kljuc je: \n");

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			printf("%d ", M[i][j]);
		printf("\n");
	}
}

int main()
{
	int K[3][3], i, j, k, det;
	int V[3], Vpom[3];
	int detinverse = -1;
	int lenght;

	char letters[] = "ABVGDĐEZIJKLMNOPRSTUFHCXYQW!~#";

	char imeFajla[50];
	char imeFajlaCrypt[50];
	char text[50] ;
	char crypt[50];

	FILE* f, *fw;

	UnosMatrice(K);

	det = DeterminantaMatrice(K);
	if (det != 0)
		detinverse = InvDeterminanta(det, 30);

	while (det == 0 || detinverse == -1)
	{
		printf("\nKljuc nije validan, pokusajte ponovo... \n");

		UnosMatrice(K);

		det = DeterminantaMatrice(K);
		detinverse = InvDeterminanta(det, 30);
	}
	
	// citanje teksta iz fajla
	printf("Unesite ime fajla: \n");
	scanf("%s", imeFajla);

	f = fopen(imeFajla, "r");

	if (f != NULL)
	{
		fgets(text, 50, f);
	}
	else
	{
		printf("Fajl nije pronadjen...");
		return;
	}
	fclose(f);
	// kriptovanje
	k = 0;
	lenght = 0;
	while (text[lenght] != '\0')
	{
		lenght++;
	}
	// adko duzina teksta nije deljiva sa 3, dodajemo X do potrebne duzine
	while (lenght % 3 != 0)
	{
		text[lenght] ='X';
		lenght++;
	}
	text[lenght] = '\0';

	while (k < lenght)
	{
		
		for (i = 0; i < 30; i++)
		{
			if (text[k] == letters[i])
				V[0] = i;
		}
		for (i = 0; i < 30; i++)
		{
			if (text[k + 1] == letters[i])
				V[1] = i;
		}
		for (i = 0; i < 30; i++)
		{
			if (text[k + 2] == letters[i])
				V[2] = i;
		}


		Vpom[0] = 0; Vpom[1] = 0; Vpom[2] = 0;

		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				Vpom[i] += (V[j] * K[j][i]);
			}
			Vpom[i] %= 30;
		}

		crypt[k] = letters[Vpom[0]];
		crypt[k + 1] = letters[Vpom[1]];
		crypt[k + 2] = letters[Vpom[2]];

		k += 3;
	}

	crypt[lenght] = '\0';

	while (imeFajla[lenght] != '\0')
	{
		lenght++;
	}
	lenght++;
	// izbacujemo .txt 
	for (i = 0; i < lenght - 5; i++)
	{
		imeFajlaCrypt[i] = imeFajla[i];
	}
	imeFajlaCrypt[i] = 'C';
	imeFajlaCrypt[i + 1] = '.';
	imeFajlaCrypt[i + 2] = 't';
	imeFajlaCrypt[i + 3] = 'x';
	imeFajlaCrypt[i + 4] = 't';

	imeFajlaCrypt[i + 5] = '\0';

	fw = fopen(imeFajlaCrypt, "w");
	fprintf(fw, crypt);
	fclose(fw);

	printf("Sifrirani tekst je sacuvan na lokaciji: %s", imeFajlaCrypt);
}

