#pragma once
#include "filedata.h"

FileData::Node::Node(Node* insertAfter)
{
	prev = insertAfter;
	next = insertAfter->next;
	insertAfter->next = this;
}