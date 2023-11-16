
// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SortedList.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==ListGetSize(...).

// Definition of the structure
struct _PersonSet_ {
  List *persons;  // points to a SortedList of Person pointers
};

// Comparison function to be used in generic SortedList.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b) {
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // You must allocate space for the struct and create an empty persons list!
  PersonSet *ps = (PersonSet *)malloc(sizeof(PersonSet));
  if (ps == NULL) abort();
  ps->persons = ListCreate(cmpP);
  return ps;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);
  ListDestroy(&((*pps)->persons));
  free(*pps);
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps) { return ListGetSize(ps->persons); }

int PersonSetIsEmpty(const PersonSet *ps) { return ListIsEmpty(ps->persons); }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (ListMoveToHead(ps->persons); ListCurrentIsInside(ps->persons);
       ListMoveToNext(ps->persons)) {
    Person *p = (Person *)ListGetCurrentItem(ps->persons);
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d)\n", PersonSetSize(ps));
  ListTestInvariants(ps->persons);
}

// Find node in list ps->persons of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  Person dummyperson;
  dummyperson.id = id;
  return ListSearch(ps->persons, &dummyperson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  if (search(ps, p->id) < 0) { // if person not already in set
    ListInsert(ps->persons, p);
  }
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the person in the first position!
  Person *p = (Person *)ListRemoveHead(ps->persons);
  return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  if (search(ps, id) >= 0) {
    Person *p = (Person *)ListRemoveCurrent(ps->persons);
    return p;
  }
  return NULL;
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  if (search(ps, id) >= 0) {
    Person *p = (Person *)ListGetCurrentItem(ps->persons);
    return p;
  }
  return NULL;
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();  // create a new set to hold the union of the two sets
  ListMoveToHead(ps1->persons);
  ListMoveToHead(ps2->persons);

  // Iterate through both lists until one of them is empty
  while (ListCurrentIsInside(ps1->persons) && ListCurrentIsInside(ps2->persons)) {
    Person *p1 = (Person *)ListGetCurrentItem(ps1->persons);
    Person *p2 = (Person *)ListGetCurrentItem(ps2->persons);

    // Add the smaller element to the new set and move the list that contained it
    if (cmpP(p1, p2) < 0) {
      ListInsert(ps->persons, p1);
      ListMoveToNext(ps1->persons);
    } else if (cmpP(p1, p2) > 0) {
      ListInsert(ps->persons, p2);
      ListMoveToNext(ps2->persons);
    } else {
      // Equal elements, add once and move both lists
      ListInsert(ps->persons, p1);
      ListMoveToNext(ps1->persons);
      ListMoveToNext(ps2->persons);
    }
  }

  // now add all the elemts from the list that is not empty because we want the union of the two sets
  // Add remaining elements from ps1, if any
  while (ListCurrentIsInside(ps1->persons)) {
    ListInsert(ps->persons, ListGetCurrentItem(ps1->persons));
    ListMoveToNext(ps1->persons);
  }

  // Add remaining elements from ps2, if any
  while (ListCurrentIsInside(ps2->persons)) {
    ListInsert(ps->persons, ListGetCurrentItem(ps2->persons));
    ListMoveToNext(ps2->persons);
  }

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  ListMoveToHead(ps1->persons);
  ListMoveToHead(ps2->persons);

  // Iterate through both lists until one of them is empty
  while (ListCurrentIsInside(ps1->persons) && ListCurrentIsInside(ps2->persons)) {
    Person *p1 = (Person *)ListGetCurrentItem(ps1->persons);
    Person *p2 = (Person *)ListGetCurrentItem(ps2->persons);

    if (cmpP(p1, p2) < 0) {
      ListMoveToNext(ps1->persons);
    } else if (cmpP(p1, p2) > 0) {
      ListMoveToNext(ps2->persons);
    } else {
      // Equal elements, add once and move both lists
      ListInsert(ps->persons, p1);
      ListMoveToNext(ps1->persons);
      ListMoveToNext(ps2->persons);
    }
  }

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  ListMoveToHead(ps1->persons);
  ListMoveToHead(ps2->persons);

  while (ListCurrentIsInside(ps1->persons) && ListCurrentIsInside(ps2->persons)) {
    Person *p1 = (Person *)ListGetCurrentItem(ps1->persons);
    Person *p2 = (Person *)ListGetCurrentItem(ps2->persons);

    if (cmpP(p1, p2) < 0) {
      // Element in ps1 is not in ps2, add it to the new set and move the list
      ListInsert(ps->persons, p1);
      ListMoveToNext(ps1->persons);
    } else if (cmpP(p1, p2) > 0) {
      // Element in ps2 is not in ps1, move the list that contains it
      ListMoveToNext(ps2->persons);
    } else {
      // Equal elements, move both lists without adding anything to the new set
      ListMoveToNext(ps1->persons);
      ListMoveToNext(ps2->persons);
    }
  }

  // now add all the elements from the list ps1 if not empty because we want the sets
  // Add remaining elements from ps1, if any
  while (ListCurrentIsInside(ps1->persons)) {
    ListInsert(ps->persons, ListGetCurrentItem(ps1->persons));
    ListMoveToNext(ps1->persons);
  }

  return ps;
}

// Return true if *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  ListMoveToHead(ps1->persons);
  ListMoveToHead(ps2->persons);

  while (ListCurrentIsInside(ps1->persons) && ListCurrentIsInside(ps2->persons)) {
    Person *p1 = (Person *)ListGetCurrentItem(ps1->persons);
    Person *p2 = (Person *)ListGetCurrentItem(ps2->persons);

    if (cmpP(p1, p2) < 0) {
      // Element in ps1 is not in ps2, ps1 is not a subset
      return 0;
    } else if (cmpP(p1, p2) > 0) {
      ListMoveToNext(ps2->persons);
    } else {
      // Equal elements, move both lists
      ListMoveToNext(ps1->persons);
      ListMoveToNext(ps2->persons);
    }
  }

  // If there are still elements in ps1, then ps1 is not a subset
  return !ListCurrentIsInside(ps1->persons);
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  return PersonSetIsSubset(ps1, ps2) && PersonSetIsSubset(ps2, ps1);
}
