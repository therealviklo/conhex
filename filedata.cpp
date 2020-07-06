#pragma once
#include "filedata.h"

FileData::Node::Node(Node** startNode)
{
	prev = nullptr;
	next = *startNode;
	if (*startNode) (*startNode)->prev = this;
	*startNode = this;
}

FileData::Node::Node(Node* insertAfter)
{
	prev = insertAfter;
	next = insertAfter->next;
	if (insertAfter->next) insertAfter->next->prev = this;
	insertAfter->next = this;
}

FileData::Reference::Reference(const Reference& o)
{
	node = o.node;
}

FileData::Reference& FileData::Reference::operator=(const Reference& o)
{
	if (this != &o)
	{
		node = o.node;
	}
	return *this;
}

void FileData::Reference::next()
{
	if (node) node = node->next;
}

void FileData::Reference::prev()
{
	if (node) node = node->prev;
}

FileData::Reference FileData::Reference::peekNext()
{
	if (node) return node->next;
	return nullptr;
}

FileData::Reference FileData::Reference::peekPrev()
{
	if (node) return node->prev;
	return nullptr;
}

bool FileData::Reference::tryMove(int steps)
{
	Reference r = *this;
	int absSteps = abs(steps);
	bool stepsNegative = steps < 0;
	for (int i = 0; i < absSteps; i++)
	{
		stepsNegative ? r.prev() : r.next();
		if (!r) return false;
	}
	node = r.node;
	return true;
}

uint8_t& FileData::Reference::operator*()
{
	return node->byte;
}

bool FileData::Reference::operator==(const Reference& o)
{
	return node == o.node;
}

bool FileData::Reference::operator!=(const Reference& o)
{
	return node != o.node;
}

FileData::FileData()
{
	startNode = nullptr;
}

FileData::~FileData()
{
	clear();
}

void FileData::clear()
{
	Node* nodeToDelete = (Node*)startNode; // Vscode tror att det här inte går men om jag konverterar till Node* så klagar Vscode inte.
	while (nodeToDelete)
	{
		Node* currNode = nodeToDelete;
		nodeToDelete = nodeToDelete->next;
		delete currNode;
	}
	startNode = nullptr;
}

FileData::Reference FileData::insertAfter(FileData::Reference r)
{
	if (r) return new Node(r.node);
	return new Node(&startNode);
}

void FileData::deleteByte(Reference r)
{
	if (r)
	{
		if (r.node->prev)
		{
			r.node->prev->next = r.node->next;
		}
		else
		{
			startNode = r.node->next;
		}
		if (r.node->next)
		{
			r.node->next->prev = r.node->prev;
		}
		delete r.node;
	}
}