#include "EntityHandler.h"

#include "Entity.h"

EntityHandler::~EntityHandler()
{
	ClearEntities();
}

bool EntityHandler::Update()
{
	UpdateEntityVector();
	for (auto& entity : m_entities)
	{
		if(!entity->Update())
		{
			return false;
		}
	}
	UpdateEntityVector();

	return true;
}

void EntityHandler::Draw(SDL_Renderer* _renderer)
{
	for(auto& entity : m_entities)
	{
		entity->Draw(_renderer);
	}
}

void EntityHandler::UpdateEntityVector()
{
	if(!m_removeEntities.empty())
	{
		for (auto& entity : m_removeEntities)
		{
			const auto index = GetEntityIndex(entity);
			if (index >= 0)
			{
				m_entities.erase(m_entities.begin() + index);
				delete entity;
				entity = nullptr;
			}
		}

		m_removeEntities.clear();
	}
	if(!m_newEntities.empty())
	{
		for (auto& entity : m_newEntities)
		{
			m_entities.push_back(entity);
		}
		
		m_newEntities.clear();
	}
}

void EntityHandler::AddEntity(Entity* _entity)
{
	_entity->SetEntityHandler(this);
	m_newEntities.push_back(_entity);
}

void EntityHandler::RemoveEntity(Entity* _entity)
{
	m_removeEntities.push_back(_entity);
}

void EntityHandler::RemoveEntityAt(const int _index)
{
	auto& entity = m_entities[_index];
	m_removeEntities.push_back(entity);
}

void EntityHandler::ClearEntities()
{
	for(auto& entity : m_entities)
	{
		delete entity;
		entity = nullptr;
	}

	m_entities.clear();
}

int EntityHandler::GetEntityIndex(Entity* _entity)
{
	auto returnIndex = -1;
	for (unsigned i = 0; i < m_entities.size(); i++)
	{
		if (m_entities[i] == _entity)
		{
			returnIndex = i;
		}
	}

	return returnIndex;
}

std::vector<Entity*>& EntityHandler::GetEntities()
{
	return m_entities;
}
