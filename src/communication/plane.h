#ifndef __COMM_PLANE__
#define __COMM_PLANE__

#include "app/plane.h"

int comm_check_destinations(struct PlaneThread* plane, int* destinations, size_t* len);

int comm_set_destination(struct PlaneThread* plane, int target);

int comm_continue(struct PlaneThread* plane);

int comm_step(struct PlaneThread* plane);

int comm_unload_stock(struct PlaneThread* plane, int* stockDelta);

#endif