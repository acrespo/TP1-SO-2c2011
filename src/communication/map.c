#include "ipc/ipc.h"
#include "models/plane.h"
#include "models/city.h"
#include "models/map.h"
#include "communication/map.h"
#include "communication/plane.h"
#include "marshall/map.h"
#include "marshall/plane.h"
#include "communication/msgqueue.h"
#include "ipc/ipc.h"


int comm_unloaded_stock(int airlineID, Plane* plane, ipc_t conn){
    
    struct StockStateMessage msg;
    msg = marshall_change_stock(airlineID, plane->id, plane->stocks);
    transmit(conn, msg);

    return 0;
}

int comm_give_destinations(Plane* plane, ipc_t conn, int cityNumber, City* cities, int* distances){

    struct DestinationsMessage msg;
    msg = marshall_give_destinations(plane->id, cityNumber, cities, distances);
    transmit(conn, msg);

    return 0;
}

int comm_turn_step(Vector* conns) {
    
    enum MapMessageType msg = StepMessageType;
    unsigned i;

    for ( i=0; i<getVectorSize(conns); i++) {
        transmit(getFromVector(conns,i),msg);
    }

    return 0;
}

int comm_turn_continue(Vector* conns) {
    
    enum MapMessageType msg = ContinueMessageType;
    unsigned i;

    for ( i=0; i<getVectorSize(conns); i++) {
        transmit(getFromVector(conns,i),msg);
    }    
    
    return 0;
}

struct MapMessage comm_get_map_message(void) {
    
    char msg[IPC_MAX_PACKET_LEN];
    struct MapMessage ans;

    ipc_read(msg, sizeof(msg));

    ans.type = (int)msg;
    if ( ans.type == CheckDestinationsType || ans.type == UnloadStockType) {
        //Chequear con la implementacion si esto es alrevez
        ans.planeInfo.airlineID = (int) msg[sizeof(int)];
        //ans.planeInfo.plane = (Plane) msg[2*sizeof(int)];
    }

    return ans;
}
