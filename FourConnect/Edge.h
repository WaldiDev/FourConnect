#pragma once
#include "Node.h"

class Edge
{
public:
	Edge() : m_startNode(nullptr), m_targetNode(nullptr) {}
	~Edge();

	void SetStartNode(Node* note) { m_startNode = note; }
	Node* GetStartNode() const { return m_startNode; }

	void SetTargetNode(Node* note) { m_targetNode = note; }
	Node* GetTargetNode() const { return m_targetNode; }

private:
	Node* m_startNode;
	Node* m_targetNode;
};

