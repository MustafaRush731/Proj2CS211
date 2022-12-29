/* CS211 Summer 2022 Project 2

	TODO:  Mustafa Rushdi, 5/22/2022, project 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int DebugMode;

/* TODO: create Point3D and PointSet data types using typedef and structs */
//Creatibg ttwo strcuts one for point3d and second one as PointSet
typedef struct {
  int ID;
  double coordinates[3];
  double luminosity;
}
Point3D;

typedef struct {
  Point3D * points;
  int nAllocated;
  int nPoints;
  double luminosity;
  double lower[3], upper[3];
}
PointSet;

/* TODO: uncomment these function prototypes.
     Functions appear below main, in the order listed here. */
int addPointToSet(PointSet * set, Point3D point);
int intersection(PointSet set, Point3D point);
void printResult(Point3D resultArray[], int inputCounter, int inputResults[]);

int main(int argc, char
  const * argv[]) {

  /*created to use detect when using in betv,=ma nd find any bus within my code */
  DebugMode = FALSE;
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      DebugMode = TRUE;
    }
  }
  /* TODO: Create a PointSet, and allocate some dynamic memory for the 
  	Point3Ds to be stored in it. */
  /* TODO: Global variable DebugMode: if -d argument is given, additional 
		information should be printed out as the program runs. */
  /* Look at lab 4 for help on this */
  PointSet * pntSet = NULL;
  pntSet = (PointSet * ) malloc(10 * sizeof(PointSet));
  pntSet -> nAllocated = 100;
  pntSet -> nPoints = 0;
  pntSet -> points = (Point3D * ) malloc(pntSet -> nAllocated * sizeof(Point3D));
  Point3D pnt3d;

  /* Read data for a series of points from standard input */
  /* For each point fill in the data for the next Point3D in the PointSet */
  /* Read data until a negative luminosity is encountered */
  double lumino = 0.0;
  int counter = 0;
  double valX = 0;
  double valY = 0;
  double valZ = 0;
  int results = 0;
  /*while loop used to have user inputs until a negative luminosity is entered then having point3d hold those va;ues so we can add them to our set */
  while (1) {
    pnt3d.ID = counter;
    scanf("%lf", & valX);
    pnt3d.coordinates[0] = valX;
    scanf("%lf", & valY);
    pnt3d.coordinates[1] = valY;
    scanf("%lf", & valZ);
    pnt3d.coordinates[2] = valZ;
    scanf("%lf", & lumino);
    pnt3d.luminosity = lumino;
    /*if a user enters a negative luminosity entered then we break from the while loop */
    if (lumino < 0) {
      break;
    }
    results = addPointToSet(pntSet, pnt3d);
    /*if the value from addPointToSet is 1 then we add point to the set and increment counter by 1 */
    if (results == 1) {
      addPointToSet(pntSet, pnt3d);
    }
    counter++;
    if (DebugMode == TRUE) {
      printf("\n");
      printf("Here print the points information for ID point %d", pnt3d.ID);
      printf("The X coordinate for this point is %f\n", pnt3d.coordinates[0]);
      printf("The Y coordinate for this point is %f\n", pnt3d.coordinates[1]);
      printf("The Z coordinate for this point is %f\n", pnt3d.coordinates[2]);
      printf("The luminosity for this point is %f\n", pnt3d.luminosity);
      printf("\n");
    }
  }

  /* Determine the upper and lower bounds of the bounding box, 
    as well as the average luminosity of the point set. Store these in the 
	PointSet structure.*/
  /* Report the bounds of the Point Set, the average luminosity, the number 
	of points in the Point Set */
  double maxX = -500;
  double minX = 500;
  double maxY = -500;
  double minY = 500;
  double maxZ = -500;
  double minZ = 500;
  double TotalLuminosity = 0;
  double luminosity = 0;
  //for loop to loop through how many Points are entered we have a variable to hold all the luminosity within the set then dividing it by the total points enterd*/
  for (int i = 0; i < pntSet -> nPoints; i++) {
    TotalLuminosity += pntSet -> points[i].luminosity;
    luminosity = (TotalLuminosity / pntSet -> nPoints);
    pntSet -> luminosity = luminosity;
    /* using multiple if staments to find the min and max values which will be the bound */
    if (maxX < pntSet -> points[i].coordinates[0]) {
      maxX = pntSet -> points[i].coordinates[0];
      pntSet -> upper[0] = maxX;
    }
    if (minX > pntSet -> points[i].coordinates[0]) {
      minX = pntSet -> points[i].coordinates[0];
      pntSet -> lower[0] = minX;
    }
    if (maxY < pntSet -> points[i].coordinates[1]) {
      maxY = pntSet -> points[i].coordinates[1];
      pntSet -> upper[1] = maxY;
    }
    if (minY > pntSet -> points[i].coordinates[1]) {
      minY = pntSet -> points[i].coordinates[1];
      pntSet -> lower[1] = minY;
    }
    if (maxZ < pntSet -> points[i].coordinates[2]) {
      maxZ = pntSet -> points[i].coordinates[2];
      pntSet -> upper[2] = maxZ;
    }
    if (minZ > pntSet -> points[i].coordinates[2]) {
      minZ = pntSet -> points[i].coordinates[2];
      pntSet -> lower[2] = minZ;
    }
  }
  /*printing the bound of each set*/
  printf("the luminosity average is %.2f\n", luminosity);
  printf("max bound for coordinate X is %.2f the min bound for coordinate X is %.2f\n", pntSet -> upper[0], pntSet -> lower[0]);
  printf("max bound for coordinate Y is %.2f the min bound for coordinate Y is %.2f\n", pntSet -> upper[1], pntSet -> lower[1]);
  printf("max bound for coordinate Z is %.2f the min bound for coordinate Z is %.2f\n", pntSet -> upper[2], pntSet -> lower[2]);

  /* Read data for a second set of points and for each point determine
	whether this point intersects with the PointSet or not. Read data until a negative luminosity is encountered */
  double valXset2 = 0;
  double valYset2 = 0;
  double valZset2 = 0;
  int inputCounter = 0;
  int inputResults[pntSet -> nPoints];
  Point3D resultsArray[pntSet -> nPoints];
  double luminositySet2 = 0;
  /*while loop similar to to what we did in the first set of points we are reading data till negative luminasity is entered*/
  while (1) {
    pnt3d.ID = inputCounter;
    scanf("%lf", & valXset2);
    pnt3d.coordinates[0] = valXset2;
    scanf("%lf", & valYset2);
    pnt3d.coordinates[1] = valYset2;
    scanf("%lf", & valZset2);
    pnt3d.coordinates[2] = valZset2;
    scanf("%lf", & luminositySet2);
    pnt3d.luminosity = luminositySet2;
    /* if the luminosity enterd is negatice then print the results and break from while loop */
    if (luminositySet2 < 0) {
      printResult(resultsArray, inputCounter, inputResults);
      break;
    }
    //here call function to see any intersections
    int intersectingResult = intersection( * pntSet, pnt3d);
    inputResults[pnt3d.ID] = intersectingResult;
    resultsArray[pnt3d.ID] = pnt3d;
    inputCounter++;
    if (DebugMode == TRUE) {
      printf("\n");
      printf("if the struct instance is holding the right values then these will match with input for the second set of points\n");
      printf("Value of coordinate X for second set is %f\n", pnt3d.coordinates[0]);
      printf("Value of coordinate X for second set is %f\n", pnt3d.coordinates[1]);
      printf("Value of coordinate X for second set is %f\n", pnt3d.coordinates[2]);
      printf("Value of coordinate X for second set is %f\n", pnt3d.luminosity);
      printf("The value of the inersection function %d\n", intersectingResult);
    }
  }
  /* TODO: Make sure you free any dynamically allocated memory before the 
	program ends.  Use Valgrind to check, because TAs will. */
  free(pntSet -> points);
  free(pntSet);
  pntSet = NULL;
  return 0;
}

/* addPointToSet Function determines first weather the size is suficent for the data to be stored withing a dynamically allocated array if not doublle the 
allocation size within heap then the compputer will store those values into the set*/
int addPointToSet(PointSet * set, Point3D point) {
  int isItAllocated = 0;
  if (set -> nPoints >= set -> nAllocated) {
    Point3D * temp;
    temp = set -> points;
    set -> points = (Point3D * ) malloc(2 * set -> nAllocated * sizeof(Point3D));
    for (int i = 0; i < set -> nAllocated; i++) {
      set -> points[i] = temp[i];
    }
    free(temp);
    temp = NULL;
    set -> nAllocated = set -> nAllocated * 2;
  }
  set -> points[set -> nPoints] = point;
  if (DebugMode == TRUE) {
    printf("\n");
    printf("Here we are checking for the correct set->nPoints %d\n", set -> nPoints);
    printf("if the add point to set was succesfull then the values will hold the same values as the values above");
    printf("the value for coordinates one in the points SetPoints struct is %f\n", set -> points[set -> nPoints].coordinates[0]);
    printf("the value for coordinates one in the points SetPoints struct is %f\n", set -> points[set -> nPoints].coordinates[1]);
    printf("the value for coordinates one in the points SetPoints struct is %f\n", set -> points[set -> nPoints].coordinates[2]);
    printf("the value for coordinates one in the points SetPoints struct is %f\n", set -> points[set -> nPoints].luminosity);
    printf("\n");
  }
  /* if the values allocated within the set equall the values within the original point then we succesfully allocated the array else set the values as -1*/
  if (set -> points[set -> nPoints].coordinates[0] == point.coordinates[0]) {
    if (set -> points[set -> nPoints].coordinates[0] == point.coordinates[0]) {
      if (set -> points[set -> nPoints].coordinates[0] == point.coordinates[0]) {
        isItAllocated = 0;
      }
    }
  } else {
    isItAllocated = -1;
  }
  set -> nPoints += 1;

  return isItAllocated;
}

/* nested if statments used to see weather the point entered leies between the low and high values within the set if it doesnt returns 1 if the 
point intersect with the set or 0 otherwise. */
int intersection(PointSet set, Point3D newPoint) {
  int intersectRange = 0;
  if (newPoint.coordinates[0] <= set.upper[0] && newPoint.coordinates[0] >= set.lower[0]) {
    if (newPoint.coordinates[1] <= set.upper[1] && newPoint.coordinates[1] >= set.lower[1]) {
      if (newPoint.coordinates[2] <= set.upper[2] && newPoint.coordinates[2] >= set.lower[2]) {
        intersectRange = 1;
      }
    }
  } else {
    intersectRange = 0;
  }
  if (DebugMode == TRUE) {
    printf("\n");
    printf("Theis values will represent if the values is within range or not meaning if it is 1 or 0 %d\n", intersectRange);
    printf("\n");
  }
  return intersectRange;
}

/*function used to print weather the second set of point coordinates intersect with the set or not
Returns 0 ( false ) if the set has no points, otherwise check if the 
point's coordinates are within or equal to the bounds of the set.
   Return 1 ( true ) if there is an intersection and 0 ( false ) otherwise */
void printResult(Point3D resultArray[], int inputCounter, int inputUser[]) {
  /*for loop used to print the coordinates of each pint entered then looping through the esults to see if it intersects*/
  for (int i = 0; i < inputCounter; i++) {
    printf("Coordinates at ID %d ", resultArray[i].ID);
    printf("X: %.2f ", resultArray[i].coordinates[0]);
    printf("Y: %.2f ", resultArray[i].coordinates[1]);
    printf("Z: %.2f ", resultArray[i].coordinates[2]);
    if (inputUser[i] == 1) {
      printf("The point intersects with the set\n");
    } else {
      printf("The point does not intersect with the set\n");
    }
  }
}
