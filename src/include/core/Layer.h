#pragma once
#include <iostream>
#include <vector>
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


class LayerStack
{
public:
	LayerStack() {}
	~LayerStack();

	void PushLayer(Layer* layer);
	void PushTopLayer(Layer* layer);
	void PopLayer(Layer* layer);
	void PopTopLayer(Layer* Layer);
	const std::vector<Layer*>& GetStack() { return m_StackLayer; }
	void PrintLayerStackList();


	
private:
	std::vector<Layer*> m_StackLayer;
	uint32_t BottomLayerIndex = 0;

};