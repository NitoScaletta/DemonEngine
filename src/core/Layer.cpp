#include "core/Layer.h"



void LayerStack::PushLayer(Layer* layer)
{
	m_StackLayer.emplace(m_StackLayer.begin() + BottomLayerIndex, layer);
	layer->onAttach();
}


void LayerStack::PushTopLayer(Layer* layer)
{
	m_StackLayer.push_back(layer);
	layer->onAttach();
}
