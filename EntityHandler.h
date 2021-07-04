#pragma once

#include <vector>

#include <SDL.h>

class Entity;

class EntityHandler
{
private:
	std::vector<Entity*> m_entities;
	std::vector<Entity*> m_newEntities;
	std::vector<Entity*> m_removeEntities;

	void UpdateEntityVector();
public:
	~EntityHandler();
	
	bool Update();
	void Draw(SDL_Renderer* _renderer);
	
	void AddEntity(Entity* _entity);
	void RemoveEntity(Entity* _entity);
	void RemoveEntityAt(int _index);

	void ClearEntities();

	int GetEntityIndex(Entity* _entity);

	std::vector<Entity*>& GetEntities();
};

