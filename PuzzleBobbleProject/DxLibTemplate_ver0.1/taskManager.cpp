#include"taskManager.h"



TaskManager::TaskManager()
{
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		pTaskArray[i] = NULL;
	}
	taskNum = 0;
	lastId = TASK_GENERATE_START_ID;
}

TaskManager::~TaskManager()
{
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		Task** ppElem = &pTaskArray[i];
		Task* pTask = *ppElem;
		if (pTask == NULL)
		{
			continue;
		}
		delete pTask;
		*ppElem = NULL;
	}
}

Task* TaskManager::search(int id)
{
	Task* ret = NULL;

	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		Task* pTask = pTaskArray[i];
		if (pTask == NULL)
		{
			continue;
		}
		if (pTaskArray[i]->getTaskId() == id)
		{
			ret = pTask;
			break;
		}
	}
	return ret;
}


bool TaskManager::addObject(Task* _Object)
{
	// すでに配列がいっぱいだったら登録をしない
	if (ALL_OBJECT_MAX <= taskNum)
	{
		return false;
	}

	// 同じIDのタスクが存在しないかチェック

	if (search(_Object->getTaskId()) != NULL)
	{
		return false;
	}

	Task** ppElem = NULL;
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		Task** ppCurElem = &pTaskArray[i];
		if (*ppCurElem == NULL)
		{
			ppElem = ppCurElem;
			break;
		}

	}
	if (ppElem == NULL)
	{
		return false;
	}
	*ppElem = _Object;
	taskNum++;

	return true;


}

void TaskManager::removeObject(Task* _pObject)
{

	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		if (pTaskArray[i] == _pObject)
		{
			delete(pTaskArray[i]);
			pTaskArray[i] = NULL;
			break;
		}

	}
}



void TaskManager::taskUpdateAll()
{
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		// 現在参照している要素のポインタ
		Task** ppElem = &pTaskArray[i];
		// そのポインタに入っているタスクのポインタ
		Task* pTask = *ppElem;
		// NULLだったら
		if (pTask == NULL)
		{
			// これ以上何もせず次の要素に
			continue;
		}

		
		int curState = pTask->getTaskState();

		// タスクが死亡状態か
		if (curState == Task::INACTIVE)
		{
			// 削除
			delete pTask;
			// NULLを設定
			*ppElem = NULL;
			// タスクの登録数をカウントダウン
			taskNum--;
			// 次の要素へ
			continue;
		}
		if (curState == Task::READY)
		{
			pTask->activate();
		}
		pTask->Update();

	}
}
void TaskManager::taskRenderAll()
{
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		Task* pTask = pTaskArray[i];
		if (pTask == NULL)
		{
			continue;
		}

		int state = pTask->getTaskState();

		if (!(state == Task::ACTIVE))
		{
			continue;
		}
		pTask->Render();
	}

}

//void TaskManager::destroyUpdate()
//{
//	for (int i = 0; i < ALL_OBJECT_MAX; i++)
//	{
//		if (pTaskArray[i] != NULL && pTaskArray[i]->isDead == true)
//		{
//			CollisionManager* pColManager = CollisionManager::getInstance();
//			pColManager->removeObject(pTaskArray[i]->pColTask);
//			pColManager->removeInfoFromCol(pTaskArray[i]->pColTask);
//
//			delete(pTaskArray[i]);
//			pTaskArray[i] = NULL;
//		}
//	}
//}

void TaskManager::destroyAll()
{
	for (int i = 0; i < ALL_OBJECT_MAX; i++)
	{
		if (pTaskArray[i] != NULL)
		{
			delete(pTaskArray[i]);
			pTaskArray[i] = NULL;
		}
	}

}

int TaskManager::generateId()
{
	return lastId++;
}
