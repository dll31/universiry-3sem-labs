﻿#include "ConnectionMap.h"



void ConnectionMap::addLink(int pipeId, CsConnectionData csData)
{
	links[pipeId] = csData;
}


int ConnectionMap::removeLink(int pipeId)
{
	if (links.count(pipeId))
	{
		links.erase(pipeId);
		return 1;
	}
	return 0;
}


int ConnectionMap::pipeIsAvailable(int pipeId)
{
	if (links.count(pipeId))
		return pipeIsUnavailable;

	return available;
}


int ConnectionMap::csIsAvailable(int csId)
{
	for (auto& i : links)
	{
		if ((i.second.startCS.id == csId) || (i.second.endCS.id == csId))
			return csIsUnavailable;
	}

	return available;
}


int ConnectionMap::getCsBusyWorkshops(int csId)
{
	int busyWorkshops = 0;

	for (auto& i : links)
	{
		if (i.second.endCS.id == csId)
			busyWorkshops++;
		
		if (i.second.startCS.id == csId)
			busyWorkshops++;
	}

	return busyWorkshops;
}


void ConnectionMap::display()
{
	for (auto& i : links)
	{
		std::cout << "\nConnection:\n"
			<< "Pipe id: " << i.first << '\n'
			<< "Start cs id: " << i.second.startCS.id << '\n'
			<< "End cs Id: " << i.second.endCS.id << '\n';
	}
}


std::stack<int> ConnectionMap::topologicalSort()
{
	std::map<int, color> visited;
	std::stack<int> out;

	for (auto& i : links)
	{
		visited.insert({ i.second.startCS.id, color::white });
		visited.insert({ i.second.endCS.id, color::white });
	}
	
	for (auto& i : visited)
	{
		dfs(i.first, visited, out);
	}

	return out;
}


void ConnectionMap::dfs(int v, std::map<int, color>& visited, std::stack<int>& out)
{
	if (visited[v] == black)
		return; //do nothing

	if (visited[v] == gray)
		return; //have cycle
		
	if (visited[v] == white)
	{
		visited[v] = gray;
		for (auto& i : links)
		{
			if (i.second.startCS.id == v)
			{
				dfs(i.second.endCS.id, visited, out);
			}
		}

		visited[v] = black;
		out.push(v);
	}
}


void ConnectionMap::displayTopSortResult(std::stack<int> res)
{
	std::cout << '\n' << "TopSortRes:" << '\n';
	
	int i = 1;
	while (!res.empty())
	{
		std::cout << i << " - " << res.top() << '\n';
		res.pop();
		i++;
	}
}


void ConnectionMap::clear()
{
	links.clear();
}