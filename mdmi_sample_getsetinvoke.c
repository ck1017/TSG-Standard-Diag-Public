/**
* MDMI sample Code for Get/Set/Invoke v2.0
*/

#include "stdlib.h"
#include "MDMI.h"

// How to use MdmiGet to get deviceName (1.1.1.1)
static void GetValueSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.3.6.1.2.1.6362.1.1.1      Device Name
    MdmiObjectName name = { 0 };
    name.length = 4;
    MdmiTypeUInt32[] oid = {1, 1, 1, 1};
    name.ids = oid;

    MdmiValue value = { 0 };

    result = MdmiGet(session, &name, &value);
    DebugWriteLine("MdmiGet result: %u", result);

    DebugWriteValue(&value);
    
    free(value);
}

// How to use MdmiSet to set value to some writable object
static void SetValueSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.8.1   This object does not exist in current mib file. Surpose this object is a writable object.
    MdmiObjectName name = { 0 };
    name.length = 3;
    MdmiTypeUInt32[] oid = {1, 8, 1};
    name.ids = oid;

    MdmiValue value = { 0 };
    value.length = 2;
    // data should be "SetRequest" SNMP message constructed based on this object structure.
    // About how to construct "SetRequest" SNMP message, please refer to MDMI implementation guidelines.
    // Since there is no use case of set in current MDMI, below is just some dummy data instead of real one.
    MdmiTypeUInt8[] val = {0x00, 0x10};
    value.data = val;

    result = MdmiSet(session, &name, &value);
    DebugWriteLine("MdmiSet result: %u", result);
}

// How to use MdmiInvoke to invoke make-a-call action (1.7.1)
static void InvokeSample(MdmiSession session)
{
    MdmiError result = MDMI_NO_ERROR;

    // 1.7.1     Make a call
    MdmiObjectName name = { 0 };
    name.length = 3;
    MdmiTypeUInt32[] oid = {1, 7, 1};
    name.ids = oid;

    MdmiValue value = { 0 };
    value.length = 38;
    MdmiTypeUInt8[] val = {0xa2, 0x24, 0x06, 0x02, 0x2f, 0x01, 0x30, 0x1e, 0x02, 0x01, 0x09, 0x02, 0x01, 0x01, 
        0x02, 0x01, 0x02, 0x02, 0x01, 0x06, 0x02, 0x01, 0x07, 0x02, 0x01, 0x05, 0x02, 0x01, 0x07, 0x02, 0x01, 
        0x07, 0x02, 0x01, 0x08, 0x02, 0x01, 0x08};
    // data should be "SetRequest" SNMP message constructed based on 1.7.1.
    // About how to construct "SetRequest" SNMP message, please refer to MDMI implementation guidelines.
    value.data = val;

    result = MdmiInvoke(session, &name, &value);
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

    GetValueSample(session); // In this sample, it will get deviceName (1.1.1.1) using MdmiGet(). Please refer to GetValueSample() definition above.
    SetValueSample(session); // In this sample, it will set value using MdmiSet(). Please refer to SetValueSample() definition above.
    InvokeSample(session); // In this sample, it will invoke makeCall (1.7.1) using MdmiInvoke().Please refer to InvokeSample() definition above.

    // Close MDMI session
    result = MdmiCloseSession(session);
    DebugWriteLine("MdmiCloseSession result: %u", result);
}


