/*Licensed under the MIT License.
For details on the licensing terms, see the LICENSE file.
SPDX-License-Identifier: MIT

Copyright 2023-2024 (c) Fraunhofer IOSB (Author: Florian Düwel)*/


#include "../test_include/service_callbacks.h"
#include "node_finder.h"

typedef struct {
    UA_String service_name;
    UA_Server *server;
    pthread_t threadId;
}UA_simple_service_handler;

static void *execute_event_with_order_result(void *ptr){
    UA_simple_service_handler *service_dict = (UA_simple_service_handler*) ptr;
    UA_String out = UA_STRING_NULL;
    UA_print(&service_dict->service_name, &UA_TYPES[UA_TYPES_STRING], &out);
    printf("Trigger the event of service : %.*s\n", (int)out.length, out.data);
    UA_String_clear(&out);

    UA_NodeId event_nodeId;
    UA_NodeId_init(&event_nodeId);
    //browse the server for the service finished event type
    find_service_event(service_dict->server, &event_nodeId, service_dict->service_name);
    UA_print(&event_nodeId, &UA_TYPES[UA_TYPES_NODEID], &out);
    printf("ServiceEvent NodeId : %.*s\n", (int)out.length, out.data);
    UA_String_clear(&out);
    UA_String_clear(&service_dict->service_name);
    //create the event
    UA_NodeId eventOutNodeId;
    UA_NodeId_init(&eventOutNodeId);
    UA_Server_createEvent(service_dict->server, event_nodeId, &eventOutNodeId);
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Trigger the event");
    UA_Server_triggerEvent(service_dict->server, eventOutNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER), NULL, UA_TRUE);

    UA_NodeId_clear(&eventOutNodeId);
    UA_NodeId_clear(&event_nodeId);
    free(service_dict);

    return UA_STATUSCODE_GOOD;
}

UA_StatusCode warehousemethodCallback(UA_Server *server,
                                      const UA_NodeId *sessionId, void *sessionHandle,
                                      const UA_NodeId *methodId, void *methodContext,
                                      const UA_NodeId *objectId, void *objectContext,
                                      size_t inputSize, const UA_Variant *input,
                                      size_t outputSize, UA_Variant *output){

    UA_String service_name = UA_String_fromChars("GetPartsFromWarehouse");
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Service execution Started");
    UA_simple_service_handler *handler = UA_calloc(1, sizeof(UA_simple_service_handler));
    UA_String_copy(&service_name, &handler->service_name);
    handler->server = server;
    pthread_create(&handler->threadId, NULL, execute_event_with_order_result, handler);
    UA_String_clear(&service_name);

    //create the ServiceExecutionAsyncResultDataType variable
    UA_ServiceExecutionAsyncResultDataType res;
    UA_ServiceExecutionAsyncResultDataType_init(&res);
    res.serviceResultCode = (UA_UInt32) 1;
    res.serviceResultMessage = UA_String_fromChars("Message");
    res.expectedServiceExecutionDuration = (UA_Double) 7;
    res.serviceTriggerResult = UA_SERVICETRIGGERRESULT_SERVICE_RESULT_ACCEPTED;

    UA_Variant_setScalarCopy(output, &res, &UA_TYPES_COMMON[UA_TYPES_COMMON_SERVICEEXECUTIONASYNCRESULTDATATYPE]);
    UA_String_clear(&res.serviceResultMessage);
    return UA_STATUSCODE_GOOD;
}