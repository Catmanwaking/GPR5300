#pragma once
//Updateable Interface.
//All IUpdateables will be added to the Update queue upon creation.
class IUpdateable
{
public:
	//Executes the Update action of the Object.
	virtual void Update() {};
};