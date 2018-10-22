#include "stdafx.h"
#include "SaveLoad.h"

void SaveLoad::SAVE(int r, int b)
{
	int i = 0;
	FILE *file;
	char fileName[] = "save.txt";
	int add[15] = { 0 };
	char c[16][4];
	int tf[15] = { 0 };

	errno_t error;
	error = fopen_s(&file, fileName, "r+");
	if (error != 0)
	{
		return;
	}
	while (fscanf_s(file, "%d %3s %d", &add[i], c[i], 6, &tf[i]) != EOF)
	{
		if (add[i] == r)
		{
			tf[i] = b;
		}
		c[i][3] = '\0';
		i++;
	}
	fclose(file);
	error = fopen_s(&file, fileName, "w");
	if (error != 0)
	{
		return;
	}
	for (i = 0; i < 15; i++)
	{
		fprintf_s(file, "%02d %s %d\n", add[i], c[i], tf[i]);
	}
	fclose(file);
}

int SaveLoad::Load(int r)
{
	int i = 0;
	FILE *file;
	char fileName[] = "save.txt";
	int add = 0;
	char c[16][4];
	int tf = 0;

	errno_t error;
	error = fopen_s(&file, fileName, "r+");
	if (error != 0)
	{
		return NULL;
	}
	while (fscanf_s(file, "%d %3s %d", &add, c[i], 6, &tf) != EOF)
	{
		c[i][3] = '\0';
		if (add == r)
		{
			fclose(file);
			return tf;
		}
		i++;
	}
	fclose(file);
	return NULL;
}