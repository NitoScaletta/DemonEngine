#pragma once
#include <iostream>
#include "core/Layer.h"
#include "core/Events/Events.h"



class Layer
{
public:
	Layer(const char* name = "Layer") : m_Name(name) {}
	~Layer() {}
	virtual void onAttach(){}
	virtual void onDetach(){}
	virtual void onUpdate(float deltatime){}
	virtual void onRender(){}
	virtual void onImGuiRender(){}
	virtual void onEvent(Event& e){}

	const char* GetName() { return m_Name.c_str(); }

protected:
	std::string m_Name;
};