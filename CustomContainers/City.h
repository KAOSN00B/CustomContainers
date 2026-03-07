#pragma once

#include "Vector.h"
#include "MSTGraph.h"
#include "MSTGraphK.h"
#include "House.h"

class City
{
public:
	Vector<House> mHouses;

	MSTGraph<House, float> mHousesGraph;
	MSTGraphK<float> mHouseEdgesGraph;

	void AddHouse(const std::string& name, const Vector2& pos)
	{
		for (size_t i = 0; i < mHouses.Size(); ++i)
		{
			if (mHouses[i].mName == name)
			{
				return;
			}
		}

		House house;
		house.mName = name;
		house.mPosition = pos;

		mHouses.PushBack({ name, pos });
		mHousesGraph.AddItem(&mHouses[mHouses.Size() - 1]);

	}

	void ConnectAllHouses()
	{
		//e.Void ConnectAllHouses()
		//i.Goes through all the houses and adds links to mHousesGraph
		//ii.Goes through all the edges and populates mHouseEdgeGraph
		//iii.Use the distance between to be the weight

		for (size_t i = 0; i < mHouses.Size(); i++)
		{
			for (size_t j = i + 1; j < mHouses.Size(); ++j)
			{
				float distance = mHouses[i].mPosition.Distance(mHouses[j].mPosition);
				mHousesGraph.AddEdge(i, j, distance);
				mHouseEdgesGraph.AddEdge(i, j, distance);
			}
		}
	}

	float GetTotalRoadDistancePrim()
	{
		float totalDistance = 0.0f;

		mHousesGraph.GenerateMST(0);

		const Vector<MSTGraph<House, float>::Edge>& mst = mHousesGraph.GetMST();

		for (std::size_t i = 0; i < mst.Size(); ++i)
		{
			totalDistance += mst[i].weight;
		}

		return totalDistance;
	}

	float GetTotalRoadDistanceKruskal()
	{
		mHouseEdgesGraph.GenerateMST();
		const Vector<MSTGraphK<float>::Edge>& mst = mHouseEdgesGraph.GetMST();
		float totalDistance = 0.0f;
		for (std::size_t i = 0; i < mst.Size(); ++i)
		{
			totalDistance += mst[i].weight;
		}
		return totalDistance;
	}

};