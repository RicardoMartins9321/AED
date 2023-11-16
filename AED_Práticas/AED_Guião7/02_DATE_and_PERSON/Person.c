
// JMR, 2021

// Complete the functions (marked by ...)
// so that it passes all tests in PersonTest.

#include "Person.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This variable stores the last ID that was assigned to a Person.
// It should be used to assign serial, unique IDs automatically upon creation.
// The first person will have id=1, the second id=2, etc.
static int lastID = 0;

// Alocate and store a Person.
// Returns the pointer to the new structure,
// or NULL if allocation fails.
// The names are copied to internally allocated memory.
Person *PersonCreate(const char *fname, const char *lname, int yy, int mm,
                     int dd) {
  Person* p = (Person*)malloc(sizeof(Person));
  if (p == NULL) return NULL;
  p->id = ++lastID;
  p->birthDate.year = yy;
  p->birthDate.month = mm;
  p->birthDate.day = dd;
  p->firstName = malloc(sizeof(char) * (strlen(fname)));
  p->lastName = malloc(sizeof(char) * (strlen(lname)));
  strcpy(p->firstName, fname);
  strcpy(p->lastName, lname);

  return p;
}

// Free the memory pointed to by *pp and by the names inside it,
// and invalidate *pp contents.
// Precondition: *pp must not be NULL.
// Postcondition: *pp is set to NULL.
void PersonDestroy(Person **pp) {
  assert(*pp != NULL);  // Precondition: *pp must not be NULL

  Person* p = *pp;
  free(p);  // Free the memory pointed to by *pp
  *pp = NULL; // Invalidate *pp contents by setting it to NULL
}

// Prints a person formatted as "[id, lastname, firstname, birthdate]",
// followed by a suffix string.
void PersonPrintf(Person *p, const char *suffix) {
  if (p == NULL)
    printf("NULL%s", suffix);
  else
    printf("(%d, %s, %s, %s)%s", p->id, p->lastName, p->firstName,
           DateFormat(&(p->birthDate), YMD), suffix);
}

// Compare birth dates of two persons.
// Return a negative/positive integer if p1 was born before/after p2.
// Return zero if p1 and p2 were born on the same date.
int PersonCompareByBirth(const Person *p1, const Person *p2) {
  if (p1->birthDate.year != p2->birthDate.year)
    return p1->birthDate.year - p2->birthDate.year;
  else if (p1->birthDate.month != p2->birthDate.month)
    return p1->birthDate.month - p2->birthDate.month;
  else if (p1->birthDate.day != p2->birthDate.day)
    return p1->birthDate.day - p2->birthDate.day;
  else
    return 0;
}

// Compare two persons by last name, then first name (if last name is the same).
// Return a -/+/0 integer if p1 precedes/succeeds/is equal to p2.
int PersonCompareByLastFirstName(const Person *p1, const Person *p2) {
  int lastNameComparison = strcmp(p1->lastName, p2->lastName);

  if (lastNameComparison != 0) {
    return lastNameComparison;
  } else {
    return strcmp(p1->firstName, p2->firstName);
  }
}
