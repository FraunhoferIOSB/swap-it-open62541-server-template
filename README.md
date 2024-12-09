# SWAP Server Template
The swap server template provides a utility function UA_server_swap_it() which can be used to make any open62541 based OPC UA 
server compatible with the SWAP-IT architecture.

## Requirements
Installed version of the open62541 OPC UA SDK version 1.3.10 (https://github.com/open62541/open62541). Since custom information models
are integrated into the servers, the build flag
    
    -DUA_NAMESPACE_ZERO=FULL -DUA_ENABLE_JSON_ENCODING=ON -DBUILD_SHARED_LIBS=ON

must be set. Depending on the server configuration, th flag

    -DUA_MULTITHREADING

must be set to, e.g.

    -DUA_MULTITHREADING > 200

to enable the server to open the corresponding number of channels

## Installation
    
    /*install dependencies check and open62541)*/
    apt-get -y update
    apt-get -y install git build-essential gcc pkg-config cmake python3 check
    git clone https://github.com/open62541/open62541
    cd open62541
    
    /*switch to open62541 version 1.3.10*/
    git fetch --all --tags
    git checkout tags/v1.3.10 -b v1.3.10-branch

    /* init submodules, build and install open62541*/
    git submodule update --init --recursive
    mkdir build && cd build
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DUA_NAMESPACE_ZERO=FULL -DUA_ENABLE_JSON_ENCODING=ON -DUA_MULTITHREADING=200 ..
    make install

    /*install the server template*/
    git clone https://github.com/FraunhoferIOSB/swap-it-open62541-server-template
    cd swap-it-open62541-server-template    
    mkdir build && cd build
    cmake ..
    make install

## Related Projects
Since the SWAP-IT Regitry Module is part of the SWAP-IT Architecture, its application is linked to other SWAP-IT projects. Here are some other relevant repositories:

- SWAP-IT Demo Scenario: https://github.com/swap-it/demo-scenario
- SWAP-IT Common Information Model: https://github.com/FraunhoferIOSB/swap-it-common-information-model
- SWAP-IT Execution Engine: https://github.com/FraunhoferIOSB/swap-it-execution-engine
- SWAP-IT Registry Module: https://github.com/FraunhoferIOSB/swap-it-registry-module
- PFDL Scheduler: https://github.com/iml130/pfdl
- SWAP-IT Dashboard: https://github.com/iml130/swap-it-dashboard

## Build Documentation
To build the documentation, sphinx and the sphinx rtd themes are required. Both can be installed with:

    pip install sphinx 
    pip install sphinx-rtd-theme

Build the documentation:

    cd swap-it-open62541-server-template
    sphinx-build -M html documentation/source/ documentation/build/