/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "binding.h"

namespace kroll
{
	StaticBoundObject::~StaticBoundObject()
	{
		std::map<std::string, Value*>::iterator iter = properties.begin();
		while (iter != properties.end())
		{
			KR_DECREF(iter->second);
			iter++;
		}

	}

	Value* StaticBoundObject::Get(const char *name, BoundObject *context)
	{
		std::map<std::string, Value*>::iterator iter;

		iter = properties.find(name);
		if (iter != properties.end()) {
			KR_ADDREF(iter->second);
			return iter->second;
		}

		return Value::Undefined();
	}

	void StaticBoundObject::Set(const char *name, Value* value, BoundObject *context)
	{
		KR_ADDREF(value);

		this->UnSet(name);
		this->properties[name] = value;
	}

	void StaticBoundObject::UnSet(const char *name)
	{
		std::map<std::string, Value*>::iterator iter = this->properties.find(name);
		if (this->properties.end() != iter)
		{
			KR_DECREF(iter->second);
			this->properties.erase(iter);
		}
	}

	std::vector<std::string> StaticBoundObject::GetPropertyNames()
	{
		std::vector<std::string> names;
		std::map<std::string, Value*>::iterator iter = properties.begin();
		while (iter != properties.end())
		{
			names.push_back(iter->first);
			iter++;
		}
		return names;
	}

	Value* StaticBoundObject::Get(const char *name)
	{
		return this->Get(name, NULL);
	}

	void StaticBoundObject::Set(const char *name, Value* value)
	{
		this->Set(name, value, NULL);
	}

	void StaticBoundObject::SetObject(const char *name, BoundObject* object)
	{
		Value* obj_val = new Value(object);
		this->Set(name, obj_val);
		KR_DECREF(obj_val);
	}
}