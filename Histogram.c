//
//  main.c
//  Created by Kaymin Dixon on 10/15/19.


#include <stdio.h>

#define MAX_BINS (5)

// Returns a single validated measurement from the user
int GetMeasurement(int msrNum, int min, int max) {
	int num = 0;
	while (1) {
		printf("Please enter a measurement %d: ", msrNum);
		scanf_s("%d", &num);
		if (num < min || num > max) {
			printf("The measurement is outside of the given range. "
				"Please try again.\n");
			continue;
		}
		else {
			break;
		}
	};
	return num;
}

void IncrementInBin(double bins[], int binCounters[], int msr) {
	for (int i = MAX_BINS - 1; i >= 0; i--) {
		if (bins[i] <= msr) {
			binCounters[i] += 1;
			return;
		}
	}
}

// Returns the validated number of measurements for a batch
int GetNumMeasurements(int min, int max, double bins[], int binCounters[]) {
	int msrsInBatch = 1;
	while (1) {
		printf("How many measurements are there for this batch: ");
		scanf_s("%d", &msrsInBatch);
		if (msrsInBatch > 0) {
			break;
		}
		else {
			printf("Batch length can not be negative. Try again.\n");
			continue;
		}
	};

	for (int i = 1; i <= msrsInBatch; i++) {
		int msr = GetMeasurement(i, min, max);
		IncrementInBin(bins, binCounters, msr);
	}
	return msrsInBatch;
}

void getRange(int* min, int* max) {
	while (1) {
		printf("Please enter the minimum and maximum values for the measurements: ");
		scanf_s("%d %d", min, max);
		int invalid = 0;
		if (*min >= *max) {
			printf("The value entered (%d and %d) are not valid. "
				"The minimum value should be less than maximum\n", *min, *max);
			invalid = 1;
		}
		if ((*max - *min) < 5) {
			printf("The value entered (%d and %d) must have a difference of at least 5 \n",
				*min, *max);
			invalid = 1;
		}
		if (invalid == 1) {
			continue;
		}
		return;
	}
}

/* Returns the updated value for a given bin based on a measurement
 *  (this function should be called 5 times, once for each bin)
 */
int UpdateBin() {
	return 0;
}

void plotHistogram(double bins[], int binCounters[]) {
	printf("\n\n\n\n");
	unsigned char block = 219;
	unsigned char bar = 179;
	unsigned char line = 196;
	unsigned char bottomLeft = 192;
	int maxY = 0;

	printf("		%c", 201);
	for (int q = 0; q < 60; q++) 
	{
		printf("%c", 205);
	}
	printf("%c\n",187);
	printf("		%c                HISTOGRAM               %c\n", 186, 186);
	printf("		%c", 200);
	for (int w = 0; w < 60; w++)
	{
		printf("%c", 205);
	}
	printf("%c\n", 188);
	printf("\n");

;	for (int i = 0; i < MAX_BINS; i++) {
		if (maxY < binCounters[i]) {
			maxY = binCounters[i];
		}
	}
	int yAxis = maxY;
	if (yAxis % 2 != 0) {
		yAxis++;
	}
	for (int y = yAxis; y > 0; y--) {
		// print number at y-axis followed by horizontal line
		if (y % 2 == 0) {
			printf("\t\t%2d", y);
			printf("%c", bar);
		}
		else {
			printf("\t\t  %c", bar);
		}

		// print blocks or blank for each bin
	
		for (int v = 0; v < MAX_BINS; v++) {
			if (binCounters[v] >= y) {
				
				printf("%c%c        ", block, block);
				
			}
			else {
				printf("          ");
			}
		}
		printf("\n");
	}
	printf("\t\t  %c", bottomLeft);
	// print x-axis bottom horizontal line
	for (int i = 0; i < 43; i++) {
		printf("%c", line);
	}
	// print x-axis values
	printf("\n\t\t   ");
	for (int i = 0; i < MAX_BINS; i++) {
		printf(" %g      ", bins[i]);
	}

	printf("\n");
}

int main() {
	int min = 0;
	int max = 0;
	double bins[MAX_BINS] = { 0 };
	int binCounters[MAX_BINS] = { 0 };


	// accepts valid range from user
	getRange(&min, &max);

	// calculate size of each bin
	int binSize = (max - min)/ MAX_BINS;

	// creates bins in array. Each element represents starting range of the bin.
	for (int i = 0; i < MAX_BINS; i++) {
		bins[i] = min + (i * binSize);
	}

	char c;
	while (1) {
		GetNumMeasurements(min, max, bins, binCounters);
		printf("Do you have another batch (Y/N)?");

		// clear the input buffer
		while ((c = getchar()) != '\n' && c != EOF);

		if ((c = getchar()) == 'y') {
			printf("\n");
			continue;
		}
		else {
			break;
		}
	}

	plotHistogram(bins, binCounters);
	return 0;
}