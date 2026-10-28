#pragma once
#include <string>
#include <vector>
#include "json.h"
#include "geo.h"

struct Stop {
    std::string name;
    geo::Coordinates position;
};
using StopPtr = const Stop*;
using StopMap = std::map<std::string, const Stop*>;

struct Bus {
	Bus(std::string n, std::vector<StopPtr> s, bool r)
		: name(std::move(n)), stops(std::move(s)), is_roundtrip(r) {
	}
	
	std::string name;
	std::vector<StopPtr> stops;
	bool is_roundtrip;
};

using BusPtr = const Bus*;

struct BusStat {
	size_t total_stops = 0;
	size_t unique_stops = 0;
	int route_length = 0;
	double geo_length = 0.;
	double curvature = 0.;
};

struct Route {
    size_t stops;
    size_t unique_stops;
    int real_length;
    double geo_length;
};