#pragma once

#include "SDL.h"

class WorldObject
{
protected:
	int m_tileWidth = 0;
	int m_tileHeight = 0;
	
	float m_X = 0;
	float m_Y = 0;

	float m_width = 0;
	float m_height = 0;

	int m_layer = 0;
public:
	explicit WorldObject(float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	virtual ~WorldObject() = default;
	
	virtual bool Update() = 0;
	virtual void Draw(SDL_Renderer* _renderer) const = 0;

	/// <summary>
	/// Get the Object's X position in pixels. This can include subpixel coordinates.
	/// </summary>
	/// <returns>The Object's X position.</returns>
	[[nodiscard]] float GetX() const;

	/// <summary>
	/// Get the Object's Y position in pixels. This can include subpixel coordinates.
	/// </summary>
	/// <returns>The Object's Y position.</returns>
	[[nodiscard]] float GetY() const;

	/// <summary>
	/// Get the width value the Object is using as a reference when converting its tile position into pixels.
	/// </summary>
	/// <returns>The width of tiles in the current map.</returns>
	[[nodiscard]] int GetTileWidth() const;

	/// <summary>
	/// Get the height value the Object is using as a reference when converting its tile position into pixels.
	/// </summary>
	/// <returns>The height of tiles in the current map.</returns>
	[[nodiscard]] int GetTileHeight() const;

	/// <summary>
	/// Get the Object's width in tiles (1 tile = tileWidth pixels)
	/// </summary>
	/// <returns>The width of the Object, in tiles.</returns>
	[[nodiscard]] float GetWidth() const;

	/// <summary>
	/// Get the Object's height in tiles (1 tile = tileHeight pixels)
	/// </summary>
	/// <returns>The height of the Object, in tiles.</returns>
	[[nodiscard]] float GetHeight() const;

	/// <summary>
	/// Get the current collision layer of the Object. Objects on different layers cannot collide.
	/// </summary>
	/// <returns>The collision layer of the Object.</returns>
	[[nodiscard]] int GetLayer() const;

	void SetX(float _x);
	void SetY(float _y);
	void SetPosition(float _x, float _y);
	void SetTile(int _x, int _y);

	void MoveX(float _amount);
	void MoveY(float _amount);
	void Move(float _xAmount, float _yAmount);

	void SetTileWidth(int _width);
	void SetTileHeight(int _height);
	void SetTileSize(int _width, int _height);

	void SetWidth(float _width);
	void SetHeight(float _height);
	void SetSize(float _width, float _height);

	void SetRect(float _x, float _y, float _width, float _height);
	
	void SetLayer(int _layer);
};

