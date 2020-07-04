#pragma once
#include <cstdint>
#include "filehandler.h"

class FileData
{
private:
	class Node
	{
	private:
		Node* prev;
		Node* next;

		Node(Node* insertAfter);
	public:
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		uint8_t byte;
	};
public:
};