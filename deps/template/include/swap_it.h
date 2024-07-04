/*
 * Copyright The open62541-server-template Contributors
 * Licensed under the MIT License.
 * For details on the licensing terms, see the LICENSE file.
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2023-2024 (c) Fraunhofer IOSB (Author: Florian Düwel)
 * Copyright 2024 (c) Fraunhofer IWU (Author: Thorben Schnellhardt)
 */

#ifndef SWAP_TEMPLATE_UTILITY_FUNCTION_SWAP_IT_H
#define SWAP_TEMPLATE_UTILITY_FUNCTION_SWAP_IT_H

#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include "config_interpreter.h"

/*
 * Method Arguments:
 * UA_Server *server:               the server instance
 * UA_MethodCallback callback:      callback of for the service method
 * UA_Boolean default_behavior:     boolean that determines wheter a default information
 *                                  model will be instantiated based on the json configuration
 * UA_Boolean *running:             running variable from the server's main function
 * UA_Boolean register_agent:       Boolean that determines wheter the Asset should register itself in a device registry
 * UA_String registry_url:          URL of the Device Regsitry instance the Asset should register itself in.
 *                                  Argument has the form ip:port => 0.0.0.0:4840
 * */

UA_StatusCode UA_server_swap_it(UA_Server *server,
                                UA_ByteString json,
                                UA_MethodCallback callback,
                                UA_Boolean default_behavior,
                                UA_Boolean *running,
                                UA_Boolean register_agent_in_registry,
                                UA_service_server_interpreter *swap_server);

void clear_swap_server(UA_service_server_interpreter *server_info, UA_Boolean unregister, UA_Server *server);

#endif //SWAP_TEMPLATE_UTILITY_FUNCTION_SWAP_IT_H
