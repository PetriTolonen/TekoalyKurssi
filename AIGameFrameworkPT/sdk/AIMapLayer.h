// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// War Game for GameAIGameFramework.
//
// Copyright (c) 2016 Mikko Romppainen. All Rights reserved.
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifndef AI_MAP_LAYER_H_
#define AI_MAP_LAYER_H_

#include <Texture.h>
#include <stdint.h>
#include <yam2d_dll_api.h>
#include <Layer.h>
#include <GameObject.h>

class YAM2D_API AIMapLayer
{
private:
	yam2d::Layer* m_layer;
protected:
	YAM2D_API AIMapLayer(yam2d::Layer* layer)
		: m_layer(layer)
	{
	}

	YAM2D_API virtual ~AIMapLayer()
	{
	}



public:
	YAM2D_API virtual void setPixel(int px, int py, float value) = 0;
	YAM2D_API virtual void setPixel(int px, int py, uint8_t* pixelValues) = 0;
	YAM2D_API virtual uint8_t* getPixel(int px, int py) = 0;
	YAM2D_API virtual const uint8_t* getPixel(int px, int py) const = 0;
	YAM2D_API virtual int getWidth() const = 0;
	YAM2D_API virtual int getHeight() const = 0;

	YAM2D_API yam2d::Layer* getLayer() const
	{
		return m_layer;
	}

	YAM2D_API const uint8_t* getPixelFromPos(const slm::vec2& pos) const
	{
		return getPixel((int)(pos.x + 0.5f), (int)(pos.y + 0.5f));
	}
};



#endif

