/*Licensed under the MIT License.
For details on the licensing terms, see the LICENSE file.
SPDX-License-Identifier: MIT

Copyright 2023-2024 (c) Fraunhofer IOSB (Author: Florian Düwel)*/

#ifndef TESTS_SERVICE_CALLBACKS_H
#define TESTS_SERVICE_CALLBACKS_H

#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/types.h>
#include <stdio.h>
#include "pthread.h"

#include <open62541/types.h>
#include "open62541/namespace_pfdl_parameter_generated.h"
#include "open62541/namespace_warehouse_generated.h"
#include "open62541/namespace_common_generated.h"
#include "open62541/types_common_generated_handling.h"
#include "open62541/types_pfdl_parameter_generated.h"


UA_StatusCode warehousemethodCallback(UA_Server *server,
                                      const UA_NodeId *sessionId, void *sessionHandle,
                                      const UA_NodeId *methodId, void *methodContext,
                                      const UA_NodeId *objectId, void *objectContext,
                                      size_t inputSize, const UA_Variant *input,
                                      size_t outputSize, UA_Variant *output);

#endif //TESTS_SERVICE_CALLBACKS_H
