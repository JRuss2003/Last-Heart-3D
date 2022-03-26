#include "ChunkManager.h"
#include "GameEngine.h"

void ChunkManager::ProcessUnloadQue()
{
	if (unloadQue.size() < 1)
		return;
	unloadQue[0]->Unload();
	for (int i = 0; i < renderVector.size(); i++) {
		if (unloadQue[0] == renderVector[i])
			renderVector.erase(renderVector.begin() + i);
	}
	renderVector.shrink_to_fit();
	unloadQue.erase(unloadQue.begin() + 0);
	unloadQue.shrink_to_fit();
}

void ChunkManager::ProcessLoadQue()
{

	/*
	for (int i = 0; i < loadQue.size(); i++) {
		loadQue[i]->Load();
		this->renderVector.push_back(loadQue[i]);
	}
	*/
	if (loadQue.size() < 1)
		return;

	loadQue[0]->Load();
	this->renderVector.push_back(loadQue[0]);
	
	
	loadQue[0]->inLoadQue = false;
	loadQue.erase(loadQue.begin() +  0);
	loadQue.shrink_to_fit();

}

void ChunkManager::AddToUnloadQue(Chunk* targetChunk)
{
	unloadQue.push_back(targetChunk);
}

void ChunkManager::AddToLoadQue(Chunk* targetChunk)
{
	loadQue.push_back(targetChunk);
}
