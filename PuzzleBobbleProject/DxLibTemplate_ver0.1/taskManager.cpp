#include"taskManager.h"


// コンストラクタの初期化リストでタスクのvectorの要素数を指定
TaskManager::TaskManager() : pTaskArray(ALL_OBJECT_MAX)
{

	// 現在のIDを初期化
	lastId = TASK_GENERATE_START_ID;
}

TaskManager::~TaskManager()
{
	pTaskArray.clear();
}

Task* TaskManager::search(int id)
{
	// とりあえずnullptrでTask*変数を定義
	Task* ret = nullptr;

	// 範囲forでpTaskArrayを見て回る
	for (std::unique_ptr<Task>& upTask : pTaskArray)
	{
		// 中身がnullptr(つまりポインタが入っていない)なら
		if (!upTask)
		{
			// 戻る
			continue;
		}
		// IDが一致するTaskが見つかったら
		if (upTask->getTaskId() == id)
		{
			// retに生ポインタをget()を通して入れる
			ret = upTask.get();
			break;
		}
	}
	// 結果をreturn 
	return ret;
}


bool TaskManager::addObject(std::unique_ptr<Task> _Object)
{


	// 同じIDのタスクが存在しないかチェック

	if (search(_Object->getTaskId()))
	{
		return false;
	}

	// vectorへの追加(unique_ptrの所有権の移譲でもあるのでmove()を使う)
	pTaskArray.push_back(std::move(_Object));


	return true;


}

void TaskManager::removeObject(Task* _pObject)
{

	// for文で走査(vectorの.size()はintでは不適なためsize_t)
	for (size_t i = 0; i < pTaskArray.size(); i++)
	{
		// vector要素の参照を取る
		std::unique_ptr<Task>& upTask = pTaskArray[i];

		// .get()で出した生ポインタと引数が一致したら
		if (upTask.get() == _pObject)
		{
			// vectorの.erase()で初期インデックス(.begin())にi(現在見ているインデックス)を足したインデックスの要素を削除
			pTaskArray.erase(pTaskArray.begin() + i);
			
			break;
		}

	}
}



void TaskManager::taskUpdateAll()
{
	for (std::unique_ptr<Task>& upTask : pTaskArray)
	{


		// NULLだったら
		if (!upTask)
		{
			// これ以上何もせず次の要素に
			continue;
		}

		
		int curState = upTask->getTaskState();

		// タスクが死亡状態か
		if (curState == Task::INACTIVE)
		{
			// 削除
			upTask.reset(nullptr);

			// 次の要素へ
			continue;
		}
		if (curState == Task::READY)
		{
			upTask->activate();
		}
		upTask->Update();

	}
}
//void TaskManager::taskRenderAll()
//{
//	for (int i = 0; i < ALL_OBJECT_MAX; i++)
//	{
//		Task* pTask = pTaskArray[i];
//		if (pTask == NULL)
//		{
//			continue;
//		}
//
//		int state = pTask->getTaskState();
//
//		if (!(state == Task::ACTIVE))
//		{
//			continue;
//		}
//		pTask->Render();
//	}
//
//}

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
	pTaskArray.clear();

}

int TaskManager::generateId()
{
	return lastId++;
}
