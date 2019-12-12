#include "stdio.h"
#include "math.h"

void InverznaMatrica(int M[3][3], int detinverse)
{
	int  i, j;
	int Mpom[3][3];
	int mod = 30;
	
	// adj M

	//kofaktori
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			Mpom[i][j] = ( M[(i + 1) % 3][(j + 1) % 3] * M[(i + 2) % 3][(j + 2) % 3] - M[(i + 1) % 3][(j + 2) % 3] * M[(i + 2) % 3][(j + 1) % 3]) % mod;
			if (Mpom[i][j] < 0) Mpom[i][j] += mod;
			Mpom[i][j] *= detinverse;
		}

	//transponovanje
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			M[i][j] = Mpom[j][i];

	// moduo matrice
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			M[i][j] = M[i][j] % mod;

	/*printf("\nInverzna matrica je je: \n");

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			printf("%d ", M[i][j]);
		printf("\n");
	}*/

}
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
	int i, j, k;
	int V[3], Vpom[3];
	int K[3][3], det;
	int detinverse = -1;  //d*d^(-1) = 1 mod 30
	int lenght;

	char letters[] = "ABVGDĐEZIJKLMNOPRSTUFHCXYQW!~#";

	char imeFajla[50];
	char imeFajlaDecrypt[50];
	char text[50];
	char decrypt[50];

	FILE* f, * fw;

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

	InverznaMatrica(K, detinverse);

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

	// dekriptovanje
	k = 0;
	lenght = 0;
	while (text[lenght] != '\0')
	{
		lenght++;
	}

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

		decrypt[k] = letters[Vpom[0]];
		decrypt[k + 1] = letters[Vpom[1]];
		decrypt[k + 2] = letters[Vpom[2]];

		k += 3;
	}

	decrypt[lenght] = '\0';

	while (imeFajla[lenght] != '\0')
	{
		lenght++;
	}
	lenght++;

	// izbacujemo .txt 
	for (i = 0; i < lenght - 5; i++)
	{
		imeFajlaDecrypt[i] = imeFajla[i];
	}
	imeFajlaDecrypt[i] = 'D';
	imeFajlaDecrypt[i + 1] = '.';
	imeFajlaDecrypt[i + 2] = 't';
	imeFajlaDecrypt[i + 3] = 'x';
	imeFajlaDecrypt[i + 4] = 't';

	imeFajlaDecrypt[i + 5] = '\0';

	fw = fopen(imeFajlaDecrypt, "w");
	fprintf(fw, decrypt);
	fclose(fw);

	printf("Sifrirani tekst je sacuvan na lokaciji: %s", imeFajlaDecrypt);
}

