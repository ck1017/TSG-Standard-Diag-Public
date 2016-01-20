/**
* MDMI sample Code for Get/Set/Invoke v1.0
*/

#include "stdafx.h"
#include "MDMI.h"

// How to use MdmiGet to get deviceName (1.3.6.1.2.1.6362.1.1.1)
static void GetValueSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.3.6.1.2.1.6362.1.1.1      Device Name
    MdmiObjectName name = { 0 };
    name.length = 10;
    name.ids = (MdmiTypeUInt32*)malloc(sizeof(MdmiTypeUInt32) * name.length);
    name.ids[0] = 1;
    name.ids[1] = 3;
    name.ids[2] = 6;
    name.ids[3] = 1;
    name.ids[4] = 2;
    name.ids[5] = 1;
    name.ids[6] = 6362;
    name.ids[7] = 1;
    name.ids[8] = 1;
    name.ids[9] = 1;

    MdmiValue value = { 0 };

    result = MdmiGet(session, &name, &value);
    DebugWriteLine("MdmiGet result: %u", result);

    DebugWriteValue(&value);
}

// How to use MdmiSet to set value to some writable object
static void SetValueSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.3.6.1.2.1.6362.1.5.1.1     purpose this object is writable
    MdmiObjectName name = { 0 };
    name.length = 11;
    name.ids = (MdmiTypeUInt32*)malloc(sizeof(MdmiTypeUInt32) * name.length);
    name.ids[0] = 1;
    name.ids[1] = 3;
    name.ids[2] = 6;
    name.ids[3] = 1;
    name.ids[4] = 2;
    name.ids[5] = 1;
    name.ids[6] = 6362;
    name.ids[7] = 1;
    name.ids[8] = 5;
    name.ids[9] = 1;
    name.ids[10] = 1;

    MdmiValue value = { 0 };
    value.length = 2;
    // data should be "SetRequest" SNMP message constructed based on this object structure. Here is just some dummy data.
    value.data = (MdmiTypeUInt8*)malloc(sizeof(MdmiTypeUInt8) * value.length);
    value.data[0] = 0;
    value.data[1] = 10;

    result = MdmiSet(session, &name, &value);
    DebugWriteLine("MdmiSet result: %u", result);
}

// How to use MdmiInvoke to invoke make-a-call action (1.3.6.1.2.1.6362.1.4.1.1)
static void InvokeSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.3.6.1.2.1.6362.1.4.1.1     Make a call
    MdmiObjectName name = { 0 };
    name.length = 11;
    name.ids = (MdmiTypeUInt32*)malloc(sizeof(MdmiTypeUInt32) * name.length);
    name.ids[0] = 1;
    name.ids[1] = 3;
    name.ids[2] = 6;
    name.ids[3] = 1;
    name.ids[4] = 2;
    name.ids[5] = 1;
    name.ids[6] = 6362;
    name.ids[7] = 1;
    name.ids[8] = 4;
    name.ids[9] = 1;
    name.ids[10] = 1;

    MdmiValue value = { 0 };
    value.length = 2;
    // data should be "SetRequest" SNMP message constructed based on 1.3.6.1.2.1.6362.1.4.1.1. Here is just some dummy data.
    value.data = (MdmiTypeUInt8*)malloc(sizeof(MdmiTypeUInt8) * value.length);
    value.data[0] = 0;
    value.data[1] = 10;

    result = MdmiInvoke(session, &name, NULL);
    DebugWriteLine("MdmiInvoke result: %u", result);
}


static void DebugWriteObjectName(const MdmiObjectName* name)
{
    if (NULL == name)
    {
        return;
    }

    for (MdmiTypeUInt32 i = 0; i < name->length; ++i){
        DebugWriteLine("name [%u] %u", i, name->ids[i]);
    }
}

static void DebugWriteValue(const MdmiValue* value)
{
    if (NULL == value)
    {
        return;
    }

    for (MdmiTypeUInt32 i = 0; i < value->length; ++i){
        DebugWriteLine("value [%u] %u", i, value->data[i]);
    }
}


extern void TestMdmiApi()
{
    // Create a MDMI session
    MdmiError result = MDMI_NO_ERROR;
    MdmiSession session = 0;

    result = MdmiCreateSession(NULL, &session);
    DebugWriteLine("MdmiCreateSession result: %u", result);

    if (result != MDMI_NO_ERROR) {
        DebugWriteLine("Failed to initialize MDMI session");
        return;
    }

    // After session created, app can also use Get, Set and Invoke. 
    // For description of those functions, please refer to MDMI spec section 5.1.3, 5.1.4 and 5.1.5.

    GetValueSample(session); // In this sample, it will get deviceName (1.3.6.1.2.1.6362.1.1.1) using MdmiGet(). Please refer to GetValueSample() definition above.
    SetValueSample(session); // In this sample, it will set value using MdmiSet(). Please refer to SetValueSample() definition above.
    InvokeSample(session); // In this sample, it will invoke makeCall (1.3.6.1.2.1.6362.1.5.1.1) using MdmiInvoke().Please refer to InvokeSample() definition above.

    // Close MDMI session
    result = MdmiCloseSession(session);
    DebugWriteLine("MdmiCloseSession result: %u", result);
}


