
// Complete the functions (marked by ...)
// so that it passes all tests in DateTimeTest.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of the structure
struct _PersonSet_ {
  int capacity;    // the current capacity of the array
  int size;        // the number of elements currently stored
  Person **array;  // points to an array of pointers to persons
};

#define INITIAL_CAPACITY 4

// You may add auxiliary definitions and declarations here, if you need to.

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // Allocate space for the struct
  PersonSet *ps = (PersonSet *)malloc(sizeof(PersonSet));
  if (ps == NULL) {
    return NULL;  // Failed to allocate memory
  }

  // Initialize the capacity and size
  ps->capacity = INITIAL_CAPACITY;
  ps->size = 0;  // currently empty

  // Allocate space for the array
  ps->array = (Person **)malloc(sizeof(Person *) * ps->capacity);
  if (ps->array == NULL) {
    free(ps);  // Free the previously allocated memory for the struct
    return NULL;  // Failed to allocate memory for the array
  }

  return ps;
}

// we have to use double **pps because we want to change the pointer to the memory and if we just use
// PersonSet *ps we would only change the value of the local variable and not what the pointer points to
// and we would lose the reference to the struct and the array and we would have a memory leak
// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL); // if pointer not null we can free the memory because the personset exists

  free((*pps)->array);  // Free the array

  free(*pps);   // Free the struct

  *pps = NULL;  // Invalidate the pointer to the struct
}

int PersonSetSize(const PersonSet *ps) { return ps->size; }

int PersonSetIsEmpty(const PersonSet *ps) { return ps->size == 0; }

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (int i = 0; i < ps->size; i++) {
    Person *p = ps->array[i];
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d, capacity=%d)\n", ps->size, ps->capacity);
}

// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  for (int i = 0; i < ps->size; i++) {
    Person *p = ps->array[i];
    if (p->id == id) {
      return i;   // Found the person, return the index
    }
  }

  return -1;  // Person not found
}

// Append person *p to *ps, without verifying presence.
// Use only when sure that *p is not contained in *ps!
// (INTERNAL function.)
static void append(PersonSet *ps, Person *p) {
  // Check if the array is full
  if (ps->size == ps->capacity) {
    // Double the array capacity
    ps->capacity *= 2;
    // Reallocate memory for the array
    ps->array = (Person **)realloc(ps->array, sizeof(Person *) * ps->capacity);
    if (ps->array == NULL) {
      // Handle realloc failure if necessary
      fprintf(stderr, "Error: realloc failed\n");
      return;
    }
  }

  // Append the person
  ps->array[ps->size] = p;
  ps->size++;
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  // Check if the person is already in the set
  if (PersonSetContains(ps, p->id)) {
    return;  // Do nothing
  }

  // Append the person
  append(ps, p);
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));

  // Decrease the size of the set
  ps->size--;

  // Return the person in the last position
  return ps->array[ps->size];
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  // Call search to find the index of the person
  int index = search(ps, id);
  if (index == -1) {
    // Person not found
    return NULL;
  }

  Person *person = ps->array[index];  // Save the person to return later

  // Remove the person from the array by shifting the elements
  for (int i = index; i < ps->size - 1; i++) {
    ps->array[i] = ps->array[i + 1];
  }

  ps->size--;   // Decrease the size of the set

  return person;  // Return the removed person
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  // You may call search here!
  int index = search(ps, id);
  if (index != -1) {
    return ps->array[index];
  }

  return NULL;
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL;  // Failed to allocate memory
  }

  // Append all persons from ps1
  for (int i = 0; i < ps1->size; i++) {
    append(ps, ps1->array[i]);
  }

  // Append all persons from ps2, if they are not already in ps because in a union we want one or the other
  for (int i = 0; i < ps2->size; i++) {
    if (search(ps, ps2->array[i]->id) == -1) {
      append(ps, ps2->array[i]);
    }
  }

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL;  // Failed to allocate memory
  }

  // Append all persons from ps1 that are also in ps2 because they are in the intersection, they must be in both
  for (int i = 0; i < ps1->size; i++) {
    if (search(ps2, ps1->array[i]->id) != -1) {
      append(ps, ps1->array[i]);
    }
  }

  return NULL;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL;  // Failed to allocate memory
  }

  // Append all persons from ps1 that are not in ps2 because they are in the difference, they must be in ps1 but not in ps2
  for (int i = 0; i < ps1->size; i++) {
    if (search(ps2, ps1->array[i]->id) == -1) {
      append(ps, ps1->array[i]);
    }
  }

  return NULL;
}

// Return true if *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  // Iterate over all persons in ps1
  for (int i = 0; i < ps1->size; i++) {
    // If a person in ps1 is not in ps2, return 0
    if (search(ps2, ps1->array[i]->id) == -1) {
      return 0;
    }
  }

  // All persons in ps1 are also in ps2, so return 1
  return 1;
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  // You may call PersonSetIsSubset here!
  return PersonSetIsSubset(ps1, ps2) && PersonSetIsSubset(ps2, ps1);
}
