//
// Algoritmos e Estruturas de Dados --- 2023/2024
//

// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==BSTreeGetNumberOfNodes(...).

// Definition of the structure
struct _PersonSet_ {
  BSTree *persons;  // points to a BSTree of Person pointers
};

// Comparison function to be used in generic BSTree.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b) {
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Print function to be used in generic BSTree.
static void printP(void *p) { PersonPrintf((Person *)p, ""); }

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // Allocate memory for the struct
  PersonSet *newSet = (PersonSet *)malloc(sizeof(PersonSet));

  // Check if the memory allocation was successful
  if (newSet == NULL) {
    return NULL;
  }

  // Create an empty persons tree
  newSet->persons = BSTreeCreate(cmpP, printP);

  // Return the created PersonSet
  return newSet;

}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);

  // Destroy the BSTree containing Person pointers
  BSTreeDestroy(&((*pps)->persons));

  // Free the memory allocated for the PersonSet structure
  free(*pps);

  // Set the pointer to NULL to avoid dangling pointers
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps) {
  return BSTreeGetNumberOfNodes(ps->persons);
}

int PersonSetIsEmpty(const PersonSet *ps) { return BSTreeIsEmpty(ps->persons); }

// Print function to use in PersonSetPrint
static void printlnP(void *p) { PersonPrintf((Person *)p, ";\n"); }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  BSTreeTraverseINOrder(ps->persons, printlnP);
  printf("}(size=%d)\n", PersonSetSize(ps));
}

// Find node in BSTree ps->persons of person with given id.
// Return a pointer to the stored Person instance.
// Or NULL, if it does not belong to the BSTree.
// (INTERNAL function.)
static Person *search(const PersonSet *ps, int id) {
  Person dummyPerson;
  dummyPerson.id = id;
  return BSTreeSearch(ps->persons, &dummyPerson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  assert(ps != NULL && p != NULL);

  // Check if the person with the same ID already exists in the set
  if (!PersonSetContains(ps, p->id)) {
    // Add the person to the BSTree
    BSTreeAdd(ps->persons, p);
  }
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the first person in the set!
  // Get the minimum person in the set (assuming Person's id is used for comparison)
  Person *minPerson = (Person *)BSTreeGetMin(ps->persons);

  // Remove the person from the set
  BSTreeRemove(ps->persons, minPerson);

  return minPerson;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  assert(ps != NULL);

  // Search for the person with the given ID in the set
  Person *targetPerson = search(ps, id);

  // If the person is found, remove it from the set
  if (targetPerson != NULL) {
    BSTreeRemove(ps->persons, targetPerson);
    return targetPerson;
  } else {
    return NULL;
  }
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  assert(ps != NULL);

  // Search for the person with the given ID in the set
  return search(ps, id);
}

// Return true (!= 0) if set contains person with given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) != NULL;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();

  // Traverse ps1 and add each person to the new PersonSet
  _treeTraverseINOrder(ps1->persons, (void (*)(void*))PersonSetAdd);

  // Traverse ps2, and for each person, if it's not already in the new PersonSet, add it
  _treeTraverseINOrder(ps2->persons, (void (*)(void*))PersonSetAdd);

  return ps;
}

void PersonSetAddIfContains(PersonSet *ps, Person *p) {
  assert(ps != NULL && p != NULL);

  // Check if the person is in the set
  if (PersonSetContains(ps, p->id)) {
    // Add the person to the set
    PersonSetAdd(ps, p);
  }
}

void PersonSetAddIfNotContains(PersonSet *ps, Person *p) {
  assert(ps != NULL && p != NULL);

  // Check if the person is in the set
  if (!PersonSetContains(ps, p->id)) {
    // Add the person to the set
    PersonSetAdd(ps, p);
  }
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();

  // Traverse ps1, and for each person, if it's also in ps2, add it to the new PersonSet
  _treeTraverseINOrder(ps1->persons, (void (*)(void*))PersonSetAddIfContains);

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();

  // Traverse ps1, and for each person, if it's not in in ps2, add it to the new PersonSet
  _treeTraverseINOrder(ps1->persons, (void (*)(void*))PersonSetAddIfNotContains);

  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  // Check if every person in ps1 is also in ps2
  return BSTreeIsSubset(ps1->persons, ps2->persons, cmpP);
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  return PersonSetSize(ps1) == PersonSetSize(ps2) &&
         PersonSetIsSubset(ps1, ps2);
}
