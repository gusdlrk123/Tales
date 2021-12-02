#pragma once

#include "GameEntity.h"

class Image;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT	 pos;
	RECT		 shape;
	float		 moveSpeed;
	int			 bodySize;
	Image*		 img;

public:
	void Move();

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	GameObject();
	~GameObject();
};

