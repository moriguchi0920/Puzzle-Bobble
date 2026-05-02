#pragma once
#include"task.h"
#include"collisionManager.h"
// タスクの配列を保持し、全てのオブジェクトの更新、描画、破壊を行うクラス

class TaskManager
{
private :
	// 生成される初回のID(固定のタスクIDを加味して32に設定)
	static const int TASK_GENERATE_START_ID = 32;

public:
	static inline TaskManager* getInstance() {
		static TaskManager instance;
		return &instance;
	}
private :
	Task* pTaskArray[ALL_OBJECT_MAX];
	int taskNum;
	int lastId;

private :
	TaskManager();

	TaskManager& operator = (const TaskManager& other){}

	TaskManager(const TaskManager& other) {}

public:
	virtual ~TaskManager();

	Task* search(int id);
	bool addObject(Task* _Object);
	void removeObject(Task* _pObject);
	void taskUpdateAll();
	void taskRenderAll();
	//void destroyUpdate();
	void destroyAll();

	int generateId();

};


