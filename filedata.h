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

		Node(Node** startNode);
		Node(Node* insertAfter);
	public:
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		uint8_t byte;

		friend FileData;
	};
public:
	class Reference
	{
	private:
		FileData::Node* node;
	public:
		Reference(FileData::Node* node) : node(node) {}

		Reference(const Reference& o);
		Reference& operator=(const Reference& o);

		void next();
		void prev();

		/*
		 * Om steps är negativ går den bakåt. Om det inte går att flytta händer inget.
		 * Returnvärdet är om den lyckades flytta på sig eller inte.
		*/
		bool tryMove(int steps);

		// Varning: Om iteratorn inte pekar till en Node (innehåller en nullpekare) så försöker denna funktion avreferera en nullpekare.
		uint8_t& operator*();

		bool isNull() {return node = nullptr;}
		// Returnerar true om iteratorn inte innehåller en nullpekare.
		operator bool() {return node != nullptr;}

		bool operator==(const Reference& o);
		bool operator!=(const Reference& o);

		friend FileData;
	};
private:
	Node* startNode;
public:
	FileData();
	~FileData();

	FileData(const FileData&) = delete;
	FileData& operator=(const FileData&) = delete;
	
	void clear();

	// Returnerar en referens till den nya noden. Om r är null läggs den nya noden i början.
	Reference insertAfter(Reference r);

	Reference start() {return startNode;}
};