/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(DOM_STORAGE)

#include "JSStorageEvent.h"

#include "JSStorage.h"
#include "KURL.h"
#include "Storage.h"
#include "StorageEvent.h"
#include <runtime/Error.h>
#include <runtime/JSString.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSStorageEvent);

/* Hash table */

static const HashTableValue JSStorageEventTableValues[7] =
{
    { "key", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventKey), (intptr_t)0 },
    { "oldValue", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventOldValue), (intptr_t)0 },
    { "newValue", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventNewValue), (intptr_t)0 },
    { "uri", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventUri), (intptr_t)0 },
    { "storageArea", DontDelete|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventStorageArea), (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsStorageEventConstructor), (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSStorageEventTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 31, JSStorageEventTableValues, 0 };
#else
    { 17, 15, JSStorageEventTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSStorageEventConstructorTableValues[1] =
{
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSStorageEventConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSStorageEventConstructorTableValues, 0 };
#else
    { 1, 0, JSStorageEventConstructorTableValues, 0 };
#endif

class JSStorageEventConstructor : public DOMConstructorObject {
public:
    JSStorageEventConstructor(ExecState* exec, JSDOMGlobalObject* globalObject)
        : DOMConstructorObject(JSStorageEventConstructor::createStructure(globalObject->objectPrototype()), globalObject)
    {
        putDirect(exec->propertyNames().prototype, JSStorageEventPrototype::self(exec, globalObject), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual bool getOwnPropertyDescriptor(ExecState*, const Identifier&, PropertyDescriptor&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, StructureFlags), AnonymousSlotCount); 
    }
    
protected:
    static const unsigned StructureFlags = OverridesGetOwnPropertySlot | ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSStorageEventConstructor::s_info = { "StorageEventConstructor", 0, &JSStorageEventConstructorTable, 0 };

bool JSStorageEventConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSStorageEventConstructor, DOMObject>(exec, &JSStorageEventConstructorTable, this, propertyName, slot);
}

bool JSStorageEventConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSStorageEventConstructor, DOMObject>(exec, &JSStorageEventConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */

static const HashTableValue JSStorageEventPrototypeTableValues[2] =
{
    { "initStorageEvent", DontDelete|Function, (intptr_t)static_cast<NativeFunction>(jsStorageEventPrototypeFunctionInitStorageEvent), (intptr_t)8 },
    { 0, 0, 0, 0 }
};

static JSC_CONST_HASHTABLE HashTable JSStorageEventPrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 0, JSStorageEventPrototypeTableValues, 0 };
#else
    { 2, 1, JSStorageEventPrototypeTableValues, 0 };
#endif

const ClassInfo JSStorageEventPrototype::s_info = { "StorageEventPrototype", 0, &JSStorageEventPrototypeTable, 0 };

JSObject* JSStorageEventPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSStorageEvent>(exec, globalObject);
}

bool JSStorageEventPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSStorageEventPrototypeTable, this, propertyName, slot);
}

bool JSStorageEventPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSStorageEventPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSStorageEvent::s_info = { "StorageEvent", &JSEvent::s_info, &JSStorageEventTable, 0 };

JSStorageEvent::JSStorageEvent(NonNullPassRefPtr<Structure> structure, JSDOMGlobalObject* globalObject, PassRefPtr<StorageEvent> impl)
    : JSEvent(structure, globalObject, impl)
{
}

JSObject* JSStorageEvent::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSStorageEventPrototype(JSStorageEventPrototype::createStructure(JSEventPrototype::self(exec, globalObject)));
}

bool JSStorageEvent::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSStorageEvent, Base>(exec, &JSStorageEventTable, this, propertyName, slot);
}

bool JSStorageEvent::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSStorageEvent, Base>(exec, &JSStorageEventTable, this, propertyName, descriptor);
}

JSValue jsStorageEventKey(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* castedThis = static_cast<JSStorageEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    StorageEvent* imp = static_cast<StorageEvent*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->key());
    return result;
}

JSValue jsStorageEventOldValue(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* castedThis = static_cast<JSStorageEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    StorageEvent* imp = static_cast<StorageEvent*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->oldValue());
    return result;
}

JSValue jsStorageEventNewValue(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* castedThis = static_cast<JSStorageEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    StorageEvent* imp = static_cast<StorageEvent*>(castedThis->impl());
    JSValue result = jsStringOrNull(exec, imp->newValue());
    return result;
}

JSValue jsStorageEventUri(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* castedThis = static_cast<JSStorageEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    StorageEvent* imp = static_cast<StorageEvent*>(castedThis->impl());
    JSValue result = jsString(exec, imp->uri());
    return result;
}

JSValue jsStorageEventStorageArea(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* castedThis = static_cast<JSStorageEvent*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    StorageEvent* imp = static_cast<StorageEvent*>(castedThis->impl());
    JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->storageArea()));
    return result;
}

JSValue jsStorageEventConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSStorageEvent* domObject = static_cast<JSStorageEvent*>(asObject(slotBase));
    return JSStorageEvent::getConstructor(exec, domObject->globalObject());
}
JSValue JSStorageEvent::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSStorageEventConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

JSValue JSC_HOST_CALL jsStorageEventPrototypeFunctionInitStorageEvent(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.inherits(&JSStorageEvent::s_info))
        return throwError(exec, TypeError);
    JSStorageEvent* castedThisObj = static_cast<JSStorageEvent*>(asObject(thisValue));
    StorageEvent* imp = static_cast<StorageEvent*>(castedThisObj->impl());
    const UString& typeArg = args.at(0).toString(exec);
    bool canBubbleArg = args.at(1).toBoolean(exec);
    bool cancelableArg = args.at(2).toBoolean(exec);
    const UString& keyArg = args.at(3).toString(exec);
    const UString& oldValueArg = valueToStringWithNullCheck(exec, args.at(4));
    const UString& newValueArg = valueToStringWithNullCheck(exec, args.at(5));
    const UString& uriArg = args.at(6).toString(exec);
    Storage* storageAreaArg = toStorage(args.at(7));

    imp->initStorageEvent(typeArg, canBubbleArg, cancelableArg, keyArg, oldValueArg, newValueArg, uriArg, storageAreaArg);
    return jsUndefined();
}


}

#endif // ENABLE(DOM_STORAGE)
