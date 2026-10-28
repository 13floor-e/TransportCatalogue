#pragma once
#include "map_renderer.h"
#include "request_handler.h"
#include "transport_router.h"
#include "transport_catalogue.h"
#include "json.h"


class MapRenderer;

class JsonReader {
public:
	json::Node ReadStatRequests(const json::Document& doc, TransportRouter& tr, const TransportCatalogue& catalogue, MapRenderer& map_);
	void ReadBaseRequests(const json::Document& doc, TransportCatalogue& catalogue);
	void BuildMapRequest(const TransportCatalogue& cat, MapRenderer& map_, const int id, json::Array& responses);
	void BuildRouteSettings(SpeedAndTimeSettings& set);
	SpeedAndTimeSettings AddBusRouteStatsInRoute(const json::Document& doc, SpeedAndTimeSettings& set);
	friend MapRenderer;
};


