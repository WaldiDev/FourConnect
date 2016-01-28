#pragma once
#include "Edge.h"

class Node
{
public:
	Node(int horizont) : m_weight(0), m_horizont(horizont) {}
	~Node();

	void AddEdge(Edge* edge) { m_edges.push_back(edge); }
	std::vector<Edge*> GetEdge() const { return m_edges; }

	void SetWeight(int weight) { m_weight = weight; }
	int GetWeight() const { return m_weight; }

private:
	std::vector<Edge*> m_edges;
	int m_weight;
	int m_horizont;
};

