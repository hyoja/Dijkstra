#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Dijkstra.h"

int main(void)
{
	char filename [100];
	FILE* filePointer = NULL;
	printf("type your file Name \n");
	while(1)
	{
		scanf("%s", &filename);
		strcat(&filename, ".txt");
		filePointer = fopen(filename, "r");
		if(filePointer == NULL)
		{
			printf("not exist file, retype your file Name example : input \n");
		}
		else
		{
			break;
		}
	}
	char readedChar = ' ';

	int indexOfWeight = 0;
	int indexOfNodeName = 0;
	char nodeName[SIZEOFINDEX];
	char weightString[SIZEOFINDEX];

	int i;
	for (i = 0; i < SIZEOFINDEX; i++)
	{
		weightString[i] = '\0';
		nodeName[i] = '\0';
	}

	TupleList tupleList;
	tupleList.size = 0;

	while (!feof(filePointer))
	{
		readedChar = fgetc(filePointer);
		if ((readedChar >= 97 && readedChar <= 122)
			|| (readedChar >= 65 && readedChar <= 90))
		{

			if (readedChar >= 97)
			{
				nodeName[indexOfNodeName] = (readedChar - 32);
			}
			else
			{
				nodeName[indexOfNodeName] = readedChar;
			}
			indexOfNodeName++;
		}
		else if (readedChar == ' ' && nodeName[0] != '\0')
		{
			Tuple* tempedTuple = &(tupleList.tulpleHead);
			int isFineded = false;

			if (tupleList.size == 0)
			{
				tempedTuple->arrayIndex = 0;
				tempedTuple->nextTuple = NULL;
				for (i = 0; i < SIZEOFINDEX; i++)
				{
					tempedTuple->NameOfNode[i] = nodeName[i];
				}
				tupleList.size++;
			}
			else
			{
				for (i = 0; i < tupleList.size; i++)
				{
					if (strcmp(tempedTuple->NameOfNode, nodeName) == 0)
					{
						isFineded = true;
					}
					if (tupleList.size - 1 != i)
					{
						tempedTuple = tempedTuple->nextTuple;
					}
				}
				if (isFineded == false && i == (tupleList.size))
				{
					Tuple* newTuple = (Tuple *)malloc(sizeof(Tuple));
					newTuple->nextTuple = NULL;
					newTuple->arrayIndex = tupleList.size;
					for (i = 0; i < SIZEOFINDEX; i++)
					{
						newTuple->NameOfNode[i] = nodeName[i];
					}
					tempedTuple->nextTuple = newTuple;
					tupleList.size++;
				}
			}
			for (i = 0; i < SIZEOFINDEX; i++)
			{
				printf("%c", nodeName[i]);
				if (nodeName[i] == '\0')
				{
					break;
				}
				nodeName[i] = '\0';
			}
			indexOfNodeName = 0;
		}
		else if (readedChar == '1' || readedChar == '2' || readedChar == '3'
			|| readedChar == '4' || readedChar == '5' || readedChar == '6'
			|| readedChar == '7' || readedChar == '8' || readedChar == '9'
			|| readedChar == '0')
		{
			weightString[indexOfWeight] = readedChar;
			indexOfWeight++;
		}
		else if ((readedChar == '\n' || readedChar == EOF)&& weightString[0] != '\0')
		{
			readedChar = 0;
			int positNumber = 1;
			int totalNumber = 0;
			for (i = 0; i < indexOfWeight; i++)
			{
				int j = 0;
				for (j = 0; j < indexOfWeight - (i + 1); j++)
				{
					positNumber *= 10;
				}
				totalNumber += (weightString[i] - 48) * positNumber;
				positNumber = 1;
			}
			printf("%d \n", totalNumber);

			for (i = 0; i < SIZEOFINDEX; i++)
			{
				if (weightString[i] == '\0')
				{
					break;
				}
				weightString[i] = '\0';
			}
			indexOfWeight = 0;
		}
	}
	fclose(filePointer);

	Tuple* tempedTuple = &(tupleList.tulpleHead);
	for (i = 0; i < tupleList.size; i++)
	{
		printf("%s \n", tempedTuple->NameOfNode);
		tempedTuple = tempedTuple->nextTuple;
	}
	int** distanceMap = (int **)malloc(sizeof(int *)*tupleList.size - 1);
	for (i = 0; i < tupleList.size; i++)
	{
		distanceMap[i] = (int *)malloc(sizeof(int)*tupleList.size - 1);
	}


	int j = 0;
	for (i = 0; i < tupleList.size; i++)
	{
		for (j = 0; j < tupleList.size; j++)
		{
			if (i == j)
			{
				distanceMap[i][j] = 0;
			}
			else
			{
				distanceMap[i][j] = INFINITY;
			}
		}
	}

	int* visitedFlag = (int *)malloc(sizeof(int)*tupleList.size);
	int* shortDistanceCounts = (int *)malloc(sizeof(int)*tupleList.size);

	for (i = 0; i < tupleList.size; i++)
	{
		visitedFlag[i] = 0;
		shortDistanceCounts[i] = INFINITY;
	}


	int indexOfFirstNode = -1;
	int indexOfSecondNode = -1;

	filePointer = fopen("input.txt", "r");
	while (!feof(filePointer))
	{
		readedChar = fgetc(filePointer);
		if ((readedChar >= 97 && readedChar <= 122)
			|| (readedChar >= 65 && readedChar <= 90))
		{
			if (readedChar >= 97)
			{
				nodeName[indexOfNodeName] = (readedChar - 32);
			}
			else
			{
				nodeName[indexOfNodeName] = readedChar;
			}
			indexOfNodeName++;
		}
		else if (readedChar == ' '&& nodeName[0] != '\0')
		{
			Tuple* tempedTuple = &(tupleList.tulpleHead);
			int isFineded = false;

			for (i = 0; i < tupleList.size; i++)
			{
				if (strcmp(tempedTuple->NameOfNode, nodeName) == 0)
				{
					if (indexOfFirstNode == -1)
					{
						indexOfFirstNode = tempedTuple->arrayIndex;
					}
					else
					{
						indexOfSecondNode = tempedTuple->arrayIndex;
					}
					isFineded = true;
				}
				if (tupleList.size - 1 != i)
				{
					tempedTuple = tempedTuple->nextTuple;
				}
			}
			for (i = 0; i < SIZEOFINDEX; i++)
			{
				printf("%c", nodeName[i]);
				if (nodeName[i] == '\0')
				{
					break;
				}
				nodeName[i] = '\0';
			}
			indexOfNodeName = 0;
		}
		else if (readedChar == '1' || readedChar == '2' || readedChar == '3'
			|| readedChar == '4' || readedChar == '5' || readedChar == '6'
			|| readedChar == '7' || readedChar == '8' || readedChar == '9'
			|| readedChar == '0')
		{
			weightString[indexOfWeight] = readedChar;
			indexOfWeight++;
		}
		else if ((readedChar == '\n' || readedChar == EOF) && weightString[0] != '\0')
		{
			readedChar = 0;
			int positNumber = 1;
			int totalNumber = 0;
			for (i = 0; i < indexOfWeight; i++)
			{
				int j = 0;
				for (j = 0; j < indexOfWeight - (i + 1); j++)
				{
					positNumber *= 10;
				}
				totalNumber += (weightString[i] - 48) * positNumber;
				positNumber = 1;
			}
			distanceMap[indexOfFirstNode][indexOfSecondNode] = totalNumber;
			distanceMap[indexOfSecondNode][indexOfFirstNode] = totalNumber;
			indexOfFirstNode = -1;
			indexOfSecondNode = -1;

			for (i = 0; i < SIZEOFINDEX; i++)
			{
				if (weightString[i] == '\0')
				{
					break;
				}
				weightString[i] = '\0';
			}
			indexOfWeight = 0;
		}
	}
	fclose(filePointer);

	int minValue = 0;
	int indexOfVisitedPlace = 0;

	printf("type the start node : ");
	char startNode[8];

	for( i = 0 ; i < 8;i++)
	{
		startNode[i] = '\0';
	}
	scanf("%s",startNode);
	for( i = 0 ; i < 8;i++)
	{
		if(startNode[i] != '\0' && startNode[i] >= 97 )
			startNode[i] = (startNode[i] - 32);
	}

	printf("%s",startNode);
	printf("\n");

	tempedTuple = &(tupleList.tulpleHead);
	int inputIndex = 0;
	for (i = 0; i < tupleList.size; i++)
	{
		if (strcmp(tempedTuple->NameOfNode, startNode) == 0)
		{
			inputIndex = tempedTuple->arrayIndex;
		}
		tempedTuple = tempedTuple->nextTuple;
	}



	shortDistanceCounts[inputIndex] = 0;

	char *storedPath = (char *)malloc(sizeof(char)*tupleList.size - 1);
	for (i = 0; i < tupleList.size; i++)
	{
		storedPath[i] = (char *)malloc(sizeof(char)*tupleList.size - 1);
	}

	int index[100];
	for (i = 0; i < tupleList.size; i++)
	{
		for (j = 0; j< tupleList.size; j++)
		{
			printf("%d\t", distanceMap[i][j]);
		}
		printf("\n", distanceMap[i][j]);
	}

	for (i = 0; i < tupleList.size; i++)
	{
		minValue = INFINITY;

		for (j = 0; j < tupleList.size; j++)
		{
			if (visitedFlag[j] == 0 && minValue > shortDistanceCounts[j])
			{
				minValue = shortDistanceCounts[j];
				indexOfVisitedPlace = j;
			}
		}
		visitedFlag[indexOfVisitedPlace] = 1;
		for (j = 0; j < tupleList.size; j++)
		{
			if (shortDistanceCounts[j] > shortDistanceCounts[indexOfVisitedPlace] + distanceMap[indexOfVisitedPlace][j])
			{
				shortDistanceCounts[j] = shortDistanceCounts[indexOfVisitedPlace] + distanceMap[indexOfVisitedPlace][j];
				index[j] = indexOfVisitedPlace;
			}
		}
	}

	printf("\n");

	printf("type the end node : ");
	char endNode[8];
	for( i = 0 ; i < 8;i++)
	{
		endNode[i] = '\0';
	}
	scanf("%s",endNode);
	for( i = 0 ; i < 8;i++)
	{
		if(endNode[i] != '\0'  && endNode[i] >= 97)
			endNode[i] = (endNode[i] - 32);
	}

	printf("%s",endNode);
	printf("\n");

	tempedTuple = &(tupleList.tulpleHead);
	inputIndex = 0;
	for (i = 0; i < tupleList.size; i++)
	{
		if (strcmp(tempedTuple->NameOfNode, endNode) == 0)
		{
			inputIndex = tempedTuple->arrayIndex;
		}
		tempedTuple = tempedTuple->nextTuple;
	}

	j = inputIndex;
	int outputArray[100];
	int outputValueArray[100];
	i = 0;
	while(index[j]< 9999 && index[j]> -1)
	{
		outputArray[i] = index[j];
		outputValueArray[i] = distanceMap[j][index[j]];
		j= index[j];
		i++;
	}
	for(j = i; j >= 0; j--)
	{
		tempedTuple = &tupleList.tulpleHead;
		for (i = 0; i < tupleList.size; i++)
		{
			if (tempedTuple->arrayIndex == outputArray[j] && outputArray[j]< 100)
			{
				printf("%s -> ",tempedTuple->NameOfNode);

				if(j == 0)
				{
					printf("( %d ) ",outputValueArray[j]);
				}
				else
				{
					printf("( %d ) -> ",outputValueArray[j]);
				}
				break;
			}
			tempedTuple = tempedTuple->nextTuple;
		}
	}




	printf(" / %d ",shortDistanceCounts[inputIndex]);


	tempedTuple = &tupleList.tulpleHead;
	return 0;
}
